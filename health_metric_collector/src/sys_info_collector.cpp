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

#include <health_metric_collector/sys_info_collector.h>
#include <ros_monitoring_msgs/msg/metric_data.hpp>
#include <sys/sysinfo.h>

#include <fstream>
#include <iostream>

using namespace ros_monitoring_msgs::msg;


#define MEGA (1000000)


void SysInfoCollector::Collect()
{
  // Obtain system statistics
  struct sysinfo si
  {
  };
  sysinfo(&si);

  AddMetric("system_uptime", si.uptime, MetricData::UNIT_SEC);
  AddMetric("free_ram", si.freeram / MEGA, MetricData::UNIT_MEGABYTES);
  AddMetric("total_ram", si.totalram / MEGA, MetricData::UNIT_MEGABYTES);
  AddMetric("process_count", si.procs, MetricData::UNIT_NONE);
}

void SysInfoCollector::AddMetric(const std::string & name, const double value,
                                 const std::string & unit)
{
  MetricData md = mgr_->CreateMetric();
  md.metric_name = name;
  md.unit = unit;
  md.value = value;
  mgr_->AddMetric(md);
}
