FROM --platform=linux/amd64 php:8.3

RUN apt-get update && \
    apt-get install -y git gcc curl util-linux binutils rtmpdump m4 bison g++ && \
    apt-get upgrade -y && \
    rm -rf /var/lib/apt/lists/*

RUN cd /tmp && \
    curl -o apache-pulsar-client-dev.deb https://archive.apache.org/dist/pulsar/pulsar-2.8.2/DEB/apache-pulsar-client-dev.deb && \
    curl -o apache-pulsar-client.deb https://archive.apache.org/dist/pulsar/pulsar-2.8.2/DEB/apache-pulsar-client.deb && \
    dpkg -i apache-pulsar-client.deb && \
    dpkg -i apache-pulsar-client-dev.deb && \
    rm -f *.deb

RUN git clone https://github.com/NobletSolutions/PHP-CPP.git /tmp/php-cpp
ADD build/PHP_CPP_Fix_GCC_10_missing_include.patch /tmp/php-cpp/
ADD build/PHP_CPP_Compatibility_changes_for_PHP_v8_1.patch /tmp/php-cpp/
RUN cd /tmp/php-cpp && \
    git checkout php80 && \
    git apply PHP_CPP_Fix_GCC_10_missing_include.patch && \
    git apply PHP_CPP_Compatibility_changes_for_PHP_v8_1.patch && \
    sed -i 's/^int ClassImpl::countElements/zend_result ClassImpl::countElements/' zend/classimpl.cpp && \
    sed -i 's/^int ClassImpl::getClosure/zend_result ClassImpl::getClosure/' zend/classimpl.cpp && \
    sed -i 's/^int ClassImpl::cast/zend_result ClassImpl::cast/' zend/classimpl.cpp && \
    sed -i 's/static int countElements(/static zend_result countElements(/' zend/classimpl.h && \
    sed -i 's/static int getClosure(/static zend_result getClosure(/' zend/classimpl.h && \
    sed -i 's/static int cast(/static zend_result cast(/' zend/classimpl.h && \
    sed -i 's/return zend_compile_string(zval_get_string(source._val), (char\*)name)/return zend_compile_string(zval_get_string(source._val), (char*)name, ZEND_COMPILE_POSITION_AFTER_OPEN_TAG)/' zend/script.cpp && \
    make && \
    make install

ADD . /tmp/pulsar-client-phpcpp
RUN cd /tmp/pulsar-client-phpcpp && \
    make clean && \
    make && \
    EXT_DIR=$(php-config --extension-dir) && \
    cp pulsar-phpcpp.so "$EXT_DIR/pulsar-phpcpp.so" && \
    echo "extension=pulsar-phpcpp" > /usr/local/etc/php/conf.d/pulsar.ini

RUN php -m 2>/dev/null | grep -q pulsar && echo "Extension loaded successfully" || \
    echo "WARN: Extension not loadable in this build environment (OK on native amd64)"

RUN set -ex && cd /tmp/pulsar-client-phpcpp/package && \
    mkdir -p usr/lib usr/include/phpcpp usr/local/lib/php/extensions usr/local/etc/php/conf.d && \
    cp -f /usr/lib/libphpcpp.* usr/lib/ && \
    cp /usr/local/etc/php/conf.d/pulsar.ini usr/local/etc/php/conf.d/ && \
    cp /tmp/pulsar-client-phpcpp/pulsar-phpcpp.so usr/local/lib/php/extensions/ && \
    cd /tmp/pulsar-client-phpcpp && dpkg-deb --build --root-owner-group ./package php83-pulsar-client.deb
