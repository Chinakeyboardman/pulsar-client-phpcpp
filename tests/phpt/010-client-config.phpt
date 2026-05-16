--TEST--
ClientConfiguration fluent setters and constants
--FILE--
<?php
use Pulsar\ClientConfiguration;

$config = new ClientConfiguration();
echo get_class($config) . "\n";

$result = $config->setUseTls(false);
echo get_class($result) . "\n";

$result = $config->setIoThreads(4);
echo get_class($result) . "\n";

$result = $config->setOperationTimeoutSeconds(30);
echo get_class($result) . "\n";

$result = $config->setMessageListenerThreads(2);
echo get_class($result) . "\n";

$result = $config->setConcurrentLookupRequest(10);
echo get_class($result) . "\n";

$result = $config->setConnectionTimeout(5000);
echo get_class($result) . "\n";

echo "LOGGER_LEVEL_DEBUG=" . ClientConfiguration::LOGGER_LEVEL_DEBUG . "\n";
echo "LOGGER_LEVEL_INFO=" . ClientConfiguration::LOGGER_LEVEL_INFO . "\n";
echo "LOGGER_LEVEL_WARN=" . ClientConfiguration::LOGGER_LEVEL_WARN . "\n";
echo "LOGGER_LEVEL_ERROR=" . ClientConfiguration::LOGGER_LEVEL_ERROR . "\n";
?>
--EXPECT--
Pulsar\ClientConfiguration
Pulsar\ClientConfiguration
Pulsar\ClientConfiguration
Pulsar\ClientConfiguration
Pulsar\ClientConfiguration
Pulsar\ClientConfiguration
Pulsar\ClientConfiguration
LOGGER_LEVEL_DEBUG=0
LOGGER_LEVEL_INFO=1
LOGGER_LEVEL_WARN=2
LOGGER_LEVEL_ERROR=3
