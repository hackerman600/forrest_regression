import pandas as pd
import random as rd
from imblearn.over_sampling import SMOTE
import os
import numpy as np

data = pd.read_csv("/home/kali/Desktop/regression_c/dataset_pre_y.csv")
zeros = pd.DataFrame(0,index=range(data.shape[0]),columns=range(1))
feature_importance_score_and_noise = {0:15000,1:55000,2:800,3:850}
data_y = pd.concat([data,zeros],axis=1).to_numpy()
print("shape of the data = ", data.shape)

for i in range(1,data.shape[0]+1):
    row = data[i-1:i].to_numpy()
    label = 0
    for val_ind,vals in enumerate(row[0]):
        label += (feature_importance_score_and_noise[val_ind] * rd.uniform(1,1.5) * row[0,val_ind])   
    data_y[i-1,4] = label


#SAVE LABELLED DATA AS CSV.
np.savetxt("labelled_data.txt",data_y,delimiter = ',')
os.system("cp labelled_data.txt labelled_data.csv")




