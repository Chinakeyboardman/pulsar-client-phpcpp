#!/usr/bin/env bash
set -euo pipefail

# Extract .so and .deb from a single Docker build.
# Usage: ./extract-so.sh <php-version> [dockerfile]
# Example: ./extract-so.sh 83
#          ./extract-so.sh 83 docker/php83.Dockerfile

PHP_VERSION="${1:?Usage: $0 <php-version> [dockerfile]}"
DOCKERFILE="${2:-docker/php${PHP_VERSION}.Dockerfile}"
PROJECT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
DIST_DIR="$PROJECT_DIR/dist/php${PHP_VERSION}"
IMAGE_TAG="pulsar-phpcpp:build-php${PHP_VERSION}"

if [ ! -f "$PROJECT_DIR/$DOCKERFILE" ]; then
    echo "ERROR: Dockerfile not found: $DOCKERFILE"
    exit 1
fi

echo "Building PHP $PHP_VERSION from $DOCKERFILE..."
docker build -f "$DOCKERFILE" -t "$IMAGE_TAG" "$PROJECT_DIR"

echo "Extracting artifacts to $DIST_DIR..."
mkdir -p "$DIST_DIR"

CONTAINER=$(docker create "$IMAGE_TAG")

docker cp "$CONTAINER:/tmp/pulsar-client-phpcpp/pulsar-phpcpp.so" "$DIST_DIR/pulsar-phpcpp.so"

docker cp "$CONTAINER:/tmp/pulsar-client-phpcpp/php${PHP_VERSION}-pulsar-client.deb" "$DIST_DIR/" 2>/dev/null || \
    echo "  (no .deb found, skipping)"

docker rm "$CONTAINER" > /dev/null

echo "Done. Artifacts:"
ls -lh "$DIST_DIR/"
