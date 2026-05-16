# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/),
and this project adheres to [Semantic Versioning](https://semver.org/).

## [2.0.0] - 2026-05-14

### Changed

- **License**: Migrated from MIT to Apache License 2.0.
- **Error handling**: All methods now throw `\Exception` on failure instead
  of returning error codes (`-1` / `1`).
- **Producer::send()**: Returns `void` and throws on error (was returning int).
- **C++ standard**: Upgraded from C++11 to C++17.
- **Include guards**: Replaced `#pragma once` with `#ifndef` guards in all headers.
- **MessageBuilder**: Fixed method registration typos
  (`setPartiionKey` -> `setPartitionKey`, `sequenceId` -> `setSequenceId`).
- **MessageBuilder::setEventTimestamp()**: Now correctly calls
  `builder.setEventTimestamp()` instead of `builder.setDeliverAt()`.
- **MessageId::serialize()**: Fixed memory leak (was allocating string
  with `new` and never freeing).
- **Dockerfiles**: Improved with proper `apt-get` cleanup, `php-config`-based
  extension directory detection, and post-build verification.
- **Makefile**: Added `install` target, `PHPCPP_DIR`/`PULSAR_DIR` variables.

### Added

- **MessageId**: Now registered in the extension (was previously orphaned).
- **ProducerConfiguration**: New class with `setSendTimeout`,
  `setCompressionType`, `setMaxPendingMessages`, `setBatchingEnabled`,
  `setBatchingMaxMessages`, `setBatchingMaxPublishDelayMs`,
  `setBlockIfQueueFull`, `setProducerName`, and compression type constants.
- **Reader**: New class with `readNext`, `hasMessageAvailable`, `close`,
  `getTopic`.
- **Client::createReader()**: Create a reader starting from a MessageId.
- **Client::close()**: Properly close client and free resources.
- **Producer::sendAsync()**: Fire-and-forget async message sending.
- **Producer::flush()**: Wait for all pending async messages.
- **Producer::close()**: Close the producer.
- **Producer::getTopic()**: Get the producer's topic name.
- **Consumer::negativeAcknowledge()**: Trigger message redelivery.
- **Consumer::close()**: Close the consumer.
- **Consumer::receive()**: Now supports optional timeout parameter.
- **ConsumerConfiguration**: Added `setConsumerName`,
  `setSubscriptionInitialPosition`, `setReceiverQueueSize`,
  `setAckGroupingTimeMs`, `setNegativeAckRedeliveryDelayMs`,
  and initial position constants.
- **Message**: Expanded with `getMessageId`, `getProperties`, `hasProperty`,
  `getProperty`, `getPublishTimestamp`, `getEventTimestamp`, `getTopicName`,
  `getPartitionKey`, `hasPartitionKey`, `getOrderingKey`, `hasOrderingKey`,
  `getLength`.
- **PHP 8.2 / 8.3 / 8.4**: Added Dockerfiles for building on newer PHP.
- **GitHub Actions CI**: Build matrix for PHP 7.4 through 8.4.
- **PECL packaging**: Added `config.m4` and `package.xml`.
- **NOTICE**: Attribution file for Apache compliance.
- **CONTRIBUTING.md**: Contributor guidelines.

## [1.0.0] - 2022-01-01

Initial release based on [oraoto/pulsar-client-phpcpp](https://github.com/oraoto/pulsar-client-phpcpp).

- Basic Producer and Consumer support
- MessageBuilder with properties, keys, delayed delivery
- ClientConfiguration with TLS, auth, timeouts, logging
- ConsumerConfiguration with consumer type
- PHP 7.4, 8.0, 8.1 support via Dockerfiles
