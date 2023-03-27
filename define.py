import os
# iterates over all files in the directory "map_pro_max"
# open a txt file to write the names of the files
with open("house1.txt", "w") as f:     
    i=0
    for file in os.listdir("map_pro_tmx"):
        # if the file starts with house1
        if file.startswith("house1"):
            # write the file name to the txt file
            f.write(f"#define {file[:-4].upper()} {i}\n")
            i+=1