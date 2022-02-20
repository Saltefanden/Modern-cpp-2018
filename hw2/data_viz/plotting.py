import matplotlib.pyplot as plt

path = r"C:\Users\nickl\Documents\GitHub\Modern cpp\my_solutions\hw2\igg_image\data"
file = r"\LenaHistogram.txt"

with open(path+file, 'r') as fp:
    data = fp.readline()

hist_array = [float(bin) for bin in data.split()]

plt.figure(figsize=(80,40))
fig = plt.bar(range(len(hist_array)), hist_array)

 