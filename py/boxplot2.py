import csv
import matplotlib.pyplot as plt

fileName = 'data2.csv'
filePath = '../csv/' + fileName

#CSVからデータを読み込む
data = []
with open(filePath, encoding='utf-8') as file:
    data = [[int(y) for y in x] for x in csv.reader(file)]

N, S = tuple(data[0])
L, R = 0, S
base = data[1][:]
array = data[2][:]

fig, axes = plt.subplots(2, 1, figsize=[6, 3], tight_layout=True)
interval = (R - L) // 10

#箱ひげ図1(base)
axes[0].set_title('base')
axes[0].set_xticks(range(L, R + 1, interval))
axes[0].boxplot(base, labels=[''], vert=False, whis=100, widths=0.4,
           medianprops={'color': 'k'},
           showmeans=True, meanprops={'marker': 'x', 'markeredgecolor': 'r', 'markersize': 10})

#箱ひげ図2(array)
array_L, array_R = 0, 5000
array_interval = (array_R - array_L) // 10

axes[1].set_title('array')
axes[1].set_xlim(array_L - array_interval // 3, array_R + array_interval // 3)
axes[1].set_xticks(range(array_L, array_R + 1, array_interval))
axes[1].boxplot(array, labels=[''], vert=False, whis=100, widths=0.4,
           medianprops={'color': 'k'},
           showmeans=True, meanprops={'marker': 'x', 'markeredgecolor': 'r', 'markersize': 10})

#画像を出力
plt.savefig('../png/' + fileName[:fileName.find('.')] + '_2.png')
