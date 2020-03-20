//
// Created by linsin on 20/03/2020.
//

#include "MainWindow.h"
#include "MappingPane.h"
void panorama::MappingPane::BashBagPlayOrigin() {
  if(!bag_play_origin_flag) std::string ret = BashExec(bag_play_origin.c_str());
  bag_play_origin = true;
}

void panorama::MappingPane::BashLaunchLego() {
  if(!launch_lego_flag) std::string ret = BashExec("gnome-terminal -t \"Play Origin Bag\" -x bash -c \"roslaunch lego_loam run.launch;exec bash; \" ");
  launch_lego_flag = true;
}

void panorama::MappingPane::BashRecordBag() {
  record_bag = header + record_bag + tail;
  if(!record_bag_flag) std::string ret = BashExec(record_bag.c_str());
  record_bag_flag = true;

}

void panorama::MappingPane::BashRoscore() {
  roscore_flag = true;
  std::string sql = header + " roscore " + tail;
  BashExec(sql.c_str());
}

void panorama::MappingPane::BashCheckBagPlayEnd() {
  while(!record_bag_flag) {
    if(bag_play_origin_flag) record_bag_flag = true;
    std::this_thread::sleep_for(std::chrono::seconds(5));
  }
}

void panorama::MappingPane::BashClock() {
  clock_flag = true;
  std::string sql = header + "rosparam set /use_sim_time true" + tail;
  BashExec(sql.c_str());
}
panorama::MappingPane::MappingPane()
    :
      m_fItemSpacing{ImGui::GetStyle().ItemSpacing.y},
      m_eBuildType{BuildType::GRAPH_NEW_MAP} {
  // For a single CPU we show the combined graph.
  if (based_on_old)
    m_eBuildType = BuildType::GRAPH_OLD_MAP;
  find_package_front_end = BashExec("gnome-terminal -e rospack find lego_loam");
  if(find_package_front_end.find("ERROR") != std::string::npos) front_end_exist = true;
  find_package_gps = BashExec("gnome-terminal -e rospack find gps_based_mapping");
  if(find_package_gps.find("ERROR") != std::string::npos) gps_based_exist = true;
  find_package_point = BashExec("gnome-terminal -e rospack find point_localization");
  if(find_package_point.find("ERROR") != std::string::npos) point_based_exist = true;
}

panorama::MappingPane::~MappingPane() { }

void panorama::MappingPane::renderUI() {
  ImGui::BeginChild("##mappingPane");

  ImGui::PushFont(panorama::getFont(PANORAMA_FONT_TITLE));
  ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1), "%s", "Check Mapping Programme");
  ImGui::PopFont();

  ImGui::Text("LEGO: ");

  ImGui::SameLine();

  ImGui::TextColored(ImVec4(int(front_end_exist),int(!front_end_exist),0,1), "%s", front_end_exist ? "NO THIS NODE" : "Prepared");

  ImGui::Text("GPS Based: ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(int(gps_based_exist),int(!gps_based_exist),0,1), "%s", gps_based_exist ? "NO THIS NODE" : "Prepared");

  ImGui::Text("Point Localization: ");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(int(point_based_exist),int(!point_based_exist),0,1), "%s", point_based_exist ? "NO THIS NODE" : "Prepared");

  ImGui::Separator();

  static char gps_param1[8] = "1e-3";
  static char gps_param2[8] = "1e-3";
  static char gps_param3[8] = "1e-3";


  ImGui::PushFont(panorama::getFont(PANORAMA_FONT_TITLE));
  ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1), "%s", "Set Param");
  ImGui::PopFont();
  ImGui::AlignTextToFramePadding();
  ImGui::PushItemWidth(60);
  ImGui::Text("GPS Param1: "); ImGui::SameLine();
  ImGui::InputText("", gps_param1, 8, ImGuiInputTextFlags_CharsNoBlank);
  ImGui::Text("GPS Param2: "); ImGui::SameLine();
  ImGui::InputText("", gps_param2, 8, ImGuiInputTextFlags_CharsNoBlank);
  ImGui::Text("GPS Param3: "); ImGui::SameLine();
  ImGui::InputText("", gps_param3, 8, ImGuiInputTextFlags_CharsNoBlank);
  ImGui::PopItemWidth();

  ImGui::Separator();
  ImGui::Text("Based on old map: "); ImGui::SameLine();
  ImGui::Checkbox(" ", &based_on_old);
  if(based_on_old) {
    static std::string old_map_path = " ";
    ImGui::Text("Please choose old map.pcd: "); ImGui::SameLine();
    DrawFileBrowser(old_map_path, "Open Old Map", ".pcd\0\0");
    int si = old_map_path.size();
    old_bag_path = " ";
    for(int i = 0 ; i < si - 8 ; ++i) {
      old_bag_path += old_map_path.at(i);
    }
    if(old_bag_path != " ") ImGui::Text("Old Map Path is %s", old_bag_path.c_str());
  } else {
    old_bag_path = " ";
  }

  ImGui::Separator();
  ImGui::Text("Please choose bag: "); ImGui::SameLine();
  DrawFileBrowser(origin_bag_path, "Open Bag", ".bag\0\0");
  if(origin_bag_path != " ") ImGui::Text("Bag path is %s", origin_bag_path.c_str());


  static std::thread clock_thread(&panorama::MappingPane::BashClock, this);
  static std::thread roscore_thread(&panorama::MappingPane::BashRoscore, this);
  if(roscore_thread.joinable() && !roscore_flag) roscore_thread.join();
  if(clock_thread.joinable() && !clock_flag) clock_thread.join();

  ImGui::Separator();
  bag_play_origin = header + " rosbag play " + origin_bag_path + " --clock" + tail;
  if(origin_bag_path != " " && ImGui::Button("Start Mapping")) {
    static std::thread lego_thread(&panorama::MappingPane::BashLaunchLego, this);
    static std::thread record_bag_thread(&panorama::MappingPane::BashRecordBag, this);
    static std::thread play_origin_bag_thread(&panorama::MappingPane::BashBagPlayOrigin, this);
    if(record_bag_thread.joinable() && !record_bag_flag) record_bag_thread.join();
    if(lego_thread.joinable() && !launch_lego_flag) lego_thread.join();
    if(play_origin_bag_thread.joinable() && !bag_play_origin_flag) play_origin_bag_thread.join();
  }
  if(launch_lego_flag) {
    ImGui::Text("click!");
    ImGui::Text("%s", bag_play_origin.c_str());
  }
  ImGui::PushFont(panorama::getFont(PANORAMA_FONT_TITLE));
  ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1), "%s", "Mapping Status...");
  ImGui::PopFont();
  if(!bag_play_origin_flag && origin_bag_path != " ") {
    ImGui::Text("Recording LEGO...Please wait...");
  } else {
    ImGui::Text("Recorded...Trying to next step...");
  }

  ImGui::EndChild();
}

