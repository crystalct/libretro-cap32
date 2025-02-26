/****************************************************************************
 *  Caprice32 libretro port
 *
 *  Copyright not6 - r-type (2015-2018)
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


#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "retro_utils.h"
#ifdef VITA
   #include "file/file_path.h"
#endif

// Verify file extension
bool file_check_extension(const char *filename, const size_t filename_size, const char *ext, const size_t ext_size)
{
#ifndef __PS3__
   size_t file_len = strnlen(filename, filename_size);
   size_t ext_len = strnlen(ext, ext_size);
#else
   size_t file_len = strlen(filename) > filename_size ? filename_size : strlen(filename);
   size_t ext_len = strlen(ext) > ext_size ? ext_size : strlen(ext);
#endif

   if( ext_len > file_len || file_len >= filename_size - 1)
      return false;

   const char * file_ext = &filename[file_len - ext_len];

   return (strncasecmp(file_ext, ext, filename_size) == 0);
}

// Verify if file exists
bool file_exists(const char *filename)
{
#ifdef VITA
   if (path_is_valid(filename) && !path_is_directory(filename))
#else
   struct stat buf;
   if (stat(filename, &buf) == 0 &&
      (buf.st_mode & (S_IRUSR|S_IWUSR)) && !(buf.st_mode & S_IFDIR))
#endif
   {
      /* file points to user readable regular file */
      return true;
   }
   return false;
}

void path_join(char* out, const char* basedir, const char* filename)
{
   snprintf(out, RETRO_PATH_MAX, "%s%s%s", basedir, RETRO_PATH_SEPARATOR, filename);
}

char* path_join_dup(const char* basedir, const char* filename)
{
   size_t dirlen = strlen(basedir);
   size_t seplen = strlen(RETRO_PATH_SEPARATOR);
   size_t filelen = strlen(filename);
   char* result = (char*)malloc(dirlen + seplen + filelen + 1);
   strcpy(result, basedir);
   strcpy(result + dirlen, RETRO_PATH_SEPARATOR);
   strcpy(result + dirlen + seplen, filename);
   return result;
}

/**
 * D_Skywalk: Imported from my 3DS pituka implementation
 *            http://david.dantoine.org/proyecto/26/
 */

#ifdef _3DS
void* linearMemAlign(size_t size, size_t alignment);
void linearFree(void* mem);
#endif

void *retro_malloc(size_t size) {
   #ifdef _3DS
   return linearMemAlign(size, 0x80);
   #else
   return malloc(size);
   #endif
}

void retro_free(void * mem) {
   #ifdef _3DS
   linearFree(mem);
   #else
   free(mem);
   #endif
}
