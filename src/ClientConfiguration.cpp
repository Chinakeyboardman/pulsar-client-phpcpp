/**
 * @docs https://github.com/apache/pulsar/blob/2.8.1/pulsar-client-cpp/lib/ClientConfiguration.cc
 * @docs https://github.com/apache/pulsar/blob/2.8.1/pulsar-client-cpp/include/pulsar/ClientConfiguration.h
 */
#include "ClientConfiguration.h"
#include "Message.h"
#include <pulsar/FileLoggerFactory.h>
#include <pulsar/Logger.h>

#define CLIENT_CONFIGURATION_CLASS_NAME "Pulsar\\ClientConfiguration"

Php::Value ClientConfiguration::setUseTls(Php::Parameters &params) {
    bool flag = params[0];
    this->config.setUseTls(flag);
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setTlsTrustCertsFilePath(Php::Parameters &params) {
    std::string ca = params[0];
    this->config.setTlsTrustCertsFilePath(ca);
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setTlsAllowInsecureConnection(Php::Parameters &params) {
    bool flag = params[0];
    this->config.setTlsAllowInsecureConnection(flag);
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setAuth(Php::Parameters &params) {
    // create(string cert.pem, string key.pem)
    pulsar::AuthenticationPtr auth = pulsar::AuthTls::create(
        params[0].stringValue(),
        params[1].stringValue()
    );
    this->config.setAuth(auth);
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setIoThreads(Php::Parameters &params) {
    int quantity = params[0];
    this->config.setIOThreads(quantity);
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setOperationTimeoutSeconds(Php::Parameters &params) {
    int delay = params[0];
    this->config.setOperationTimeoutSeconds(delay);
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setMessageListenerThreads(Php::Parameters &params) {
    int quantity = params[0];
    this->config.setMessageListenerThreads(quantity);
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setConcurrentLookupRequest(Php::Parameters &params) {
    int quantity = params[0];
    this->config.setConcurrentLookupRequest(quantity);
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setStatsIntervalInSeconds(Php::Parameters &params) {
    unsigned int delay = params[0].numericValue();
    this->config.setStatsIntervalInSeconds(delay);
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setPartitionsUpdateInterval(Php::Parameters &params) {
    unsigned int delay = params[0].numericValue();
    this->config.setPartititionsUpdateInterval(delay);
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setConnectionTimeout(Php::Parameters &params) {
    int delay = params[0];
    this->config.setConnectionTimeout(delay);
    return Php::Object(CLIENT_CONFIGURATION_CLASS_NAME, this);
}

Php::Value ClientConfiguration::setFileLogger(Php::Parameters &params) {
    std::string filePath = params[0];
    pulsar::Logger::Level level;
    if (params.size() == 2 && params[1].isNumeric()) {
        switch (params[1].numericValue()) {
            case 0:
                level = ::pulsar::Logger::LEVEL_DEBUG;
                break;
            case 1:
                level = ::pulsar::Logger::LEVEL_INFO;
                break;
            case 2:
                level = ::pulsar::Logger::LEVEL_WARN;
                break;
            case 3:
                level = ::pulsar::Logger::LEVEL_ERROR;
                break;
            default:
                level = ::pulsar::Logger::LEVEL_INFO;
                break;
        }
    } else {
        level = ::pulsar::Logger::LEVEL_INFO;
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
    clientConfiguration.property("LOGGER_LEVEL_INFO", ::pulsar::Logger::LEVEL_INFO, Php::Const);
    clientConfiguration.property("LOGGER_LEVEL_WARN", ::pulsar::Logger::LEVEL_WARN, Php::Const);
    clientConfiguration.property("LOGGER_LEVEL_ERROR", ::pulsar::Logger::LEVEL_ERROR, Php::Const);

    pulsarNamespace.add(clientConfiguration);
}
