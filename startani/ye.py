from PIL import Image, ImageDraw

w,h = 800,800

img =  Image.new("RGBA",(w,h))
for i in range(0,w,32):
    for j in range(0,h,32):
        img1 = ImageDraw.Draw(img)
        shape = [i,j,i+32,j+32]
        img1.rectangle(shape,fill = "black",outline = "green",width = 2)


img.save("aa.bmp")
img.show()