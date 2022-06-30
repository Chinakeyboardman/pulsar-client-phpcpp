#pragma once

#include <phpcpp.h>
#include <pulsar/ClientConfiguration.h>

class ClientConfiguration : public Php::Base {

  public:
    pulsar::ClientConfiguration config;

    ClientConfiguration(){};

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
