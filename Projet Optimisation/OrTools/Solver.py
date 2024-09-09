import sys
from ortools.sat.python import cp_model
from ortools.linear_solver import pywraplp
import time
from ortools.constraint_solver import pywrapcp, routing_enums_pb2
import math
###################SAC PART####################
class Problem:
    def __init__(self, n_var, n_cont, type_opt, fonc_obj, a, signe_cont, b):
        self.n_var = n_var
        self.n_cont = n_cont
        self.type_opt = type_opt  # 1 for max, 0 for min
        self.fonc_obj = fonc_obj
        self.a = a
        self.signe_cont = signe_cont
        self.b = b

def lire_probleme(nom_fichier):
    try:
        with open(nom_fichier, "r") as fichier:
            # Extraire le nombre de variables
            n_var = int(next(fichier).split()[1])
            # Extraire le nombre de contraintes
            n_cont = int(next(fichier).split()[1])
            # Lire le type d"optimisation
            type_opt = 1 if "max" in next(fichier).strip() else 0

            # Lire la fonction objectif sur une seule ligne
            fonc_obj_line = next(fichier).strip().split()
            fonc_obj = []
            for i in range(1, len(fonc_obj_line), 3):
                signe = fonc_obj_line[i-1]
                value = float(fonc_obj_line[i])
                if signe == "-":
                    value = -value
                fonc_obj.append(value)
            
            # Lire les contraintes
            a = []
            signe_cont = []
            b = []
            for _ in range(n_cont):
                next(fichier) 
                constraint_line = next(fichier).strip().split()
                row = []
                for i in range(1, len(constraint_line) - 2, 3):
                    signe = constraint_line[i-1]
                    value = float(constraint_line[i])
                    if signe == "-":
                        value = -value
                    row.append(value)
                relation = constraint_line[-2]
                rhs_value = float(constraint_line[-1])
                if relation == "<=":
                    signe_cont.append(0)
                elif relation == ">=":
                    signe_cont.append(1)
                b.append(rhs_value)
                a.append(row)

            return Problem(n_var, n_cont, type_opt, fonc_obj, a, signe_cont, b)
    except Exception as e:
        print(f"Probleme lecture fichier: {e}")
        return None

def afficher_probleme(prob):
    if prob:
        print("Lecture réussie.")
        print("Nombre de variables:", prob.n_var)
        print("Nombre de contraintes:", prob.n_cont)
        print("Type d'optimisation (1 pour max, 0 pour min):", prob.type_opt)
        print("Fonction objectif:", prob.fonc_obj)
        print("Matrice des contraintes A:")
        for row in prob.a:
            print(row)
        print("Vecteur des signes des contraintes (0 pour <=, 1 pour >=):", prob.signe_cont)
        print("Vecteur b (droite des contraintes):", prob.b)
    else:
        print("Échec de la lecture du fichier.")

def resoudre(problem):

    # Création du solveur SCIP
    solver = pywraplp.Solver.CreateSolver("SCIP")
    if not solver:
        print("SCIP solver not available.")
        return
    
    # Variables
    x = [solver.IntVar(0.0, solver.infinity(), "x%d") for i in range(problem.n_var)]

    # Fonction objectif
    if problem.type_opt == 1:  # Maximisation
        solver.Maximize(solver.Sum(problem.fonc_obj[i] * x[i] for i in range(problem.n_var)))
    else:  # Minimisation
        solver.Minimize(solver.Sum(problem.fonc_obj[i] * x[i] for i in range(problem.n_var)))
    
    # Contraintes
    for i in range(problem.n_cont):
        constraint_expr = solver.Sum(problem.a[i][j] * x[j] for j in range(problem.n_var))
        if problem.signe_cont[i] == 0:  # <=
            solver.Add(constraint_expr <= problem.b[i])
        else:  # >=
            solver.Add(constraint_expr >= problem.b[i])
    
    # Résolution du problème
    status = solver.Solve()
    return status, solver, x
   
def read_sac_file(file_path):
    # lecture du fichier
    with open(file_path, 'r') as file:
        lines = file.readlines()
    # Extraire les paramètres du problème
    n = int(lines[0].split(':')[1].strip())
    capacity = int(lines[1].split(':')[1].strip())

    # lire volumes et utilités
    volumes = []
    utilities = []
    for line in lines[2:]:
        # Skip empty lines
        if line.strip():
            values = line.split()
            if len(values) == 2:
                volume, utility = map(int, values)
                volumes.append(volume)
                utilities.append(utility)

    # Construction du problème
    problem = Problem(
        n_var=n,                
        n_cont=1,               
        type_opt=1,             
        fonc_obj=utilities,     
        a=[volumes],            
        signe_cont=[0],        
        b=[capacity]           
    )

    return problem

def afficher_solution(problem, status, solver, x):
    if status == pywraplp.Solver.OPTIMAL:
        print("Solution:")
        for i in range(problem.n_var):
            if (x[i].solution_value() != 0.0):
                print("x[%d] = %d" % (i, int(x[i].solution_value())))
        print("Valeur optimale de la fonction objectif: %d" % round(solver.Objective().Value()))
    else:
        print("Pas de solution trouvée.")


###################TSP PART####################
def read_graph_from_file(file_path):
    "FILE FOR graphe 2 - 15 "
    with open(file_path, 'r') as file:
        lines = file.readlines()

    # Extraire constantes
    n_sommets = int(lines[0].split()[1])
    oriente = int(lines[1].split()[1])
    value = int(lines[2].split()[1])

    # create distance matrix
    distance_matrix = [[0 if i == j else sys.maxsize for j in range(n_sommets)] for i in range(n_sommets)]

    start_index = lines.index("DEBUT_DEF_ARETES\n") + 1
    end_index = lines.index("FIN_DEF_ARETES\n")

    for line in lines[start_index:end_index]:
        parts = line.split()
        start = int(parts[0])
        end = int(parts[1])
        weight = int(parts[2])

        distance_matrix[start][end] = weight
        if not oriente:
            distance_matrix[end][start] = weight

    edge_type = "prob"

    return edge_type, distance_matrix

def solve_tsp(distance_matrix):
    
    manager = pywrapcp.RoutingIndexManager(len(distance_matrix), 1, 0)
    routing = pywrapcp.RoutingModel(manager)

    def distance_callback(from_index, to_index):
        from_node = manager.IndexToNode(from_index)
        to_node = manager.IndexToNode(to_index)
        return distance_matrix[from_node][to_node]

    transit_callback_index = routing.RegisterTransitCallback(distance_callback)

    routing.SetArcCostEvaluatorOfAllVehicles(transit_callback_index)

    search_parameters = pywrapcp.DefaultRoutingSearchParameters()
    search_parameters.first_solution_strategy = (
        routing_enums_pb2.FirstSolutionStrategy.PATH_CHEAPEST_ARC)

    # Solve the problem.
    solution = routing.SolveWithParameters(search_parameters)
    return solution, routing, manager

def parse_explicit_weights(lines, dimension):
    matrix = [[0] * dimension for _ in range(dimension)]
    index = 0
    for i in range(dimension):
        for j in range(i + 1):
            matrix[i][j] = int(lines[index])
            if i != j:
                matrix[j][i] = matrix[i][j]
            index += 1
    return matrix

def read_tsplib_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    node_coords = []
    reading_nodes = False
    reading_weights = False
    edge_weight_type = None
    edge_weight_format = None
    dimension = 0
    weight_lines = []

    # Type de graphe
    for line in lines:
        if "EDGE_WEIGHT_TYPE" in line:
            edge_weight_type = line.split(":")[1].strip()
        if "EDGE_WEIGHT_FORMAT" in line:
            edge_weight_format = line.split(":")[1].strip()
        if "DIMENSION" in line:
            dimension = int(line.split(":")[1].strip())
        if line.strip() == "NODE_COORD_SECTION":
            reading_nodes = True
            continue
        elif line.strip() == "EDGE_WEIGHT_SECTION":
            reading_weights = True
            continue
        elif line.strip() == "EOF":
            break
        elif reading_nodes:
            parts = line.split()
            lat_lon = (float(parts[1]), float(parts[2]))
            node_coords.append(lat_lon)
        elif reading_weights:
            weight_lines.extend(line.split())

    # Si explicit
    if edge_weight_type == "EXPLICIT" and edge_weight_format == "LOWER_DIAG_ROW":
        distance_matrix = parse_explicit_weights(weight_lines, dimension)
    else: # Sinon GEO ou EUC_2D
        n = len(node_coords)
        distance_matrix = [[0] * n for _ in range(n)]
        scale_factor = 1000

        if edge_weight_type == "GEO":
            # Calculate geographical distances
            for i in range(n):
                for j in range(i + 1, n):
                    lat1, lon1 = node_coords[i]
                    lat2, lon2 = node_coords[j]
                    distance = calculate_geo_distance(lat1, lon1, lat2, lon2)
                    scaled_distance = int(distance * scale_factor + 0.5)
                    distance_matrix[i][j] = scaled_distance
                    distance_matrix[j][i] = scaled_distance
        elif edge_weight_type == "EUC_2D":
            # Calculate Euclidean distances
            for i in range(n):
                for j in range(i + 1, n):
                    x1, y1 = node_coords[i]
                    x2, y2 = node_coords[j]
                    distance = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
                    scaled_distance = int(distance * scale_factor + 0.5)
                    distance_matrix[i][j] = scaled_distance
                    distance_matrix[j][i] = scaled_distance
        else:
            raise ValueError(f"Unsupported EDGE_WEIGHT_TYPE: {edge_weight_type}")

    return edge_weight_type, distance_matrix

def calculate_geo_distance(lat1, lon1, lat2, lon2):
    # Calculer la distance entre deux points géographiques longitude/latitude
    lat1, lon1, lat2, lon2 = map(math.radians, [lat1, lon1, lat2, lon2])

    dlon = lon2 - lon1
    dlat = lat2 - lat1
    a = math.sin(dlat/2)**2 + math.cos(lat1) * math.cos(lat2) * math.sin(dlon/2)**2
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
    R = 6371.0 
    distance = R * c

    return distance

def afficherSolutionTSP(solution, routing, manager, iftsp, edge_type):
    if solution:

        index = routing.Start(0)
        route = []
        print("Route:")
        while not routing.IsEnd(index):
            node = manager.IndexToNode(index)
            route.append(node)
            print('%d -> ' % node, end='')
            previous_index = index
            index = solution.Value(routing.NextVar(index))
        node = manager.IndexToNode(index)
        route.append(node)
        print('%d' % node)

        route_distance = solution.ObjectiveValue()
        if (iftsp == "0"):
            print(f'Total distance: {route_distance}')
        elif (iftsp == "1"):
            if (edge_type == "EUC_2D" or edge_type == "GEO"):
                print(f'Total distance: {route_distance / 1000:.2f}')
            else:
                print(f'Total distance: {route_distance:.2f}')
    else:
        print("No solution found!")

def main():
    if len(sys.argv) < 4:
        print("Usage: python SacSolverOrtools.py <type> <ifprob> <nom_fichier>")
        return
    type = sys.argv[1]
    ifprob = sys.argv[2]

    if (type == "0"): #Sac à dos
        nom_fichier = "data/sac/%s" % sys.argv[3] + ".txt"
        if (ifprob == "0"):
            prob = lire_probleme(nom_fichier)
        else:
            prob = read_sac_file(nom_fichier)

        start_time = time.time()
        status, solver, x = resoudre(prob)
        end_time = time.time()
        afficher_solution(prob, status, solver, x)
        print("Temps d'exécution: %f secondes" % (end_time - start_time))

    elif (type=="1"): #TSP
        if(ifprob == "0"):
            file_path = "data/tsp/%s" %sys.argv[3] + ".txt"
            edge_type,distance_matrix = read_graph_from_file(file_path)
        else:
            file_path = "data/tsp/%s" %sys.argv[3] + ".tsp"
            edge_type,distance_matrix = read_tsplib_file(file_path)

        start_time = time.time()
        tsp_solution, routing, manager = solve_tsp(distance_matrix)
        end_time = time.time()
        afficherSolutionTSP(tsp_solution, routing, manager, ifprob, edge_type)
        timespend = end_time - start_time
        print("Temps d'exécution: %f secondes" % timespend)
    
if __name__ == "__main__":
    main()