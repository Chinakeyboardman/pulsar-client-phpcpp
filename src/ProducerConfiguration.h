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

#ifndef PULSAR_CLIENT_PHPCPP_PRODUCER_CONFIGURATION_H
#define PULSAR_CLIENT_PHPCPP_PRODUCER_CONFIGURATION_H

#include <phpcpp.h>
#include <pulsar/ProducerConfiguration.h>

/**
 * @brief PHP wrapper for the Pulsar ProducerConfiguration.
 *
 * Controls send timeout, compression, batching behaviour,
 * queue limits, and routing mode for a Producer.
 */
class ProducerConfiguration : public Php::Base {
  public:
    pulsar::ProducerConfiguration config;

    ProducerConfiguration() {}

    Php::Value setSendTimeout(Php::Parameters &params);
    Php::Value setCompressionType(Php::Parameters &params);
    Php::Value setMaxPendingMessages(Php::Parameters &params);
    Php::Value setBatchingEnabled(Php::Parameters &params);
    Php::Value setBatchingMaxMessages(Php::Parameters &params);
    Php::Value setBatchingMaxPublishDelayMs(Php::Parameters &params);
    Php::Value setBlockIfQueueFull(Php::Parameters &params);
    Php::Value setProducerName(Php::Parameters &params);
};

void registerProducerConfiguration(Php::Namespace &pulsarNamespace);

#endif // PULSAR_CLIENT_PHPCPP_PRODUCER_CONFIGURATION_H
