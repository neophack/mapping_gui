//
// Created by linsin on 03/04/2020.
//

#ifndef PANORAMA_INCLUDE_GL_POINTLOCALIZATION_H
#define PANORAMA_INCLUDE_GL_POINTLOCALIZATION_H


#include "imgui.h"
#include "imgui_internal.h"
#include "Bash.h"
#include "RosRelated.h"
#include "Utils.h"

namespace panorama {
// Enums
class PointLocalizationPane {
 public:
  // Cnstr.
  PointLocalizationPane();

  // Dstr.
  ~PointLocalizationPane();

  // Renderer
  void renderUI();

  // Getter for the information and the usage
 private:
  void clearAllNode();
  void BashRoscore();
  void BashBagPlayOrigin();
  void BashLocalization();
  void BashG2o();
  void BashCurb();
  const float m_fItemSpacing;
  FileRelated open_bag;
  std::string origin_bag_path = " ";
  std::string bag_play_origin = "";
  std::string localization_launch = "";
  std::string g2o_saver_run = "";

  bool origin_bag_path_flag = false;
  bool finish_build = false;
  bool bag_play_origin_flag = false;
  bool record_point = false;
  bool localization_launch_flag = false;
  bool g2o_saver_run_flag = false;
  bool look_node = true;
  bool clear_node = false;
  bool curb_app = false;

};
}
#endif //PANORAMA_INCLUDE_GL_POINTLOCALIZATION_H
