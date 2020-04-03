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

  void InitMemory();
  void NewManual();
  void PoseView();

  const float m_fItemSpacing;
  bool accept_loop = false;
  bool init_memory = false;

  int flag_address = 0;
  int opt_address = 0;
  int start_address = 0;
  int end_address = 0;
  int near_address = 0;
  int max_address = 0;
  int accept_address = 0;

  char *flag_text = nullptr;
  char *opt_text = nullptr;
  char *start_text = nullptr;
  char *end_text = nullptr;
  char *near_text = nullptr;
  char *max_text = nullptr;
  char *accept_text = nullptr;

};
}


#endif //PANORAMA_INCLUDE_LOOPCLOSUREPANE_H_
