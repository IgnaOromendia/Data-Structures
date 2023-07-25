import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

data = pd.read_csv("runtime.csv")

rate = np.polyfit(data['n'], data['time'], 1)
trend_line = np.polyval(rate, data['n'])

plt.plot(data['n'], data['time'], linewidth = 2.5, label = 'Time')
plt.plot(data['n'], trend_line, color = 'red', linewidth = 1.5, label = 'Tendency')

plt.xlabel('N')
plt.ylabel('Time (microseconds)')
plt.title('Linked list access time')
plt.legend()
plt.show()