import pandas as pd
import numpy as np
import os

data = pd.read_csv("/home/kali/Desktop/regression_c/final_dataset.csv")
data = data.iloc[:,:-1].to_numpy()
print(data.shape," ", type(data))
#print("\n", data)


sorted_indices = np.argsort(data[:, -1])
sorted_dataset = data[sorted_indices]
print(sorted_dataset[:,4:])

np.savetxt("final_dataset.txt",sorted_dataset)
os.system("cp final_dataset.txt final_dataset.csv")
