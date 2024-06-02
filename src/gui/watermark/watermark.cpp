//
// Created by Riley on 4/25/2024.
//

#include "watermark.hpp"

#include <format>

void c_watermark::draw() {
  g_draw->string(fonts::FONT_SEGOE, 5, ctx->screen_height * 0.08, true, e_text_align::TEXT_LEFT,
                 color(1.f, 1.f, 1.f, 1.f), "cutebase by Pixy - Built: " __DATE__);
}