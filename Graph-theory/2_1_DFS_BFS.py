import pandas as pd
from collections import deque
import sys
from datetime import datetime

class Graph:
    def __init__(self):
        """
        Αρχικοποιεί έναν κενό γράφο
        adjacency_list: dictionary που αποθηκεύει {κορυφή: [γείτονες]}
        vertices: set με όλες τις κορυφές του γράφου
        """       
        self.adjacency_list = {}
        self.vertices = set()
        #Η αποθήκευση θα γίνει σε ξεχωριστό file για καλύτερη ανάγνωση των αποτελεσμάτων
        self.output_file = None

    def set_output_file(self, filename):
        """
        Ορίζει το αρχείο εξόδου για τα αποτελέσματα
        """
        self.output_file = filename

    def print_output(self,message):
        """
        Εκτυπώνει μήνυμα στο terminal και το γράφει σε αρχείο 
        """
        print(message)
        if self.output_file:
            with open(self.output_file, 'a', encoding='utf-8') as f:
                f.write(message + '\n')


    def load_from_csv(self, filename):
        """
        Φορτώνει γράφο από CSV αρχείο
        Μορφή CSV: κορυφή γείτονας1 γείτονας2 ...
        Παραλείπει γραμμές που αρχίζουν με #
        """
        try:
            with open(filename, 'r', encoding = 'UTF-8') as file:
                for line_num, line in enumerate(file,1):
                    line = line.strip()

                    if not line or line.startswith('#'):
                        continue
                    
                    parts = line.split()
                    if len(parts)==0:
                        continue

                    vertex = int(parts[0])
                    neighbors = []
                    for i in range(1, len(parts)):
                        neighbors.append(int(parts[i]))

                    self.add_vertex(vertex)
                    for neighbor in neighbors:
                        self.add_edge(vertex,neighbor)
                    
        except FileNotFoundError:   
                print("File not found")
        except ValueError as e:
                print(f"Σφάλμα στη γραμμή {line_num}: {e}")

    def add_vertex(self,vertex):
        """
        Προσθέτει κορυφή στον γράφο
        """
        self.vertices.add(vertex)
        if vertex not in self.adjacency_list:
             self.adjacency_list[vertex] = []

    def add_edge(self,from_vertex, to_vertex):
         """
        Προσθέτει ακμή από from_vertex προς to_vertex
        """
        # Προσθέτουμε τις κορυφές αν δεν υπάρχουν
         self.add_vertex(from_vertex)
         self.add_vertex(to_vertex)

         #Προσθέτουμε την ακμή
         if to_vertex not in self.adjacency_list[from_vertex]:
            self.adjacency_list[from_vertex].append(to_vertex)
    
    def get_neighbors(self, vertex):
        """
        Επιστρέφει τους γείτονες μιας κορυφής
        """
        return self.adjacency_list.get(vertex, [])
    
    def get_vertices(self):
        """
        Επιστρέφει όλες τις κορυφές του γράφου
        """
        return self.vertices
    
    def has_vertex(self, vertex):
        """
        Ελέγχει αν υπάρχει κορυφή στον γράφο
        """
        return vertex in self.vertices
    
    def display_graph(self):
        """
        Εμφανίζει τον γράφο σε αναγνώσιμη μορφή
        """
        print("Γράφος:")
        for vertex in sorted(self.vertices):
            neighbors = self.get_neighbors(vertex)
            print(f"  {vertex} -> {neighbors}")
    
    def get_stats(self):
        """
        Επιστρέφει βασικά στατιστικά του γράφου
        """
        total_vertices = len(self.vertices)
        total_edges = sum(len(neighbors) for neighbors in self.adjacency_list.values())
        
        return {
            'vertices': total_vertices,
            'edges': total_edges,
            'avg_degree': total_edges / total_vertices if total_vertices > 0 else 0
        }
    
    def DFS(self, start_vertex):
        """
        Depth-First Search (DFS) - Αναζήτηση πρώτα κατά βάθος
        Επιστρέφει τη σειρά επίσκεψης των κορυφών
        """
        if not self.has_vertex(start_vertex):
            print(f"Η κορυφή {start_vertex} δεν υπάρχει στον γράφο")
            return []
        
        visited = set()
        result = []
        
        def dfs_recursive(vertex):
            visited.add(vertex)
            result.append(vertex)
            print(f"Επισκέπτομαι κορυφή: {vertex}")
            
            # Επισκεπτόμαστε όλους τους γείτονες
            for neighbor in sorted(self.get_neighbors(vertex)):  # Ταξινόμηση γειτόνων
                if neighbor not in visited:
                    dfs_recursive(neighbor)
        
        print(f"\n=== DFS ξεκινώντας από κορυφή {start_vertex} ===")
        dfs_recursive(start_vertex)
        return result
    

    def BFS(self, start_vertex):
        """
        Breadth-First Search (BFS) - Αναζήτηση πρώτα κατά πλάτος
        Επιστρέφει τη σειρά επίσκεψης των κορυφών
        """
        if not self.has_vertex(start_vertex):
            print(f"Η κορυφή {start_vertex} δεν υπάρχει στον γράφο")
            return []

        visited = set()
        result = []
        queue = deque([start_vertex])

        print(f"\n=== BFS ξεκινώντας από κορυφή {start_vertex} ===")
        while queue:
            vertex = queue.popleft()

            if vertex not in visited:
                visited.add(vertex)
                result.append(vertex)
                print(f"Επισκέπτομαι κορυφή: {vertex}")

                for neighbor in sorted(self.get_neighbors(vertex)):
                    if neighbor not in visited:
                        queue.append(neighbor)
            
        return result
    
    def run_searches(self, start_vertex):
        """
        Εκτελεί και τις δύο αναζητήσεις (DFS και BFS) και εμφανίζει τα αποτελέσματα
        """
        self.print_output(f"\n{'='*50}")
        self.print_output(f"ΑΝΑΖΗΤΗΣΕΙΣ ΣΤΟ ΓΡΑΦΟ")
        self.print_output(f"{'='*50}")
        
        # DFS
        dfs_result = self.DFS(start_vertex)
        self.print_output(f"\nΣειρά επίσκεψης DFS: {dfs_result}")
        
        # BFS
        bfs_result = self.BFS(start_vertex)
        self.print_output(f"\nΣειρά επίσκεψης BFS: {bfs_result}")
        
        # Σύγκριση
        self.print_output(f"\n{'='*50}")
        self.print_output(f"ΣΥΓΚΡΙΣΗ ΑΠΟΤΕΛΕΣΜΑΤΩΝ")
        self.print_output(f"{'='*50}")
        self.print_output(f"DFS επισκέφθηκε {len(dfs_result)} κορυφές: {dfs_result}")
        self.print_output(f"BFS επισκέφθηκε {len(bfs_result)} κορυφές: {bfs_result}")
        
        if dfs_result == bfs_result:
            self.print_output("Οι δύο αλγόριθμοι επισκέφθηκαν τις κορυφές με την ίδια σειρά")
        else:
            self.print_output("Οι δύο αλγόριθμοι επισκέφθηκαν τις κορυφές με διαφορετική σειρά")

    def save_detailed_results(self, filename, start_vertex):
        """
        Αποθηκεύει λεπτομερή αποτελέσματα σε αρχείο (δομή γράφου, αποτελέσματα εκτέλεσης, σύγκριση των δύο αλγοριθμών για τον γράφο)
        """
        with open(filename, 'w', encoding='utf-8') as f:
            # Header που κράταει την ημερομήνια εκτέλεσης
            f.write("="*60 + "\n")
            f.write(f"ΑΝΑΛΥΣΗ ΓΡΑΦΟΥ - {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
            f.write("="*60 + "\n\n")
            
            # Στατιστικά γράφου
            stats = self.get_stats()
            f.write("ΣΤΑΤΙΣΤΙΚΑ ΓΡΑΦΟΥ:\n")
            f.write(f"  Αριθμός κορυφών: {stats['vertices']}\n")
            f.write(f"  Αριθμός ακμών: {stats['edges']}\n")
            f.write(f"  Μέσος βαθμός: {stats['avg_degree']:.2f}\n\n")
            
            # Δομή γράφου
            f.write("ΔΟΜΗ ΓΡΑΦΟΥ:\n")
            for vertex in sorted(self.vertices):
                neighbors = self.get_neighbors(vertex)
                f.write(f"  {vertex} -> {neighbors}\n")
            f.write("\n")
            
            # Αποτελέσματα αναζητήσεων
            f.write("ΑΠΟΤΕΛΕΣΜΑΤΑ ΑΝΑΖΗΤΗΣΕΩΝ:\n")
            f.write(f"Αφετηρία: {start_vertex}\n\n")
            
            # Εκτέλεση DFS
            dfs_result = self.DFS(start_vertex)
            f.write(f"DFS: {dfs_result}\n")
            
            # Εκτέλεση BFS  
            bfs_result = self.BFS(start_vertex)
            f.write(f"BFS: {bfs_result}\n\n")
            
            # Σύγκριση
            f.write("ΣΥΓΚΡΙΣΗ:\n")
            f.write(f"O DFS επισκέφθηκε {len(dfs_result)} κορυφές\n")
            f.write(f"O BFS επισκέφθηκε {len(bfs_result)} κορυφές\n")
            
            if dfs_result == bfs_result:
                f.write("Ίδια σειρά επίσκεψης\n")
            else:
                f.write("Διαφορετική σειρά επίσκεψης\n")



if __name__ == "__main__":
    # Δημιουργία γράφου
    graph = Graph()
    
    # Import από CSV
    graph.load_from_csv('graph1.csv')
    
    # Εμφάνιση στατιστικών
    stats = graph.get_stats()
    graph.print_output(f"Στατιστικά γράφου:")
    graph.print_output(f"  Κορυφές: {stats['vertices']}")
    graph.print_output(f"  Ακμές: {stats['edges']}")
    graph.print_output(f"  Μέσος βαθμός: {stats['avg_degree']:.2f}")
    
    # Εκτέλεση αναζητήσεων
    first_vertex = min(graph.get_vertices())
    graph.run_searches(first_vertex)
    
    # Δημιουργία λεπτομερούς αναφοράς
    graph.save_detailed_results("detailed_analysis.txt", first_vertex)
    
    print(f"\nΤα αποτελέσματα αποθηκεύτηκαν στο αρχείο:")
    print(f"  - detailed_analysis.txt ")