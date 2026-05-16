<?php
/**
 * Integration test: negative acknowledge triggers message redelivery.
 *
 * Requires a running Pulsar broker at PULSAR_SERVICE_URL.
 */

$serviceUrl = getenv('PULSAR_SERVICE_URL') ?: 'pulsar://pulsar:6650';
$topic = 'persistent://public/default/nack-test-' . uniqid();
$subscription = 'nack-sub';

echo "=== Negative Ack Integration Test ===\n";
echo "Broker: $serviceUrl\n";
echo "Topic:  $topic\n\n";

$client = new Pulsar\Client($serviceUrl);

$producer = $client->createProducer($topic);
$message = (new Pulsar\MessageBuilder())
    ->setContent("nack-message")
    ->build();
$producer->send($message);
echo "  Produced: nack-message\n";
$producer->close();

$config = new Pulsar\ConsumerConfiguration();
$config->setSubscriptionInitialPosition(Pulsar\ConsumerConfiguration::InitialPositionEarliest)
       ->setNegativeAckRedeliveryDelayMs(1000);

$consumer = $client->subscribe($topic, $subscription, $config);

$msg1 = $consumer->receive(10000);
echo "  First receive: " . $msg1->getDataAsString() . "\n";
$consumer->negativeAcknowledge($msg1);
echo "  Negative acknowledged, waiting for redelivery...\n";

$msg2 = $consumer->receive(15000);
echo "  Redelivered: " . $msg2->getDataAsString() . "\n";
$consumer->acknowledge($msg2);

$consumer->close();
$client->close();

if ($msg1->getDataAsString() === $msg2->getDataAsString()) {
    echo "\nPASS: Message was redelivered after negative ack.\n";
    exit(0);
} else {
    echo "\nFAIL: Redelivered message does not match.\n";
    exit(1);
}
