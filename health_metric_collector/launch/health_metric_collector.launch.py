#<launch>
#    <!-- If a node_name argument is provided by the caller then we will set the node's name to that value -->
#    <arg name="node_name" default="health_metric_collector" />
#    <!-- If a config file argument is provided by the caller then we will load it into the node's namespace -->
#    <arg name="config_file" default="" />
#
#    <node name="$(arg node_name)" pkg="health_metric_collector" type="health_metric_collector" respawn="true">
#        <!-- If the caller specified a config file then load it here. -->
#        <rosparam if="$(eval config_file!='')" command="load" file="$(arg config_file)"/>
#    </node>
#</launch>
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

"""Launch a lifecycle lex node"""

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    # TODO(wjwwood): Use a substitution to find share directory once this is implemented in launch
    parameters_file_path = os.path.join(get_package_share_directory('health_metric_collector_node'),
                                        'config', 'sample_configuration.yaml')
    return LaunchDescription([
        Node(package='health_metric_collector_node',
             node_executable='health_metric_collector_node',
             parameters=[parameters_file_path],
             output='screen'),
    ])
