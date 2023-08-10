import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

data_fibo_i = pd.read_csv('samples/fibo_insertion.csv')
data_pq_i = pd.read_csv('../samples_cpp/pqueue_insertion.csv')
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

data_fib_min = pd.read_csv('samples/fibo_min.csv')
data_pq_min = pd.read_csv('../samples_cpp/pqueue_min.csv')

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

data_fib_wf = pd.read_csv('samples/fibo_min_wf.csv')

fig3 = plt.figure(figsize=(8, 6))

plt.plot(data_fib_wf['n'], data_fib_wf['time'], label='From second extraction', color='red', linewidth = 2)
plt.scatter(data_fib_wf['n'], data_fib_wf['time'], color='red', linewidth = 2)
plt.plot(data_fib_min['n'], data_fib_min['time'], label='All extractions', color='blue', linewidth = 2)
plt.scatter(data_fib_min['n'], data_fib_min['time'], color='blue', linewidth = 2)
plt.xlabel('Length')
plt.ylabel('Time (milliseconds)')
plt.title('Extract min without the first extract and all extracts in Fibonacci Heap')
plt.grid(True)
plt.legend()

data_fib_p1dN = pd.read_csv("samples/dijkstra_1divN.csv")
data_fib_plogNdN = pd.read_csv("samples/dijkstra_logNdivN.csv")

fig4 = plt.figure(figsize=(8, 6))

plt.plot(data_fib_p1dN['n'], data_fib_p1dN['time'], label='p = 1 / n', color='red', linewidth = 2)
plt.scatter(data_fib_p1dN['n'], data_fib_p1dN['time'], color='red', linewidth = 2)
plt.plot(data_fib_plogNdN['n'], data_fib_plogNdN['time'], label='p = log n / n', color='blue', linewidth = 2)
plt.scatter(data_fib_plogNdN['n'], data_fib_plogNdN['time'], color='blue', linewidth = 2)
plt.xlabel('Length')
plt.ylabel('Time (milliseconds)')
plt.title('Time in dijkstra on a graph with density probabilities 1/n and (log n)/n')
plt.grid(True)
plt.legend()

data_fib_p1dN_bo = pd.read_csv("samples/bo_dijkstra_1divN.csv")
data_fib_plogNdN_bo = pd.read_csv("samples/bo_dijkstra_logNdivN.csv")

fig5 = plt.figure(figsize=(8, 6))

plt.plot(data_fib_p1dN_bo['n'], data_fib_p1dN_bo['time'], label='p = 1 / n', color='red', linewidth = 2)
plt.scatter(data_fib_p1dN_bo['n'], data_fib_p1dN_bo['time'], color='red', linewidth = 2)
plt.plot(data_fib_plogNdN_bo['n'], data_fib_plogNdN_bo['time'], label='p = log n / n', color='blue', linewidth = 2)
plt.scatter(data_fib_plogNdN_bo['n'], data_fib_plogNdN_bo['time'], color='blue', linewidth = 2)
plt.xlabel('Length')
plt.ylabel('Basic operations')
plt.title('Basic operations in dijkstra on a graph with density probabilities 1/n and (log n)/n')
plt.grid(True)
plt.legend()

data_fib_p_0_5 = pd.read_csv("samples/dijkstra_p=0_5.csv")
data_fib_p_0_6 = pd.read_csv("samples/dijkstra_p=0_6.csv")
data_fib_p_0_7 = pd.read_csv("samples/dijkstra_p=0_7.csv")
data_fib_p_0_8 = pd.read_csv("samples/dijkstra_p=0_8.csv")
data_fib_p_0_9 = pd.read_csv("samples/dijkstra_p=0_9.csv")

fig6 = plt.figure(figsize=(8, 6))

plt.plot(data_fib_p_0_5['n'], data_fib_p_0_5['time'], label='p = 0.5', color='red', linewidth = 2)
plt.scatter(data_fib_p_0_5['n'], data_fib_p_0_5['time'], color='red', linewidth = 2)

plt.plot(data_fib_p_0_6['n'], data_fib_p_0_6['time'], label='p = 0.6', color='blue', linewidth = 2)
plt.scatter(data_fib_p_0_6['n'], data_fib_p_0_6['time'], color='blue', linewidth = 2)

plt.plot(data_fib_p_0_7['n'], data_fib_p_0_7['time'], label='p = 0.7', color='green', linewidth = 2)
plt.scatter(data_fib_p_0_7['n'], data_fib_p_0_7['time'], color='green', linewidth = 2)

plt.plot(data_fib_p_0_8['n'], data_fib_p_0_8['time'], label='p = 0.8', color='orange', linewidth = 2)
plt.scatter(data_fib_p_0_8['n'], data_fib_p_0_8['time'], color='orange', linewidth = 2)

plt.plot(data_fib_p_0_9['n'], data_fib_p_0_9['time'], label='p = 0.9', color='purple', linewidth = 2)
plt.scatter(data_fib_p_0_9['n'], data_fib_p_0_9['time'], color='purple', linewidth = 2)

plt.xlabel('Length')
plt.ylabel('Time (milliseconds)')
plt.title('Time in dijkstra on graphs with density probabilities from 0.5 to 0.9')
plt.grid(True)
plt.legend()

data_fib_p_0_5_bo = pd.read_csv("samples/bo_dijkstra_p=0_5.csv")
data_fib_p_0_6_bo = pd.read_csv("samples/bo_dijkstra_p=0_6.csv")
data_fib_p_0_7_bo = pd.read_csv("samples/bo_dijkstra_p=0_7.csv")
data_fib_p_0_8_bo = pd.read_csv("samples/bo_dijkstra_p=0_8.csv")
data_fib_p_0_9_bo = pd.read_csv("samples/bo_dijkstra_p=0_9.csv")

fig6 = plt.figure(figsize=(8, 6))

plt.plot(data_fib_p_0_5_bo['n'], data_fib_p_0_5_bo['time'], label='p = 0.5', color='red', linewidth = 2)
plt.scatter(data_fib_p_0_5_bo['n'], data_fib_p_0_5_bo['time'], color='red', linewidth = 2)

plt.plot(data_fib_p_0_6_bo['n'], data_fib_p_0_6_bo['time'], label='p = 0.6', color='blue', linewidth = 2)
plt.scatter(data_fib_p_0_6_bo['n'], data_fib_p_0_6_bo['time'], color='blue', linewidth = 2)

plt.plot(data_fib_p_0_7_bo['n'], data_fib_p_0_7_bo['time'], label='p = 0.7', color='green', linewidth = 2)
plt.scatter(data_fib_p_0_7_bo['n'], data_fib_p_0_7_bo['time'], color='green', linewidth = 2)

plt.plot(data_fib_p_0_8_bo['n'], data_fib_p_0_8_bo['time'], label='p = 0.8', color='orange', linewidth = 2)
plt.scatter(data_fib_p_0_8_bo['n'], data_fib_p_0_8_bo['time'], color='orange', linewidth = 2)

plt.plot(data_fib_p_0_9_bo['n'], data_fib_p_0_9_bo['time'], label='p = 0.9', color='purple', linewidth = 2)
plt.scatter(data_fib_p_0_9_bo['n'], data_fib_p_0_9_bo['time'], color='purple', linewidth = 2)

plt.xlabel('Length')
plt.ylabel('Basic operations')
plt.title('Basic operations in dijkstra on graphs with density probabilities from  0.5 to 0.9')
plt.grid(True)
plt.legend()

plt.show()