import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

data_fibo_i = pd.read_csv('samples/fibo_insertion.csv')
data_pq_i = pd.read_csv('../samples_cpp/pqueue_insertion.csv')

data_fib_min = pd.read_csv('samples/fibo_min.csv')
data_pq_min = pd.read_csv('../samples_cpp/pqueue_min.csv')

data_fib_wf = pd.read_csv('samples/fibo_min_wf.csv')
data_pq_wf = pd.read_csv('../samples_cpp/pqueue_min_wf.csv')



fig1 = plt.figure(figsize=(8, 6))

plt.plot(data_fibo_i['n'], data_fibo_i['time'], label='Fibonacci Heap', color='red', linewidth = 2)
plt.scatter(data_fibo_i['n'], data_fibo_i['time'], color='red', linewidth = 2)
plt.plot(data_pq_i['n'], data_pq_i['time'], label='C++ Heap', color='blue', linewidth = 2)
plt.scatter(data_pq_i['n'], data_pq_i['time'], color='blue', linewidth = 2)
plt.xlabel('Length')
plt.ylabel('Time (milliseconds)')
plt.title('Insertion in Fibonacci Heap and C++ Heap')
plt.grid(True)
plt.legend()
plt.show()

fig2 = plt.figure(figsize=(8, 6))

plt.plot(data_fib_min['n'], data_fib_min['time'], label='Fibonacci Heap', color='red', linewidth = 2)
plt.scatter(data_fib_min['n'], data_fib_min['time'], color='red', linewidth = 2)
plt.plot(data_pq_min['n'], data_pq_min['time'], label='C++ Heap', color='blue', linewidth = 2)
plt.scatter(data_pq_min['n'], data_pq_min['time'], color='blue', linewidth = 2)
plt.xlabel('Length')
plt.ylabel('Time (milliseconds)')
plt.title('Extract min in Fibonacci Heap and C++ Heap')
plt.grid(True)
plt.legend()
plt.show()

fig3 = plt.figure(figsize=(8, 6))

plt.plot(data_fib_wf['n'], data_fib_wf['time'], label='Fibonacci Heap', color='red', linewidth = 2)
plt.scatter(data_fib_wf['n'], data_fib_wf['time'], color='red', linewidth = 2)
plt.plot(data_pq_wf['n'], data_pq_wf['time'], label='C++ Heap', color='blue', linewidth = 2)
plt.scatter(data_pq_wf['n'], data_pq_wf['time'], color='blue', linewidth = 2)
plt.xlabel('Length')
plt.ylabel('Time (milliseconds)')
plt.title('Extract min without the first extract in Fibonacci Heap and C++ Heap')
plt.grid(True)
plt.legend()
plt.show()

fig4 = plt.figure(figsize=(8, 6))

plt.plot(data_fib_wf['n'], data_fib_wf['time'], label='All extractions', color='red', linewidth = 2)
plt.scatter(data_fib_wf['n'], data_fib_wf['time'], color='red', linewidth = 2)
plt.plot(data_fib_min['n'], data_fib_min['time'], label='From second extraction', color='blue', linewidth = 2)
plt.scatter(data_fib_min['n'], data_fib_min['time'], color='blue', linewidth = 2)
plt.xlabel('Length')
plt.ylabel('Time (milliseconds)')
plt.title('Extract min without the first extract and all extracts in Fibonacci Heap')
plt.grid(True)
plt.legend()
plt.show()