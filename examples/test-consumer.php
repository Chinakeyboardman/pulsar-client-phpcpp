<?php

use Pulsar\Client;
use Pulsar\Consumer;
use Pulsar\ConsumerConfiguration;
use Pulsar\MessageBuilder;

$client = new Client("pulsar://172.17.0.1:6650");

$config = new ConsumerConfiguration();
$config->setConsumerType(Consumer::ConsumerShared);

$consumer = $client->subscribe("persistent://prop/r1/ns1/test-topic", "consumer-1", $config);

while (true) {
    $message = $consumer->receive();
    var_dump($message->getDataAsString());
    $consumer->acknowledge($message);
}
