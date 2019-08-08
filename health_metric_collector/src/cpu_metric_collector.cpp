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

#include <health_metric_collector/cpu_metric_collector.h>
#include <health_metric_collector/cpu_stats.h>
#include <ros_monitoring_msgs/msg/metric_data.hpp>

#include <chrono>
#include <thread>

using namespace ros_monitoring_msgs::msg;


#define BASE_METRIC_NAME "cpu_usage_"


void CPUMetricCollector::Collect()
{
  // new snapshot
  new_ = std::make_shared<CPUStats>();
  new_->ReadStatsCPU();

  if (old_) {
    CollectCpuUsage(old_->GetEntries(), new_->GetEntries());
  }

  old_ = new_;
  new_.reset();
}

void CPUMetricCollector::CollectCpuUsage(const std::vector<CPUData> & entries1,
                                         const std::vector<CPUData> & entries2)
{
  const size_t num_of_entries = std::min(entries1.size(), entries2.size());

  for (size_t i = 0; i < num_of_entries; ++i) {
    const CPUData & e1 = entries1[i];
    const CPUData & e2 = entries2[i];

    const auto active_time = static_cast<float>(e2.GetActiveTime() - e1.GetActiveTime());
    const auto idle_time = static_cast<float>(e2.GetIdleTime() - e1.GetIdleTime());
    const float total_time = active_time + idle_time;
    const float usage = 100.f * active_time / total_time;

    MetricData md = mgr_->CreateMetric();
    md.metric_name = BASE_METRIC_NAME + entries1[i].cpu;
    md.unit = MetricData::UNIT_PERCENTAGE;
    md.value = usage;
    mgr_->AddMetric(md);
  }
}
