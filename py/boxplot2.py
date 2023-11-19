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
array.sort()
diff = [array[i + 1] - L if i == -1 else R - array[i] if i == N - 1 else array[i + 1] - array[i] for i in range(-1, N)]

fig, axes = plt.subplots(2, 1, figsize=[6, 3], tight_layout=True)

#箱ひげ図1(array)
axes[0].set_title('array')
axes[0].set_xticks(range(L, R + 1, (R - L) // 10))
axes[0].boxplot(array, labels=[''], vert=False, whis=100, widths=0.4,
           medianprops={'color': 'k'},
           showmeans=True, meanprops={'marker': 'x', 'markeredgecolor': 'r', 'markersize': 10})

#箱ひげ図2(diff)
diff_L, diff_R = 0, 5000
axes[1].set_title('difference')
axes[1].set_xlim(diff_L - (diff_R - diff_L) / 30, diff_R + (diff_R - diff_L) / 30)
axes[1].set_xticks(range(0, 5001, 500))
axes[1].boxplot(diff, labels=[''], vert=False, whis=100, widths=0.4,
           medianprops={'color': 'k'},
           showmeans=True, meanprops={'marker': 'x', 'markeredgecolor': 'r', 'markersize': 10})

#画像を出力
plt.savefig('../png/' + fileName[:fileName.find('.')] + '_2.png')
