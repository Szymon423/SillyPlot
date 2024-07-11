# Base Debian Bullseye image for arm64v8 architecture - Raspberry Pi 64 bit OS (Legacy) Lite
FROM arm64v8/debian:bullseye

# Dependencies 
RUN rm /var/lib/dpkg/info/libc-bin.*
RUN apt clean && apt update && apt install -y libc-bin \
    git \
    curl \
    zip \
    unzip \
    tar \
    build-essential \
    pkg-config \
    ninja-build \
    wget \
    gcc-aarch64-linux-gnu \
    g++-aarch64-linux-gnu \
    && apt clean \
    && rm -rf /var/lib/apt/lists/*

# Install CMake 3.29
RUN curl -LO https://github.com/Kitware/CMake/releases/download/v3.29.6/cmake-3.29.6-linux-aarch64.sh \
    && chmod +x cmake-3.29.6-linux-aarch64.sh \
    && ./cmake-3.29.6-linux-aarch64.sh --skip-license --prefix=/usr/local \
    && rm cmake-3.29.6-linux-aarch64.sh

# Skopiuj kod źródłowy do obrazu
COPY . /YAPL

# Przejdź do katalogu z kodem źródłowym
WORKDIR /YAPL

# Punkt wejścia: kompilacja, uruchomienie testów i przykładu
CMD ["bash", "-c", "mkdir -p build && cd build && cmake .. && make && ctest && ./example"]