dnl config.m4 for extension pulsar-phpcpp
dnl
dnl Licensed to the Apache Software Foundation (ASF) under one
dnl or more contributor license agreements.  See the NOTICE file
dnl distributed with this work for additional information
dnl regarding copyright ownership.
dnl

PHP_ARG_WITH([pulsar],
  [for Apache Pulsar support],
  [AS_HELP_STRING([--with-pulsar],
    [Include Apache Pulsar client support])])

if test "$PHP_PULSAR" != "no"; then

  dnl Check for the Pulsar C++ client library
  SEARCH_PATH="/usr/local /usr /opt/pulsar"
  SEARCH_FOR="/include/pulsar/Client.h"
  AC_MSG_CHECKING([for pulsar-client-cpp])

  for i in $PHP_PULSAR $SEARCH_PATH; do
    if test -r $i/$SEARCH_FOR; then
      PULSAR_DIR=$i
      AC_MSG_RESULT(found in $i)
      break
    fi
  done

  if test -z "$PULSAR_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please install the Apache Pulsar C++ client library (libpulsar)])
  fi

  PHP_ADD_INCLUDE($PULSAR_DIR/include)
  PHP_ADD_LIBRARY_WITH_PATH(pulsar, $PULSAR_DIR/lib, PULSAR_SHARED_LIBADD)

  dnl Check for PHP-CPP
  PHPCPP_SEARCH="/usr/local /usr"
  AC_MSG_CHECKING([for PHP-CPP])

  for i in $PHPCPP_SEARCH; do
    if test -r $i/include/phpcpp.h; then
      PHPCPP_DIR=$i
      AC_MSG_RESULT(found in $i)
      break
    fi
  done

  if test -z "$PHPCPP_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please install PHP-CPP (https://github.com/CopernicaMarketingSoftware/PHP-CPP)])
  fi

  PHP_ADD_INCLUDE($PHPCPP_DIR/include)
  PHP_ADD_LIBRARY_WITH_PATH(phpcpp, $PHPCPP_DIR/lib, PULSAR_SHARED_LIBADD)

  PHP_REQUIRE_CXX()
  CXXFLAGS="$CXXFLAGS -std=c++17 -Wall"

  PHP_SUBST(PULSAR_SHARED_LIBADD)

  PHP_NEW_EXTENSION(pulsar, [
    src/Client.cpp
    src/ClientConfiguration.cpp
    src/Consumer.cpp
    src/ConsumerConfiguration.cpp
    src/Message.cpp
    src/MessageBuilder.cpp
    src/MessageId.cpp
    src/Producer.cpp
    src/ProducerConfiguration.cpp
    src/Reader.cpp
    src/Pulsar.cpp
  ], $ext_shared,, -std=c++17)
fi
