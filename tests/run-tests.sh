#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PHPT_DIR="$SCRIPT_DIR/phpt"

if [ ! -d "$PHPT_DIR" ]; then
    echo "ERROR: phpt directory not found at $PHPT_DIR"
    exit 1
fi

# run-tests.php writes temp files (.php, .log, …) next to each .phpt file.
# When the source tree is mounted read-only (e.g. Docker `:ro`), this fails.
# Copy tests to a writable tmpdir so run-tests.php can work normally.
if [ ! -w "$PHPT_DIR" ]; then
    WORK_DIR="$(mktemp -d)"
    cp -a "$PHPT_DIR" "$WORK_DIR/phpt"
    PHPT_DIR="$WORK_DIR/phpt"
    echo "Tests copied to writable directory: $PHPT_DIR"
fi

PHP_BIN="${PHP_BIN:-php}"
RUN_TESTS="$("$PHP_BIN" -r 'echo PHP_BINARY;' | xargs dirname)/../lib/php/build/run-tests.php"

if [ ! -f "$RUN_TESTS" ]; then
    RUN_TESTS=$(find /usr/local/lib/php -name run-tests.php 2>/dev/null | head -1)
fi

if [ -f "$RUN_TESTS" ]; then
    echo "Using run-tests.php at: $RUN_TESTS"
    NO_INTERACTION=1 TEST_PHP_EXECUTABLE="$("$PHP_BIN" -r 'echo PHP_BINARY;')" "$PHP_BIN" "$RUN_TESTS" "$PHPT_DIR"
else
    echo "run-tests.php not found, running phpt files directly..."
    PASS=0
    FAIL=0
    for test in "$PHPT_DIR"/*.phpt; do
        name=$(basename "$test")
        expected=$("$PHP_BIN" -r "
            \$content = file_get_contents('$test');
            if (preg_match('/--EXPECT--\n(.*)/s', \$content, \$m)) echo trim(\$m[1]);
        ")
        actual=$("$PHP_BIN" -r "
            \$content = file_get_contents('$test');
            if (preg_match('/--FILE--\n(.*?)--EXPECT--/s', \$content, \$m)) {
                \$code = trim(\$m[1]);
                \$code = preg_replace('/^<\?php/', '', \$code);
                eval(\$code);
            }
        " 2>&1) || true

        if [ "$expected" = "$actual" ]; then
            echo "PASS: $name"
            PASS=$((PASS + 1))
        else
            echo "FAIL: $name"
            echo "  Expected: $(echo "$expected" | head -3)"
            echo "  Actual:   $(echo "$actual" | head -3)"
            FAIL=$((FAIL + 1))
        fi
    done
    echo ""
    echo "Results: $PASS passed, $FAIL failed"
    [ "$FAIL" -eq 0 ] || exit 1
fi
