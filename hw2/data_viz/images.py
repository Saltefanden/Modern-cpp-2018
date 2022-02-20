import matplotlib.pyplot as plt
import numpy as np



def show_image(path, sep='  ', inverted=False):
    with open(path, 'r') as fp:
        data = fp.read().splitlines()
    
    # Remove comments
    data = [row for row in data if row[0]!='#']


    rows, cols = (int(i) for i in data[1].split(sep) )

    if inverted:
        vec = np.matrix(
            [250 - int(j) for i in [ #  The absolute madman subtracted 250 rather than maxval (255)
                line.strip().split(sep) for line in data[3:]
            ]
            for j in i
            ]
        )
    else:
        vec = np.matrix(
            [int(j) for i in [
                line.strip().split(sep) for line in data[3:]
            ]
            for j in i
            ]
        )

    matrix = vec.reshape(rows,cols)

    fig, ax = plt.subplots(nrows=1, figsize=(10,10))
    ax.imshow(matrix, 'gray')
    return matrix


base_path = r"..\igg_image\data"


# _ = show_image(base_path +r"\lena.ascii.pgm")
# _ = show_image(base_path+r"\Downscaled_Lena.pgm")
# _ = show_image(base_path+r"\Downscaled2_Lena.pgm")
# lena_3 = show_image(base_path+r"\Downscaled_Lena_3.pgm")
# lena_13 = show_image(base_path+r"\Downscaled_Lena_13.pgm")
# lena_up = show_image(base_path + r"\Upscaled_Lena.pgm")
# lena_up = show_image(base_path + r"\Upscaled_Lena3.pgm")

base_path = r"..\..\..\Solutions\bonn-cc\homework_2\igg_image\data"

lena_ext = show_image(base_path+r"\lena.ascii.pgm")
lena_ext2 = show_image(base_path+r"\lena.ascii-2.pgm", sep=' ', inverted=True)
lena_ext3 = show_image(base_path+r"\lena.ascii-3.pgm", sep=' ', inverted=True)
lena_ext4 = show_image(base_path+r"\lena.ascii-4.pgm", sep=' ', inverted=True)

