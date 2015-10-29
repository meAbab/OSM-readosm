# OSM_dev

=============================================
FINAL CODE COULD BE FOUND => final_src folder
=============================================

Many times I've seen a tv commercial of Auto as it taking voice command and replying geo-finding. For example, Driver 
is asking for "Restaurant" - and maybe it will reply result - 
"You have 5 restaurant wihtin 5 Km radius from your current position."

So, my idea is to do the same. with a small resources. My target is to port (if all succeed) it to 
Intel Galileo. After testing many, I found readosm is small and takes less resource.

My plan is to use Yocto in Galileo, so - once which running in any i386, would run there too.

All of these program, is on Ubuntu with Gcc - 4.8.2

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

The program play_it.c is for playing wav file using ALSA library. I used files form 

https://evolution.voxeo.com/library/audio/prompts/numbers/audio-numbers.zip [ they are opensource ]

But to let ALSA work on these files, you still need to conver the files format using ffmpeg. 

Command is - ffmpeg -i 0.wav -acodec pcm_s16le -ar 8000 0_t.wav

on the other hand you can use the shell script named audconv.sh

Right now, the play_it.c is an individual program, which just playing 0 to 99. Later it will added with main openstreetmap parsing program.

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
