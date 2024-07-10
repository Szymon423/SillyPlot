# Base Debian Bullseye image for arm64v8 architecture - Raspberry Pi 64 bit OS (Legacy) Lite
FROM arm64v8/debian:bullseye

# Dependencies for vcpkg
RUN apt update && apt-get install -y \
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

# Set environmental variable for vcpkg, second one is needed becouse of vcpkg 
ENV VCPKG_ROOT /usr/local/vcpkg
ENV VCPKG_FORCE_SYSTEM_BINARIES=1

# Now clone and bootstrap vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git $VCPKG_ROOT \
    && cd $VCPKG_ROOT \
    && ./bootstrap-vcpkg.sh

# Add vcpkg to system path
ENV PATH="$VCPKG_ROOT:$PATH"

# Update vcpkg for new vcpkg packages definitions
RUN vcpkg update

RUN vcpkg install pngwriter --clean-after-build

# Skopiuj kod źródłowy do obrazu
COPY . /SillyPlot

# Przejdź do katalogu z kodem źródłowym
WORKDIR /SillyPlot

# Punkt wejścia: kompilacja, uruchomienie testów i przykładu
CMD ["bash", "-c", "mkdir -p build && cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake && make && ctest && ./example"]