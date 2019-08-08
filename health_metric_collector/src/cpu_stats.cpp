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

#include <health_metric_collector/cpu_stats.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void CPUStats::ReadStatsCPU()
{
  std::ifstream file_stat("/proc/stat");

  std::string line;

  const std::string str_tot("tot");
  const std::string str_cpu("cpu");
  const std::size_t len_str_cpu = str_cpu.size();

  while (std::getline(file_stat, line)) {
    // cpu stats line found
    if (!line.compare(0, len_str_cpu, str_cpu)) {
      std::istringstream ss(line);

      // store entry
      entries_.emplace_back(CPUData());
      CPUData & entry = entries_.back();

      // read cpu label
      ss >> entry.cpu;

      // remove "cpu" from the label when it's a processor number
      if (entry.cpu.size() > len_str_cpu) {
        entry.cpu.erase(0, len_str_cpu);
        entry.cpu = "core_" + entry.cpu;
      }
      // replace "cpu" with "tot" when it's total values
      else {
        entry.cpu = str_tot;
      }
      // read times
      for (int i = 0; i < CPUData::kNumCpuStates; ++i) {
        ss >> entry.times[i];
      }
    }
  }
}
