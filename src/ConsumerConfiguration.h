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

#ifndef PULSAR_CLIENT_PHPCPP_CONSUMER_CONFIGURATION_H
#define PULSAR_CLIENT_PHPCPP_CONSUMER_CONFIGURATION_H

#include <phpcpp.h>
#include <pulsar/ConsumerConfiguration.h>

/**
 * @brief PHP wrapper for the Pulsar ConsumerConfiguration.
 *
 * Controls subscription type, consumer name, initial position,
 * receiver queue sizes, and acknowledgement behaviour.
 */
class ConsumerConfiguration : public Php::Base {
  public:
    pulsar::ConsumerConfiguration config;

    ConsumerConfiguration() {}

    Php::Value setConsumerType(Php::Parameters &params);
    Php::Value setConsumerName(Php::Parameters &params);
    Php::Value setSubscriptionInitialPosition(Php::Parameters &params);
    Php::Value setReceiverQueueSize(Php::Parameters &params);
    Php::Value setAckGroupingTimeMs(Php::Parameters &params);
    Php::Value setNegativeAckRedeliveryDelayMs(Php::Parameters &params);
};

void registerConsumerConfiguration(Php::Namespace &pulsarNamespace);

#endif // PULSAR_CLIENT_PHPCPP_CONSUMER_CONFIGURATION_H
