import matplotlib.pyplot as plt

path = r"C:\Users\nickl\Documents\GitHub\Modern cpp\my_solutions\hw2\igg_image\data"
file = r"\lena.ascii.pgm"

with open(path+file, 'r') as fp:
    data = fp.read().splitlines()

all_values = [int(j) for i in [line.split('  ') for line in data[3:]] for j in i]

plt.figure(figsize=(80,40))
fig = plt.hist(all_values, bins=199, range=(0, 255), density=True)
