--TEST--
MessageBuilder fluent API and build()
--FILE--
<?php
use Pulsar\MessageBuilder;
use Pulsar\Message;

$builder = new MessageBuilder();
$result = $builder->setContent("hello world");
echo get_class($result) . "\n";

$result = $builder->setProperty("key", "value");
echo get_class($result) . "\n";

$result = $builder->setProperties(["a" => "1", "b" => "2"]);
echo get_class($result) . "\n";

$message = $builder->build();
echo get_class($message) . "\n";
echo $message->getDataAsString() . "\n";
?>
--EXPECT--
Pulsar\MessageBuilder
Pulsar\MessageBuilder
Pulsar\MessageBuilder
Pulsar\Message
hello world
