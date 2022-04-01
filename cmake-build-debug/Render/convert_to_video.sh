#!/bin/bash

ffmpeg -framerate 24 -pattern_type glob -i '*.pbm' \
  -c:v libx264 -pix_fmt yuv420p out.mp4
