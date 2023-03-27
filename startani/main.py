import os
from PIL import Image
i = 0
# os.mkdir("Output")
for f in  os.listdir("."):
    if f.endswith(".png"):
        # print(f)
        img = Image.open(f)
        img = img.crop((0,0,512,384))

        img.save(f"Output/{i}.bmp")
        i+=1
# a = Image.open("ezgif-frame-009.png")
# a.crop((0,0,512,384)).save("test.bmp")