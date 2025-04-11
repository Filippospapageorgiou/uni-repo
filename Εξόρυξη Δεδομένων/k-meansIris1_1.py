from sklearn.datasets import load_iris
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
from sklearn.metrics import silhouette_score

#βήμα 1 φόρτωση δεδομένων
meas = load_iris().data

#βήμα 2 εκτέλεση k-means
X = meas[:, [2, 3]] #χρήση των δύο τελευταίων στήλων
k = 3 #αριθμός cluster
kmeans = KMeans(n_clusters=k).fit(X)
IDX = kmeans.labels_ 
C = kmeans.cluster_centers_ 

#βήμα 3 οπτικοποιήση αποτελεσμάτων
plt.figure(figsize=(12,4))

plt.subplot(122)
plt.plot(X[IDX==0][:,0], X[IDX==0][:,1], 'limegreen', marker='o', linewidth=0, label='C1')
plt.plot(X[IDX==1][:,0], X[IDX==1][:,1], 'yellow', marker='o', linewidth=0, label='C2')
plt.plot(X[IDX==2][:,0], X[IDX==2][:,1], 'c.', marker='o', label='C3')
plt.scatter(C[:,0], C[:,1], marker='x', color='black', s=150, linewidth=3, label="Centroids", zorder=10)
plt.legend()
plt.title('Scatter plot συστάδων')
plt.xlabel('Μήκος πετάλου')
plt.ylabel('Πλάτος πετάλου')
plt.show()

# βήμα 4 ανάλυση επίδρασης του k
# Υπολογισμός SSE και silhouette score για διάφορες τιμές του k

k_range = range(2, 11)  # Δοκιμάζουμε τιμές k από 2 έως 10
sse = []
silhouette_scores = []

for k in k_range:
    kmeans = KMeans(n_clusters=k, random_state=42).fit(X)
    sse.append(kmeans.inertia_)  # inertia είναι το SSE
    silhouette_scores.append(silhouette_score(X, kmeans.labels_))

# Plotting
plt.figure(figsize=(12, 4))

# Plot SSE
plt.subplot(121)
plt.plot(list(k_range), sse, 'bo-')
plt.xlabel('Αριθμός συστάδων (k)')
plt.ylabel('SSE')
plt.title('κ - sse απεικόνιση')

# Plot Silhouette Score
plt.subplot(122)
plt.plot(list(k_range), silhouette_scores, 'ro-')
plt.xlabel('Αριθμός συστάδων (k)')
plt.ylabel('Silhouette Score')
plt.title('Συντελεστής περιγράμματος')

plt.tight_layout()
plt.show()



