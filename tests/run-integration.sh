#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
COMPOSE_FILE="$PROJECT_DIR/docker/docker-compose.yml"

echo "=== Starting Pulsar standalone and PHP test runner ==="

cd "$PROJECT_DIR"
docker compose -f "$COMPOSE_FILE" up --build --abort-on-container-exit --exit-code-from php-tests
EXIT_CODE=$?

echo "=== Cleaning up ==="
docker compose -f "$COMPOSE_FILE" down -v

if [ "$EXIT_CODE" -eq 0 ]; then
    echo "All integration tests passed."
else
    echo "Integration tests failed with exit code $EXIT_CODE."
fi

exit $EXIT_CODE
