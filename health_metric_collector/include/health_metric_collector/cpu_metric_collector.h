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

#pragma once

#include <health_metric_collector/cpu_data.h>
#include <health_metric_collector/cpu_stats.h>
#include <health_metric_collector/metric_collector.h>
#include <health_metric_collector/metric_manager.h>


namespace ros_monitoring_msgs {
namespace msg {
/**
 * collects cpu usage metric.
 */
class CPUMetricCollector : public MetricCollectorInterface
{
public:
  /**
   * @brief Constructor.
   *
   * @param m metric manager which creates and aggregates metrics.
   */
  CPUMetricCollector(std::shared_ptr<ros_monitoring_msgs::msg::MetricManagerInterface> m)
    : MetricCollectorInterface(m) {}

  /**
   * @brief activates metrics collection.
   */
  void Collect() override final;

private:
  void CollectCpuUsage(const std::vector<CPUData> & entries1,
                       const std::vector<CPUData> & entries2);

  std::shared_ptr<CPUStats> old_;
  std::shared_ptr<CPUStats> new_;
};

}}  // namespace ros_monitoring_msgs::msg
