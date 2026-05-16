--TEST--
MessageId serialize and deserialize roundtrip
--FILE--
<?php
use Pulsar\MessageId;

$original = MessageId::earliest();
$serialized = $original->serialize();
echo "serialized type: " . gettype($serialized) . "\n";
echo "serialized length > 0: " . (strlen($serialized) > 0 ? "yes" : "no") . "\n";

$restored = MessageId::deserialize($serialized);
echo get_class($restored) . "\n";

$reserialized = $restored->serialize();
echo "roundtrip match: " . ($serialized === $reserialized ? "yes" : "no") . "\n";
?>
--EXPECT--
serialized type: string
serialized length > 0: yes
Pulsar\MessageId
roundtrip match: yes
