import matplotlib.pyplot as plt
y=[2, 268, 20, 1482, 20, 6924, 20, 36070, 20, 165231, 20, 442752, 20, 20833, 20, 4582872, 20, 14992721, 20]
x=[2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]


plt.xlabel("Square size")         # ось абсцисс
plt.ylabel("Number of operations")    # ось ординат
plt.grid()              # включение отображение сетки

plt.title("Dependence of the number of operations\n on the size of the square")
plt.plot(x, y)
plt.savefig('Dependence')