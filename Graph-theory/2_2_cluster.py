import numpy as np
import matplotlib.pyplot as plt

class Graph:
    def __init__(self):
        self.adj_matrix = None
        self.n_vertices = 0
        self.vertices = []
        self.adj_list = {}  
    
    def load_from_csv(self, filename):
        """
        Φορτώνει τον γράφο από το CSV αρχείο
        """
        print("Διαβάζω αρχείο:", filename)
        
       
        with open(filename, 'r',encoding='utf-8') as file:
            lines = file.readlines()
        
       
        data_lines = []
        for line in lines:
            line = line.strip()
            if not line.startswith('#') and line:
                data_lines.append(line)
        
        print(f"Βρήκα {len(data_lines)} γραμμές δεδομένων")
        
        
        all_vertices = set()
        temp_adj_list = {}
        
        for line in data_lines:
            parts = line.split()
            vertex = int(parts[0])
            neighbors = [int(x) for x in parts[1:]]
            
            # Προσθέτουμε όλες τις κορυφές στο σύνολο
            all_vertices.add(vertex)
            for neighbor in neighbors:
                all_vertices.add(neighbor)
            
            # Αποθηκεύουμε τη λίστα γειτνίασης
            temp_adj_list[vertex] = neighbors
        
        #Δημιουργούμε το μητρώο γειτνίασης
        self.vertices = sorted(list(all_vertices))
        self.n_vertices = len(self.vertices)
        
        print(f"Συνολικές κορυφές: {self.n_vertices}")
        print(f"Εύρος κορυφών: {min(self.vertices)} έως {max(self.vertices)}")
        
        # Δημιουργούμε mapping από κορυφή σε index
        vertex_to_index = {v: i for i, v in enumerate(self.vertices)}
        
        # Δημιουργούμε το μητρώο γειτνίασης
        self.adj_matrix = np.zeros((self.n_vertices, self.n_vertices), dtype=int)
        
        # Συμπληρώνουμε το μητρώο
        edge_count = 0
        for vertex, neighbors in temp_adj_list.items():
            vertex_idx = vertex_to_index[vertex]
            for neighbor in neighbors:
                neighbor_idx = vertex_to_index[neighbor]
                self.adj_matrix[vertex_idx][neighbor_idx] = 1
                edge_count += 1
        
        # Δημιουργούμε και τη λίστα γειτνίασης με indices
        self.adj_list = {}
        for vertex, neighbors in temp_adj_list.items():
            vertex_idx = vertex_to_index[vertex]
            self.adj_list[vertex_idx] = [vertex_to_index[n] for n in neighbors]
        
        print(f"Συνολικές ακμές: {edge_count}")
        print("Γράφος φορτώθηκε επιτυχώς!")
        
        return self
    
    def to_undirected(self):
        """
        Μετατρέπει τον γράφο σε μη-κατευθυνόμενο
        """
        print("Μετατρέπω τον γράφο σε μη-κατευθυνόμενο...")
        
        # Για το μητρώο γειτνίασης: A_undirected = A + A.T
        # Αλλά θέλουμε να μείνουν 0 και 1, όχι 2
        self.adj_matrix = np.clip(self.adj_matrix + self.adj_matrix.T, 0, 1)
        
        # Ενημερώνουμε και τη λίστα γειτνίασης
        new_adj_list = {}
        for i in range(self.n_vertices):
            neighbors = set()
            # Προσθέτουμε τους υπάρχοντες γείτονες
            if i in self.adj_list:
                neighbors.update(self.adj_list[i])
            # Προσθέτουμε και τους "αντίστροφους" γείτονες
            for j in range(self.n_vertices):
                if self.adj_matrix[i][j] == 1:
                    neighbors.add(j)
            new_adj_list[i] = list(neighbors)
        
        self.adj_list = new_adj_list
        
        # Μετράμε τις νέες ακμές , διαιρούμε με 2 γιατί κάθε ακμή μετράται 2 φορές
        edge_count = np.sum(self.adj_matrix) // 2  
        print(f"Μετατροπή ολοκληρώθηκε. Νέος αριθμός ακμών: {edge_count}")
        
        return self
    
    def find_triangles_optimized(self):
        # Χρησιμοποιούμε τον τύπο: A³[i,i] = αριθμός τριγώνων που περιέχουν την κορυφή i
        
        # Μέθοδος 1: Πολλαπλασιασμός μητρώων
        A = self.adj_matrix.astype(np.int32)  # Μετατροπή σε int32 για ταχύτητα
        A_squared = np.dot(A, A)
        
        triangles_per_vertex = np.zeros(self.n_vertices, dtype=int)
        
        # Για κάθε κορυφή i, μετράμε τα τρίγωνα
        for i in range(self.n_vertices):
            # Βρίσκουμε τους γείτονες της κορυφής i
            neighbors = np.where(A[i] == 1)[0]
            
            # Για κάθε ζεύγος γειτόνων, ελέγχουμε αν συνδέονται
            triangle_count = 0
            for j in range(len(neighbors)):
                for k in range(j + 1, len(neighbors)):
                    neighbor1 = neighbors[j]
                    neighbor2 = neighbors[k]
                    if A[neighbor1][neighbor2] == 1:
                        triangle_count += 1
            
            triangles_per_vertex[i] = triangle_count
        
        # Συνολικός αριθμός τριγώνων (κάθε τρίγωνο μετράται 3 φορές)
        total_triangles = np.sum(triangles_per_vertex) // 3
        
        print(f"Βρήκα {total_triangles} τρίγωνα συνολικά")
        print(f"Μέσος αριθμός τριγώνων ανά κορυφή: {np.mean(triangles_per_vertex):.2f}")
        
        return total_triangles, triangles_per_vertex
    
    def find_triangles_super_fast(self):
        A = self.adj_matrix
        triangles_per_vertex = np.zeros(self.n_vertices, dtype=int)
        
        # Για κάθε κορυφή, χρησιμοποιούμε vectorized operations
        for i in range(self.n_vertices):
            # Βρίσκουμε τους γείτονες
            neighbors = A[i] == 1
            
            if np.sum(neighbors) < 2:
                continue  # Δεν μπορεί να σχηματίσει τρίγωνο
            
            # Παίρνουμε το υπο-μητρώο των γειτόνων
            neighbor_indices = np.where(neighbors)[0]
            submatrix = A[np.ix_(neighbor_indices, neighbor_indices)]
            
            # Μετράμε τις συνδέσεις μεταξύ γειτόνων
            triangles_per_vertex[i] = np.sum(np.triu(submatrix, k=1))
        
        total_triangles = np.sum(triangles_per_vertex) // 3
        
        print(f"Βρήκα {total_triangles} τρίγωνα συνολικά")
        print(f"Μέσος αριθμός τριγώνων ανά κορυφή: {np.mean(triangles_per_vertex):.2f}")
        
        return total_triangles, triangles_per_vertex
    
    def calculate_clustering_coefficients(self):
        """
        Υπολογίζει τους συντελεστές συσταδοποίησης
        """
        print("\nΥπολογίζω συντελεστές συσταδοποίησης...")
        
        
        total_triangles, triangles_per_vertex = self.find_triangles_super_fast()
        
        # Υπολογίζουμε τους βαθμούς των κορυφών
        degrees = np.sum(self.adj_matrix, axis=1)
        
        # Υπολογίζουμε τους συντελεστές συσταδοποίησης για κάθε κορυφή
        clustering_coefficients = np.zeros(self.n_vertices)
        open_triangles = np.zeros(self.n_vertices, dtype=int)
        
        for i in range(self.n_vertices):
            degree = degrees[i]
            
            # Υπολογίζουμε τον αριθμό των δυνατών τριγώνων (open triangles)
            # oi = di * (di - 1) / 2
            if degree >= 2:
                open_triangles[i] = degree * (degree - 1) // 2
                
                # Υπολογίζουμε τον συντελεστή συσταδοποίησης
                # ci = ti / oi
                clustering_coefficients[i] = triangles_per_vertex[i] / open_triangles[i]
            else:
                # Αν η κορυφή έχει βαθμό < 2, δεν μπορεί να σχηματίσει τρίγωνο
                clustering_coefficients[i] = 0.0
        
        # Υπολογίζουμε τον ολικό συντελεστή συσταδοποίησης C
        # C = (1/n) * Σ(ci)
        C = np.mean(clustering_coefficients)
        
        # Υπολογίζουμε τον εναλλακτικό συντελεστή C'
        # C' = Σ(ti) / Σ(oi)
        total_triangles_sum = np.sum(triangles_per_vertex)
        total_open_triangles = np.sum(open_triangles)
        
        if total_open_triangles > 0:
            C_prime = total_triangles * 3 / total_open_triangles
        else:
            C_prime = 0.0
        
        
        print(f"\n=== ΑΠΟΤΕΛΕΣΜΑΤΑ ΣΥΣΤΑΔΟΠΟΙΗΣΗΣ ===")
        print(f"Συνολικά τρίγωνα: {total_triangles}")
        print(f"Άθροισμα τριγώνων ανά κορυφή: {total_triangles_sum} (κάθε τρίγωνο μετράται 3 φορές)")
        print(f"Μέσος αριθμός τριγώνων ανά κορυφή: {np.mean(triangles_per_vertex):.2f}")
        print(f"Μέσος αριθμός δυνατών τριγώνων ανά κορυφή: {np.mean(open_triangles):.2f}")
        print(f"\nΟλικός συντελεστής συσταδοποίησης C: {C:.6f}")
        print(f"Εναλλακτικός συντελεστής C': {C_prime:.6f}")
        print(f"Διαφορά C - C': {C - C_prime:.6f}")
        
        
        
        print(f"\n=== ΣΤΑΤΙΣΤΙΚΑ ΣΥΝΤΕΛΕΣΤΩΝ ===")
        print(f"Ελάχιστος συντελεστής: {np.min(clustering_coefficients):.6f}")
        print(f"Μέγιστος συντελεστής: {np.max(clustering_coefficients):.6f}")
        print(f"Διάμεσος συντελεστής: {np.median(clustering_coefficients):.6f}")
        print(f"Τυπική απόκλιση: {np.std(clustering_coefficients):.6f}")
        
        return {
            'total_triangles': total_triangles,
            'triangles_per_vertex': triangles_per_vertex,
            'clustering_coefficients': clustering_coefficients,
            'open_triangles': open_triangles,
            'C': C,
            'C_prime': C_prime
        }
    
    def plot_results(self, results):
        
        
        fig, axes = plt.subplots(2, 2, figsize=(15, 12))
        
        # 1. Κατανομή συντελεστών συσταδοποίησης
        axes[0, 0].hist(results['clustering_coefficients'], bins=50, alpha=0.7, color='blue')
        axes[0, 0].set_title('Κατανομή Συντελεστών Συσταδοποίησης')
        axes[0, 0].set_xlabel('Συντελεστής Συσταδοποίησης')
        axes[0, 0].set_ylabel('Συχνότητα')
        axes[0, 0].axvline(results['C'], color='red', linestyle='--', label=f'Μέσος C={results["C"]:.3f}')
        axes[0, 0].legend()
        
        # 2. Σχέση βαθμού - αριθμού τριγώνων
        degrees = np.sum(self.adj_matrix, axis=1)
        axes[0, 1].scatter(degrees, results['triangles_per_vertex'], alpha=0.6, s=20)
        axes[0, 1].set_title('Βαθμός vs Αριθμός Τριγώνων')
        axes[0, 1].set_xlabel('Βαθμός Κορυφής')
        axes[0, 1].set_ylabel('Αριθμός Τριγώνων')
        
        # 3. Σχέση βαθμού - συντελεστή συσταδοποίησης
        axes[1, 0].scatter(degrees, results['clustering_coefficients'], alpha=0.6, s=20, color='green')
        axes[1, 0].set_title('Βαθμός vs Συντελεστής Συσταδοποίησης')
        axes[1, 0].set_xlabel('Βαθμός Κορυφής')
        axes[1, 0].set_ylabel('Συντελεστής Συσταδοποίησης')
        
        # 4. Σύγκριση C και C'
        comparison_data = [results['C'], results['C_prime']]
        labels = ['C (μέσος όρος)', "C' (εναλλακτικός)"]
        axes[1, 1].bar(labels, comparison_data, color=['blue', 'red'], alpha=0.7)
        axes[1, 1].set_title('Σύγκριση Συντελεστών C και C\'')
        axes[1, 1].set_ylabel('Τιμή Συντελεστή')
        
        # Προσθέτουμε τις τιμές πάνω από τις μπάρες
        for i, v in enumerate(comparison_data):
            axes[1, 1].text(i, v + 0.001, f'{v:.6f}', ha='center', va='bottom')
        
        plt.tight_layout()
        plt.show()
        
        
        print(f"\n=== ΕΠΙΠΛΕΟΝ ΑΝΑΛΥΣΗ ===")
        print(f"Συσχέτιση βαθμού-τριγώνων: {np.corrcoef(degrees, results['triangles_per_vertex'])[0,1]:.4f}")
        print(f"Συσχέτιση βαθμού-συντελεστή: {np.corrcoef(degrees, results['clustering_coefficients'])[0,1]:.4f}")
        
        # Βρίσκουμε τις πιο και λιγότερο συσταδοποιημένες κορυφές
        max_idx = np.argmax(results['clustering_coefficients'])
        min_idx = np.argmin(results['clustering_coefficients'])
        
        print(f"\nΠιο συσταδοποιημένη κορυφή: {self.vertices[max_idx]} (ci={results['clustering_coefficients'][max_idx]:.6f})")
        print(f"Λιγότερο συσταδοποιημένη κορυφή: {self.vertices[min_idx]} (ci={results['clustering_coefficients'][min_idx]:.6f})")
    
    def print_basic_info(self):
        """
        Εμφανίζει βασικές πληροφορίες για τον γράφο
        """
        print("\n=== ΒΑΣΙΚΕΣ ΠΛΗΡΟΦΟΡΙΕΣ ΓΡΑΦΟΥ ===")
        print(f"Κορυφές: {self.n_vertices}")
        print(f"Μέγεθος μητρώου: {self.adj_matrix.shape}")
        
        # Υπολογίζουμε τους βαθμούς των κορυφών
        degrees = np.sum(self.adj_matrix, axis=1)
        print(f"Μέσος βαθμός κορυφών: {np.mean(degrees):.2f}")
        print(f"Ελάχιστος βαθμός: {np.min(degrees)}")
        print(f"Μέγιστος βαθμός: {np.max(degrees)}")
        
        # Δείχνουμε μερικά παραδείγματα
        print("\nΠαραδείγματα συνδέσεων:")
        for i in range(min(5, self.n_vertices)):
            vertex_name = self.vertices[i]
            degree = degrees[i]
            print(f"Κορυφή {vertex_name} (index {i}): βαθμός {degree}")


# Δοκιμάζουμε τον κώδικα
if __name__ == "__main__":
    # Δημιουργούμε τον γράφο
    g = Graph()
    
    # Φορτώνουμε τα δεδομένα
    g.load_from_csv("graph1.csv")
    
    # Εμφανίζουμε βασικές πληροφορίες
    g.print_basic_info()
    
    # Μετατρέπουμε σε μη-κατευθυνόμενο
    g.to_undirected()
    
    # Εμφανίζουμε πάλι τις πληροφορίες
    g.print_basic_info()
    
    # Υπολογίζουμε τους συντελεστές συσταδοποίησης
    results = g.calculate_clustering_coefficients()
    
    # Δημιουργούμε γραφήματα
    g.plot_results(results)