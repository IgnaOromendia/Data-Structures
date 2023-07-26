import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

data_pb_l = pd.read_csv("samples/linked_push_back.csv")
data_pf_l = pd.read_csv("samples/linked_push_front.csv")
data_push_v = pd.read_csv("../samples_cpp/vector_push_back.csv")
data_pb_lc = pd.read_csv("../samples_cpp/list_push_back.csv")
data_pf_lc = pd.read_csv("../samples_cpp/list_push_front.csv")

fig1 = plt.figure(figsize=(8, 6))

plt.plot(data_pb_lc['n'], data_pb_lc['time'], label='C++ List push back', color='red', linewidth = 2)
plt.plot(data_pf_lc['n'], data_pf_lc['time'], label='C++ List push front', color='orange', linewidth = 2)
plt.plot(data_pb_l['n'], data_pb_l['time'], label='List push back', color='blue', linewidth = 2)
plt.plot(data_pf_l['n'], data_pf_l['time'], label='List push front', color='green', linewidth = 2)
plt.xlabel('N')
plt.ylabel('Time (miliseconds)')
plt.title('Insertion Double Linked List vs C++ List')
plt.suptitle('Insertion comparison with C++ list')
plt.grid(True)
plt.legend()
plt.show()

fig2 = plt.figure(figsize=(8, 6))

plt.plot(data_push_v['n'], data_push_v['time'], label='C++ Vector', color='red', linewidth = 2)
plt.plot(data_pb_l['n'], data_pb_l['time'], label='List push back', color='blue', linewidth = 2)
plt.plot(data_pf_l['n'], data_pf_l['time'], label='List push front', color='green', linewidth = 2)
plt.xlabel('N')
plt.ylabel('Time (miliseconds)')
plt.title('Insertion Double Linked List vs C++ bector')
plt.suptitle('Insertion comparison with C++ vector')
plt.grid(True)
plt.legend()
plt.show()

fig3 = plt.figure(figsize=(8, 6))








