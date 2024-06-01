ffmpeg -r 60 -f image2 -s 50x50 -i %d.pmg -vcodec libx264 -crf 25  -pix_fmt yuv420p test.mp4
