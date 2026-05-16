--TEST--
Verify all Pulsar namespace classes exist
--FILE--
<?php
$classes = [
    'Pulsar\Client',
    'Pulsar\ClientConfiguration',
    'Pulsar\Consumer',
    'Pulsar\ConsumerConfiguration',
    'Pulsar\Message',
    'Pulsar\MessageBuilder',
    'Pulsar\MessageId',
    'Pulsar\Producer',
    'Pulsar\ProducerConfiguration',
    'Pulsar\Reader',
];

foreach ($classes as $class) {
    echo $class . ': ' . (class_exists($class) ? 'yes' : 'no') . "\n";
}
?>
--EXPECT--
Pulsar\Client: yes
Pulsar\ClientConfiguration: yes
Pulsar\Consumer: yes
Pulsar\ConsumerConfiguration: yes
Pulsar\Message: yes
Pulsar\MessageBuilder: yes
Pulsar\MessageId: yes
Pulsar\Producer: yes
Pulsar\ProducerConfiguration: yes
Pulsar\Reader: yes
