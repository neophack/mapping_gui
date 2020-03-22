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
  ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1), "%s", "Coming Soon");
  ImGui::PopFont();

  ImGui::EndChild();
}

