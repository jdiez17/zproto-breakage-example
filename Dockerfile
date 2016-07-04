FROM fedora:23

RUN dnf install -y git wget unzip make gcc-c++ \
    autoconf automake cmake libtool python cross-binutils-common mingw64-gcc-c++
RUN dnf install -y pkgconfig lcov

# Install zeromq
RUN cd /tmp && git clone https://github.com/zeromq/zeromq4-1
RUN cd /tmp/zeromq4-1 && \
    sed -i 's/libzmq_werror="yes"/libzmq_werror="no"/' configure.ac && \
    ./autogen.sh && \
    ./configure --with-libsodium=no && \
    make -j 4 && make install && ldconfig

# Install czmq
RUN cd /tmp && wget https://github.com/zeromq/czmq/archive/v3.0.2.tar.gz && \
    tar xzf v3.0.2.tar.gz
RUN cd /tmp/czmq-3.0.2 && \
    ./autogen.sh && \
    ./configure && \
    make -j 4 && make install && ldconfig

# Install gsl
RUN dnf install -y pcre-devel
RUN cd /tmp && git clone git://github.com/imatix/gsl
RUN cd /tmp/gsl/src && \
    make && make install

# Install zproto
RUN cd /tmp && git clone https://github.com/zeromq/zproto.git && \
    cd /tmp/zproto && git checkout 4ca8a24406f5c9c8d2528521d9d32782378e0a0c
RUN cd /tmp/zproto && \
   ./autogen.sh && ./configure && \
    make && make install 

# Install zproject
RUN cd /tmp && git clone https://github.com/zeromq/zproject.git
RUN cd /tmp/zproject && \
    ./autogen.sh && ./configure && \
    make && make install 

VOLUME ["/workspace"]
