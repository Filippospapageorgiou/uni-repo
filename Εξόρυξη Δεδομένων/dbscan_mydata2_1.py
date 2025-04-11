import scipy.io
import numpy as np
from sklearn.cluster import DBSCAN
import matplotlib.pyplot as plt


 #βήμα 1 φόρττωση δεδομένων
mat_file = scipy.io.loadmat('mydata.mat')
X = np.array(mat_file['X'])

#eps (ε): Η μέγιστη απόσταση μεταξύ δύο σημείων για να θεωρηθούν γείτονες
#min_samples: Ο ελάχιστος αριθμός σημείων για να σχηματιστεί μια συστάδα
 
#βήμα 2 έκτελεση DBSCAN αλγορίθμου 
#Με τις παραμέτρους που μας ζητάει 
dbscan = DBSCAN(eps=0.5, min_samples=15).fit(X)
IDX = dbscan.labels_

#βήμα 3 γράφημα διασποεάς αρχικών δεδομένων
plt.figure(figsize=(10,5))
plt.subplot(121)
plt.scatter(X[:,0],X[:,1])
plt.title('Αρχικά δεδομένα')
plt.xlabel('Διάσταση 1')
plt.ylabel('Δίασταση 2')

#βήμα 4 γράφημα συστάδων
plt.subplot(122)
plt.scatter(X[:,0],X[:,1],c=IDX,cmap='viridis')
plt.title('Συστάδες DBSCAN')
plt.xlabel('Διάσταση 1')
plt.ylabel('Διάσταση 2')
plt.colorbar(label='αριθμός συστάδας')

plt.tight_layout()
plt.show()

#Προσθήκη εκτύπωση για extra πληροφορίες
n_clusters = len(set(IDX)) - (1 if -1 in IDX else 0)
n_noise = list(IDX).count(-1)

print("\nΑποτελέσματα DBSCAN:")
print(f"Αριθμός σύσταδων: {n_clusters}")
print(f"Αριθμός σημείων Θορύβου: {n_noise}")