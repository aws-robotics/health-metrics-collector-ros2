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

#include <rclcpp/rclcpp.hpp>
#include <ros_monitoring_msgs/msg/metric_data.hpp>
#include <ros_monitoring_msgs/msg/metric_list.hpp>

#include <vector>


namespace ros_monitoring_msgs {
namespace msg {
/**
 * @brief Interface for MetricManager.
 */
class MetricManagerInterface {
public:
    /**
     * @brief add global dimension (applies to all metrics).
     */
    virtual void AddDimension(const std::string &name, const std::string &value) = 0;

    /**
     * @brief create a metric.
     */
    virtual MetricData CreateMetric() const = 0;

    /**
     * @brief add a metric to list of metrics to be published.
     *
     * @param md a metric.
     */
    virtual void AddMetric(MetricData md) = 0;

    /**
     * @brief publishes all metrics and then discards them.
     */
    virtual void Publish() = 0;

    /** @brief destructor. */
    virtual ~MetricManagerInterface() {}
};

/**
 * @brief Create, aggregate and publish metrics to ros topic.
 **/
class MetricManager : public MetricManagerInterface {
public:
  explicit MetricManager(
    rclcpp::Node::SharedPtr node,
    std::string metrics_topic_name,
    int topic_buffer_size
    ) :
      node_(node),
      publisher_(node->create_publisher<MetricList>(metrics_topic_name, topic_buffer_size)) {}

  virtual void AddDimension(const std::string &name, const std::string &value) override final;

  virtual MetricData CreateMetric() const override final;

  virtual void AddMetric(MetricData md) override final;

  virtual void Publish() override final;

private:
  rclcpp::Node::SharedPtr node_;
  rclcpp::Publisher<MetricList>::SharedPtr publisher_;
  MetricList mlist_;
  MetricData dimensions_;
};

}}  // namespace ros_monitoring_msgs::msg
