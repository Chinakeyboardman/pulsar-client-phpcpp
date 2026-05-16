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

#include "Reader.h"
#include "Message.h"

Php::Value Reader::readNext(Php::Parameters &params) {
    Message *message = new Message();
    pulsar::Result result;

    if (params.size() >= 1 && params[0].isNumeric()) {
        result = this->reader.readNext(message->message,
                                       params[0].numericValue());
    } else {
        result = this->reader.readNext(message->message);
    }

    if (result != pulsar::ResultOk) {
        delete message;
        throw Php::Exception(std::string("Failed to read message: ") +
                             pulsar::strResult(result));
    }

    return Php::Object("Pulsar\\Message", message);
}

Php::Value Reader::hasMessageAvailable() {
    bool available = false;
    pulsar::Result result = this->reader.hasMessageAvailable(available);
    if (result != pulsar::ResultOk) {
        throw Php::Exception(
            std::string("Failed to check message availability: ") +
            pulsar::strResult(result));
    }
    return available;
}

void Reader::close() {
    this->reader.close();
}

Php::Value Reader::getTopic() {
    return this->reader.getTopic();
}

void registerReader(Php::Namespace &pulsarNamespace) {
    Php::Class<Reader> reader("Reader");
    reader.method<&Reader::readNext>("readNext");
    reader.method<&Reader::hasMessageAvailable>("hasMessageAvailable");
    reader.method<&Reader::close>("close");
    reader.method<&Reader::getTopic>("getTopic");
    pulsarNamespace.add(reader);
}
