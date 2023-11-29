import csv
import matplotlib.pyplot as plt
from matplotlib.patches import ArrowStyle

fileName = 'data3.csv'
filePath = '../csv/' + fileName

#CSVからデータを読み込む
data = []
with open(filePath, encoding='utf-8') as file:
    data = [[int(y) for y in x] for x in csv.reader(file)]

N, S = tuple(data[0])
L, R = 0, S
base = data[1][:]
array = data[2][:]

fig, ax = plt.subplots(figsize=[6, 1.5], tight_layout=True)

#散布図1
ax.set_yticks([0])
ax.set_yticklabels([])
ax.scatter(base, [0] * (N + 1), marker='o', color='none', edgecolor='k', alpha=0.5)
for i in range(N + 1):
    ax.text(base[i], 0.01, str(base[i]), ha='center')

for i in range(N):
    ax.text((base[i] + base[i + 1]) / 2, -0.03, str(array[i]), size='large', color='r', ha='center')
    ax.annotate('', xy=[base[i + 1], 0], xytext=[base[i], 0], 
                    arrowprops={'arrowstyle': '<|-|>', 'shrinkA': 0, 'shrinkB': 0, 'facecolor': 'r', 'edgecolor': 'r'})


#画像を出力
plt.savefig('../png/' + fileName[:fileName.find('.')] + '_3.png')
