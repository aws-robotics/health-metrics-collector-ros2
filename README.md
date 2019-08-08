# health_metric_collector

**Note: this repository is under active development. The package provided here is a release candidate; the API may change without notice and no support is provided for it at the moment.**

## Overview
This `health_metric_collector` ROS node collects system metrics and publishes them to `/metrics` topic. The `cloudwatch_metrics_collector` node is subscribed to this topic and will publish the metrics to AWS CloudWatch when it is instantiated.

**Keywords**: ROS, AWS, CloudWatch, Metrics

### License
The source code is released under an [Apache 2.0].

**Author**: AWS RoboMaker<br/>
**Affiliation**: [Amazon Web Services (AWS)]<br/>
**Maintainer**: AWS RoboMaker, ros-contributions@amazon.com

### Supported ROS Distributions
- Dashing

### Build status
* Travis CI:
    * "master" branch [![Build Status](https://travis-ci.org/aws-robotics/health-metrics-collector-ros2.svg?branch=master)](https://travis-ci.org/aws-robotics/health-metrics-collector-ros2/branches)
    * "release-latest" branch [![Build Status](https://travis-ci.org/aws-robotics/health-metrics-collector-ros2.svg?branch=release-latest)](https://travis-ci.org/aws-robotics/health-metrics-collector-ros2/branches)
* ROS build farm:
    * Unreleased

## Installation

### AWS Credentials
You will need to create an AWS Account and configure the credentials to be able to communicate with AWS services. You may find [AWS Configuration and Credential Files] helpful. Specifying AWS [credentials by setting environment variables](https://docs.aws.amazon.com/cli/latest/userguide/cli-environment.html) is not supported. 

This node will require the following AWS account IAM role permissions:
- `cloudwatch:PutMetricData`

### Binaries
On Ubuntu you can install the latest version of this package using the following command

        sudo apt-get update
        sudo apt-get install -y ros-$ROS_DISTRO-health-metric-collector

### Building from Source

To build from source you'll need to create a new workspace, clone and checkout the latest release branch of this repository, install all the dependencies, and compile. If you need the latest development features you can clone from the `master` branch instead of the latest release branch. While we guarantee the release branches are stable, __the `master` should be considered to have an unstable build__ due to ongoing development. 

- Create a ROS workspace and a source directory

        mkdir -p ~/ros-workspace/src

- Clone the package into the source directory . 

        cd ~/ros-workspace/src
        git clone https://github.com/aws-robotics/health-metrics-collector-ros2.git -b release-latest

- Install dependencies

        cd ~/ros-workspace 
        sudo apt-get update && rosdep update
        rosdep install --from-paths src --ignore-src -r -y
        
_Note: If building the master branch instead of a release branch you may need to also checkout and build the master branches of the packages this package depends on._

- Build the packages

        cd ~/ros-workspace && colcon build

- Configure ROS library Path

        source ~/ros-workspace/install/setup.bash
        
- Build and run the unit tests

        colcon build --packages-select health_metric_collector --cmake-target tests
        colcon test --packages-select health_metric_collector && colcon test-result --all


## Launch Files
An example launch file called `sample_application.launch` is included in this project that gives an example of how you can include this node in your project together with the [`cloudwatch_metrics_collector`] node.


## Usage

### Run the node
- **With** launch file:
  - ROS: `roslaunch health_metric_collector sample_application.launch`

- **Without** launch file using default values
  - ROS: `rosrun health_metric_collector health_metric_collector`

### Running the sample application
To launch the sample application for the metrics node you can run the following command:

    roslaunch health_metric_collector sample_application.launch --screen


## Configuration file and Parameters
The `health_metric_collector` node receives an interval parameter that indicates the frequency in which it should sample metrics. e.g. interval=5 indicates sampling every five seconds. The default value is 5.

#### Supported Metrics Types
- Free RAM (in MB)
- Total RAM (in MB)
- Total cpu usage (percentage)
- Per core cpu usage (percentage)
- Uptime (in sec)
- Number of processes

## Performance and Benchmark Results
We evaluated the performance of this node by runnning the followning scenario on a Raspberry Pi 3 Model B:

- Launch a baseline graph containing the talker and listener nodes from the [roscpp_tutorials package](https://wiki.ros.org/roscpp_tutorials), plus two additional nodes that collect CPU and memory usage statistics. Allow the nodes to run 60 seconds. 
- Launch the `health_metric_collector` ROS node using the launch file `sample_application.launch` as described above. That launch file also starts a `cloudwatch_metrics_collector` node, that forwards to the Amazon CloudWatch Metrics service each of the metric messages the `health_metric_collector` ROS node is publishing to the `/metrics` topic. 
- Allow the nodes to run for 180 seconds. 
- Terminate the `health_metric_collector` and `cloudwatch_metrics_collector` nodes, and allow the remaining nodes to run for 60 seconds. 

The following graph shows the CPU usage during that scenario. After launching the nodes with `sample_application.launch`, the 1 minute average CPU usage increases from around 7% to a peak of 15%, and stabilizes around 6%, until the nodes are stopped around second 266. 

![cpu](wiki/images/cpu.svg)

The following graph shows the memory usage during that scenario. We start with a memory usage of 225 MB for the baseline graph, that increases to 251 MB (+11.56%) when `sample_application.launch` is launched. Memory usage keeps stable until we stop the nodes, and after tthat it goes back to 225 MB.

![memory](wiki/images/memory.svg)


## Node

### health_metric_collector

#### Published Topics
- **`/metrics`**

#### Subscribed Topics
None

#### Services
None


## Bugs & Feature Requests
Please contact the team directly if you would like to request a feature.

Please report bugs in [Issue Tracker].


[`cloudwatch_metrics_collector`]: https://github.com/aws-robotics/cloudwatchmetrics-ros2
[Amazon Web Services (AWS)]: https://aws.amazon.com/
[Apache 2.0]: https://aws.amazon.com/apache-2-0/
[AWS Configuration and Credential Files]: https://docs.aws.amazon.com/cli/latest/userguide/cli-config-files.html
[Issue Tracker]: https://github.com/aws-robotics/health-metrics-collector-ros2/issues
[ROS]: http://www.ros.org
