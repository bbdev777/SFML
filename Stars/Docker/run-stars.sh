#!/bin/bash
xhost +
docker run --privileged -it --network host -e DISPLAY=${DISPLAY} 10.74.33.15:5000/stars-sfml:1.0.1 /Stars
