FROM ubuntu:18.04

RUN apt-get update && apt-get install -y locales && \
    locale-gen en_US.UTF-8 && \
    apt-get update -q && \
    apt-get install -y build-essential automake cmake autoconf libtool wget \
                       libboost-dev libboost-program-options-dev libboost-filesystem-dev \
                       libboost-system-dev libboost-regex-dev libboost-thread-dev \
                       libicu-dev \
                       zlib1g-dev && \
    cd /tmp && \
    wget --progress=dot:giga https://github.com/TALP-UPC/FreeLing/releases/download/4.1/FreeLing-4.1.tar.gz && \
    tar xvzf FreeLing-4.1.tar.gz && \
    rm -rf FreeLing-4.1.tar.gz && \
    cd /tmp/FreeLing-4.1 && \
    mkdir build && \
    cd build && \
    cmake .. && make install && \
    rm -rf /tmp/FreeLing-4.1 && \
    apt-get --purge -y remove build-essential libicu-dev \
            libboost-regex-dev libboost-system-dev \
            libboost-program-options-dev libboost-thread-dev zlib1g-dev\
            automake autoconf libtool wget && \
    apt-get autoremove -y && \
    apt-get clean -y && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /home

# способ поместить аддон в контейнер без гита?
RUN apt-get update && apt-get install -y git && \
    git clone git@github.com:Pauline-sh/freeling-nodejs-addon.git && \
    cd freeling-nodejs-addon/addon && \
    npm install && npm install -g cmake-js && \
    cmake-js build

EXPOSE 50005
