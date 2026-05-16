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

#ifndef PULSAR_CLIENT_PHPCPP_MESSAGE_BUILDER_H
#define PULSAR_CLIENT_PHPCPP_MESSAGE_BUILDER_H

#include <phpcpp.h>
#include <pulsar/MessageBuilder.h>

/**
 * @brief Fluent builder for constructing Pulsar Message instances.
 *
 * All setter methods return $this for method chaining.
 * Call build() to produce the final Message object.
 */
class MessageBuilder : public Php::Base {
  public:
    pulsar::MessageBuilder builder;

    MessageBuilder() {}

    Php::Value setContent(Php::Parameters &params);
    Php::Value build();
    Php::Value setProperty(Php::Parameters &params);
    Php::Value setPartitionKey(Php::Parameters &params);
    Php::Value setOrderingKey(Php::Parameters &params);
    Php::Value setDeliverAfter(Php::Parameters &params);
    Php::Value setDeliverAt(Php::Parameters &params);
    Php::Value setEventTimestamp(Php::Parameters &params);
    Php::Value setSequenceId(Php::Parameters &params);
    Php::Value disableReplication(Php::Parameters &params);
    Php::Value setProperties(Php::Parameters &params);
};

void registerMessageBuilder(Php::Namespace &pulsarNamespace);

#endif // PULSAR_CLIENT_PHPCPP_MESSAGE_BUILDER_H
