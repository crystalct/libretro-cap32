/****************************************************************************
 *  Caprice32 libretro port
 *
 *  Copyright David Colmenero - D_Skywalk (2019-2021)
 *  Copyright Daniel De Matteis (2012-2021)
 *
 *  Redistribution and use of this code or any derivative works are permitted
 *  provided that the following conditions are met:
 *
 *   - Redistributions may not be sold, nor may they be used in a commercial
 *     product or activity.
 *
 *   - Redistributions that are modified from the original source must include the
 *     complete source code, including the source code for all components used by a
 *     binary built from the modified sources. However, as a special exception, the
 *     source code distributed need not include anything that is normally distributed
 *     (in either source or binary form) with the major components (compiler, kernel,
 *     and so on) of the operating system on which the executable runs, unless that
 *     component itself accompanies the executable.
 *
 *   - Redistributions must reproduce the above copyright notice, this list of
 *     conditions and the following disclaimer in the documentation and/or other
 *     materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <libretro.h>
#include <libretro-core.h>

#include "gfx/software.h"
#include "retro_render.h"
#include "assets/assets.h"

//unsigned int number = 0;

void render_rect(PIXEL_TYPE * buffer, mu_Rect rect, mu_Color color)
{
   //printf("%u rect: %ix%i %i-%i\n", number, rect.x, rect.y, rect.w, rect.h);
   draw_rect(buffer, rect.x, rect.y, rect.w, rect.h, RGB2COLOR(color.r, color.g, color.b));
}

void render_text(PIXEL_TYPE * buffer, const char *text, mu_Vec2 pos, mu_Color color)
{
   draw_text(buffer, pos.x, pos.y, text, RGB2COLOR(color.r, color.g, color.b));
}

void render_icon(PIXEL_TYPE * buffer, int id, mu_Rect rect, mu_Color color)
{
   char chr = 0;
   int x, y;
   x = rect.x + FNT_CHAR_WIDTH / 4;
   y = rect.y + FNT_CHAR_HEIGHT / 4;

   switch (id)
   {
      case MU_ICON_CLOSE:		chr = 'X'; break;
      case MU_ICON_CHECK:		chr = 'X'; break;
      case MU_ICON_COLLAPSED:	chr = '>'; break;
      case MU_ICON_EXPANDED:	chr = 'v'; break;
      //case MU_ICON_RESIZE:	chr = '+'; break;
  }

  draw_rect(buffer, rect.x, rect.y, rect.w, rect.h, RGB2COLOR(52, 25, 52));
  draw_char(buffer, x, y, chr, RGB2COLOR(color.r, color.g, color.b));
}

// unneed it
void render_clip(PIXEL_TYPE * buffer, mu_Rect rect)
{}

int text_width(mu_Font font, const char *text, int len)
{
  if (len == -1) { len = strlen(text); }
  return len * 8 * EMULATION_SCALE;
}

int text_height(mu_Font font)
{
  return 8 * EMULATION_SCALE;
}
