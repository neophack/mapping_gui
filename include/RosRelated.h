//
// Created by linsin on 21/03/2020.
//

#ifndef PANORAMA_INCLUDE_ROSRELATED_H_
#define PANORAMA_INCLUDE_ROSRELATED_H_

#include <ros/ros.h>
#include <ros/master.h>
#include "Utils.h"
#include "Bash.h"

namespace panorama {
bool lookupNode(const std::string& node, std::string&uri) ;
bool killRoscore();
bool killAllNode();
bool killNode(const std::string& node);
}

#endif //PANORAMA_INCLUDE_ROSRELATED_H_
