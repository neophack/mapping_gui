//
// Created by linsin on 20/03/2020.
//
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include "MainWindow.h"
#include "LoopClosurePane.h"
panorama::LoopClosurePane::LoopClosurePane()
    :
    m_fItemSpacing{ImGui::GetStyle().ItemSpacing.y}{}

panorama::LoopClosurePane::~LoopClosurePane() {
}

void panorama::LoopClosurePane::NewManual() {
  std::string ret = BashExec("gnome-terminal -t \"Launch LEGO\" -x bash -c \"roslaunch lego_loam run.launch;exec bash; \" ");
}

void panorama::LoopClosurePane::InitMemory() {
  flag_address = shmget(IPC_PRIVATE, 129, IPC_CREAT | 0644);
  opt_address = shmget(IPC_PRIVATE, 129, IPC_CREAT | 0644);
  start_address = shmget(IPC_PRIVATE, 129, IPC_CREAT | 0644);
  end_address = shmget(IPC_PRIVATE, 129, IPC_CREAT | 0644);
  near_address = shmget(IPC_PRIVATE, 129, IPC_CREAT | 0644);
  max_address = shmget(IPC_PRIVATE, 129, IPC_CREAT | 0644);
  accept_address = shmget(IPC_PRIVATE, 129, IPC_CREAT | 0644);
  flag_text = (char*)shmat(flag_address, NULL , 0);
  opt_text = (char*)shmat(opt_address, NULL , 0);
  start_text = (char*)shmat(start_address, NULL , 0);
  end_text = (char*)shmat(end_address, NULL , 0);
  near_text = (char*)shmat(near_address, NULL , 0);
  max_text = (char*)shmat(max_address, NULL , 0);
  accept_text = (char*)shmat(accept_address, NULL , 0);
  strcpy(flag_text, "false");
  strcpy(opt_text, "@opt");
  strcpy(start_text, "@start");
  strcpy(end_text, "@end");
  strcpy(near_text, "@near");
  strcpy(max_text, "@max");
  strcpy(accept_text, "@accept");

  printf("%d %d %d %d %d %d %d\n", flag_address, opt_address, start_address, end_address, near_address, max_address, accept_address);
  init_memory = true;
}

void panorama::LoopClosurePane::renderUI() {
  if(!init_memory) {
    InitMemory();
  }
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
    strcpy(start_text, past_frame);
    strcpy(end_text, current_frame);
    strcpy(near_text, number_of_frame);
    strcpy(max_text, max_distance);
    strcpy(opt_text, "loop");
    strcpy(flag_text, "true");
    ImGui::OpenPopup("Accept?");
  }
  bool opt_click_accept = false;
  if (ImGui::BeginPopupModal("Accept?", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
    ImGui::Text("Checkout the point cloud window.\nDo u want to accept this loop closure!\n\n");
    ImGui::Separator();

    if (ImGui::Button("Sure!", ImVec2(120, 0))) {
      strcpy(accept_text, "Y");
      accept_loop = true;opt_click_accept = true; ImGui::CloseCurrentPopup();
    }
    ImGui::SetItemDefaultFocus();
    ImGui::SameLine();
    if (ImGui::Button("Hell u r", ImVec2(120, 0))) {
      strcpy(accept_text, "N");
      accept_loop = false; opt_click_accept = true; ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }
  if(opt_click_accept ) {
    if( accept_loop) {
      std::cout << "sure\n";
    } else{
      std::cout << "hell u r\n";
    }
  }

  ImGui::Separator();
  ImGui::PushFont(panorama::getFont(PANORAMA_FONT_TITLE));
  ImGui::TextColored(ImVec4(0.5, 0.5, 0.5, 1), "%s", "Rebuild");
  ImGui::PopFont();

  if(ImGui::Button("Rebuild the map")) {
    strcpy(opt_text, "r");
    strcpy(flag_text, "true");
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

  ImGui::Separator();
  if(ImGui::Button("Finished!!!")) {
    strcpy(opt_text, "e");
    strcpy(flag_text, "true");
  }



  ImGui::EndChild();
}

