# Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License").
# You may not use this file except in compliance with the License.
# A copy of the License is located at
#
#  http://aws.amazon.com/apache2.0
#
# or in the "license" file accompanying this file. This file is distributed
# on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
# express or implied. See the License for the specific language governing
# permissions and limitations under the License.

import os

import launch
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    default_config = os.path.join(get_package_share_directory('health_metric_collector'),
                                        'config', 'sample_configuration.yaml')
    parameters = [launch.substitutions.LaunchConfiguration("config_file")]
    return LaunchDescription([
        launch.actions.DeclareLaunchArgument(
            "node_name",
            default_value="health_metric_collector",
        ),
        launch.actions.DeclareLaunchArgument(
            "config_file",
            default_value=default_config
        ),
        Node(
            package='health_metric_collector',
            node_executable='health_metric_collector',
            node_name=launch.substitutions.LaunchConfiguration('node_name'),
            parameters=parameters,
            output='screen'
        ),
    ])
