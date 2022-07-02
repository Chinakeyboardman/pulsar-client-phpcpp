FROM php:8.0

RUN apt update && \
    apt install -y git gcc curl util-linux binutils rtmpdump m4 bison g++ && \
    apt upgrade -y

RUN cd /tmp && \
    curl -o apache-pulsar-client-dev.deb https://archive.apache.org/dist/pulsar/pulsar-2.8.2/DEB/apache-pulsar-client-dev.deb  && \
    curl -o apache-pulsar-client.deb https://archive.apache.org/dist/pulsar/pulsar-2.8.2/DEB/apache-pulsar-client.deb && \
    dpkg -i apache-pulsar-client.deb && \
    dpkg -i apache-pulsar-client-dev.deb

RUN git clone https://github.com/NobletSolutions/PHP-CPP.git /tmp/php-cpp
ADD build/PHP_CPP_Fix_GCC_10_missing_include.patch /tmp/php-cpp/PHP_CPP_Fix_GCC_10_missing_include.patch
RUN cd /tmp/php-cpp && \
    git checkout php80 && \
    git apply PHP_CPP_Fix_GCC_10_missing_include.patch && \
    make && \
    make install

ADD . /tmp/pulsar-client-phpcpp
RUN cd /tmp/pulsar-client-phpcpp && \
    make clean &&  \
    make && \
    ls -al . /usr/local/lib/php/extensions && \
    cp pulsar-phpcpp.so /usr/local/lib/php/extensions/`ls /usr/local/lib/php/extensions/|grep zts`/pulsar-phpcpp.so && \
    echo "extension=pulsar-phpcpp" > /usr/local/etc/php/conf.d/pulsar.ini && \
    ls -al /usr/local/lib/php/extensions/`ls /usr/local/lib/php/extensions/|grep zts`/

# RUN [[ `php -m |grep pulsar |wc -l` == 0 ]] && { echo "ERROR modul \"pulsar-phpcpp\" nebyl zaveden do PHP !!!"; exit 1; }

# Build the deb package
RUN set -ex && cd /tmp/pulsar-client-phpcpp/package && \
    mkdir -p usr/lib usr/include/phpcpp usr/local/lib/php/extensions usr/local/etc/php/conf.d && \
    cp -f /usr/lib/libphpcpp.* usr/lib/ && \
    cp /usr/local/etc/php/conf.d/pulsar.ini usr/local/etc/php/conf.d/ && \
    cp /tmp/pulsar-client-phpcpp/pulsar-phpcpp.so usr/local/lib/php/extensions/ && \
    cd /tmp/pulsar-client-phpcpp && dpkg-deb --build --root-owner-group ./package php80-pulsar-client.deb