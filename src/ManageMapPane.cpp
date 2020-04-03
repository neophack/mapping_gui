//
// Created by linsin on 03/04/2020.
//
#include "ManageMapPane.h"
#include "MainWindow.h"

panorama::ManageMapPane::ManageMapPane()
    :
    m_fItemSpacing{ImGui::GetStyle().ItemSpacing.y}{}

panorama::ManageMapPane::~ManageMapPane() {
}

void panorama::ManageMapPane::renderUI() {
  ImGui::BeginChild("##manageMapPane");

  ImGui::PushFont(panorama::getFont(PANORAMA_FONT_TITLE));
  ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1), "%s", "Maybe Coming soon");
  ImGui::PopFont();

  ImGui::EndChild();
}