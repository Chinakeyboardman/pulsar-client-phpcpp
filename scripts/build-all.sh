#!/usr/bin/env bash
set -euo pipefail

# Build the extension for all supported PHP versions and extract
# .so and .deb files into dist/phpXX/.

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

PHP_VERSIONS=(74 80 81 82 83 84)

echo "========================================"
echo " Building pulsar-phpcpp for all PHP versions"
echo "========================================"

PASS=()
FAIL=()

for ver in "${PHP_VERSIONS[@]}"; do
    echo ""
    echo "--- PHP $ver ---"
    if bash "$SCRIPT_DIR/extract-so.sh" "$ver"; then
        PASS+=("$ver")
    else
        echo "WARN: PHP $ver build failed"
        FAIL+=("$ver")
    fi
done

echo ""
echo "========================================"
echo " Build Summary"
echo "========================================"
echo "Passed: ${PASS[*]:-none}"
echo "Failed: ${FAIL[*]:-none}"
echo ""

if [ "${#FAIL[@]}" -gt 0 ]; then
    echo "Some builds failed. Check output above."
    exit 1
fi

echo "All builds succeeded. Artifacts in $PROJECT_DIR/dist/"
ls -R "$PROJECT_DIR/dist/"
