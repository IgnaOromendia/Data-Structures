import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

data_bst_i = pd.read_csv("samples/bst_insertion_random.csv")
data_rbst_i = pd.read_csv("samples/rbst_insertion_random.csv")

data_bst_is = pd.read_csv("samples/bst_insertion_sorted.csv")
data_rbst_is = pd.read_csv("samples/rbst_insertion_sorted.csv")

data_bst_max = pd.read_csv("samples/bst_max_sorted.csv")
data_rbst_max = pd.read_csv("samples/rbst_max_sorted.csv")

fig1 = plt.figure(figsize=(8, 6))

plt.plot(data_bst_i['n'], data_bst_i['time'], label='BST', color='red', linewidth = 2)
plt.scatter(data_bst_i['n'], data_bst_i['time'], color='red', linewidth = 2)
plt.plot(data_rbst_i['n'], data_rbst_i['time'], label='RBST', color='blue', linewidth = 2)
plt.scatter(data_rbst_i['n'], data_rbst_i['time'], color='blue', linewidth = 2)
plt.xlabel('Length [power of 2]')
plt.ylabel('Time (miliseconds)')
plt.title('Insertion of random numbers in Binary Search Tree and Randomized BST')
plt.grid(True)
plt.legend()
plt.show()

fig2 = plt.figure(figsize=(8, 6))

plt.plot(data_bst_max['n'], data_bst_max['time'], label='BST', color='red', linewidth = 2)
plt.scatter(data_bst_max['n'], data_bst_max['time'], color='red', linewidth = 2)
plt.plot(data_rbst_max['n'], data_rbst_max['time'], label='RBST', color='blue', linewidth = 2)
plt.scatter(data_rbst_max['n'], data_rbst_max['time'], color='blue', linewidth = 2)
plt.xlabel('Length')
plt.ylabel('Time (microseconds)')
plt.title('Max in sorted Binary Search Tree and Randomized BST')
plt.grid(True)
plt.legend()
plt.show()