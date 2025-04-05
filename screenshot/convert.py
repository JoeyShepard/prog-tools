#!/usr/bin/env python3

import os

DWIDTH=396
DHEIGHT=224

with open("screenshot.raw","rb") as f:
    pixels=f.read()

print(f"{len(pixels)} bytes read - {len(pixels)/2} pixels (should be {DWIDTH*DHEIGHT})")

with open("screenshot.ppm","wt") as f:
    f.write("P3\n")
    f.write(f"{DWIDTH} {DHEIGHT}\n")
    f.write("255\n")

    pixel_count=0
    for y in range(DHEIGHT):
        for x in range(DWIDTH):
            index=y*(DWIDTH*2)+x*2
            pixel=pixels[index]|(pixels[index+1]<<8)
            blue=int(((pixel&31)/31)*255)
            green=int((((pixel>>6)&31)/31)*255)
            red=int((((pixel>>11)&31)/31)*255)
            f.write(f"{red} {green} {blue}  ")
            pixel_count+=1
        f.write("\n")
    print(f"{pixel_count} pixels written")

os.system("convert -filter point screenshot.ppm -resize 200% screenshot.png")
os.system("open screenshot.png")
