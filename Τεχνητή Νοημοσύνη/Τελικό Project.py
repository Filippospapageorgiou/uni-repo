import copy
from collections import deque
import sys  
import heapq
sys.setrecursionlimit(10**6) 


#Συναρτήσεις τελεστών μετάβασης:

def go_to_floor1(state):
    #Έλεγχος για αν το ασανσέρ δεν είναι γεμάτο και για το αν ο πρώτος όροφος έχει ενοίκους
    if state[-1]<8 and state[1]>0:
        #Έλεγχος για αν ο πρώτος όροφος έχει περισσότερους ενοίκους απο αυτούς που χωράει το ασανσέρ
        if state[1]>8-state[-1]:
            new_state = [1] + [state[1] + state[-1] - 8] + [state[2]] + [state[3]] + [state[4]] + [8]
        #Αλλίως βάλε στον πρώτο όροφο 0 ενοίκους και στο ασανσερ όσους είχε ήδη μέσα και τους υπολοιπόμενους ενοίκους από τον 1ο όροφο
        else:
            new_state = [1] + [0] + [state[2]] + [state[3]] + [state[4]] + [state[1] + state[-1]]
        return new_state
 
def go_to_floor2(state):
    #Έλεγχος για αν το ασανσέρ δεν είναι γεμάτο και για το αν ο δεύτερος όροφος έχει ενοίκους
    if state[5]<8 and state[2]>0:
        #Έλεγχος για αν ο δεύτερος όροφος έχει περισσότερους ενοίκους απο αυτούς που χωράει το ασανσέρ
        if state[2]>8-state[5]:
            new_state = [2] + [state[1]] + [state[2] + state[5] - 8] + [state[3]] + [state[4]] + [8]
        #Αλλίως βάλε στον δεύτερο όροφο 0 ενοίκους και στο ασανσερ όσους είχε ήδη μέσα και τους υπολοιπόμενους ενοίκους από τον 2ο όροφο
        else:
            new_state = [2] + [state[1]] + [0] + [state[3]] + [state[4]] + [state[2] + state[5]]
        return new_state

def go_to_floor3(state):
    #Έλεγχος για αν το ασανσέρ δεν είναι γεμάτο και για το αν ο τρίτος όροφος έχει ενοίκους
    if state[5]<8 and state[3]>0:
        #Έλεγχος για αν ο τρίτος όροφος έχει περισσότερους ενοίκους απο αυτούς που χωράει το ασανσέρ
        if state[3]>8-state[5]:
            new_state = [3] + [state[1]] + [state[2]] + [state[3]+state[5]-8] + [state[4]] + [8]
        #Αλλίως βάλε στον τρίτο όροφο 0 ενοίκους και στο ασανσερ όσους είχε ήδη μέσα και τους υπολοιπόμενους ενοίκους από τον 3ο όροφο
        else:
            new_state = [3] +  [state[1]] + [state[2]] + [0] + [state[4]] + [state[3] + state[5]]
        return new_state              

def go_to_floor4(state):
    #Έλεγχος για αν το ασανσέρ δεν είναι γεμάτο και για το αν ο τέταρτος όροφος έχει ενοίκους
    if state[5]<8 and state[4]>0:
        #Έλεγχος για αν ο τέταρτος όροφος έχει περισσότερους ενοίκους απο αυτούς που χωράει το ασανσέρ
        if state[4]>8-state[5]:
            new_state = [4] + [state[1]] + [state[2]] + [state[3]] + [state[4]+state[5] - 8] + [8]
        else:            
        #Αλλίως βάλε στον τέταρτο όροφο 0 ενοίκους και στο ασανσερ όσους είχε ήδη μέσα και τους υπολοιπόμενους ενοίκους από τον 4ο όροφο
            new_state = [4] +  [state[1]] + [state[2]] + [state[3]] + [0] + [state[4] + state[5]]
        return new_state


def go_to_roof(state):
    #Έλεγχος για αν το ασανσέρ είναι άδειο και επέστρψε None
    if state[5] == 0:
       return None
    #Αλλιώς βάλε 5 στην θέση του ασανσέρ και 0 στους ενοίκους που περιέχει, επέστρεψε το new_state
    else:
       new_state = [5] + [state[1]] + [state[2]] + [state[3]] + [state[4]] + [0]
       return new_state    

        
#Συνάρτηση εύρεσης παιδιών:

def find_children(state):
    #Ορισμός του πίνακα children
    children=[]
    #Δημιουργία μίας αντιγραφής του state -> floor1_state
    floor1_state=copy.deepcopy(state)
    #Κάθε παιδί θα δημιουργηθεί από τις συναρτήσεις των τελεστών μετάβασης με όρισμα το προηγούμενο deepcopy
    floor1_child=go_to_floor1(floor1_state)
    floor2_child=go_to_floor2(floor1_state)
    floor3_child=go_to_floor3(floor1_state)
    floor4_child=go_to_floor4(floor1_state)
    roof_child=go_to_roof(floor1_state)

    #Έλεγχος για το αν τα παιδιά είναι None, αν δεν είναι βάλτα στον children

    if roof_child!=None: 
        children.append(roof_child)
    if floor4_child!=None:
        children.append(floor4_child)
    if floor3_child!=None:
        children.append(floor3_child)    
    if floor2_child!=None:
        children.append(floor2_child)
    if floor1_child!=None:
        children.append(floor1_child)     
    
    #Επιστροφή του children
    return children



def make_front(state):
    return [state]

#Συνάρτηση 
def expand_front(front, method):  
    if method=='DFS':        
        if front:
            node=front.pop(0)
            for child in find_children(node):     
                front.insert(0,child)
    elif method == 'BFS':
        if front:
            front=deque(front)
            node = front.popleft()  
            for child in find_children(node):
                front.append(child) 
           
    return front

def make_queue(state):
    return [[state]]

"""
Συνάρτηση όπου κάνει extend την ούρα βασεί την συκγεκριμένη μέθοδο αναζήτησης
Αναλυτική επεξήγηση στο ΘΩΜΑΣ-21390068-ΠΑΠΑΓΕΩΡΓΙΟΥ-21390174.pdf
"""

def extend_queue(queue, method):
    if method=='DFS':
        node=queue.pop(0)
        queue_copy=copy.deepcopy(queue)
        children=find_children(node[-1])
        for child in children:
            path=copy.deepcopy(node)
            path.append(child)
            queue_copy.insert(0,path)
    elif method == 'BFS':
        queue=deque(queue)
        node =queue.popleft()
        queue_copy = copy.deepcopy(queue)
        children = find_children(node[-1])
        for child in children:
           path = copy.deepcopy(node)
           path.append(child)
           queue_copy.append(path)
    
    return queue_copy

"""
Συνάρτηση ευριστικού μηχανισμού A*
"""

#Συνάρτηση που υπολογίζει την απόσταση Μανχάταν 

def heuristic(state, goal):
    return sum(abs(state[i] - goal[i]) for i in range(len(state)))

#Συνάρτηση Α*, ορίσματα: initial_state, goal

def a_star_search(initial_state, goal):
    #Αρχικοποίηση μιας ουράς προτεραιότητας με το συνολικό κόστος, με το πραγματικό κόστος, με την αρχική κατάσταση και ένα κενό μονοπάτι 
    open_list = [(0, 0, initial_state, [])] 
    #Ένα κλειστό σύνολο για τις καταστάσεις που έχει επισκεφτεί
    closed_set = set()

    #Αρχικοποίηση μιας while    
    while open_list:
        #Pop το μικρότερο στοιχείο από την open_list
        total_cost, actual_cost, current_state, path = heapq.heappop(open_list)

        #Έλεγχος για το αν βρέθηκε ο στόχος
        if current_state == goal:
            print('_GOAL_FOUND_WITH_METHOD A*')
            print("Path:", [(actual_cost, state) for state in path + [current_state]])
            return total_cost

        """
        Tuple είναι μία συλλογή η οποία είναι ταξινομημένη και δεν αλλάζει
        Έλεγχος αν έχει επισκεφθεί ήδη αυτό το state
        Αν ναι πήγαινε στην αρχή του while
        """
        if tuple(current_state) in closed_set:
            continue

        #Αλλιώς προσθεσέ το στη λίστα με τα ήδη επισκεπτόμενα states
        closed_set.add(tuple(current_state))

        #Για κάθε παιδί στην find_children με το τρέχον state
        for child in find_children(current_state):
            #Αύξησε το πραγματικό κόστος κατα 1
            child_actual_cost = actual_cost + 1 
            #Χρησιμοποίησε την heuristic για την εύρεση του κόστους
            heuristic_cost = heuristic(child, goal)
            #Βάλε στο συνολικό κόστος, το πραγματικό και το ευριστικό
            child_total_cost = child_actual_cost + heuristic_cost
            #Push στην open_list το συνολικό κόστος, το πραγματικό κόστος, το νέο state, και τα state που έχει ήδη επισκεφθεί
            heapq.heappush(open_list, (child_total_cost, child_actual_cost, child, path + [current_state]))

    print("Goal not found")

#Συνάρτηση find_solution, ορίσματα: front, queue, close, goal, method
def find_solution(front, queue, closed, goal, method):

    #Έλεγχος για αν το front είναι άδειο   
    if not front:
        print('_NO_SOLUTION_FOUND_')
        return None
    
   
    #Έλεγχος αν το πρώτο στοιχείο υπάρχει στα closed
    elif front[0] in closed:
        #Κάνε την front να μπορεί να επεξεργαστεί και από τις δύο μεριές
        front=deque(front)
        #Δημιούργησε μία αντιγραφή του front
        new_front=copy.deepcopy(front)
        #Βγάλε απο την αντιγραφή new_front το πρώτο στοιχείο
        new_front.popleft()
        #Δημιούργησε μία αντιγραφή του queue
        new_queue=copy.deepcopy(queue)
        #Βγάλε απο την αντιγραφή new_queue το πρώτο στοιχείο
        new_queue.popleft()
        #Επέστρεψε το αποτέλεσμα της find_solution με τα νέα ορίσματα
        return find_solution(new_front, new_queue, closed, goal, method)

    #Έλεγχος για το αν βρέθηκε ο στόχος
    elif front[0]==goal:
        print('_GOAL_FOUND_WITH_METHOD ' + method)
        print(queue[0]) 
        return len(queue[0])
    #Αλλιώς
    else:
        #Πρόσθεσε στα ήδη επισκεπτόμενα(closed) το πρώτο στοιχείο της front
        closed.append(front[0])
        #Δημιούργησε μία αντιγραφή του front
        front_copy=copy.deepcopy(front)
        #Τελεστής front_children με το αποτέλεσμα από την expand_front με ορίσματα: την αντιγραφή του front και την μέθοδο
        front_children=expand_front(front_copy, method)
        #Δημιούργησε μία αντιγραφή του queue
        queue_copy=copy.deepcopy(queue)
        #Τελεστής queue_children με το αποτέλεσμα από την extend_queue με ορίσματα: την αντιγραφή του queue και την μέθοδο
        queue_children=extend_queue(queue_copy, method)
        #Δημιούργησε μία αντιγραφή του closed
        closed_copy=copy.deepcopy(closed)
        #Επέστρεψε το αποτέλεσμα της find_solution με τα νέα ορίσματα
        return  find_solution(front_children, queue_children, closed_copy, goal, method)
           
def main():
    
    initial_state = [0, 9, 4, 12, 7, 0]
    goal = [5, 0, 0, 0, 0, 0]
    methodbfs='BFS'
    methoddfs='DFS'

    print('____BEGIN__SEARCHING____')
    find_solution(make_front(initial_state), make_queue(initial_state), [], goal, methodbfs)
    find_solution(make_front(initial_state), make_queue(initial_state), [], goal, methoddfs)
    a_star_search(initial_state, goal)
   
if __name__ == "__main__":
    main()