import numpy as np

np.random.seed(1337)

for instance in range(9, 10):
    n = 100000 + (100000 * instance)
    f = open("../inputs/input_" + str(instance+1), "w") 
    for i in range(0,n):
        number = np.random.randint(10000)
        f.write(str(number) + "\n")
    f.close()