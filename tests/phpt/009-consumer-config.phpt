--TEST--
ConsumerConfiguration fluent setters and constants
--FILE--
<?php
use Pulsar\Consumer;
use Pulsar\ConsumerConfiguration;

$config = new ConsumerConfiguration();
echo get_class($config) . "\n";

$result = $config->setConsumerType(Consumer::ConsumerShared);
echo get_class($result) . "\n";

$result = $config->setConsumerName("my-consumer");
echo get_class($result) . "\n";

$result = $config->setSubscriptionInitialPosition(ConsumerConfiguration::InitialPositionEarliest);
echo get_class($result) . "\n";

$result = $config->setReceiverQueueSize(500);
echo get_class($result) . "\n";

echo "ConsumerExclusive=" . Consumer::ConsumerExclusive . "\n";
echo "ConsumerShared=" . Consumer::ConsumerShared . "\n";
echo "ConsumerFailover=" . Consumer::ConsumerFailover . "\n";
echo "ConsumerKeyShared=" . Consumer::ConsumerKeyShared . "\n";
echo "InitialPositionLatest=" . ConsumerConfiguration::InitialPositionLatest . "\n";
echo "InitialPositionEarliest=" . ConsumerConfiguration::InitialPositionEarliest . "\n";
?>
--EXPECT--
Pulsar\ConsumerConfiguration
Pulsar\ConsumerConfiguration
Pulsar\ConsumerConfiguration
Pulsar\ConsumerConfiguration
Pulsar\ConsumerConfiguration
ConsumerExclusive=0
ConsumerShared=1
ConsumerFailover=2
ConsumerKeyShared=3
InitialPositionLatest=0
InitialPositionEarliest=1
