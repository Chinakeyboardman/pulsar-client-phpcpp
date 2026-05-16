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

#include "MessageId.h"
#include <string>

#define MESSAGE_ID_CLASS_NAME "Pulsar\\MessageId"

MessageId::MessageId(pulsar::MessageId msgId) : messageId(msgId) {}

Php::Value MessageId::earliest(Php::Parameters &params) {
    return Php::Object(MESSAGE_ID_CLASS_NAME,
                       new MessageId(pulsar::MessageId::earliest()));
}

Php::Value MessageId::latest(Php::Parameters &params) {
    return Php::Object(MESSAGE_ID_CLASS_NAME,
                       new MessageId(pulsar::MessageId::latest()));
}

Php::Value MessageId::getTopicName() {
    return this->messageId.getTopicName();
}

void MessageId::setTopicName(Php::Parameters &params) {
    this->messageId.setTopicName(params[0].stringValue());
}

Php::Value MessageId::serialize(Php::Parameters &params) {
    std::string result;
    this->messageId.serialize(result);
    return result;
}

Php::Value MessageId::deserialize(Php::Parameters &params) {
    return Php::Object(
        MESSAGE_ID_CLASS_NAME,
        new MessageId(pulsar::MessageId::deserialize(params[0].stringValue())));
}

void registerMessageId(Php::Namespace &pulsarNamespace) {
    Php::Class<MessageId> messageId("MessageId");
    messageId.method<&MessageId::earliest>("earliest");
    messageId.method<&MessageId::latest>("latest");
    messageId.method<&MessageId::getTopicName>("getTopicName");
    messageId.method<&MessageId::setTopicName>("setTopicName");
    messageId.method<&MessageId::serialize>("serialize");
    messageId.method<&MessageId::deserialize>("deserialize");
    pulsarNamespace.add(messageId);
}
