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

#include <health_metric_collector/metric_manager.h>

namespace ros_monitoring_msgs {
namespace msg {

/**
 * @brief Interface for a metrics collector.
 */
class MetricCollectorInterface
{
public:
  /**
   * @brief Constructor.
   */
  MetricCollectorInterface(
    std::shared_ptr<ros_monitoring_msgs::msg::MetricManagerInterface> mgr
    ) : mgr_(mgr) {}

  /**
   * @brief callback for collecting metrics.
   */
  virtual void Collect() = 0;

protected:
  /**
   * @brief creates metric entries and publishes them.
   */
  std::shared_ptr<ros_monitoring_msgs::msg::MetricManagerInterface> mgr_;
};

}}  // namespace ros_monitoring_msgs::msg
