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

#include <health_metric_collector/metric_manager.h>
#include <ros_monitoring_msgs/msg/metric_dimension.hpp>

#include <chrono>

using namespace ros_monitoring_msgs::msg;


MetricData MetricManager::CreateMetric() const
{
  MetricData md;
  // FIXME use builtin_interfaces.msg.time and node->now()
  md.header.stamp = node_->now();
  md.time_stamp = md.header.stamp;
  md.dimensions = dimensions_.dimensions;
  return md;
}

void MetricManager::AddDimension(const std::string & name, const std::string & value)
{
  MetricDimension dim;
  dim.name = name;
  dim.value = value;
  dimensions_.dimensions.push_back(dim);
}

void MetricManager::AddMetric(MetricData md) { mlist_.metrics.push_back(md); }

void MetricManager::Publish()
{
  publisher_->publish(mlist_);
  mlist_.metrics.clear();
}
