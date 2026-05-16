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

#include "Message.h"
#include "MessageId.h"

Message::Message(pulsar::Message msg) : message(msg) {}

Php::Value Message::getDataAsString() {
    return this->message.getDataAsString();
}

Php::Value Message::getMessageId() {
    auto *msgId = new MessageId(this->message.getMessageId());
    return Php::Object("Pulsar\\MessageId", msgId);
}

Php::Value Message::getProperties() {
    Php::Value result;
    for (auto &kv : this->message.getProperties()) {
        result[kv.first] = kv.second;
    }
    return result;
}

Php::Value Message::hasProperty(Php::Parameters &params) {
    return this->message.hasProperty(params[0].stringValue());
}

Php::Value Message::getProperty(Php::Parameters &params) {
    return this->message.getProperty(params[0].stringValue());
}

Php::Value Message::getPublishTimestamp() {
    return static_cast<int64_t>(this->message.getPublishTimestamp());
}

Php::Value Message::getEventTimestamp() {
    return static_cast<int64_t>(this->message.getEventTimestamp());
}

Php::Value Message::getTopicName() {
    return this->message.getTopicName();
}

Php::Value Message::getPartitionKey() {
    return this->message.getPartitionKey();
}

Php::Value Message::hasPartitionKey() {
    return this->message.hasPartitionKey();
}

Php::Value Message::getOrderingKey() {
    return this->message.getOrderingKey();
}

Php::Value Message::hasOrderingKey() {
    return this->message.hasOrderingKey();
}

Php::Value Message::getLength() {
    return static_cast<int64_t>(this->message.getLength());
}

void registerMessage(Php::Namespace &pulsarNamespace) {
    Php::Class<Message> message("Message");
    message.method<&Message::getDataAsString>("getDataAsString");
    message.method<&Message::getMessageId>("getMessageId");
    message.method<&Message::getProperties>("getProperties");
    message.method<&Message::hasProperty>("hasProperty");
    message.method<&Message::getProperty>("getProperty");
    message.method<&Message::getPublishTimestamp>("getPublishTimestamp");
    message.method<&Message::getEventTimestamp>("getEventTimestamp");
    message.method<&Message::getTopicName>("getTopicName");
    message.method<&Message::getPartitionKey>("getPartitionKey");
    message.method<&Message::hasPartitionKey>("hasPartitionKey");
    message.method<&Message::getOrderingKey>("getOrderingKey");
    message.method<&Message::hasOrderingKey>("hasOrderingKey");
    message.method<&Message::getLength>("getLength");
    pulsarNamespace.add(message);
}
