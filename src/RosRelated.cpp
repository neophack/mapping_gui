//
// Created by linsin on 21/03/2020.
//

#include "RosRelated.h"

int fuck_count = 0;
bool panorama::lookupNode(const std::string &node, std::string &uri) {
//  XmlRpc::XmlRpcValue args, result, payload;
//  args[0] = ros::this_node::getName();
//  args[1] = node;
//  if (!ros::master::execute("lookupNode", args, result, payload, false)) {
//    std::cout << "Failed!" << std::endl;
//    return false;
//  }
//  std::cout << "----------LookupedNode----------" << ++fuck_count << std::endl;
//  uri = std::string(payload);
//  std::cout << node << ":" << std::string(payload) << std::endl;
//  return true;


  ros::V_string v_nodes;
  ros::master::getNodes(v_nodes);

  auto it = std::find(v_nodes.begin(), v_nodes.end(), node.c_str());
  if(it == v_nodes.end()) {
    return false;
  } return true;
}

bool panorama::killRoscore() {
  std::string cmd = "gnome-terminal -e killall -9 roscore";
  BashExec(cmd.c_str());
  cmd = "gnome-terminal -e killall -9 rosmaster";
  BashExec(cmd.c_str());
}

bool panorama::killAllNode() {
  std::string cmd = "gnome-terminal -e rosnode kill -a";
  BashExec(cmd.c_str());

}

bool panorama::killNode(const std::string &node) {
  std::string cmd = "gnome-terminal -e rosnode kill " + node ;
  BashExec(cmd.c_str());
}