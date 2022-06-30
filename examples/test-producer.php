<?php

use Pulsar\Client;
use Pulsar\ClientConfiguration;
use Pulsar\MessageBuilder;

$config = new ClientConfiguration();
//$config->setFileLogger('/tmp/examples/client.log', ClientConfiguration::LOGGER_LEVEL_INFO);
$client = new Client("pulsar://172.17.0.1:6650", $config);

$producer = $client->createProducer("persistent://prop/r1/ns1/test-topic");

$prop = [
    "a" => 1,
];

$builder = new MessageBuilder();
$builder->setContent("Amazing " . time())
        ->setProperties($prop);

unset($prop);

$message = $builder->setDeliverAfter(5000)->build();
$producer->send($message);
