import heapq

class Graph:
    def __init__(self):
        """
        Αρχικοποιεί έναν κενό γράφο
        adjacency_list: dictionary που αποθηκεύει {κορυφή: [γείτονες]}
        vertices: set με όλες τις κορυφές του γράφου
        """
        self.adjacency_list = {}
        self.vertices = set()
    
    def load_from_csv(self, filename):
        """
        Φορτώνει γράφο από CSV αρχείο
        Μορφή CSV: κορυφή γείτονας1 γείτονας2 ...
        Παραλείπει γραμμές που αρχίζουν με #
        """
        try:
            with open(filename, 'r', encoding='utf-8') as file:
                for line_num, line in enumerate(file, 1):
                    # Αφαίρεση κενών και έλεγχος αν είναι κενή γραμμή
                    line = line.strip()
                    if not line or line.startswith('#'):
                        continue
                    
                    # Διαχωρισμός της γραμμής σε μέρη
                    parts = line.split()
                    if len(parts) == 0:
                        continue
                    
                    # Το πρώτο στοιχείο είναι η κορυφή
                    vertex = int(parts[0])
                    
                    # Τα υπόλοιπα είναι οι γείτονες
                    neighbors = []
                    for i in range(1, len(parts)):
                        neighbors.append(int(parts[i]))
                    
                    # Προσθήκη στον γράφο
                    self.add_vertex(vertex)
                    for neighbor in neighbors:
                        self.add_edge(vertex, neighbor)
                        
        except FileNotFoundError:
            print(f"Σφάλμα: Το αρχείο {filename} δεν βρέθηκε.")
        except ValueError as e:
            print(f"Σφάλμα στη γραμμή {line_num}: {e}")
    
    def add_vertex(self, vertex):
        """
        Προσθέτει κορυφή στον γράφο
        """
        self.vertices.add(vertex)
        if vertex not in self.adjacency_list:
            self.adjacency_list[vertex] = []
    
    def add_edge(self, from_vertex, to_vertex):
        """
        Προσθέτει ακμή από from_vertex προς to_vertex
        """
        # Προσθέτουμε τις κορυφές αν δεν υπάρχουν
        self.add_vertex(from_vertex)
        self.add_vertex(to_vertex)
        
        # Προσθέτουμε την ακμή
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
            print(f"  {vertex} → {neighbors}")
    
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


def dijkstra(graph: Graph, start_vertex, end_vertex=None):
    """
    Υλοποίηση του αλγορίθμου Dijkstra για εύρεση συντομότερων διαδρομών
    
    παραμέτροι:
        graph: Αντικείμενο Graph
        start_vertex: Αρχική κορυφή
        end_vertex: Τελική κορυφή (προαιρετικό - αν δοθεί, σταματάει όταν τη βρει)
    
    γυρναέι:
        distances: Dictionary με αποστάσεις από start_vertex σε κάθε κορυφή
        previous: Dictionary για ανακατασκευή διαδρομών
    """
    distances = {}
    previous = {}
    visisted = set()

    #ολές οι αποστασείς αρχίκα άπειρες , εκτός από την πρώτη
    for vertex in graph.get_vertices():
        distances[vertex] = float('infinity')
        previous[vertex] = None
    
    distances[start_vertex] = 0

    #priority queue: (αποστάση, κορυφή)
    priority_queue = [(0, start_vertex)]

    print(f"Ξεκινάμε Dijkstra από κορυφή {start_vertex}")
    if end_vertex:
        print(f"Στόχος: κορυφή {end_vertex}")
    print("=" * 50)

    steps = 0
    while priority_queue:
        #Παίρνουμε την κορυφή με την μικρότερη απόσταση
        current_distance, current_vertex = heapq.heappop(priority_queue)

        if current_vertex in visisted:
            continue

        visisted.add(current_vertex)
        steps += 1

        #αν current_vertex = στόχος σταματάμε
        if current_vertex == end_vertex:
            print(f"Βρήκαμε τον στόχο. Αποστάση : {current_distance}")
            break

        #εξετάζουμε ολούς τους γειτονές
        for neighbor in graph.get_neighbors(current_vertex):
            if neighbor in visisted:
                continue
            # Υπολογισμός νέας απόστασης (κόστος κάθε ακμής = 1)
            new_distance = current_distance + 1

            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                previous[neighbor] = current_vertex
                heapq.heappush(priority_queue, (new_distance, neighbor))

    print(f"Dijkstra ολοκληρώθηκε σε {steps} βήματα")
    return distances, previous

def reconstruct_path(previous, start_vertex, end_vertex):
    """
    Ανακατασκευάζει τη διαδρομή από start_vertex σε end_vertex
    
    παραμέτροι:
        previous: Dictionary από dijkstra
        start_vertex: Αρχική κορυφή
        end_vertex: Τελική κορυφή
    
    γυρνάει:
        path: Λίστα με τη διαδρομή, ή None αν δεν υπάρχει
    """
    if previous[end_vertex] is None and start_vertex != end_vertex:
        return None  # Δεν υπάρχει διαδρομή
    
    path = []
    current = end_vertex

    while current is not None:
        path.append(current)
        current = previous[current]
    
    path.reverse()
    return path

def print_path_info(path, distance):
    if path is None:
        print("Δεν υπάρχει διαδρομή")
        return 
    print(f" Διαδρομή μήκους {distance}")

    if len(path) <= 20:
        print(f"   {' → '.join(map(str, path))}")
    else:
        print(f"   {path[0]} → {path[1]} → {path[2]} → ... → {path[-3]} → {path[-2]} → {path[-1]}")
        print(f"   (συνολικά {len(path)} κορυφές)")

def solve_dijkstra_problem(csv_file, source, destination):
    """
    Λύνει το πρόβλημα Dijkstra για ένα συγκεκριμένο αρχείο
    """
    print(f"\n{'='*60}")
    print(f"Φόρτωση αρχείου: {csv_file}")
    print(f"Από κορυφή {source} στην κορυφή {destination}")
    print(f"{'='*60}")
    
    
    graph = Graph()
    graph.load_from_csv(csv_file)
    
    stats = graph.get_stats()
    print(f"Κορυφές: {stats['vertices']}, Ακμές: {stats['edges']}")
    
    
    distances, previous = dijkstra(graph, source, destination)
    
    path = reconstruct_path(previous, source, destination)
    distance = distances.get(destination, float('infinity'))
    
    print_path_info(path, distance)
    
    return path, distance, graph


if __name__ == "__main__":
    # Λύση για dijkstra1.csv
    path1, dist1, graph1 = solve_dijkstra_problem('dijkstra1.csv', 0, 127)
    
    # Λύση για dijkstra2.csv
    path2, dist2, graph2 = solve_dijkstra_problem('dijkstra2.csv', 0, 127)
    
    # Σύγκριση αποτελεσμάτων
    print(f"\n{'='*60}")
    print("ΣΥΓΚΡΙΣΗ ΑΠΟΤΕΛΕΣΜΑΤΩΝ")
    print(f"{'='*60}")
    print(f"dijkstra1.csv: Απόσταση = {dist1}")
    print(f"dijkstra2.csv: Απόσταση = {dist2}")
    