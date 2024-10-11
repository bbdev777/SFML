#!/bin/bash
xhost +
docker run --privileged -it --network host -e DISPLAY=${DISPLAY} docker.io/bbdev007/stars-sfml:1.0.1 /Stars

