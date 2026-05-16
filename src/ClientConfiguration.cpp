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

#include "ClientConfiguration.h"
#include <pulsar/FileLoggerFactory.h>
#include <pulsar/Logger.h>

#define CLIENT_CONFIGURATION_CLASS_NAME "Pulsar\\ClientConfiguration"

Php::Value ClientConfiguration::setUseTls(Php::Parameters &params) {
    this->config.setUseTls(params[0].boolValue());
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setTlsTrustCertsFilePath(Php::Parameters &params) {
    this->config.setTlsTrustCertsFilePath(params[0].stringValue());
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setTlsAllowInsecureConnection(Php::Parameters &params) {
    this->config.setTlsAllowInsecureConnection(params[0].boolValue());
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setAuth(Php::Parameters &params) {
    pulsar::AuthenticationPtr auth = pulsar::AuthTls::create(
        params[0].stringValue(), params[1].stringValue());
    this->config.setAuth(auth);
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setIoThreads(Php::Parameters &params) {
    this->config.setIOThreads(params[0].numericValue());
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setOperationTimeoutSeconds(Php::Parameters &params) {
    this->config.setOperationTimeoutSeconds(params[0].numericValue());
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setMessageListenerThreads(Php::Parameters &params) {
    this->config.setMessageListenerThreads(params[0].numericValue());
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setConcurrentLookupRequest(Php::Parameters &params) {
    this->config.setConcurrentLookupRequest(params[0].numericValue());
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setStatsIntervalInSeconds(Php::Parameters &params) {
    this->config.setStatsIntervalInSeconds(
        static_cast<unsigned int>(params[0].numericValue()));
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setPartitionsUpdateInterval(Php::Parameters &params) {
    this->config.setPartititionsUpdateInterval(
        static_cast<unsigned int>(params[0].numericValue()));
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setConnectionTimeout(Php::Parameters &params) {
    this->config.setConnectionTimeout(params[0].numericValue());
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setFileLogger(Php::Parameters &params) {
    std::string filePath = params[0].stringValue();
    pulsar::Logger::Level level = ::pulsar::Logger::LEVEL_INFO;

    if (params.size() >= 2 && params[1].isNumeric()) {
        switch (params[1].numericValue()) {
            case 0: level = ::pulsar::Logger::LEVEL_DEBUG; break;
            case 1: level = ::pulsar::Logger::LEVEL_INFO;  break;
            case 2: level = ::pulsar::Logger::LEVEL_WARN;  break;
            case 3: level = ::pulsar::Logger::LEVEL_ERROR; break;
            default: break;
        }
    }

    this->config.setLogger(new ::pulsar::FileLoggerFactory(level, filePath));
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

void registerClientConfiguration(Php::Namespace &pulsarNamespace) {
    Php::Class<ClientConfiguration> clientConfiguration("ClientConfiguration");
    clientConfiguration.method<&ClientConfiguration::setUseTls>("setUseTls");
    clientConfiguration.method<&ClientConfiguration::setTlsTrustCertsFilePath>("setTlsTrustCertsFilePath");
    clientConfiguration.method<&ClientConfiguration::setTlsAllowInsecureConnection>("setTlsAllowInsecureConnection");
    clientConfiguration.method<&ClientConfiguration::setAuth>("setAuth");
    clientConfiguration.method<&ClientConfiguration::setIoThreads>("setIoThreads");
    clientConfiguration.method<&ClientConfiguration::setOperationTimeoutSeconds>("setOperationTimeoutSeconds");
    clientConfiguration.method<&ClientConfiguration::setMessageListenerThreads>("setMessageListenerThreads");
    clientConfiguration.method<&ClientConfiguration::setConcurrentLookupRequest>("setConcurrentLookupRequest");
    clientConfiguration.method<&ClientConfiguration::setStatsIntervalInSeconds>("setStatsIntervalInSeconds");
    clientConfiguration.method<&ClientConfiguration::setPartitionsUpdateInterval>("setPartitionsUpdateInterval");
    clientConfiguration.method<&ClientConfiguration::setConnectionTimeout>("setConnectionTimeout");
    clientConfiguration.method<&ClientConfiguration::setFileLogger>("setFileLogger");

    clientConfiguration.property("LOGGER_LEVEL_DEBUG", ::pulsar::Logger::LEVEL_DEBUG, Php::Const);
    clientConfiguration.property("LOGGER_LEVEL_INFO",  ::pulsar::Logger::LEVEL_INFO,  Php::Const);
    clientConfiguration.property("LOGGER_LEVEL_WARN",  ::pulsar::Logger::LEVEL_WARN,  Php::Const);
    clientConfiguration.property("LOGGER_LEVEL_ERROR", ::pulsar::Logger::LEVEL_ERROR, Php::Const);

    pulsarNamespace.add(clientConfiguration);
}
