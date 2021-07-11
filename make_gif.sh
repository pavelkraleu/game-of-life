#!/bin/bash

#ffmpeg -y -i examples/out/1.png -vf palettegen=16 palette.png
#ffmpeg -y -i examples/out/%d.png -i palette.png -filter_complex "fps=20,scale=1080:-1:flags=lanczos[x];[x][1:v]paletteuse" video.gif

ffmpeg -y -i examples/out/%d.png -r 15 video.gif
ffmpeg -y -i video.gif -pix_fmt yuv420p  video.mp4

#rm palette.png