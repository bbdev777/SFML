FROM 10.74.33.15:5000/ubuntu-20.04-dev-image:1.0.1 AS build

ENV DEBIAN_FRONTEND="noninteractive"
ENV TZ="UTC"

RUN apt update
RUN apt-get install -y autoconf libtool pkg-config libudev-dev libsfml-dev
RUN /opt/vcpkg/vcpkg install libx11 libxrandr glm

####################################################################################################
# Apps
####################################################################################################

RUN mkdir -p /src/SFML
RUN mkdir -p /build-folder

RUN --mount=type=bind,source=.,target=/src/SFML \
    --mount=type=cache,target=/build-folder \
    cd /build-folder \
    && cmake -G Ninja \
        -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake \
        -DCMAKE_BUILD_TYPE=Release \
        /src/SFML \
    && ninja clean \
    && ninja -j4 \
    && cp -r /build-folder/Stars /Stars \
    && cp /src/SFML/StarImg.png /StarImg.png

FROM 10.74.33.15:5000/ubuntu-20.04-rel-image:1.0.1 AS Release

RUN apt update
RUN apt-get install -y autoconf libtool pkg-config libudev-dev libsfml-dev

COPY --from=build /Stars /Stars
COPY --from=build /StarImg.png /StarImg.png
