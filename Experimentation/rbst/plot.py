import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

data_bst_i = pd.read_csv("samples/bst_insertion_random.csv")
data_rbst_i = pd.read_csv("samples/rbst_insertion_random.csv")

data_bst_is = pd.read_csv("samples/bst_insertion_sorted.csv")
data_rbst_is = pd.read_csv("samples/rbst_insertion_sorted.csv")

data_bst_max_r = pd.read_csv("samples/bst_max_random.csv")
data_rbst_max_r = pd.read_csv("samples/rbst_max_random.csv")

fig1 = plt.figure(figsize=(8, 6))

plt.plot(data_bst_i['n'], data_bst_i['time'], label='BST', color='red', linewidth = 2)
plt.scatter(data_bst_i['n'], data_bst_i['time'], color='red', linewidth = 2)
plt.plot(data_rbst_i['n'], data_rbst_i['time'], label='RBST', color='blue', linewidth = 2)
plt.scatter(data_rbst_i['n'], data_rbst_i['time'], color='blue', linewidth = 2)
plt.xlabel('Length [power of 2]')
plt.ylabel('Time (milliseconds)')
plt.title('Insertion of random numbers in BST and Randomized BST')
plt.grid(True)
plt.legend()
plt.show()

fig2 = plt.figure(figsize=(8, 6))

plt.plot(data_bst_is['n'], data_bst_is['time'], label='BST', color='red', linewidth = 2)
plt.scatter(data_bst_is['n'], data_bst_is['time'], color='red', linewidth = 2)
plt.plot(data_rbst_is['n'], data_rbst_is['time'], label='RBST', color='blue', linewidth = 2)
plt.scatter(data_rbst_is['n'], data_rbst_is['time'], color='blue', linewidth = 2)
plt.xlabel('Length')
plt.ylabel('Time (milliseconds)')
plt.title('Insertion of sorted numbers in BST and Randomized BST')
plt.grid(True)
plt.legend()
plt.show()

fig3 = plt.figure(figsize=(8, 6))

plt.plot(data_bst_max_r['n'], data_bst_max_r['time'], label='BST', color='red', linewidth = 2)
plt.scatter(data_bst_max_r['n'], data_bst_max_r['time'], color='red', linewidth = 2)
plt.plot(data_rbst_max_r['n'], data_rbst_max_r['time'], label='RBST', color='blue', linewidth = 2)
plt.scatter(data_rbst_max_r['n'], data_rbst_max_r['time'], color='blue', linewidth = 2)
plt.xlabel('Length')
plt.ylabel('Time (nanoseconds)')
plt.title('Max with random input in BST and Randomized BST')
plt.grid(True)
plt.legend()
plt.show()