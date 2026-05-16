<?php
/**
 * Integration test: sendAsync + flush, verify delivery via consumer.
 *
 * Requires a running Pulsar broker at PULSAR_SERVICE_URL.
 */

$serviceUrl = getenv('PULSAR_SERVICE_URL') ?: 'pulsar://pulsar:6650';
$topic = 'persistent://public/default/async-test-' . uniqid();
$subscription = 'async-sub';
$messageCount = 20;

echo "=== Async Send Integration Test ===\n";
echo "Broker: $serviceUrl\n";
echo "Topic:  $topic\n";
echo "Count:  $messageCount\n\n";

$client = new Pulsar\Client($serviceUrl);

$producer = $client->createProducer($topic);

for ($i = 0; $i < $messageCount; $i++) {
    $message = (new Pulsar\MessageBuilder())
        ->setContent("async-$i")
        ->build();
    $producer->sendAsync($message);
}
echo "  Enqueued $messageCount messages via sendAsync.\n";

$producer->flush();
echo "  Flush completed.\n";
$producer->close();

$config = new Pulsar\ConsumerConfiguration();
$config->setSubscriptionInitialPosition(Pulsar\ConsumerConfiguration::InitialPositionEarliest);

$consumer = $client->subscribe($topic, $subscription, $config);

$received = 0;
for ($i = 0; $i < $messageCount; $i++) {
    $message = $consumer->receive(10000);
    $consumer->acknowledge($message);
    $received++;
}
$consumer->close();
$client->close();

if ($received === $messageCount) {
    echo "\nPASS: Received all $messageCount async messages.\n";
    exit(0);
} else {
    echo "\nFAIL: Expected $messageCount, received $received.\n";
    exit(1);
}
