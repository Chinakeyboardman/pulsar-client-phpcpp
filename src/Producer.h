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

#ifndef PULSAR_CLIENT_PHPCPP_PRODUCER_H
#define PULSAR_CLIENT_PHPCPP_PRODUCER_H

#include <phpcpp.h>
#include <pulsar/Producer.h>

/**
 * @brief PHP wrapper for the Pulsar Producer.
 *
 * Publishes messages to a Pulsar topic. Supports both
 * synchronous and asynchronous (fire-and-forget) sends.
 */
class Producer : public Php::Base {
  public:
    pulsar::Producer producer;

    Producer() {}

    /**
     * @brief Synchronously send a message.
     * @param params[0] object  Message instance built via MessageBuilder
     * @throws Php::Exception on send failure
     */
    void send(Php::Parameters &params);

    /**
     * @brief Asynchronously enqueue a message for sending.
     *
     * The message is placed in an internal buffer and sent by the
     * background I/O thread. Call flush() to wait for completion.
     * @param params[0] object  Message instance
     */
    void sendAsync(Php::Parameters &params);

    /**
     * @brief Flush all pending async messages, blocking until done.
     */
    void flush();

    /**
     * @brief Close the producer and release resources.
     */
    void close();

    /**
     * @brief Get the topic this producer is attached to.
     * @return string
     */
    Php::Value getTopic();
};

void registerProducer(Php::Namespace &pulsarNamespace);

#endif // PULSAR_CLIENT_PHPCPP_PRODUCER_H
