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

#ifndef PULSAR_CLIENT_PHPCPP_CLIENT_H
#define PULSAR_CLIENT_PHPCPP_CLIENT_H

#include <phpcpp.h>
#include <pulsar/Client.h>

/**
 * @brief PHP wrapper for the Pulsar C++ Client.
 *
 * Provides the entry point for connecting to an Apache Pulsar cluster.
 * Users create producers, consumers, and readers through this class.
 */
class Client : public Php::Base {
  public:
    pulsar::Client *client = nullptr;

    ~Client();

    /**
     * @brief Construct a Pulsar client connected to the given service URL.
     * @param params[0] string  Service URL (e.g. "pulsar://localhost:6650")
     * @param params[1] object  Optional ClientConfiguration instance
     */
    void __construct(Php::Parameters &params);

    /**
     * @brief Create a producer for the given topic.
     * @param params[0] string  Topic name
     * @param params[1] object  Optional ProducerConfiguration instance
     * @return Pulsar\Producer
     */
    Php::Value createProducer(Php::Parameters &params);

    /**
     * @brief Subscribe to a topic.
     * @param params[0] string  Topic name
     * @param params[1] string  Subscription name
     * @param params[2] object  Optional ConsumerConfiguration instance
     * @return Pulsar\Consumer
     */
    Php::Value subscribe(Php::Parameters &params);

    /**
     * @brief Create a reader on a topic starting from a given message ID.
     * @param params[0] string     Topic name
     * @param params[1] object     MessageId start position
     * @return Pulsar\Reader
     */
    Php::Value createReader(Php::Parameters &params);

    /**
     * @brief Close the client and release all associated resources.
     */
    void close();
};

void registerClient(Php::Namespace &pulsarNamespace);

#endif // PULSAR_CLIENT_PHPCPP_CLIENT_H
