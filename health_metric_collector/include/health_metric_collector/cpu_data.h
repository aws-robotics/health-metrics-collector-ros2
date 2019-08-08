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

#include <string>

/**
 * struct for holding CPU time in each cpu state.
 */
struct CPUData
{
  enum CPUStates {
    kUser = 0,
    kNice,
    kSystem,
    kIdle,
    kIOWait,
    kIrq,
    kSoftIrq,
    kSteal,
    kGuest,
    kGuestNice,
    kNumCpuStates
  };

  std::string cpu;
  size_t times[kNumCpuStates];

  size_t GetIdleTime() const;
  size_t GetActiveTime() const;
};
