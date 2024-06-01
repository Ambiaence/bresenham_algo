ffmpeg -i test.mp4 \
  -vf scale=500x500:flags=lanczos \
  result.gif
