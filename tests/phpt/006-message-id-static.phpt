--TEST--
MessageId::earliest() and MessageId::latest() return MessageId objects
--FILE--
<?php
use Pulsar\MessageId;

$earliest = MessageId::earliest();
echo get_class($earliest) . "\n";

$latest = MessageId::latest();
echo get_class($latest) . "\n";

echo "OK\n";
?>
--EXPECT--
Pulsar\MessageId
Pulsar\MessageId
OK
