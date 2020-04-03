//
// Created by linsin on 03/04/2020.
//

#ifndef PANORAMA_INCLUDE_GL_MANAGEMAP_H_
#define PANORAMA_INCLUDE_GL_MANAGEMAP_H_


#include "imgui.h"
#include "imgui_internal.h"
#include "Bash.h"
#include "RosRelated.h"
#include "Utils.h"

namespace panorama {
// Enums
class ManageMapPane {
 public:
  // Cnstr.
  ManageMapPane();

  // Dstr.
  ~ManageMapPane();

  // Renderer
  void renderUI();

  // Getter for the information and the usage
 private:

  const float m_fItemSpacing;

};
}
#endif //PANORAMA_INCLUDE_GL_MANAGEMAP_H_
