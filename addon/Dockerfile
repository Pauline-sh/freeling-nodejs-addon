# Get the base Ubuntu image from Docker Hub
FROM ubuntu:18.04

# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# Install the gcc and building tools compiler
RUN apt-get -y install \
  gcc g++ \
  make cmake \
  libboost-dev libboost-program-options-dev libboost-system-dev libboost-regex-dev libboost-thread-dev \
  libicu-dev \
  zlib1g-dev \
  curl software-properties-common \

# Install LTS Node.js
RUN curl -sL https://deb.nodesource.com/setup_10.x | bash
RUN apt-get -y install nodejs

RUN mkdir -p /home/node/app

# Copy source code to the Docker image
COPY ./include /home/node/freeling/include
COPY ./src /home/node/freeling/src
COPY ./freeling /home/node/freeling/freeling
COPY ./test /home/node/freeling/test
COPY ./examples /home/node/freeling/examples
COPY CMakeLists.txt /home/node/freeling/
COPY package*.json /home/node/freeling/
COPY index.js /home/node/freeling/

# Вот это место я не понимаю как делать
RUN apt-get -y install \
  build-essential automake autoconf libtool \
  tar
COPY FreeLing-4.1.tar.gz /home/node/

RUN tar xzvf /home/node/FreeLing-4.1.tar.gz
WORKDIR /home/node/FreeLing-4.1
RUN ls
RUN mkdir build
WORKDIR /home/node/FreeLing-4.1/build
RUN ls
RUN cmake .. && make install
# Конец непонятного

# Go to app dir
WORKDIR /home/node/freeling

# Install required packages
RUN npm install && npm install -g cmake-js

# Build project
RUN cmake-js build

# Run result
CMD ["./examples/pos_tagger.js"]
