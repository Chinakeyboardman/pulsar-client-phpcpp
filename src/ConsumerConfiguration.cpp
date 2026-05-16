/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "ConsumerConfiguration.h"
#include <pulsar/ConsumerType.h>

#define CONSUMER_CONFIGURATION_CLASS_NAME "Pulsar\\ConsumerConfiguration"

Php::Value ConsumerConfiguration::setConsumerType(Php::Parameters &params) {
    auto consumerType =
        static_cast<pulsar::ConsumerType>(params[0].numericValue());
    this->config.setConsumerType(consumerType);
    return Php::Object(CONSUMER_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ConsumerConfiguration::setConsumerName(Php::Parameters &params) {
    this->config.setConsumerName(params[0].stringValue());
    return Php::Object(CONSUMER_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ConsumerConfiguration::setSubscriptionInitialPosition(
    Php::Parameters &params) {
    auto position = static_cast<pulsar::InitialPosition>(
        params[0].numericValue());
    this->config.setSubscriptionInitialPosition(position);
    return Php::Object(CONSUMER_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ConsumerConfiguration::setReceiverQueueSize(Php::Parameters &params) {
    this->config.setReceiverQueueSize(params[0].numericValue());
    return Php::Object(CONSUMER_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ConsumerConfiguration::setAckGroupingTimeMs(Php::Parameters &params) {
    this->config.setAckGroupingTimeMs(params[0].numericValue());
    return Php::Object(CONSUMER_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ConsumerConfiguration::setNegativeAckRedeliveryDelayMs(
    Php::Parameters &params) {
    this->config.setNegativeAckRedeliveryDelayMs(params[0].numericValue());
    return Php::Object(CONSUMER_CONFIGURATION_CLASS_NAME, this);
}

void registerConsumerConfiguration(Php::Namespace &pulsarNamespace) {
    Php::Class<ConsumerConfiguration> consumerConfiguration("ConsumerConfiguration");
    consumerConfiguration.method<&ConsumerConfiguration::setConsumerType>("setConsumerType");
    consumerConfiguration.method<&ConsumerConfiguration::setConsumerName>("setConsumerName");
    consumerConfiguration.method<&ConsumerConfiguration::setSubscriptionInitialPosition>("setSubscriptionInitialPosition");
    consumerConfiguration.method<&ConsumerConfiguration::setReceiverQueueSize>("setReceiverQueueSize");
    consumerConfiguration.method<&ConsumerConfiguration::setAckGroupingTimeMs>("setAckGroupingTimeMs");
    consumerConfiguration.method<&ConsumerConfiguration::setNegativeAckRedeliveryDelayMs>("setNegativeAckRedeliveryDelayMs");

    consumerConfiguration.property("InitialPositionLatest",
        static_cast<int>(pulsar::InitialPositionLatest), Php::Const);
    consumerConfiguration.property("InitialPositionEarliest",
        static_cast<int>(pulsar::InitialPositionEarliest), Php::Const);

    pulsarNamespace.add(consumerConfiguration);
}
