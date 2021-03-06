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
  void  BashRecordBag();
  void  BashLaunchLego();
  void BashLaunchGps();
  void BashLegoBag();
  void  BashBagPlayOrigin();
  void  BashRoscore();
  void  BashCheckBagPlayEnd();
  void  BashClock();
  void ClearNode();

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
  std::string old_bag_path = " ";
  std::string origin_bag_path = " ";
  std::string record_bag = "rosbag record -O ~/lego.bag /top/rslidar_points /novatel718d/pos /aft_mapped_to_init  __name:=lego_record_node";
  std::string launch_lego = "roslaunch lego_loam run.launch __name:=lego_node";
  std::string bag_play_origin = " ";
  std::string bag_play_lego = " rosbag play ~/lego.bag --clock __name:=play_lego_bag" ;
  std::string launch_gps = "roslaunch gps_based_mapping run.launch ";
  std::string launch_point = "roslaunch point_localization localization.launch";

  std::atomic_bool record_bag_flag{false};
  std::atomic_bool launch_lego_flag{false};
  std::atomic_bool bag_play_origin_flag{false};
  std::atomic_bool clock_flag{false};
  std::atomic_bool roscore_flag{false};
  std::atomic_bool launch_gps_flag{false};
  std::atomic_bool bag_play_lego_bag_flag{false};


  bool started_lego = false;
  bool started_gps = false;
  bool finished_lego = false;
  bool finished_gps = false;

  bool clear_before_lego = false;
  bool clear_lego_node = false;
  bool clear_gps_node = false;
  bool selected_old_path = false;

  bool look_node = true;

  FileRelated open_bag;
  FileRelated open_pcd;


  std::string old_map_path = " ";


};
}


#endif //PANORAMA_INCLUDE_MAPPINGPANE_H_
