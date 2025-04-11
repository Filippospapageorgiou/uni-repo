from sklearn.datasets import load_iris
from sklearn.cluster import DBSCAN
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import zscore 


#βήμα 1 φόρτωση δεδομένων iris 
meas = load_iris().data
X = meas[:,[2,3]]

#βήμα 2 εκτέλεση dbscan στα σρχικά δεδομένα 
dbscan = DBSCAN(eps=0.1, min_samples=5).fit(X)
IDX = dbscan.labels_

#βήμα 3 & 4 γραφήματα για τα αρχικά δεδομένα
plt.figure(figsize=(12,4))

#αρχικά δεδομένα 
plt.subplot(131)
plt.scatter(X[:,0],X[:,1])
plt.title("Αρχικά δεδομένα")
plt.xlabel("Μήκος πέταλου")
plt.ylabel("Πλάτος πέταλου")

# Συστάδες DBSCAN στα αρχικά δεδομένα
plt.subplot(132)
plt.scatter(X[:,0], X[:,1], c=IDX, cmap='viridis')
plt.title('Συστάδες DBSCAN\nΑρχικά δεδομένα')
plt.xlabel('Μήκος πετάλου')
plt.ylabel('Πλάτος πετάλου')
plt.colorbar(label='Αριθμός συστάδας')


#βήμα 5 κανονικοποιήση και DBSCNA 
# Και κανονικοποιηση με z-score
xV1 = zscore(X[:,0])
xV2 = zscore(X[:,1])
Xnew = np.transpose(np.array([xV1,xV2]))

#εκτέλεση DBSCAN στα κανονικοποιημενα δεδομένα 
dbscan_norm = DBSCAN(eps=0.1, min_samples=5).fit(Xnew)
IDX_norm = dbscan_norm.labels_

# Γράφημα για κανονικοποιημένα δεδομένα
plt.subplot(133)
plt.scatter(Xnew[:,0], Xnew[:,1], c=IDX_norm, cmap='viridis')
plt.title('Συστάδες DBSCAN\nΚανονικοποιημένα δεδομένα')
plt.xlabel('Μήκος πετάλου (z-score)')
plt.ylabel('Πλάτος πετάλου (z-score)')
plt.colorbar(label='Αριθμός συστάδας')

plt.tight_layout()
plt.show()

# Εκτύπωση στατιστικών για τα αποτελέσματα
# για βοήθεια κατανοήσης των δεδομένων και αποτελεσμάτων
print("\nΑποτελέσματα για αρχικά δεδομένα:")
n_clusters = len(set(IDX)) - (1 if -1 in IDX else 0)
n_noise = list(IDX).count(-1)
print(f"Αριθμός συστάδων: {n_clusters}")
print(f"Αριθμός σημείων θορύβου: {n_noise}")

print("\nΑποτελέσματα για κανονικοποιημένα δεδομένα:")
n_clusters_norm = len(set(IDX_norm)) - (1 if -1 in IDX_norm else 0)
n_noise_norm = list(IDX_norm).count(-1)
print(f"Αριθμός συστάδων: {n_clusters_norm}")
print(f"Αριθμός σημείων θορύβου: {n_noise_norm}")