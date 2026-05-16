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

#include "Consumer.h"
#include "Message.h"

Php::Value Consumer::receive(Php::Parameters &params) {
    Message *message = new Message();
    pulsar::Result result;

    if (params.size() >= 1 && params[0].isNumeric()) {
        result = this->consumer.receive(message->message,
                                        params[0].numericValue());
    } else {
        result = this->consumer.receive(message->message);
    }

    if (result != pulsar::ResultOk) {
        delete message;
        throw Php::Exception(std::string("Failed to receive message: ") +
                             pulsar::strResult(result));
    }

    return Php::Object("Pulsar\\Message", message);
}

void Consumer::acknowledge(Php::Parameters &params) {
    auto *message = dynamic_cast<Message *>(params[0].implementation());
    if (!message) {
        throw Php::Exception("Expected a Message instance");
    }
    this->consumer.acknowledge(message->message);
}

void Consumer::negativeAcknowledge(Php::Parameters &params) {
    auto *message = dynamic_cast<Message *>(params[0].implementation());
    if (!message) {
        throw Php::Exception("Expected a Message instance");
    }
    this->consumer.negativeAcknowledge(message->message);
}

void Consumer::close() {
    this->consumer.close();
}

void registerConsumer(Php::Namespace &pulsarNamespace) {
    Php::Class<Consumer> consumer("Consumer");
    consumer.method<&Consumer::receive>("receive");
    consumer.method<&Consumer::acknowledge>("acknowledge");
    consumer.method<&Consumer::negativeAcknowledge>("negativeAcknowledge");
    consumer.method<&Consumer::close>("close");

    consumer.property("ConsumerExclusive",  ::pulsar::ConsumerExclusive,  Php::Const);
    consumer.property("ConsumerShared",     ::pulsar::ConsumerShared,     Php::Const);
    consumer.property("ConsumerFailover",   ::pulsar::ConsumerFailover,   Php::Const);
    consumer.property("ConsumerKeyShared",  ::pulsar::ConsumerKeyShared,  Php::Const);

    pulsarNamespace.add(consumer);
}
