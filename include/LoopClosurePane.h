//
// Created by linsin on 19/03/2020.
//

#ifndef PANORAMA_INCLUDE_LOOPCLOSUREPANE_H_
#define PANORAMA_INCLUDE_LOOPCLOSUREPANE_H_

#include <vector>
#include <string>
#include <future>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <atomic>
#include <ros/ros.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "Bash.h"
#include "RosRelated.h"
#include "Utils.h"

namespace panorama {
// Enums
class LoopClosurePane {
 public:
  // Cnstr.
  LoopClosurePane();

  // Dstr.
  ~LoopClosurePane();

  // Renderer
  void renderUI();

  // Getter for the information and the usage
 private:

  const float m_fItemSpacing;
};
}


#endif //PANORAMA_INCLUDE_LOOPCLOSUREPANE_H_
