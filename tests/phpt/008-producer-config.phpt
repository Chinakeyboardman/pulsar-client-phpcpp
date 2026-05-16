--TEST--
ProducerConfiguration fluent setters and constants
--FILE--
<?php
use Pulsar\ProducerConfiguration;

$config = new ProducerConfiguration();
echo get_class($config) . "\n";

$result = $config->setSendTimeout(5000);
echo get_class($result) . "\n";

$result = $config->setBatchingEnabled(true);
echo get_class($result) . "\n";

$result = $config->setBatchingMaxMessages(100);
echo get_class($result) . "\n";

$result = $config->setMaxPendingMessages(500);
echo get_class($result) . "\n";

$result = $config->setBlockIfQueueFull(true);
echo get_class($result) . "\n";

$result = $config->setProducerName("test-producer");
echo get_class($result) . "\n";

echo "CompressionNone=" . ProducerConfiguration::CompressionNone . "\n";
echo "CompressionLZ4=" . ProducerConfiguration::CompressionLZ4 . "\n";

$result = $config->setCompressionType(ProducerConfiguration::CompressionLZ4);
echo get_class($result) . "\n";
?>
--EXPECT--
Pulsar\ProducerConfiguration
Pulsar\ProducerConfiguration
Pulsar\ProducerConfiguration
Pulsar\ProducerConfiguration
Pulsar\ProducerConfiguration
Pulsar\ProducerConfiguration
Pulsar\ProducerConfiguration
CompressionNone=0
CompressionLZ4=1
Pulsar\ProducerConfiguration
