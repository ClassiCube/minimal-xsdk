FROM ubuntu:24.04

RUN apt-get update
RUN apt-get -y install bash python3 tar gzip make libmpc3 glslang-tools curl

RUN echo "## Exporting ps3dev environment" >> /root/.bashrc
RUN echo "export XSDK_TOOLCHAIN=/usr/local/xsdk-gcc" >> /root/.bashrc
RUN echo "export XSDK_SDK=/usr/local/xsdk" >> /root/.bashrc

COPY . /usr/local
