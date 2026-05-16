# pulsar-client-phpcpp

A PHP extension for [Apache Pulsar](https://pulsar.apache.org/) built on top of
the official [Pulsar C++ client](https://github.com/apache/pulsar-client-cpp)
and [PHP-CPP](https://www.php-cpp.com/).

## Features

- **Producer** &ndash; synchronous and async (fire-and-forget) message publishing
- **Consumer** &ndash; exclusive, shared, failover, and key-shared subscriptions
- **Reader** &ndash; non-subscription topic reading from any position
- **MessageBuilder** &ndash; fluent API for constructing messages with properties,
  keys, delayed delivery, and event timestamps
- **TLS & Authentication** &ndash; TLS encryption and mTLS auth via
  ClientConfiguration
- **Batching & Compression** &ndash; LZ4 / ZLib / ZSTD / Snappy compression and
  configurable batching through ProducerConfiguration
- **PHP 7.4 &ndash; 8.4** support

## Requirements

| Dependency | Minimum version |
|---|---|
| PHP | 7.4 |
| [Apache Pulsar C++ client](https://pulsar.apache.org/docs/client-libraries-cpp/) | 2.8.x |
| [PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP) | 2.x (use [NobletSolutions fork](https://github.com/NobletSolutions/PHP-CPP) `php80` branch for PHP 8.0+) |
| g++ with C++17 support | GCC 7+ or Clang 5+ |

## Installation

### Using Docker (recommended)

Pre-built Dockerfiles are provided for each supported PHP version:

```bash
# Build for PHP 8.3
docker build -f Dockerfile-83 -t pulsar-phpcpp:8.3 .

# Verify the extension is loaded
docker run --rm pulsar-phpcpp:8.3 php -m | grep pulsar
```

### Manual build

```bash
# 1. Install the Pulsar C++ client (Debian/Ubuntu)
dpkg -i apache-pulsar-client.deb apache-pulsar-client-dev.deb

# 2. Install PHP-CPP
git clone https://github.com/NobletSolutions/PHP-CPP.git
cd PHP-CPP && git checkout php80 && make && sudo make install

# 3. Build the extension
cd pulsar-client-phpcpp
make
sudo make install

# 4. Verify
php -m | grep pulsar
```

### Custom library paths

If PHP-CPP or the Pulsar client are installed in non-standard locations:

```bash
make PHPCPP_DIR=/opt/phpcpp PULSAR_DIR=/opt/pulsar
```

## Quick start

### Producer

```php
<?php
use Pulsar\Client;
use Pulsar\ClientConfiguration;
use Pulsar\MessageBuilder;
use Pulsar\ProducerConfiguration;

$config = new ClientConfiguration();
$client = new Client("pulsar://localhost:6650", $config);

$prodConf = new ProducerConfiguration();
$prodConf->setBatchingEnabled(true)
         ->setCompressionType(ProducerConfiguration::CompressionLZ4);

$producer = $client->createProducer("persistent://public/default/my-topic", $prodConf);

$message = (new MessageBuilder())
    ->setContent("Hello Pulsar!")
    ->setProperty("key", "value")
    ->build();

$producer->send($message);
$producer->close();
$client->close();
```

### Consumer

```php
<?php
use Pulsar\Client;
use Pulsar\Consumer;
use Pulsar\ConsumerConfiguration;

$client = new Client("pulsar://localhost:6650");

$config = new ConsumerConfiguration();
$config->setConsumerType(Consumer::ConsumerShared)
       ->setSubscriptionInitialPosition(ConsumerConfiguration::InitialPositionEarliest);

$consumer = $client->subscribe(
    "persistent://public/default/my-topic",
    "my-subscription",
    $config
);

while (true) {
    $message = $consumer->receive();
    echo $message->getDataAsString() . "\n";
    echo "Topic: " . $message->getTopicName() . "\n";
    echo "Published at: " . $message->getPublishTimestamp() . "\n";
    $consumer->acknowledge($message);
}
```

### Reader

```php
<?php
use Pulsar\Client;
use Pulsar\MessageId;

$client = new Client("pulsar://localhost:6650");
$reader = $client->createReader(
    "persistent://public/default/my-topic",
    MessageId::earliest()
);

while ($reader->hasMessageAvailable()) {
    $message = $reader->readNext(5000); // 5s timeout
    echo $message->getDataAsString() . "\n";
}

$reader->close();
$client->close();
```

## API Reference

### Pulsar\Client

| Method | Description |
|---|---|
| `__construct(string $serviceUrl [, ClientConfiguration $config])` | Connect to a Pulsar cluster |
| `createProducer(string $topic [, ProducerConfiguration $config]): Producer` | Create a message producer |
| `subscribe(string $topic, string $subscription [, ConsumerConfiguration $config]): Consumer` | Subscribe to a topic |
| `createReader(string $topic, MessageId $startMessageId): Reader` | Create a topic reader |
| `close(): void` | Close the client |

### Pulsar\Producer

| Method | Description |
|---|---|
| `send(Message $msg): void` | Synchronously send a message (throws on failure) |
| `sendAsync(Message $msg): void` | Asynchronously enqueue a message |
| `flush(): void` | Block until all async messages are sent |
| `close(): void` | Close the producer |
| `getTopic(): string` | Get the producer's topic |

### Pulsar\Consumer

| Method | Description |
|---|---|
| `receive([int $timeoutMs]): Message` | Receive the next message |
| `acknowledge(Message $msg): void` | Acknowledge a message |
| `negativeAcknowledge(Message $msg): void` | Negative-ack to trigger redelivery |
| `close(): void` | Close the consumer |

### Pulsar\Reader

| Method | Description |
|---|---|
| `readNext([int $timeoutMs]): Message` | Read the next message |
| `hasMessageAvailable(): bool` | Check for available messages |
| `close(): void` | Close the reader |
| `getTopic(): string` | Get the reader's topic |

### Pulsar\Message

| Method | Description |
|---|---|
| `getDataAsString(): string` | Get message payload |
| `getMessageId(): MessageId` | Get the message ID |
| `getProperties(): array` | Get all properties |
| `hasProperty(string $key): bool` | Check for a property |
| `getProperty(string $key): string` | Get a property value |
| `getPublishTimestamp(): int` | Publish time (epoch ms) |
| `getEventTimestamp(): int` | Event time (epoch ms) |
| `getTopicName(): string` | Topic name |
| `getPartitionKey(): string` | Partition key |
| `hasPartitionKey(): bool` | Whether a partition key is set |
| `getOrderingKey(): string` | Ordering key |
| `hasOrderingKey(): bool` | Whether an ordering key is set |
| `getLength(): int` | Payload length in bytes |

### Pulsar\MessageBuilder

All setter methods return `$this` for chaining.

| Method | Description |
|---|---|
| `setContent(string $data)` | Set message payload |
| `setProperty(string $key, string $value)` | Add a property |
| `setProperties(array $map)` | Set all properties |
| `setPartitionKey(string $key)` | Set partition routing key |
| `setOrderingKey(string $key)` | Set ordering key |
| `setDeliverAfter(int $delayMs)` | Delay delivery by N ms |
| `setDeliverAt(int $timestampMs)` | Deliver at a specific time |
| `setEventTimestamp(int $timestampMs)` | Set event timestamp |
| `setSequenceId(int $id)` | Set sequence ID |
| `disableReplication(bool $flag)` | Disable geo-replication |
| `build(): Message` | Build the final Message |

### Pulsar\MessageId

| Method | Description |
|---|---|
| `earliest(): MessageId` | Earliest available message position |
| `latest(): MessageId` | Latest (newest) message position |
| `serialize(): string` | Serialize to binary string |
| `deserialize(string $data): MessageId` | Deserialize from binary |
| `getTopicName(): string` | Associated topic name |
| `setTopicName(string $name): void` | Set topic name |

### Pulsar\ClientConfiguration

| Method | Description |
|---|---|
| `setUseTls(bool $flag)` | Enable TLS |
| `setTlsTrustCertsFilePath(string $path)` | Set CA certificate path |
| `setTlsAllowInsecureConnection(bool $flag)` | Allow insecure TLS |
| `setAuth(string $certPath, string $keyPath)` | Configure mTLS authentication |
| `setIoThreads(int $n)` | Set I/O thread count |
| `setOperationTimeoutSeconds(int $seconds)` | Set operation timeout |
| `setMessageListenerThreads(int $n)` | Set listener thread count |
| `setConcurrentLookupRequest(int $n)` | Set concurrent lookup limit |
| `setStatsIntervalInSeconds(int $seconds)` | Set stats interval |
| `setPartitionsUpdateInterval(int $seconds)` | Set partition update interval |
| `setConnectionTimeout(int $ms)` | Set connection timeout |
| `setFileLogger(string $path [, int $level])` | Enable file logging |

### Pulsar\ProducerConfiguration

| Method | Description |
|---|---|
| `setSendTimeout(int $ms)` | Send timeout in milliseconds |
| `setCompressionType(int $type)` | Compression algorithm (see constants) |
| `setMaxPendingMessages(int $n)` | Max pending message queue size |
| `setBatchingEnabled(bool $flag)` | Enable/disable batching |
| `setBatchingMaxMessages(int $n)` | Max messages per batch |
| `setBatchingMaxPublishDelayMs(int $ms)` | Max batch publish delay |
| `setBlockIfQueueFull(bool $flag)` | Block on full queue |
| `setProducerName(string $name)` | Set producer name |

### Pulsar\ConsumerConfiguration

| Method | Description |
|---|---|
| `setConsumerType(int $type)` | Subscription type (see Consumer constants) |
| `setConsumerName(string $name)` | Consumer name |
| `setSubscriptionInitialPosition(int $pos)` | Initial position (see constants) |
| `setReceiverQueueSize(int $size)` | Receiver queue size |
| `setAckGroupingTimeMs(int $ms)` | Ack grouping time |
| `setNegativeAckRedeliveryDelayMs(int $ms)` | Negative ack redelivery delay |

## License

Licensed under the [Apache License 2.0](LICENSE).

## Acknowledgements

This project is based on prior work by
[oraoto/pulsar-client-phpcpp](https://github.com/oraoto/pulsar-client-phpcpp).
