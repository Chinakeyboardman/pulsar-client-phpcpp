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

#include "MessageBuilder.h"
#include "Message.h"
#include <chrono>

#define MESSAGE_BUILDER_CLASS_NAME "Pulsar\\MessageBuilder"

Php::Value MessageBuilder::setContent(Php::Parameters &params) {
    this->builder.setContent(params[0].stringValue());
    return Php::Object(MESSAGE_BUILDER_CLASS_NAME, this);
}

Php::Value MessageBuilder::setProperty(Php::Parameters &params) {
    this->builder.setProperty(params[0].stringValue(), params[1].stringValue());
    return Php::Object(MESSAGE_BUILDER_CLASS_NAME, this);
}

Php::Value MessageBuilder::setPartitionKey(Php::Parameters &params) {
    this->builder.setPartitionKey(params[0].stringValue());
    return Php::Object(MESSAGE_BUILDER_CLASS_NAME, this);
}

Php::Value MessageBuilder::setOrderingKey(Php::Parameters &params) {
    this->builder.setOrderingKey(params[0].stringValue());
    return Php::Object(MESSAGE_BUILDER_CLASS_NAME, this);
}

Php::Value MessageBuilder::setDeliverAfter(Php::Parameters &params) {
    this->builder.setDeliverAfter(
        std::chrono::milliseconds(params[0].numericValue()));
    return Php::Object(MESSAGE_BUILDER_CLASS_NAME, this);
}

Php::Value MessageBuilder::setDeliverAt(Php::Parameters &params) {
    this->builder.setDeliverAt(static_cast<int64_t>(params[0].numericValue()));
    return Php::Object(MESSAGE_BUILDER_CLASS_NAME, this);
}

Php::Value MessageBuilder::setEventTimestamp(Php::Parameters &params) {
    this->builder.setEventTimestamp(
        static_cast<uint64_t>(params[0].numericValue()));
    return Php::Object(MESSAGE_BUILDER_CLASS_NAME, this);
}

Php::Value MessageBuilder::setSequenceId(Php::Parameters &params) {
    this->builder.setSequenceId(
        static_cast<int64_t>(params[0].numericValue()));
    return Php::Object(MESSAGE_BUILDER_CLASS_NAME, this);
}

Php::Value MessageBuilder::disableReplication(Php::Parameters &params) {
    this->builder.disableReplication(params[0].boolValue());
    return Php::Object(MESSAGE_BUILDER_CLASS_NAME, this);
}

Php::Value MessageBuilder::setProperties(Php::Parameters &params) {
    std::map<std::string, std::string> properties;
    for (auto &v : params[0].mapValue()) {
        properties[v.first] = v.second.stringValue();
    }
    this->builder.setProperties(properties);
    return Php::Object(MESSAGE_BUILDER_CLASS_NAME, this);
}

Php::Value MessageBuilder::build() {
    return Php::Object("Pulsar\\Message",
                       new Message(this->builder.build()));
}

void registerMessageBuilder(Php::Namespace &pulsarNamespace) {
    Php::Class<MessageBuilder> builder("MessageBuilder");
    builder.method<&MessageBuilder::setContent>("setContent");
    builder.method<&MessageBuilder::setProperty>("setProperty");
    builder.method<&MessageBuilder::setProperties>("setProperties");
    builder.method<&MessageBuilder::setPartitionKey>("setPartitionKey");
    builder.method<&MessageBuilder::setOrderingKey>("setOrderingKey");
    builder.method<&MessageBuilder::setDeliverAfter>("setDeliverAfter");
    builder.method<&MessageBuilder::setDeliverAt>("setDeliverAt");
    builder.method<&MessageBuilder::setEventTimestamp>("setEventTimestamp");
    builder.method<&MessageBuilder::setSequenceId>("setSequenceId");
    builder.method<&MessageBuilder::disableReplication>("disableReplication");
    builder.method<&MessageBuilder::build>("build");
    pulsarNamespace.add(builder);
}
