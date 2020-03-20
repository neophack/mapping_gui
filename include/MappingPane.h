//
// Created by linsin on 19/03/2020.
//

#ifndef PANORAMA_INCLUDE_MAPPINGPANE_H_
#define PANORAMA_INCLUDE_MAPPINGPANE_H_

#include <vector>
#include <string>
#include <future>
#include <chrono>
#include <cstdlib>

#include "imgui.h"
#include "imgui_internal.h"
#include "Bash.h"
#include "Utils.h"

namespace panorama {
// Enums
enum BuildType : int {
  GRAPH_NEW_MAP = 0,
  GRAPH_OLD_MAP
};

class MappingPane {
 public:
  // Cnstr.
  MappingPane();

  // Dstr.
  ~MappingPane();

  // Renderer
  void renderUI();

  // Getter for the information and the usage

 private:
  // Information getters
  const float m_fItemSpacing;
  BuildType m_eBuildType;
  bool based_on_old = false;
  bool front_end_exist = false;
  bool gps_based_exist = false;
  bool point_based_exist = false;


  std::string find_package_front_end;
  std::string find_package_gps;
  std::string find_package_point;
  std::string old_bag_path = "";



};
}


#endif //PANORAMA_INCLUDE_MAPPINGPANE_H_
