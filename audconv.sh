#!/bin/bash


for files in *.wav
do

	ffmpeg -i "$files" -acodec pcm_s16le -ar 8000 /home/rafiq/program_c++/manzke/parse/helper/aud/"$files"
#	echo "$files"
done
