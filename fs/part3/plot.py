import matplotlib.pyplot as plt
import math
with open('ran.txt', 'r') as f:
	r = f.readlines()
f.close()

x = []
y = []

for line in r:
	line = line.split(' ')
	x = x + [math.log2(eval(line[0]) / 1024)]
	y = y +[math.log2(eval(line[1]))]

with open('seq.txt', 'r') as f:
	r = f.readlines()
f.close()

a = []
b = []

for line in r:
	line = line.split(' ')
	a = a + [math.log2(eval(line[0]))]
	b = b +[math.log2(eval(line[1]))]


# plot scatter plot
ax = plt.gca()
plt.scatter(x, y)
ran, = plt.plot(x, y, label = "Random Read")
plt.xlabel('log(File size (MB))')
plt.ylabel('log(Cycles per block)')
ax.set_ylim([22,25])

plt.scatter(a, b)
seq, = plt.plot(a, b, label = "Sequential Read")
plt.legend(loc=9, bbox_to_anchor=(0.5, -0.1), ncol=2)

plt.show()
