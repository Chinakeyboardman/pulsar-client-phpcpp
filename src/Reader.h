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

#ifndef PULSAR_CLIENT_PHPCPP_READER_H
#define PULSAR_CLIENT_PHPCPP_READER_H

#include <phpcpp.h>
#include <pulsar/Reader.h>

/**
 * @brief PHP wrapper for the Pulsar Reader.
 *
 * A Reader allows reading messages from a topic starting at a specific
 * position without the subscription/acknowledgement semantics of a Consumer.
 * Useful for replaying messages or building stream-processing pipelines.
 */
class Reader : public Php::Base {
  public:
    pulsar::Reader reader;

    Reader() {}

    /**
     * @brief Read the next message from the topic.
     * @param params[0] int  Optional timeout in milliseconds
     * @return Pulsar\Message
     * @throws Php::Exception on timeout or read failure
     */
    Php::Value readNext(Php::Parameters &params);

    /**
     * @brief Check whether more messages are available.
     * @return bool
     */
    Php::Value hasMessageAvailable();

    /**
     * @brief Close the reader and release resources.
     */
    void close();

    /**
     * @brief Get the topic this reader is attached to.
     * @return string
     */
    Php::Value getTopic();
};

void registerReader(Php::Namespace &pulsarNamespace);

#endif // PULSAR_CLIENT_PHPCPP_READER_H
