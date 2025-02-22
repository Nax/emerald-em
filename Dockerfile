FROM debian:12

RUN apt-get update && apt-get install -y \
  gcc-arm-none-eabi \
  python3 \
  python3-pip \
  python3-dev \
  build-essential \
  libssl-dev \
  libffi-dev \
  python3-setuptools \
  python3-venv \
  pkg-config \
  libpng-dev \
  && apt-get clean

WORKDIR /emerald
