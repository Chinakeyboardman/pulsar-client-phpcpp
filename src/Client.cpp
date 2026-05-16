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

#include "Client.h"
#include "ClientConfiguration.h"
#include "Consumer.h"
#include "ConsumerConfiguration.h"
#include "MessageId.h"
#include "Producer.h"
#include "ProducerConfiguration.h"
#include "Reader.h"
#include <pulsar/ReaderConfiguration.h>
#include <string>

Client::~Client() {
    if (client) {
        client->close();
        delete client;
        client = nullptr;
    }
}

void Client::__construct(Php::Parameters &params) {
    std::string serviceUrl = params[0];
    if (params.size() >= 2 && params[1].isObject()) {
        auto *conf = dynamic_cast<ClientConfiguration *>(params[1].implementation());
        if (!conf) {
            throw Php::Exception("Expected a ClientConfiguration instance");
        }
        this->client = new ::pulsar::Client(serviceUrl, conf->config);
    } else {
        this->client = new ::pulsar::Client(serviceUrl);
    }
}

Php::Value Client::createProducer(Php::Parameters &params) {
    Producer *producer = new Producer();
    pulsar::Result result;

    if (params.size() >= 2 && params[1].isObject()) {
        auto *conf = dynamic_cast<ProducerConfiguration *>(params[1].implementation());
        if (!conf) {
            throw Php::Exception("Expected a ProducerConfiguration instance");
        }
        result = this->client->createProducer(params[0].stringValue(), conf->config,
                                              producer->producer);
    } else {
        result = this->client->createProducer(params[0].stringValue(),
                                              producer->producer);
    }

    if (result != pulsar::ResultOk) {
        delete producer;
        throw Php::Exception(std::string("Failed to create producer: ") +
                             pulsar::strResult(result));
    }

    return Php::Object("Pulsar\\Producer", producer);
}

Php::Value Client::subscribe(Php::Parameters &params) {
    Consumer *consumer = new Consumer();
    pulsar::Result result;

    if (params.size() >= 3 && params[2].isObject()) {
        auto *conf = dynamic_cast<ConsumerConfiguration *>(params[2].implementation());
        if (!conf) {
            delete consumer;
            throw Php::Exception("Expected a ConsumerConfiguration instance");
        }
        result = this->client->subscribe(
            params[0].stringValue(), params[1].stringValue(),
            conf->config, consumer->consumer);
    } else if (params.size() >= 2) {
        result = this->client->subscribe(
            params[0].stringValue(), params[1].stringValue(),
            consumer->consumer);
    } else {
        delete consumer;
        throw Php::Exception("subscribe() requires at least topic and subscription name");
    }

    if (result != pulsar::ResultOk) {
        delete consumer;
        throw Php::Exception(std::string("Failed to subscribe: ") +
                             pulsar::strResult(result));
    }

    return Php::Object("Pulsar\\Consumer", consumer);
}

Php::Value Client::createReader(Php::Parameters &params) {
    if (params.size() < 2 || !params[1].isObject()) {
        throw Php::Exception(
            "createReader() requires topic and MessageId start position");
    }

    auto *startId = dynamic_cast<MessageId *>(params[1].implementation());
    if (!startId) {
        throw Php::Exception("Expected a MessageId instance as second argument");
    }

    Reader *reader = new Reader();
    pulsar::ReaderConfiguration readerConf;
    pulsar::Result result = this->client->createReader(
        params[0].stringValue(), startId->messageId, readerConf, reader->reader);

    if (result != pulsar::ResultOk) {
        delete reader;
        throw Php::Exception(std::string("Failed to create reader: ") +
                             pulsar::strResult(result));
    }

    return Php::Object("Pulsar\\Reader", reader);
}

void Client::close() {
    if (client) {
        client->close();
        delete client;
        client = nullptr;
    }
}

void registerClient(Php::Namespace &pulsarNamespace) {
    Php::Class<Client> client("Client");
    client.method<&Client::__construct>("__construct");
    client.method<&Client::createProducer>("createProducer");
    client.method<&Client::subscribe>("subscribe");
    client.method<&Client::createReader>("createReader");
    client.method<&Client::close>("close");
    pulsarNamespace.add(client);
}
