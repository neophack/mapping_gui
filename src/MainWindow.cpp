/*
 *  Panorama -  A simple system monitor for Linux, written using dear ImGui.
 *  Copyright (C) 2018-2019 Ronen Lapushner
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "MainWindow.h"

using std::string;

panorama::MainWindow::MainWindow(SDL_Window *pSdlWindow,
                                const std::string &sTitle, int w, int h) : Window(pSdlWindow, sTitle, w, h),
        m_eMeasurementUnits{MeasurementUnits::MEASUREMENT_UNITS_BINARY},
        m_oSidebar{w * 0.1f} { }

panorama::MainWindow::~MainWindow() { }

void panorama::MainWindow::renderUI() {
    // Static updater tasks
    // TOFIX: This whole block is kindda ugly. Must be some way of unifying and templating this entire thing...

    // Begin rendering the UI
    ImGui::PushFont(panorama::getFont(PANORAMA_FONT_REGULAR));

    // Main column layout
    ImGui::BeginColumns("columns", 2, ImGuiColumnsFlags_NoResize);

    // Render the sidebar
    ImGui::SetColumnWidth(0, m_oSidebar.width());
    m_oSidebar.renderUI();

    ImGui::NextColumn();

    // Here we actually determine what pane we need to render.
    switch (m_oSidebar.currentlyVisiblePane()) {
        case PaneType::PANETYPE_CPU:
            m_oMappingPane.renderUI();
            break;
        case PaneType::PANETYPE_PROCESSES:
            m_oLoopClosurePane.renderUI();
            break;
        case PaneType::PANETYPE_MEMORY:
            m_oManageMapPane.renderUI();
            break;
    }

    ImGui::EndColumns();

    ImGui::PopFont();
}
