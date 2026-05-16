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

#ifndef PULSAR_CLIENT_PHPCPP_CONSUMER_H
#define PULSAR_CLIENT_PHPCPP_CONSUMER_H

#include <phpcpp.h>
#include <pulsar/Consumer.h>
#include <pulsar/ConsumerType.h>

/**
 * @brief PHP wrapper for the Pulsar Consumer.
 *
 * Receives messages from a subscribed topic. Supports exclusive,
 * shared, failover, and key-shared subscription types.
 */
class Consumer : public Php::Base {
  public:
    pulsar::Consumer consumer;

    Consumer() {}

    /**
     * @brief Receive the next message from the topic.
     * @param params[0] int  Optional timeout in milliseconds
     * @return Pulsar\Message
     */
    Php::Value receive(Php::Parameters &params);

    /**
     * @brief Acknowledge successful processing of a message.
     * @param params[0] object  Message instance to acknowledge
     */
    void acknowledge(Php::Parameters &params);

    /**
     * @brief Negatively acknowledge a message, triggering redelivery.
     * @param params[0] object  Message instance
     */
    void negativeAcknowledge(Php::Parameters &params);

    /**
     * @brief Close the consumer and release resources.
     */
    void close();
};

void registerConsumer(Php::Namespace &pulsarNamespace);

#endif // PULSAR_CLIENT_PHPCPP_CONSUMER_H
