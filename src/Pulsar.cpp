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
#include "Message.h"
#include "MessageBuilder.h"
#include "MessageId.h"
#include "Producer.h"
#include "ProducerConfiguration.h"
#include "Reader.h"
#include <phpcpp.h>

extern "C" {

PHPCPP_EXPORT void *get_module() {
    static Php::Extension extension("pulsar-phpcpp", "2.0.0");

    Php::Namespace pulsarNamespace("Pulsar");

    registerMessage(pulsarNamespace);
    registerMessageId(pulsarNamespace);
    registerMessageBuilder(pulsarNamespace);
    registerProducer(pulsarNamespace);
    registerProducerConfiguration(pulsarNamespace);
    registerConsumer(pulsarNamespace);
    registerConsumerConfiguration(pulsarNamespace);
    registerReader(pulsarNamespace);
    registerClient(pulsarNamespace);
    registerClientConfiguration(pulsarNamespace);

    extension.add(pulsarNamespace);

    return extension;
}

} // extern "C"
