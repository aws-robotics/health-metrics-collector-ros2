# health_metric_collector

## Overview
This `health_metric_collector` ROS node collects system metrics and publishes them to `/metrics` topic. The `cloudwatch_metrics_collector` node is subscribed to this topic and will publish the metrics to AWS CloudWatch when it is instantiated.

**Keywords**: ROS, ROS2, AWS, CloudWatch, Metrics

### License
The source code is released under an [Apache 2.0].

**Author**: AWS RoboMaker<br/>
**Affiliation**: [Amazon Web Services (AWS)]<br/>
**Maintainer**: AWS RoboMaker, ros-contributions@amazon.com

### Supported ROS Distributions
- Dashing

### Build status
GitHub Action Status
* master: ![Build & Test](https://github.com/aws-robotics/health-metrics-collector-ros2/workflows/Build%20&%20Test/badge.svg?branch=master&event=schedule)
* release-latest: ![Build & Test release-latest](https://github.com/aws-robotics/health-metrics-collector-ros2//workflows/Build%20&%20Test%20release-latest/badge.svg?event=schedule)

* Travis CI:
    * "master" branch [![Build Status](https://travis-ci.org/aws-robotics/health-metrics-collector-ros2.svg?branch=master)](https://travis-ci.org/aws-robotics/health-metrics-collector-ros2/branches)
    * "release-latest" branch [![Build Status](https://travis-ci.org/aws-robotics/health-metrics-collector-ros2.svg?branch=release-latest)](https://travis-ci.org/aws-robotics/health-metrics-collector-ros2/branches)
* ROS build farm:
   * ROS Dashing @ u18.04 Bionic [![Build Status](http://build.ros2.org/job/Dbin_uB64__health_metric_collector__ubuntu_bionic_amd64__binary/badge/icon)](http://build.ros2.org/job/Dbin_uB64__health_metric_collector__ubuntu_bionic_amd64__binary)

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

        source ~/ros-workspace/install/local_setup.bash
        
- Run the unit tests

        colcon test --packages-select health_metric_collector && colcon test-result --all


## Launch Files
An example launch file called `sample_application.launch` is included in this project that gives an example of how you can include this node in your project together with the [`cloudwatch_metrics_collector`] node.


## Usage

### Run the node
  - `ros2 launch health_metric_collector health_metric_collector.launch.py`


### Running the sample application
To launch the sample application for the metrics node you can run the following command:

  - `ros2 launch health_metric_collector sample_application.launch.py --screen`

This will launch `cloudwatch_metrics_collector` too, and will start emitting metrics to Amazon CloudWatch.

## Configuration file and Parameters
The `health_metric_collector` node receives an interval parameter that indicates the frequency in which it should sample metrics. e.g. interval=5 indicates sampling every five seconds. The default value is 5.

#### Supported Metrics Types
- Free RAM (in MB)
- Total RAM (in MB)
- Total cpu usage (percentage)
- Per core cpu usage (percentage)
- Uptime (in sec)
- Number of processes


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
