import csv
import matplotlib.pyplot as plt

fileName = 'data1.csv'
filePath = '../csv/' + fileName

#CSVからデータを読み込む
data = []
with open(filePath, encoding='utf-8') as file:
    data = [[int(y) for y in x] for x in csv.reader(file)]

N, L, R = tuple(data[0])
array = data[1][:]

fig, axes = plt.subplots(2, 1, figsize=[6, 2.5], sharex=True, tight_layout=True)
plt.xticks(range(L, R + 1, (R - L) // 10))

#散布図
axes[0].set_yticks([0])
axes[0].set_yticklabels([])
axes[0].scatter(array, [0] * N, marker='o', color='none', edgecolor='k', alpha=0.5)

#箱ひげ図
axes[1].boxplot(array, labels=[''], vert=False, whis=100, widths=0.4,
           medianprops={'color': 'k'},
           showmeans=True, meanprops={'marker': 'x', 'markeredgecolor': 'r', 'markersize': 10})

#画像を出力
plt.savefig('../png/' + fileName[:fileName.find('.')] + '.png')
