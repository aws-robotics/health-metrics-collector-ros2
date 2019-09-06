^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package health_metric_collector
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Forthcoming
-----------
* remove changelog for new release
* Add launch dependencies
* Update version to 3.0.0 for first ROS2 release (`#5 <https://github.com/aws-robotics/health-metrics-collector-ros2/issues/5>`_)
  * Update version to 2.0.1 for consistency with health-metrics-collector-ros1
  * Bumping version to 3.0.0 and upgrading package.xml format to 3
  * Update changelog
* Allow undeclared params and add default ones to the yaml config file.
* Add unit tests (equivalent to the ROS1 version)
* Remove cmake-build-debug folder
* Rename package, make launch file ROS1 compatible
  - Rename package to health_metric_collector, removing the _node suffix
  to keep this package consistent with all our others (where github repo,
  folder name and package name are all the same).
  - Improve launch file to be the same as ROS1 where users can override
  node_name or config_file.
* Merge pull request `#2 <https://github.com/aws-robotics/health-metrics-collector-ros2/issues/2>`_ from aws-robotics/namespace-fixup
  Fixes the namespacing that was mistakenly added for several files during the conversion.
* Fixes the namespacing that was mistakenly added for several files during the conversion.
* Adding basic implementation
* Contributors: AAlon, Avishay Alon, M M, Nick Burek, Tim Robinson, burekn
