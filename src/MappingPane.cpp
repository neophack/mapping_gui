//
// Created by linsin on 20/03/2020.
//

#include "MainWindow.h"
#include "MappingPane.h"

void panorama::MappingPane::BashLaunchGps() {
  if(!launch_gps_flag) {
    launch_gps_flag = true;
    std::string cmd = header + launch_gps;
    std::string okk = "";
    int si = old_bag_path.size();
    for(int i = 1 ; i < si ; ++i) okk += old_bag_path.at(i);
    if(based_on_old) {
      cmd += " old_map:=" + okk + " __name:=gps_node" + tail_no_exit;
      std::cout << cmd << std::endl;
    } else {
      cmd += "__name:=gps_node" + tail_no_exit;
    }
    std::string res = BashExec(cmd.c_str());
  }
}

void panorama::MappingPane::BashLegoBag() {
  if(!bag_play_lego_bag_flag) {
    bag_play_lego_bag_flag = true;
    std::string cmd = header + bag_play_lego + tail_no_exit;
    std::string res = BashExec(cmd.c_str());
  }
}

void panorama::MappingPane::BashBagPlayOrigin() {
  if(!bag_play_origin_flag) {
    bag_play_origin_flag = true;
    BashExec(bag_play_origin.c_str());
  }
}

void panorama::MappingPane::BashLaunchLego() {
  if(!launch_lego_flag)  {
    launch_lego_flag = true;
    std::string ret = BashExec("gnome-terminal -t \"Launch LEGO\" -x bash -c \"roslaunch lego_loam run.launch;exec bash; \" ");
  }
}

void panorama::MappingPane::BashRecordBag() {
  if(!record_bag_flag) {
    record_bag_flag = true;
    record_bag = header + record_bag + tail_no_exit;
    std::string ret = BashExec(record_bag.c_str());
  }

}

void panorama::MappingPane::BashRoscore() {
  roscore_flag = true;
  std::string sql = "gnome-terminal -t \"Roscore\" -x bash -c \"roscore;exec bash; \" ";
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
  std::string sql ="gnome-terminal -t \"Sim Time\" -x bash -c \"rosparam set /use_sim_time true;exec bash; \" ";
  BashExec(sql.c_str());
}
panorama::MappingPane::MappingPane()
    :
      m_fItemSpacing{ImGui::GetStyle().ItemSpacing.y},
      m_eBuildType{BuildType::GRAPH_NEW_MAP} {
  // For a single CPU we show the combined graph
  BashClock();
  if (based_on_old)
    m_eBuildType = BuildType::GRAPH_OLD_MAP;
  find_package_front_end = BashExec("gnome-terminal -e rospack find lego_loam");
  if(find_package_front_end.find("ERROR") != std::string::npos) front_end_exist = true;
  find_package_gps = BashExec("gnome-terminal -e rospack find gps_based_mapping");
  if(find_package_gps.find("ERROR") != std::string::npos) gps_based_exist = true;
  find_package_point = BashExec("gnome-terminal -e rospack find point_localization");
  if(find_package_point.find("ERROR") != std::string::npos) point_based_exist = true;
}

panorama::MappingPane::~MappingPane() {
  killAllNode();
  killRoscore();
}
void panorama::MappingPane::ClearNode() {
  if(!started_lego && !clear_before_lego) {
    killAllNode();
    killRoscore();
    clear_before_lego = true;
  }
}
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
  ImGui::InputText("GPS Param1", gps_param1, 8, ImGuiInputTextFlags_CharsNoBlank);
  ImGui::InputText("GPS Param2", gps_param2, 8, ImGuiInputTextFlags_CharsNoBlank);
  ImGui::InputText("GPS Param3", gps_param3, 8, ImGuiInputTextFlags_CharsNoBlank);
  ImGui::PopItemWidth();

  ImGui::Separator();
  ImGui::Text("Based on old map: "); ImGui::SameLine();
  ImGui::Checkbox(" ", &based_on_old);
  if(based_on_old) {
    if(old_bag_path == " ") {
      ImGui::Text("Please choose old map.pcd: "); ImGui::SameLine();
      open_pcd.DrawFileBrowser(old_map_path, "Open Old Map", ".pcd\0.bag\0\0", "oldmap");
    }
    int si = old_map_path.size();
    old_bag_path = " ";
    for(int i = 0 ; i < si - 8 ; ++i) {
      old_bag_path += old_map_path.at(i);
    }
    if(old_bag_path != " ") {
      ImGui::Text("Old Map Path is  %s", old_bag_path.c_str());
    }
  } else if(!based_on_old){
    old_bag_path = " ";
  }

  ImGui::Separator();
  ImGui::Text("Please choose bag: "); ImGui::SameLine();
  open_bag.DrawFileBrowser(origin_bag_path, "Open Bag", ".bag\0.pcd \0\0", "openbag");
  if(origin_bag_path != " ") {
    ImGui::Text("Bag path is %s", origin_bag_path.c_str());
  }


  static std::thread clock_thread(&panorama::MappingPane::BashClock, this);
  if(clock_thread.joinable() && !clock_flag) clock_thread.join();

  ImGui::Separator();
  bag_play_origin = header + " rosbag play " + origin_bag_path + " --clock __name:=origin_play_node" + tail_no_exit;
  if(origin_bag_path != " " && ((based_on_old && old_bag_path != " ") || (!based_on_old)) && ImGui::Button("Start Mapping")) {
    static std::thread lego_thread(&panorama::MappingPane::BashLaunchLego, this);
    static std::thread record_bag_thread(&panorama::MappingPane::BashRecordBag, this);
    static std::thread play_origin_bag_thread(&panorama::MappingPane::BashBagPlayOrigin, this);
    if(record_bag_thread.joinable() && !record_bag_flag) record_bag_thread.join();
    if(lego_thread.joinable() && !launch_lego_flag) lego_thread.join();
    if(play_origin_bag_thread.joinable() && !bag_play_origin_flag) play_origin_bag_thread.join();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    started_lego = true;
  }
  ImGui::PushFont(panorama::getFont(PANORAMA_FONT_TITLE));
  ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1), "%s", "Mapping Status...");
  ImGui::PopFont();

//  if(bag_play_origin_flag ) {
//    ImGui::Text("STOP");
//    ros::V_string v_nodes;
//    ros::master::getNodes(v_nodes);
//    std::string node_name = std::string("/origin_play_node");
//    auto it = std::find(v_nodes.begin(), v_nodes.end(), node_name.c_str());
//    if (it != v_nodes.end()){
//      std::string lego_node_name = std::string("/lego_record_node");
//      auto it_lego = std::find(v_nodes.begin(), v_nodes.end(), lego_node_name.c_str());
//      if(it_lego != v_nodes.end()) {
//        std::string cmd_str = "rosnode kill " + lego_node_name;
//        BashExec(cmd_str.c_str());
//        record_bag_flag = true;
//        finished_lego = true;
//        std::cout << "## stop rosbag record cmd: " << cmd_str << std::endl;
//      }
//
//    }
//  }
  std::string node, node_uri;
  node = "/origin_play_node";
  if(!finished_lego) {
    look_node = lookupNode(node, node_uri);
  }
  if((!finished_lego) && started_lego && (!look_node)) {
    if(!clear_lego_node) {
      node = "/lego_node";
      killNode(node);
      node = "/lego_record_node";
      killNode(node);
      killAllNode();
      finished_lego = true;
      clear_lego_node = true;
    }
  }

  if(started_lego && (!finished_lego)) {
    ImGui::Text("Recording LEGO...Please wait...");
  } else if(finished_lego){
    ImGui::TextColored(ImVec4(0, 1, 0, 1), "Recorded LEGO...Trying to next step..." );
  }

  /**********************LEGO finished************************/
  /**********************GPS Started************************/
  if(finished_lego && (!started_gps)) {
    static std::thread bag_play_lego_thread(&panorama::MappingPane::BashLegoBag, this);
    static std::thread gps_thread(&panorama::MappingPane::BashLaunchGps, this);
    if(!launch_gps_flag && gps_thread.joinable()) gps_thread.join();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if(!bag_play_lego_bag_flag && bag_play_lego_thread.joinable()) bag_play_lego_thread.join();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    started_gps = true;
  }

  node = "/play_lego_bag";
  if(finished_lego && (!finished_gps) && started_gps && (!lookupNode(node, node_uri))) {
    if(!clear_gps_node) {
      node = "/gps_node";
      killNode(node);
      killAllNode();
      finished_gps = true;
      clear_gps_node = true;
    }
  }

  if(finished_lego && started_gps && (!finished_gps)) {
    ImGui::Text("Running GPS Based Mapping...Please wait...");
  } else if(finished_lego && finished_gps){
    ImGui::TextColored(ImVec4(0, 1, 0, 1), "GPS Mapping Finished...Map saved in ~/.ros/Map..." );
  }



  ImGui::EndChild();
}

