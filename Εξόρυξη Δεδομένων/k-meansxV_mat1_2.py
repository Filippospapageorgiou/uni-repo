import scipy.io
import numpy as np
from sklearn.cluster import KMeans
import  matplotlib.pyplot as plt

#βήμα 1 φορτώση δεδομένων 
mat_file = scipy.io.loadmat('xV.mat') 
xV = np.array(mat_file['xV'])
sse_array = [] 

#Σύναρτηση για την εκτέλεση k-means και δημιουργία γραφήματος
#Και γυρνάει το SSE για να μην επναλμβάνω κώδικα
def perform_clustering(X, k=3, title=""):
    
    kmeans = KMeans(n_clusters=k).fit(X)
    IDX = kmeans.labels_
    C = kmeans.cluster_centers_
    
    plt.figure(figsize=(8, 6))
    plt.plot(X[IDX==0][:,0], X[IDX==0][:,1], 'limegreen', marker='o', linewidth=0, label='C1')
    plt.plot(X[IDX==1][:,0], X[IDX==1][:,1], 'yellow', marker='o', linewidth=0, label='C2')
    plt.plot(X[IDX==2][:,0], X[IDX==2][:,1], 'c.', marker='o', label='C3')
    plt.scatter(C[:,0], C[:,1], marker='x', color='black', s=150, linewidth=3, label="Centroids", zorder=10)
    plt.legend()
    plt.title(title)
    plt.show()
    
    # Υπολογισμός SSE
    sse = kmeans.inertia_
    return sse

#βήμα 2 , k-means με τα πρώτα δύο χαρακτηριστικά
X_first = xV[:,[0,1]]
sse_first = perform_clustering(X_first,title="k-means με τα πρώτα δύο χαρακτηριστικά")
sse_array.append(sse_first)


#βήμα 3 k-means με τα χαρακτηριστικά [296, 305]
X_middle = xV[:,[296, 305]]
sse_middle = perform_clustering(X_middle, title="K-means με τα χαρακτηριστικά [296, 305]")
sse_array.append(sse_middle)


#βήμα 4 k-means με τα δύο τελευταία χαρακτηριστικά
X_last = xV[:,-2:]
sse_last = perform_clustering(X_last, title="K-means με τα δύο τελευταία χαρακτηριστικά")
sse_array.append(sse_last)

#βήμα 5 k-means με τα χαρακτηριστικά [205, 175]
X_custom = xV[:,[205, 175]]
sse_custom = perform_clustering(X_custom, title="K-means με τα χαρακτηριστικά [205, 175]")
sse_array.append(sse_custom)

#format print sse τιμών
print("\nΠίνακας SSE:")
print("-" * 50)
print("| Βήμα | Χαρακτηριστικά         | SSE         |")
print("-" * 50)
print(f"| 2    | Πρώτα                 | {sse_array[0]:.2f}     |")
print(f"| 3    | [296, 305]            | {sse_array[1]:.2f}     |")
print(f"| 4    | Τελευταία             | {sse_array[2]:.2f}     |")
print(f"| 5    | [205, 175]            | {sse_array[3]:.2f}     |")
print("-" * 50)