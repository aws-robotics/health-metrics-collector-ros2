# health_metric_collector

## Overview
This `health_metric_collector` ROS node collects system metrics and publishes them to `/metrics` topic. The `cloudwatch_metrics_collector` node is subscribed to this topic and will publish the metrics to AWS CloudWatch when it is instantiated.

**Keywords**: ROS, ROS2, AWS, CloudWatch, Metrics

### License
The source code is released under an [Apache 2.0].

**Author**: AWS RoboMaker<br/>
**Affiliation**: [Amazon Web Services (AWS)]<br/>

RoboMaker cloud extensions rely on third-party software licensed under open-source licenses and are provided for demonstration purposes only. Incorporation or use of RoboMaker cloud extensions in connection with your production workloads or commercial product(s) or devices may affect your legal rights or obligations under the applicable open-source licenses. License information for this repository can be found [here](https://github.com/aws-robotics/health-metrics-collector-ros2/blob/master/LICENSE). AWS does not provide support for this cloud extension. You are solely responsible for how you configure, deploy, and maintain this cloud extension in your workloads or commercial product(s) or devices.

### Supported ROS Distributions
- Dashing

## Installation

### AWS Credentials
You will need to create an AWS Account and configure the credentials to be able to communicate with AWS services. You may find [AWS Configuration and Credential Files] helpful. Specifying AWS [credentials by setting environment variables](https://docs.aws.amazon.com/cli/latest/userguide/cli-environment.html) is not supported. 

This node will require the following AWS account IAM role permissions:
- `cloudwatch:PutMetricData`

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

[`cloudwatch_metrics_collector`]: https://github.com/aws-robotics/cloudwatchmetrics-ros2
[Amazon Web Services (AWS)]: https://aws.amazon.com/
[Apache 2.0]: https://aws.amazon.com/apache-2-0/
[AWS Configuration and Credential Files]: https://docs.aws.amazon.com/cli/latest/userguide/cli-config-files.html
[Issue Tracker]: https://github.com/aws-robotics/health-metrics-collector-ros2/issues
[ROS]: http://www.ros.org
