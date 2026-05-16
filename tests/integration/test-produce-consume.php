<?php
/**
 * Integration test: produce N messages, then consume and verify all received.
 *
 * Requires a running Pulsar broker at PULSAR_SERVICE_URL (default: pulsar://pulsar:6650).
 * Exit code 0 on success, 1 on failure.
 */

$serviceUrl = getenv('PULSAR_SERVICE_URL') ?: 'pulsar://pulsar:6650';
$topic = 'persistent://public/default/integration-test-' . uniqid();
$subscription = 'test-sub';
$messageCount = 10;

echo "=== Produce/Consume Integration Test ===\n";
echo "Broker: $serviceUrl\n";
echo "Topic:  $topic\n";
echo "Count:  $messageCount\n\n";

$client = new Pulsar\Client($serviceUrl);

$producer = $client->createProducer($topic);

$sentPayloads = [];
for ($i = 0; $i < $messageCount; $i++) {
    $payload = "message-$i-" . time();
    $message = (new Pulsar\MessageBuilder())
        ->setContent($payload)
        ->setProperty("index", (string)$i)
        ->build();
    $producer->send($message);
    $sentPayloads[] = $payload;
    echo "  Sent: $payload\n";
}
$producer->close();

$config = new Pulsar\ConsumerConfiguration();
$config->setConsumerType(Pulsar\Consumer::ConsumerExclusive)
       ->setSubscriptionInitialPosition(Pulsar\ConsumerConfiguration::InitialPositionEarliest);

$consumer = $client->subscribe($topic, $subscription, $config);

$receivedPayloads = [];
for ($i = 0; $i < $messageCount; $i++) {
    $message = $consumer->receive(10000);
    $data = $message->getDataAsString();
    $receivedPayloads[] = $data;
    echo "  Received: $data (index=" . $message->getProperty("index") . ")\n";
    $consumer->acknowledge($message);
}
$consumer->close();
$client->close();

if ($sentPayloads === $receivedPayloads) {
    echo "\nPASS: All $messageCount messages received in order.\n";
    exit(0);
} else {
    echo "\nFAIL: Sent and received payloads do not match.\n";
    exit(1);
}
