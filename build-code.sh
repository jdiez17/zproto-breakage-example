#!/bin/bash

USER=$(whoami)

sudo docker build -t zproto-breakage-example .
sudo docker run --rm -v $(pwd):/workspace zproto-breakage-example /bin/sh -c "cd /workspace && \
    mkdir -p include && cd src && \
    cp aggregator_msg.xml aggregator_msg_python.xml && sed -i 's/zproto_codec_c/zproto_codec_python/' aggregator_msg_python.xml && \
    gsl aggregator_msg.xml && \
    gsl aggregator_broker.xml && \
    cd .. && gsl project.xml"
sudo chown -R $USER:$USER include src
