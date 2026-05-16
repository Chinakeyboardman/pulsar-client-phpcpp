--TEST--
Client can be constructed with a service URL
--FILE--
<?php
use Pulsar\Client;
use Pulsar\ClientConfiguration;

$client = new Client("pulsar://localhost:6650");
echo get_class($client) . "\n";

$config = new ClientConfiguration();
$client2 = new Client("pulsar://localhost:6650", $config);
echo get_class($client2) . "\n";

echo "OK\n";
?>
--EXPECT--
Pulsar\Client
Pulsar\Client
OK
