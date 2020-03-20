//
// Created by linsin on 20/03/2020.
//

#ifndef PANORAMA_INCLUDE_BASH_H_
#define PANORAMA_INCLUDE_BASH_H_

#include <cstdlib>
#include <memory>
#include <stdexcept>

namespace panorama {
#define    COLOR_NONE                    "\033[0m"
#define     FONT_COLOR_RED             "\033[1;31m"
#define    FONT_COLOR_BLUE            "\033[1;34m"
#define    FONT_COLOR_GREEN            "\033[1;32m"

std::string BashExec(const char* cmd);
}
#endif //PANORAMA_INCLUDE_BASH_H_
