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

#include <health_metric_collector/cpu_data.h>

size_t CPUData::GetActiveTime() const
{
  return times[kUser] + times[kNice] + times[kSystem] + times[kIrq] + times[kSoftIrq] +
         times[kSteal] + times[kGuest] + times[kGuestNice];
}

size_t CPUData::GetIdleTime() const { return times[kIdle] + times[kIOWait]; }
