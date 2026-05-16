--TEST--
Check that pulsar-phpcpp extension is loaded
--FILE--
<?php
var_dump(extension_loaded('pulsar-phpcpp'));
?>
--EXPECT--
bool(true)
