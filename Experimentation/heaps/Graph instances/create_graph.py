import numpy as np
import random

np.random.seed(1337)

start_n = 2000
step_n = 2000

for instance in range(0, 5):
    n = start_n + (instance * step_n)
    for i in range(0,5):
        p = 0.5 + (0.1 * i)
        f = open("inputs/progressive/input_" + str(n) + "_p_" + str(i), "w") 
        for i in range(0,n):
            for j in range(0,n):
                if i != j:
                    if random.random() <= p:
                        v = i+1
                        w = j+1
                        c = 1 + np.random.randint(1000)
                        f.write(str(v) + " " + str(w) + " " + str(c) + "\n")
    f.close()