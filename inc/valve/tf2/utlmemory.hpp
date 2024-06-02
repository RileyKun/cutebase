//
// Created by Riley on 4/28/2024.
//

#pragma once

#include <cassert>

namespace why
{
void* gameAlloc( size_t size );
void* gameRealloc( void* mem, size_t size );
void gameFree( void* mem );
}

//-----------------------------------------------------------------------------
// The CUtlMemory class:
// A growable memory class which doubles in size by default.
//-----------------------------------------------------------------------------
template <class T> class CUtlMemory {
public:
  // constructor, destructor
  CUtlMemory(int nGrowSize = 0, int nInitSize = 0);
  CUtlMemory(T* pMemory, int numElements);
  ~CUtlMemory();

  // element access
  T&       operator[](int i);
  T const& operator[](int i) const;
  T&       Element(int i);
  T const& Element(int i) const;

  // Can we use this index?
  bool     IsIdxValid(int i) const;

  // Gets the base address (can change when adding elements!)
  T*       Base();
  T const* Base() const;

  // Attaches the buffer to external memory....
  void     SetExternalBuffer(T* pMemory, int numElements);

  // Size
  int      NumAllocated() const;
  int      Count() const;

  // Grows the memory, so that at least allocated + num elements are allocated
  void     Grow(int num = 1);

  // Memory deallocation
  void     Purge();

  // is the memory externally allocated?
  bool     IsExternallyAllocated() const;

  // Set the size by which the memory grows
  void     SetGrowSize(int size);

  enum {
    EXTERNAL_BUFFER_MARKER = -1,
  };

  T*  m_pMemory;
  int m_nAllocationCount;
  int m_nGrowSize;
};

//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------
template< class T >
CUtlMemory<T>::CUtlMemory( int nGrowSize, int nInitAllocationCount ) : m_pMemory( 0 ),
      m_nAllocationCount( nInitAllocationCount ), m_nGrowSize( nGrowSize )
{
  //Assert((nGrowSize >= 0) && (nGrowSize != EXTERNAL_BUFFER_MARKER));
  if ( m_nAllocationCount )
  {
    m_pMemory = ( T* )why::gameAlloc( m_nAllocationCount * sizeof( T ) );
  }
}

template< class T >
CUtlMemory<T>::CUtlMemory( T* pMemory, int numElements ) : m_pMemory( pMemory ),
      m_nAllocationCount( numElements )
{
  // Special marker indicating externally supplied memory
  m_nGrowSize = EXTERNAL_BUFFER_MARKER;
}

template< class T >
CUtlMemory<T>::~CUtlMemory( )
{
  Purge( );
}


//-----------------------------------------------------------------------------
// Attaches the buffer to external memory....
//-----------------------------------------------------------------------------
template< class T >
void CUtlMemory<T>::SetExternalBuffer( T* pMemory, int numElements )
{
  // Blow away any existing allocated memory
  Purge( );

  m_pMemory = pMemory;
  m_nAllocationCount = numElements;

  // Indicate that we don't own the memory
  m_nGrowSize = EXTERNAL_BUFFER_MARKER;
}


//-----------------------------------------------------------------------------
// element access
//-----------------------------------------------------------------------------
template< class T >
inline T& CUtlMemory<T>::operator[]( int i )
{
  //Assert(IsIdxValid(i));
  return m_pMemory[ i ];
}

template< class T >
inline T const& CUtlMemory<T>::operator[]( int i ) const
{
  //Assert(IsIdxValid(i));
  return m_pMemory[ i ];
}

template< class T >
inline T& CUtlMemory<T>::Element( int i )
{
  //Assert(IsIdxValid(i));
  return m_pMemory[ i ];
}

template< class T >
inline T const& CUtlMemory<T>::Element( int i ) const
{
  //Assert(IsIdxValid(i));
  return m_pMemory[ i ];
}


//-----------------------------------------------------------------------------
// is the memory externally allocated?
//-----------------------------------------------------------------------------
template< class T >
bool CUtlMemory<T>::IsExternallyAllocated( ) const
{
  return m_nGrowSize == EXTERNAL_BUFFER_MARKER;
}


template< class T >
void CUtlMemory<T>::SetGrowSize( int nSize )
{
  //Assert((nSize >= 0) && (nSize != EXTERNAL_BUFFER_MARKER));
  m_nGrowSize = nSize;
}


//-----------------------------------------------------------------------------
// Gets the base address (can change when adding elements!)
//-----------------------------------------------------------------------------
template< class T >
inline T* CUtlMemory<T>::Base( )
{
  return m_pMemory;
}

template< class T >
inline T const* CUtlMemory<T>::Base( ) const
{
  return m_pMemory;
}


//-----------------------------------------------------------------------------
// Size
//-----------------------------------------------------------------------------
template< class T >
inline int CUtlMemory<T>::NumAllocated( ) const
{
  return m_nAllocationCount;
}

template< class T >
inline int CUtlMemory<T>::Count( ) const
{
  return m_nAllocationCount;
}


//-----------------------------------------------------------------------------
// Is element index valid?
//-----------------------------------------------------------------------------
template< class T >
inline bool CUtlMemory<T>::IsIdxValid( int i ) const
{
  return ( i >= 0 ) && ( i < m_nAllocationCount );
}

#pragma warning (push)
#pragma warning (disable : 6308)

//-----------------------------------------------------------------------------
// Grows the memory
//-----------------------------------------------------------------------------
template< class T >
void CUtlMemory<T>::Grow( int num )
{
  assert( num > 0 );

  if ( IsExternallyAllocated( ) )
  {
    // Can't grow a buffer whose memory was externally allocated
    assert( 0 );
    return;
  }

  // Make sure we have at least nuwhy::gameAllocated + num allocations.
  // Use the grow rules specified for this memory (in m_nGrowSize)
  int nAllocationRequested = m_nAllocationCount + num;
  while ( m_nAllocationCount < nAllocationRequested )
  {
    if ( m_nAllocationCount != 0 )
    {
      if ( m_nGrowSize )
      {
        m_nAllocationCount += m_nGrowSize;
      }
      else
      {
        m_nAllocationCount += m_nAllocationCount;
      }
    }
    else
    {
      // Compute an allocation which is at least as big as a cache line...
      m_nAllocationCount = ( 31 + sizeof( T ) ) / sizeof( T );
      assert( m_nAllocationCount != 0 );
    }
  }

  if ( m_pMemory )
  {
    m_pMemory = ( T* )why::gameRealloc( m_pMemory, m_nAllocationCount * sizeof( T ) );
  }
  else
  {
    m_pMemory = ( T* )why::gameAlloc( m_nAllocationCount * sizeof( T ) );
  }
}

#pragma warning (pop)

//-----------------------------------------------------------------------------
// Memory deallocation
//-----------------------------------------------------------------------------
template< class T >
void CUtlMemory<T>::Purge( )
{
  if ( !IsExternallyAllocated( ) )
  {
    if ( m_pMemory )
    {
      why::gameFree( ( void* )m_pMemory );
      m_pMemory = 0;
    }
    m_nAllocationCount = 0;
  }
}