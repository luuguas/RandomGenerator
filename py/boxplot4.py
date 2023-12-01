import csv
import matplotlib.pyplot as plt

fileName = 'data5.csv'
filePath = '../csv/' + fileName

#CSVからデータを読み込む
data = []
with open(filePath, encoding='utf-8') as file:
    data = [[float(y) if y.find('.') != -1 else int(y) for y in x] for x in csv.reader(file)]

Q = tuple(data[0])
RANGE = data[1][:]
N = data[2][:]

errs = [[data[3 + i * 4 + j][:] for j in range(4)] for i in range(4)]

fig, axes = plt.subplots(2, 2, sharey='all', tight_layout=True)

for i, range in enumerate(RANGE, 0):
    #図の表示位置
    box_i = i // 2
    box_j = i % 2;

    labels = []
    if box_i == 0 and box_j == 0:
        labels = [f'N = {n}' for n in N]
    else:
        labels = ['' for _ in N]

    axes[box_i][box_j].set_title(f'range = {range}')
    axes[box_i][box_j].boxplot(errs[i], labels=labels, vert=False, whis=100, widths=0.4,
               medianprops={'color': 'k'},
               showmeans=True, meanprops={'marker': 'x', 'markeredgecolor': 'r'})

#画像を出力
plt.savefig('../png/' + fileName[:fileName.find('.')] + '_4.png')
