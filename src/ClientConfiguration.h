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

#ifndef PULSAR_CLIENT_PHPCPP_CLIENT_CONFIGURATION_H
#define PULSAR_CLIENT_PHPCPP_CLIENT_CONFIGURATION_H

#include <phpcpp.h>
#include <pulsar/ClientConfiguration.h>

/**
 * @brief PHP wrapper for the Pulsar ClientConfiguration.
 *
 * Holds TLS settings, authentication, thread pool sizes,
 * timeouts, and logging configuration for a Pulsar Client.
 */
class ClientConfiguration : public Php::Base {
  public:
    pulsar::ClientConfiguration config;

    ClientConfiguration() {}

    Php::Value setUseTls(Php::Parameters &params);
    Php::Value setTlsTrustCertsFilePath(Php::Parameters &params);
    Php::Value setTlsAllowInsecureConnection(Php::Parameters &params);
    Php::Value setAuth(Php::Parameters &params);
    Php::Value setIoThreads(Php::Parameters &params);
    Php::Value setOperationTimeoutSeconds(Php::Parameters &params);
    Php::Value setMessageListenerThreads(Php::Parameters &params);
    Php::Value setConcurrentLookupRequest(Php::Parameters &params);
    Php::Value setStatsIntervalInSeconds(Php::Parameters &params);
    Php::Value setPartitionsUpdateInterval(Php::Parameters &params);
    Php::Value setConnectionTimeout(Php::Parameters &params);
    Php::Value setFileLogger(Php::Parameters &params);
};

void registerClientConfiguration(Php::Namespace &pulsarNamespace);

#endif // PULSAR_CLIENT_PHPCPP_CLIENT_CONFIGURATION_H
