<?php
/**
 * Integration test: create reader from earliest, verify messages can be read.
 *
 * Requires a running Pulsar broker at PULSAR_SERVICE_URL.
 */

$serviceUrl = getenv('PULSAR_SERVICE_URL') ?: 'pulsar://pulsar:6650';
$topic = 'persistent://public/default/reader-test-' . uniqid();
$messageCount = 5;

echo "=== Reader Integration Test ===\n";
echo "Broker: $serviceUrl\n";
echo "Topic:  $topic\n\n";

$client = new Pulsar\Client($serviceUrl);

$producer = $client->createProducer($topic);
for ($i = 0; $i < $messageCount; $i++) {
    $message = (new Pulsar\MessageBuilder())
        ->setContent("reader-msg-$i")
        ->build();
    $producer->send($message);
    echo "  Produced: reader-msg-$i\n";
}
$producer->close();

$reader = $client->createReader($topic, Pulsar\MessageId::earliest());

$readCount = 0;
for ($i = 0; $i < $messageCount; $i++) {
    $message = $reader->readNext(10000);
    $data = $message->getDataAsString();
    echo "  Read: $data\n";

    $msgId = $message->getMessageId();
    echo "  MessageId class: " . get_class($msgId) . "\n";

    $readCount++;
}
$reader->close();
$client->close();

if ($readCount === $messageCount) {
    echo "\nPASS: Reader read all $messageCount messages.\n";
    exit(0);
} else {
    echo "\nFAIL: Expected $messageCount, read $readCount.\n";
    exit(1);
}
