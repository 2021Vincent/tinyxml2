from PIL import Image
import os
# create a txt file to store every tileset's width/32 * height/32


for f in os.listdir("Graphics/Tilesets"):
    name, ext = os.path.splitext(f)
    if not os.path.exists(f"Output/{name}"):
        os.mkdir(f"Output/{name}")

    tile = Image.open(f"Graphics/Tilesets/{f}")

    width, height = tile.size
    
    k = 0
    for i in range(0, height, 32):
        for j in range(0, width, 32):
            box = (j, i, j + 32, i + 32)
            sub_img = tile.crop(box).convert("RGBA")
            # create a new blank image with black background
            bg = Image.new("RGBA", sub_img.size, (204, 255, 0, 255))
            # paste the sub-image onto the blank image
            bg.paste(sub_img, (0, 0), sub_img)
            
            bg.save(f"Output/{name}/image{k}.bmp")
            k += 1
    print(f"Output/{name} complete")
    tile.close()