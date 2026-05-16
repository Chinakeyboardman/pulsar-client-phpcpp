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

#include "ProducerConfiguration.h"

#define PRODUCER_CONFIGURATION_CLASS_NAME "Pulsar\\ProducerConfiguration"

Php::Value ProducerConfiguration::setSendTimeout(Php::Parameters &params) {
    this->config.setSendTimeout(params[0].numericValue());
    return Php::Object(PRODUCER_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ProducerConfiguration::setCompressionType(Php::Parameters &params) {
    auto type =
        static_cast<pulsar::CompressionType>(params[0].numericValue());
    this->config.setCompressionType(type);
    return Php::Object(PRODUCER_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ProducerConfiguration::setMaxPendingMessages(Php::Parameters &params) {
    this->config.setMaxPendingMessages(params[0].numericValue());
    return Php::Object(PRODUCER_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ProducerConfiguration::setBatchingEnabled(Php::Parameters &params) {
    this->config.setBatchingEnabled(params[0].boolValue());
    return Php::Object(PRODUCER_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ProducerConfiguration::setBatchingMaxMessages(Php::Parameters &params) {
    this->config.setBatchingMaxMessages(
        static_cast<unsigned int>(params[0].numericValue()));
    return Php::Object(PRODUCER_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ProducerConfiguration::setBatchingMaxPublishDelayMs(
    Php::Parameters &params) {
    this->config.setBatchingMaxPublishDelayMs(
        static_cast<unsigned long>(params[0].numericValue()));
    return Php::Object(PRODUCER_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ProducerConfiguration::setBlockIfQueueFull(Php::Parameters &params) {
    this->config.setBlockIfQueueFull(params[0].boolValue());
    return Php::Object(PRODUCER_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ProducerConfiguration::setProducerName(Php::Parameters &params) {
    this->config.setProducerName(params[0].stringValue());
    return Php::Object(PRODUCER_CONFIGURATION_CLASS_NAME, this);
}

void registerProducerConfiguration(Php::Namespace &pulsarNamespace) {
    Php::Class<ProducerConfiguration> producerConfiguration("ProducerConfiguration");
    producerConfiguration.method<&ProducerConfiguration::setSendTimeout>("setSendTimeout");
    producerConfiguration.method<&ProducerConfiguration::setCompressionType>("setCompressionType");
    producerConfiguration.method<&ProducerConfiguration::setMaxPendingMessages>("setMaxPendingMessages");
    producerConfiguration.method<&ProducerConfiguration::setBatchingEnabled>("setBatchingEnabled");
    producerConfiguration.method<&ProducerConfiguration::setBatchingMaxMessages>("setBatchingMaxMessages");
    producerConfiguration.method<&ProducerConfiguration::setBatchingMaxPublishDelayMs>("setBatchingMaxPublishDelayMs");
    producerConfiguration.method<&ProducerConfiguration::setBlockIfQueueFull>("setBlockIfQueueFull");
    producerConfiguration.method<&ProducerConfiguration::setProducerName>("setProducerName");

    producerConfiguration.property("CompressionNone",   static_cast<int>(pulsar::CompressionNone),   Php::Const);
    producerConfiguration.property("CompressionLZ4",    static_cast<int>(pulsar::CompressionLZ4),    Php::Const);
    producerConfiguration.property("CompressionZLib",   static_cast<int>(pulsar::CompressionZLib),   Php::Const);
    producerConfiguration.property("CompressionZSTD",   static_cast<int>(pulsar::CompressionZSTD),   Php::Const);
    producerConfiguration.property("CompressionSNAPPY", static_cast<int>(pulsar::CompressionSNAPPY), Php::Const);

    pulsarNamespace.add(producerConfiguration);
}
