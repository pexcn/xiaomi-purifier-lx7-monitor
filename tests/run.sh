#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
mkdir -p work/tests
"${CXX:-g++}" -std=c++17 -Wall -Wextra -Werror -g \
  -fsanitize=address,undefined -fno-omit-frame-pointer -no-pie \
  -Itests/stubs -Iinclude -I.pio/libdeps/nodemcuv2/ArduinoJson/src \
  tests/test_main.cpp tests/crypto_openssl.cpp \
  src/Controller.cpp src/Lx7Protocol.cpp src/MiioCodec.cpp src/MiioClient.cpp src/ConfigJson.cpp src/Config.cpp \
  -lcrypto -o work/tests/monitor-tests
work/tests/monitor-tests
