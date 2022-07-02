#include "Producer.h"
#include "Message.h"

Php::Value Producer::send(Php::Parameters &params) {
    auto message = (Message *)(params[0].implementation());
    // this->producer.send(message->message);
    pulsar::Result result = this->producer.send(message->message);
    
    if (result != pulsar::ResultOk) {
        // LOG_ERROR("Error creating producer: " << result);
        return -1;
    } else {
        return 1;
    }
}

void registerProducer(Php::Namespace &pulsarNamespace) {
    Php::Class<Producer> producer("Producer");
    producer.method<&Producer::send>("send");
    pulsarNamespace.add(producer);
}
