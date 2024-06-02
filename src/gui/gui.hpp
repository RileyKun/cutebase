//
// Created by Riley on 4/25/2024.
//

#pragma once

#include "watermark/watermark.hpp"
#include "menu/menu.hpp"
#include "debug/debug.hpp"

// links gui classes together
namespace cutegui {
singleton(watermark, c_watermark);
singleton(mainmenu, c_main_menu);
singleton(debug, c_debug);
}