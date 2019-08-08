/*
 * Copyright 2018 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <rclcpp/rclcpp.hpp>

#include <aws/core/utils/logging/LogMacros.h>
#include <aws_ros2_common/sdk_utils/ros2_node_parameter_reader.h>
#include <health_metric_collector/collect_and_publish.h>
#include <health_metric_collector/cpu_metric_collector.h>
#include <health_metric_collector/metric_collector.h>
#include <health_metric_collector/metric_manager.h>
#include <health_metric_collector/sys_info_collector.h>
#include <ros_monitoring_msgs/msg/metric_list.hpp>

#include <chrono>
#include <vector>


using namespace Aws::Client;
using namespace ros_monitoring_msgs::msg;
using namespace std::chrono_literals;


#define DEFAULT_INTERVAL_SEC 5
#define TOPIC_BUFFER_SIZE 1000
#define INTERVAL_PARAM_NAME "interval"
#define ROBOT_ID_DIMENSION "robot_id"
#define CATEGORY_DIMENSION "category"
#define HEALTH_CATEGORY "RobotHealth"
#define DEFAULT_ROBOT_ID "Default_Robot"
#define DEFAULT_NODE_NAME "health_metric_collector"
#define METRICS_TOPIC_NAME "metrics"


int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared(DEFAULT_NODE_NAME);

  auto param_reader = std::make_shared<Ros2NodeParameterReader>(node);

  // get interval param
  double interval = DEFAULT_INTERVAL_SEC;
  param_reader->ReadParam(ParameterPath(INTERVAL_PARAM_NAME), interval);

  // get robot id
  std::string robot_id = DEFAULT_ROBOT_ID;
  param_reader->ReadParam(ParameterPath(ROBOT_ID_DIMENSION), robot_id);

  // advertise
  AWS_LOG_INFO(__func__, "Starting Health Metric Collector Node...");
  auto mg = std::make_shared<MetricManager>(node, METRICS_TOPIC_NAME, TOPIC_BUFFER_SIZE);
  mg->AddDimension(ROBOT_ID_DIMENSION, robot_id);
  mg->AddDimension(CATEGORY_DIMENSION, HEALTH_CATEGORY);

  std::vector<std::shared_ptr<MetricCollectorInterface>> collectors;
  auto cpu_collector = std::make_shared<CPUMetricCollector>(mg);
  collectors.push_back(cpu_collector);

  auto sys_collector = std::make_shared<SysInfoCollector>(mg);
  collectors.push_back(sys_collector);

  // start metrics collection
  CollectAndPublish f(mg, collectors);
  auto timer = node->create_wall_timer(1s, [&f]{f.Publish();});

  rclcpp::spin(node);

  AWS_LOG_INFO(__func__, "Shutting down Health Metric Collector Node...");
  return 0;
}
