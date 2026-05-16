--TEST--
Message property getters
--FILE--
<?php
use Pulsar\MessageBuilder;

$builder = new MessageBuilder();
$message = $builder
    ->setContent("test payload")
    ->setProperty("env", "staging")
    ->setProperties(["region" => "us-east"])
    ->build();

echo $message->getDataAsString() . "\n";
echo "length: " . $message->getLength() . "\n";

$props = $message->getProperties();
echo "env=" . $props["env"] . "\n";
echo "region=" . $props["region"] . "\n";

echo "hasProperty(env): " . ($message->hasProperty("env") ? "yes" : "no") . "\n";
echo "hasProperty(missing): " . ($message->hasProperty("missing") ? "yes" : "no") . "\n";
echo "getProperty(env): " . $message->getProperty("env") . "\n";
?>
--EXPECT--
test payload
length: 12
env=staging
region=us-east
hasProperty(env): yes
hasProperty(missing): no
getProperty(env): staging
