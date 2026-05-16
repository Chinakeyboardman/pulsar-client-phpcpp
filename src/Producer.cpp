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

#include "Producer.h"
#include "Message.h"

void Producer::send(Php::Parameters &params) {
    auto *message = dynamic_cast<Message *>(params[0].implementation());
    if (!message) {
        throw Php::Exception("Expected a Message instance");
    }

    pulsar::Result result = this->producer.send(message->message);
    if (result != pulsar::ResultOk) {
        throw Php::Exception(std::string("Failed to send message: ") +
                             pulsar::strResult(result));
    }
}

void Producer::sendAsync(Php::Parameters &params) {
    auto *message = dynamic_cast<Message *>(params[0].implementation());
    if (!message) {
        throw Php::Exception("Expected a Message instance");
    }

    this->producer.sendAsync(
        message->message,
        [](pulsar::Result, const pulsar::MessageId &) {});
}

void Producer::flush() {
    pulsar::Result result = this->producer.flush();
    if (result != pulsar::ResultOk) {
        throw Php::Exception(std::string("Failed to flush producer: ") +
                             pulsar::strResult(result));
    }
}

void Producer::close() {
    this->producer.close();
}

Php::Value Producer::getTopic() {
    return this->producer.getTopic();
}

void registerProducer(Php::Namespace &pulsarNamespace) {
    Php::Class<Producer> producer("Producer");
    producer.method<&Producer::send>("send");
    producer.method<&Producer::sendAsync>("sendAsync");
    producer.method<&Producer::flush>("flush");
    producer.method<&Producer::close>("close");
    producer.method<&Producer::getTopic>("getTopic");
    pulsarNamespace.add(producer);
}
