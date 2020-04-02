//
// Created by linsin on 20/03/2020.
//

#include "MainWindow.h"
#include "LoopClosurePane.h"
panorama::LoopClosurePane::LoopClosurePane()
    :
    m_fItemSpacing{ImGui::GetStyle().ItemSpacing.y}{}

panorama::LoopClosurePane::~LoopClosurePane() {
}

void panorama::LoopClosurePane::renderUI() {
  ImGui::BeginChild("##loopclosurePane");

  ImGui::PushFont(panorama::getFont(PANORAMA_FONT_TITLE));
  ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1), "%s", "Loop closure");
  ImGui::PopFont();

  ImGui::PushItemWidth(60);

  static char current_frame[8] = "12";
  static char past_frame[8] = "24";
  static char number_of_frame[8] = "10";
  static char max_distance[8] = "5";
  ImGui::InputText("current frame", current_frame, 8, ImGuiInputTextFlags_CharsNoBlank);
  ImGui::InputText("past frame", past_frame, 8, ImGuiInputTextFlags_CharsNoBlank);
  ImGui::InputText("number of frames nearby", number_of_frame, 8, ImGuiInputTextFlags_CharsNoBlank);
  ImGui::InputText("max correspondence distance", max_distance, 8, ImGuiInputTextFlags_CharsNoBlank);
  ImGui::PopItemWidth();


  if (ImGui::Button("Loop these frames..")) {
    ImGui::OpenPopup("Accept?");
  }
  bool opt_click_accept = false;
  if (ImGui::BeginPopupModal("Accept?", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
    ImGui::Text("Checkout the point cloud window.\nDo u want to accept this loop closure!\n\n");
    ImGui::Separator();

    if (ImGui::Button("Sure!", ImVec2(120, 0))) {accept_loop = true;opt_click_accept = true; ImGui::CloseCurrentPopup(); }
    ImGui::SetItemDefaultFocus();
    ImGui::SameLine();
    if (ImGui::Button("Hell u r", ImVec2(120, 0))) {accept_loop = false; opt_click_accept = true; ImGui::CloseCurrentPopup(); }
    ImGui::EndPopup();
  }
  if(opt_click_accept ) {
    if( accept_loop) {
      std::cout << "sure\n";
      std::cout << current_frame << std::endl;
    } else{
      std::cout << "hell u r\n";
    }
  }

  ImGui::Separator();
  ImGui::PushFont(panorama::getFont(PANORAMA_FONT_TITLE));
  ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1), "%s", "Rebuild");
  ImGui::PopFont();

  if(ImGui::Button("Rebuild the map")) {
    std::cout << "Rebuild the map\n";
  }

  ImGui::Separator();
  ImGui::PushFont(panorama::getFont(PANORAMA_FONT_TITLE));
  ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1), "%s", "Delete frames");
  ImGui::PopFont();

  ImGui::PushItemWidth(60);
  static char start_frame[8] = "2";
  static char end_frame[8] = "8";

  ImGui::InputText("start frame", start_frame, 8, ImGuiInputTextFlags_CharsNoBlank);
  ImGui::InputText("end frame", end_frame, 8, ImGuiInputTextFlags_CharsNoBlank);
  ImGui::PopItemWidth();

  if(ImGui::Button("delete..")) {
    std::cout << "delete\n";
  }



  ImGui::EndChild();
}

