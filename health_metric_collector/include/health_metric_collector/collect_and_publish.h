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

#include <health_metric_collector/metric_collector.h>
#include <health_metric_collector/metric_manager.h>

#include <vector>

/**
 * @brief activates collectors and then publishes metrics.
 */
class CollectAndPublish
{
public:
  /**
   * @brief Constructor
   *
   * @param mg the metric manager that publishes collected metrics.
   * @param c a list of metrics collectors.
   */
  CollectAndPublish(
    std::shared_ptr<ros_monitoring_msgs::msg::MetricManagerInterface> mg,
    std::vector<std::shared_ptr<ros_monitoring_msgs::msg::MetricCollectorInterface>> & c
    ) : mg_(mg), collectors_(c) {}

  /**
   * @brief activates all collectors and then publishes the metrics.
   *
   * @param event time event in which this run occurs.
   */
  void Publish()
  {
    for (auto c : collectors_) {
      c->Collect();
    }
    mg_->Publish();
  }

private:
  std::shared_ptr<ros_monitoring_msgs::msg::MetricManagerInterface> mg_;
  const std::vector<std::shared_ptr<ros_monitoring_msgs::msg::MetricCollectorInterface>> &
    collectors_;
};
