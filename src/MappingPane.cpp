//
// Created by linsin on 20/03/2020.
//

#include "MainWindow.h"
#include "MappingPane.h"

panorama::MappingPane::MappingPane()
    :
      m_fItemSpacing{ImGui::GetStyle().ItemSpacing.y},
      m_eBuildType{BuildType::GRAPH_NEW_MAP} {
  // For a single CPU we show the combined graph.
  if (based_on_old)
    m_eBuildType = BuildType::GRAPH_OLD_MAP;
  find_package_front_end = BashExec("rospack find lego_loam");
  if(find_package_front_end.find("ERROR") != std::string::npos) front_end_exist = true;
  find_package_gps = BashExec("rospack find gps_based_mapping");
  if(find_package_gps.find("ERROR") != std::string::npos) gps_based_exist = true;
  find_package_point = BashExec("rospack find point_localization");
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

    ImGui::Text("%s", old_bag_path.c_str());
  }


  ImGui::EndChild();
}