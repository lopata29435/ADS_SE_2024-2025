import numpy as np
import matplotlib.pyplot as plt

class HashTable:
    def __init__(self, size, probing_method, c1=1, c2=1, c3=1):
        self.size = size
        self.table = [None] * size
        self.probing_method = probing_method
        self.c1 = c1
        self.c2 = c2
        self.c3 = c3

    def hash_function(self, key):
        return key % self.size

    def insert(self, key):
        h = self.hash_function(key)
        for i in range(self.size):
            if self.probing_method == "quadratic":
                index = (h + self.c1 * i + self.c2 * i**2) % self.size
            elif self.probing_method == "cubic":
                index = (h + self.c1 * i + self.c2 * i**2 + self.c3 * i**3) % self.size
            else:
                raise ValueError("Unknown probing method")

            if self.table[index] is None:
                self.table[index] = key
                return True

        return False  # Table is full

    def count_clusters(self):
        clusters = 0
        in_cluster = False
        for cell in self.table:
            if cell is not None:
                if not in_cluster:
                    clusters += 1
                    in_cluster = True
            else:
                in_cluster = False
        return clusters

    
def average_probes(size, load_factor, probing_method, trials=1000):
    num_elements = int(size * load_factor) 
    total_probes = 0

    for _ in range(trials):
        keys = np.random.randint(0, 10000, num_elements)
        table = HashTable(size, probing_method, c1=1, c2=1, c3=1)

        for key in keys:
            table.insert(key)

        for key in keys:
            h = table.hash_function(key)
            for i in range(size):
                if probing_method == "quadratic":
                    index = (h + table.c1 * i + table.c2 * i**2) % size
                elif probing_method == "cubic":
                    index = (h + table.c1 * i + table.c2 * i**2 + table.c3 * i**3) % size

                total_probes += 1
                if table.table[index] == key:
                    break 

    return total_probes / (num_elements * trials)
    

table_size = 101
num_keys = [50, 60, 70, 80, 85, 90, 95]
trials = 10

quadratic_clusters = []
cubic_clusters = []

for k in range(0, 7):
    num_key = num_keys[k]
    for _ in range(trials):
        keys = np.random.randint(0, 10000, num_key)

        # Квадратичное пробирование
        quad_table = HashTable(table_size, "quadratic", c1=1, c2=1)
        for key in keys:
            quad_table.insert(key)
        quadratic_clusters.append(quad_table.count_clusters())

        # Кубическое пробирование
        cubic_table = HashTable(table_size, "cubic", c1=1, c2=1, c3=1)
        for key in keys:
            cubic_table.insert(key)
        cubic_clusters.append(cubic_table.count_clusters())

    plt.hist(quadratic_clusters, bins=10, alpha=0.5, label="Quadratic", color="blue", edgecolor="black")
    plt.hist(cubic_clusters, bins=10, alpha=0.5, label="Cubic", color="red", edgecolor="black")
    plt.xlabel("Number of Clusters" )
    plt.ylabel("Frequency")
    plt.title("Distribution of Clusters in Quadratic vs Cubic Probing for num_keys = " + str(num_key))
    plt.legend()
    plt.grid(axis="y", linestyle="--", alpha=0.7)
    plt.show()

load_factors = np.linspace(0.1, 0.9, 9)
quad_probes = [average_probes(101, lf, "quadratic") for lf in load_factors]
cubic_probes = [average_probes(101, lf, "cubic") for lf in load_factors]

plt.plot(load_factors, quad_probes, marker="o", linestyle="-", label="Quadratic Probing", color="blue")
plt.plot(load_factors, cubic_probes, marker="s", linestyle="-", label="Cubic Probing", color="red")
plt.xlabel("Load Factor (λ)")
plt.ylabel("Average Probes (Successful Search)")
plt.title("Comparison of Quadratic vs Cubic Probing")
plt.legend()
plt.grid()
plt.show()

quad_probes, cubic_probes
