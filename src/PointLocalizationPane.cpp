//
// Created by linsin on 03/04/2020.
//
#include "PointLocalizationPane.h"
#include "MainWindow.h"

panorama::PointLocalizationPane::PointLocalizationPane()
    :
    m_fItemSpacing{ImGui::GetStyle().ItemSpacing.y}{
}

panorama::PointLocalizationPane::~PointLocalizationPane() {
}
void panorama::PointLocalizationPane::BashCurb() {
  if(!g2o_saver_run_flag)  {
    g2o_saver_run_flag = true;
    std::string ret = BashExec("gnome-terminal -t \"Cloud Compare\" -x bash -c \"cloudcompare.CloudCompare;exec bash; \" ");
  }
}
void panorama::PointLocalizationPane::BashG2o() {
  if(!curb_app)  {
    curb_app = true;
    std::string ret = BashExec("gnome-terminal -t \"G2O saver \" -x bash -c \"rosrun point_localization g2o_saver.py;exec bash; \" ");
  }
}
void panorama::PointLocalizationPane::BashRoscore() {
  std::string sql = "gnome-terminal -t \"Roscore\" -x bash -c \"roscore;exec bash; \" ";
  BashExec(sql.c_str());
}
void panorama::PointLocalizationPane::BashLocalization() {
  if(!localization_launch_flag)  {
    localization_launch_flag = true;
    std::string ret = BashExec("gnome-terminal -t \"Launch G2O\" -x bash -c \"roslaunch point_localization localization.launch;exec bash; \" ");
  }
}
void panorama::PointLocalizationPane::clearAllNode() {
  killAllNode();
  killRoscore();
}
void panorama::PointLocalizationPane::BashBagPlayOrigin() {
  if(!bag_play_origin_flag) {
    bag_play_origin_flag = true;
    BashExec(bag_play_origin.c_str());
  }
}
void panorama::PointLocalizationPane::renderUI() {
  ImGui::BeginChild("##PointLocalizationMapPane");

  ImGui::PushFont(panorama::getFont(PANORAMA_FONT_TITLE));
  ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1), "%s", "Point Localization");
  ImGui::PopFont();

  ImGui::Separator();
  ImGui::Text("Please choose the origin bag: "); ImGui::SameLine();

  open_bag.DrawFileBrowser(origin_bag_path, "Open Origin Bag", ".bag \0\0", "openOriginbag");
  if(origin_bag_path != " ") {
    ImGui::Text("Bag path is %s", origin_bag_path.c_str());
    origin_bag_path_flag = true;
    bag_play_origin = header + " rosbag play " + origin_bag_path + " __name:=origin_bag_node" + tail_no_exit;
  }
  if(ImGui::Button("Start Point Localization")) {
    if((!finish_build) && origin_bag_path_flag) {
      BashRoscore();
      static std::thread play_origin_bag_thread(&panorama::PointLocalizationPane::BashBagPlayOrigin, this);
      static std::thread localization_launch_thread(&panorama::PointLocalizationPane::BashLocalization, this);
      static std::thread g20_run_thread(&panorama::PointLocalizationPane::BashG2o, this);
      if(play_origin_bag_thread.joinable() && !bag_play_origin_flag) play_origin_bag_thread.join();
      if(localization_launch_thread.joinable() && !localization_launch_flag) localization_launch_thread.join();
      std::this_thread::sleep_for(std::chrono::seconds(1));
      if(g20_run_thread.joinable() && !g2o_saver_run_flag) g20_run_thread.join();
      record_point = true;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }

  std::string node, node_uri;
  node = "/origin_bag_node";
  if(!finish_build && record_point) {
    look_node = lookupNode(node, node_uri);
  } if((!finish_build) && record_point && (!look_node)) {
    if(!clear_node) {
      std::cout << "finished ufck \n";
      clear_node = true;
      killAllNode();
      finish_build = true;
    }
  } if(finish_build) {
    ImGui::Separator();
    ImGui::Text("Finished Point Localization");
    static std::thread g20_run_thread(&panorama::PointLocalizationPane::BashCurb, this);
    if(!curb_app && g20_run_thread.joinable()) g20_run_thread.join();
  }

  ImGui::EndChild();
}