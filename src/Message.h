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

#ifndef PULSAR_CLIENT_PHPCPP_MESSAGE_H
#define PULSAR_CLIENT_PHPCPP_MESSAGE_H

#include <phpcpp.h>
#include <pulsar/Message.h>

/**
 * @brief PHP wrapper for a Pulsar Message.
 *
 * Represents a single message received from or to be sent to a Pulsar topic.
 * Provides access to payload, properties, timestamps, and message identity.
 */
class Message : public Php::Base {
  public:
    pulsar::Message message;

    Message() {}
    Message(pulsar::Message msg);

    /** @brief Get the message payload as a UTF-8 string. */
    Php::Value getDataAsString();

    /** @brief Get the MessageId associated with this message. */
    Php::Value getMessageId();

    /** @brief Get all user-defined properties as an associative array. */
    Php::Value getProperties();

    /** @brief Check whether a specific property exists. */
    Php::Value hasProperty(Php::Parameters &params);

    /** @brief Get the value of a specific property by key. */
    Php::Value getProperty(Php::Parameters &params);

    /** @brief Get the publish timestamp (epoch milliseconds). */
    Php::Value getPublishTimestamp();

    /** @brief Get the event timestamp (epoch milliseconds). */
    Php::Value getEventTimestamp();

    /** @brief Get the topic name this message belongs to. */
    Php::Value getTopicName();

    /** @brief Get the partition key if set. */
    Php::Value getPartitionKey();

    /** @brief Check whether a partition key is set. */
    Php::Value hasPartitionKey();

    /** @brief Get the ordering key if set. */
    Php::Value getOrderingKey();

    /** @brief Check whether an ordering key is set. */
    Php::Value hasOrderingKey();

    /** @brief Get the payload length in bytes. */
    Php::Value getLength();
};

void registerMessage(Php::Namespace &pulsarNamespace);

#endif // PULSAR_CLIENT_PHPCPP_MESSAGE_H
