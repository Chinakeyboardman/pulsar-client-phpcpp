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

#ifndef PULSAR_CLIENT_PHPCPP_MESSAGE_ID_H
#define PULSAR_CLIENT_PHPCPP_MESSAGE_ID_H

#include <phpcpp.h>
#include <pulsar/MessageId.h>

/**
 * @brief PHP wrapper for a Pulsar MessageId.
 *
 * Uniquely identifies a message within a topic partition.
 * Provides factory methods for well-known positions (earliest/latest)
 * and serialization helpers for persistent storage.
 */
class MessageId : public Php::Base {
  public:
    pulsar::MessageId messageId;

    MessageId() {}
    MessageId(pulsar::MessageId msgId);

    /** @brief Get a MessageId representing the earliest available message. */
    static Php::Value earliest(Php::Parameters &params);

    /** @brief Get a MessageId representing the latest (newest) message. */
    static Php::Value latest(Php::Parameters &params);

    /** @brief Get the topic name associated with this message ID. */
    Php::Value getTopicName();

    /** @brief Set the topic name on this message ID. */
    void setTopicName(Php::Parameters &params);

    /** @brief Serialize this MessageId to a binary string. */
    Php::Value serialize(Php::Parameters &params);

    /** @brief Deserialize a MessageId from a binary string. */
    static Php::Value deserialize(Php::Parameters &params);
};

void registerMessageId(Php::Namespace &pulsarNamespace);

#endif // PULSAR_CLIENT_PHPCPP_MESSAGE_ID_H
