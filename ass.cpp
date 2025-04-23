Assignment - 1
#include <iostream>
#include <queue>
using namespace std;

// Node structure representing each dictionary entry
struct Node {
    string key;
    string value;
    Node* left;
    Node* right;

    Node(string k, string v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

// Dictionary class using Binary Search Tree (BST)
class Dictionary {
private:
    Node* root;

    // Recursive function to insert a new key-value pair into the BST
    Node* insert(Node* root, string key, string value) {
        if (root == nullptr) {
            return new Node(key, value);
        }
        if (key < root->key) {
            root->left = insert(root->left, key, value);
        } else if (key > root->key) {
            root->right = insert(root->right, key, value);
        }
        return root;
    }

    // Recursive function to search for a key in the BST
    Node* search(Node* root, string key) {
        if (root == nullptr || root->key == key) {
            return root;
        }
        if (key < root->key) {
            return search(root->left, key);
        }
        return search(root->right, key);
    }

    // Recursive function to delete a key from the BST
    Node* deleteNode(Node* root, string key) {
        if (root == nullptr) {
            return root;
        }

        if (key < root->key) {
            root->left = deleteNode(root->left, key); // Fix: assignment operator used instead of comparison
        } else if (root->key < key) {
            root->right = deleteNode(root->right, key);
        } else {
            // Node with only one child or no child
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children: Get the in-order successor
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->key);
        }
        return root;
    }

    // Function to find the node with the minimum key value
    Node* minValueNode(Node* root) {
        Node* current = root;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // In-order traversal (left-root-right) to display dictionary in sorted order
    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->key << " -> " << root->value << endl;
            inorder(root->right);
        }
    }

    // Level-order traversal to display dictionary level-wise
    void levelOrder(Node* root) {
        if (root == nullptr) return;

        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* temp = q.front();
            cout << temp->key << " -> " << temp->value << " ";
            q.pop();

            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
        cout << endl;
    }

    // Function to create a mirror image of the BST
    Node* mirror(Node* root) {
        if (root == nullptr) return nullptr;

        Node* newNode = new Node(root->key, root->value);
        newNode->left = mirror(root->right);
        newNode->right = mirror(root->left);
        return newNode;
    }

    // Function to create a deep copy of the BST
    Node* copy(Node* root) {
        if (root == nullptr) return nullptr;

        Node* newNode = new Node(root->key, root->value);
        newNode->left = copy(root->left);
        newNode->right = copy(root->right);
        return newNode;
    }

public:
    Dictionary() : root(nullptr) {}

    // Public insert function
    void insert(string key, string value) {
        root = insert(root, key, value);
    }

    // Public delete function
    void deleteNode(string key) {
        root = deleteNode(root, key);
    }

    // Public search function
    void searchWord(string key) {
        Node* result = search(root, key);
        if (result != nullptr) {
            cout << "Found: " << result->key << " -> " << result->value << endl;
        } else {
            cout << "Not found!" << endl;
        }
    }

    // Display BST in-order
    void display() {
        cout << "Dictionary (In-Order traversal): " << endl;
        inorder(root);
    }

    // Display mirror image of the dictionary
    void mirrorImage() {
        Node* mirroredRoot = mirror(root);
        cout << "Mirror image of dictionary: " << endl;
        inorder(mirroredRoot);
    }

    // Create and display a copy of the dictionary
    void copyDictionary() {
        Node* copiedRoot = copy(root);
        cout << "Copied dictionary: " << endl;
        inorder(copiedRoot);
    }

    // Display BST level-wise
    void displayLevelWise() {
        cout << "Dictionary (Level-wise): " << endl;
        levelOrder(root);
    }
};

// Driver function to run the menu-based program
int main() {
    Dictionary dict;
    int choice;
    string key, value;

    cout << "\nMenu:\n";
    cout << "1. Insert word\n";
    cout << "2. Delete word\n";
    cout << "3. Search specific word\n";
    cout << "4. Display dictionary (In-order)\n";
    cout << "5. Mirror image of dictionary\n";
    cout << "6. Create a copy of dictionary\n";
    cout << "7. Display dictionary level-wise\n";
    cout << "8. Exit\n";

    do {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                cin.ignore();  // Handle newline after reading key
                cout << "Enter value: ";
                getline(cin, value);  // Read value as sentence
                dict.insert(key, value);
                break;
            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                dict.deleteNode(key);
                break;
            case 3:
                cout << "Enter key to search: ";
                cin >> key;
                dict.searchWord(key);
                break;
            case 4:
                dict.display();
                break;
            case 5:
                dict.mirrorImage();
                break;
            case 6:
                dict.copyDictionary();
                break;
            case 7:
                dict.displayLevelWise();
                break;
            case 8:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}
__________________________________________________________________________________________________________________________________________________
Assignment - 2
#include <iostream>
using namespace std;

// Structure for each player node in the AVL tree
struct Player
{
    int player_id;      // Unique ID of the player
    int score;          // Player's score (used as key in BST)
    Player* left;       // Pointer to left child
    Player* right;      // Pointer to right child
    int height;         // Height of the node for AVL balancing
};

// Function to get the height of a node
int getHeight(Player* node)
{
    return node ? node->height : 0;
}

// Function to get balance factor of a node
int getBalanceFactor(Player* node)
{
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Function to create a new player node
Player* createPlayer(int id, int score)
{
    Player* newPlayer = new Player{id, score, nullptr, nullptr, 1};
    return newPlayer;
}

// Right rotation for AVL balancing
Player* rotateRight(Player* y)
{
    Player* x = y->left;
    Player* T2 = x->right;

    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // New root
}

// Left rotation for AVL balancing
Player* rotateLeft(Player* x)
{
    Player* y = x->right;
    Player* T2 = y->left;

    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // New root
}

// Function to insert a player into the AVL tree
Player* insertPlayer(Player* root, int id, int score)
{
    if (!root)
        return createPlayer(id, score); // Insert new node

    if (score < root->score)
        root->left = insertPlayer(root->left, id, score);
    else if (score > root->score)
        root->right = insertPlayer(root->right, id, score);
    else
        return root; // Duplicate score not allowed

    // Update height and balance the tree
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalanceFactor(root);

    // Perform AVL rotations
    if (balance > 1 && score < root->left->score)
        return rotateRight(root);

    if (balance < -1 && score > root->right->score)
        return rotateLeft(root);

    if (balance > 1 && score > root->left->score)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && score < root->right->score)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Helper function to find the node with minimum score in a subtree
Player* minValueNode(Player* node)
{
    Player* current = node;
    while (current->left)
        current = current->left;
    return current;
}

// Function to delete a player from the AVL tree
Player* deletePlayer(Player* root, int score)
{
    if (!root)
        return root;

    if (score < root->score)
        root->left = deletePlayer(root->left, score);
    else if (score > root->score)
        root->right = deletePlayer(root->right, score);
    else
    {
        // Node found
        if (!root->left || !root->right)
        {
            Player* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }

        // Node with two children
        Player* temp = minValueNode(root->right);
        root->score = temp->score;
        root->right = deletePlayer(root->right, temp->score);
    }

    // Update height and balance
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalanceFactor(root);

    // Balance the node if needed
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalanceFactor(root->left) < 0)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalanceFactor(root->right) > 0)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Display leaderboard in descending order of scores (reverse in-order traversal)
void displayLeaderboard(Player* root)
{
    if (root)
    {
        displayLeaderboard(root->right);
        cout << "Player Id: " << root->player_id << " | Score: " << root->score << endl;
        displayLeaderboard(root->left);
    }
}

// Main function with menu-driven interface
int main()
{
    Player* root = nullptr;
    int choice, id, score;

    cout << "\nMenu: \n";
    cout << "1. Register Player\n";
    cout << "2. Display Leaderboard\n";
    cout << "3. Remove Player\n";
    cout << "4. Exit\n";

    while (true)
    {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter player Id & score: ";
                cin >> id >> score;
                root = insertPlayer(root, id, score);
                break;

            case 2:
                cout << "\nLeaderboard: \n";
                displayLeaderboard(root);
                break;

            case 3:
                cout << "Enter score to remove player: ";
                cin >> score;
                root = deletePlayer(root, score);
                cout << "Player with score " << score << " is removed.\n";
                break;

            case 4:
                cout << "Exiting..." << endl;
                return 0;

            default:
                cout << "Invalid choice! Please try again." << endl;
		}
	}
}
________________________________________________________________________________________________________________________________________________________________________________________________________________
Assignment - 3
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class MazeSolver {
private:
    int rows, cols;
    vector<vector<int>> maze; // 0 = open path, 1 = wall
    pair<int, int> start, goal;

    // 4 movement directions: Right, Down, Left, Up
    vector<pair<int, int>> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}
    };

    // Check if a cell is valid for traversal
    bool isValid(int x, int y, vector<vector<bool>>& visited) {
        return (x >= 0 && x < rows && y >= 0 && y < cols &&
                maze[x][y] == 0 && !visited[x][y]);
    }

public:
    MazeSolver() {}

    // Function to take user input for maze
    void inputMaze() {
        cout << "Enter number of rows and columns: ";
        cin >> rows >> cols;
        maze.resize(rows, vector<int>(cols));

        cout << "Enter maze values (0 = open, 1 = blocked):\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> maze[i][j];
            }
        }

        cout << "Enter start position (row col): ";
        cin >> start.first >> start.second;

        cout << "Enter goal position (row col): ";
        cin >> goal.first >> goal.second;
    }

    // Display maze layout with Start and Goal
    void printMaze() {
        cout << "\nMaze:\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (make_pair(i, j) == start)
                    cout << "S "; // Start
                else if (make_pair(i, j) == goal)
                    cout << "G "; // Goal
                else
                    cout << (maze[i][j] ? "# " : ". "); // . = open, # = blocked
            }
            cout << "\n";
        }
    }

    // Depth First Search (DFS) for pathfinding
    void DFS() {
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        stack<pair<int, int>> stk;
        stk.push(start);

        cout << "\nDFS Traversal:\n";
        while (!stk.empty()) {
            auto [x, y] = stk.top();
            stk.pop();

            if (!isValid(x, y, visited)) continue;

            visited[x][y] = true;
            cout << "Visited: (" << x << ", " << y << ")\n";

            if (make_pair(x, y) == goal) {
                cout << "Goal reached using DFS!\n";
                return;
            }

            for (auto [dx, dy] : directions)
                stk.push({x + dx, y + dy});
        }

        cout << "No path found using DFS.\n";
    }

    // Breadth First Search (BFS) for shortest path
    void BFS() {
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        queue<pair<int, int>> q;
        q.push(start);

        cout << "\nBFS Traversal:\n";
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            if (!isValid(x, y, visited)) continue;

            visited[x][y] = true;
            cout << "Visited: (" << x << ", " << y << ")\n";

            if (make_pair(x, y) == goal) {
                cout << "Goal reached using BFS!\n";
                return;
            }

            for (auto [dx, dy] : directions)
                q.push({x + dx, y + dy});
        }

        cout << "No path found using BFS.\n";
    }
};

// -------- Main Function --------
int main() {
    MazeSolver solver;
    int choice;

    cout << "========== Maze Solver ==========\n";
    solver.inputMaze();

    cout << "\n====== Menu ======\n";
    cout << "1. Display Maze\n";
    cout << "2. Solve using DFS\n";
    cout << "3. Solve using BFS\n";
    cout << "4. Exit\n";

    do {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                solver.printMaze();
                break;
            case 2:
                solver.DFS();
                break;
            case 3:
                solver.BFS();
                break;
            case 4:
                cout << "Exiting Maze Solver.\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
_____________________________________________________________________________________________________________________________________________________________________________________________________
Assignment - 4
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class CampusGraph {
private:
    int V;  // Number of departments (vertices)
    vector<vector<int>> graph;  // Adjacency matrix to store distances
    vector<string> departments; // Department names for display

public:
    CampusGraph(int vertices) {
        V = vertices;
        graph.resize(V, vector<int>(V, 0)); // Initialize graph with 0s
        departments.resize(V);
    }

    // Input department names
    void inputDepartments() {
        cout << "Enter names of " << V << " departments:\n";
        for (int i = 0; i < V; i++) {
            cout << "Department " << i << ": ";
            cin >> ws; // Ignore any whitespace
            getline(cin, departments[i]);
        }
    }

    // Input distances between departments (0 if not directly connected)
    void inputDistances() {
        cout << "\nEnter distances between departments (0 if not connected):\n";
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                cout << "Distance between " << departments[i] << " and " << departments[j] << ": ";
                int dist;
                cin >> dist;
                graph[i][j] = graph[j][i] = dist;
            }
        }
    }

    // Display adjacency matrix for the graph
    void displayAdjacencyMatrix() {
        cout << "\nAdjacency Matrix:\n\t";
        for (int i = 0; i < V; i++) cout << departments[i] << "\t";
        cout << endl;
        for (int i = 0; i < V; i++) {
            cout << departments[i] << "\t";
            for (int j = 0; j < V; j++) {
                cout << graph[i][j] << "\t";
            }
            cout << endl;
        }
    }

    // Prim's algorithm to find MST
    void primMST() {
        vector<int> parent(V);           // Stores constructed MST
        vector<int> key(V, INT_MAX);     // Key values used to pick min weight edge
        vector<bool> inMST(V, false);    // To represent set of vertices included in MST

        key[0] = 0;     // Start from first vertex
        parent[0] = -1; // Root of MST

        for (int count = 0; count < V - 1; count++) {
            int u = minKey(key, inMST); // Pick minimum key vertex not yet in MST
            inMST[u] = true;

            // Update keys of adjacent vertices
            for (int v = 0; v < V; v++) {
                if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }

        printMST(parent);
    }

    // Utility function to find vertex with minimum key value
    int minKey(vector<int>& key, vector<bool>& inMST) {
        int min = INT_MAX, minIndex = -1;
        for (int v = 0; v < V; v++) {
            if (!inMST[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }
        return minIndex;
    }

    // Print edges and weights of the constructed MST
    void printMST(vector<int>& parent) {
        cout << "\n🛠️ Minimum Spanning Tree (Prim's Algorithm):\n";
        int totalWeight = 0;
        cout << "Edge\t\tDistance (meters)\n";
        for (int i = 1; i < V; i++) {
            cout << departments[parent[i]] << " - " << departments[i]
                 << "\t" << graph[i][parent[i]] << " m\n";
            totalWeight += graph[i][parent[i]];
        }
        cout << "Total Distance: " << totalWeight << " meters\n";
    }
};

// Main function with menu
int main() {
    int V, choice;

    cout << "Enter number of departments: ";
    cin >> V;

    CampusGraph campus(V);
    campus.inputDepartments();
    campus.inputDistances();

    do {
        cout << "\n--- College Campus Graph Menu ---\n";
        cout << "1. Display Adjacency Matrix\n";
        cout << "2. Find MST using Prim's Algorithm\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                campus.displayAdjacencyMatrix();
                break;
            case 2:
                campus.primMST();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 3);

    return 0;
}
___________________________________________________________________________________________________________________________________________________________________________________________________________
Assignment - 5
#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

class SupplyChain {
private:
    int V; // Number of locations
    vector<vector<int>> graph; // Adjacency matrix to store distances
    vector<string> locations; // Names of supply chain locations

public:
    // Constructor to initialize graph and location list
    SupplyChain(int v) {
        V = v;
        graph.resize(V, vector<int>(V, 0)); // Initialize distance matrix with 0
        locations.resize(V);
    }

    // Accept names of all locations
    void inputLocations() {
        cout << "\nEnter names of the locations in supply chain:\n";
        for (int i = 0; i < V; i++) {
            cout << "Location " << i << ": ";
            cin >> ws; // Flush input buffer
            getline(cin, locations[i]);
        }
    }

    // Accept distances between locations
    void inputDistances() {
        cout << "\nEnter distances (in km) between locations (0 if no direct connection):\n";
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                cout << "Distance from " << locations[i] << " to " << locations[j] << ": ";
                int d;
                cin >> d;
                graph[i][j] = graph[j][i] = d; // Undirected graph (symmetric matrix)
            }
        }
    }

    // Display the adjacency matrix
    void displayAdjacencyMatrix() {
        cout << "\nAdjacency Matrix (Distances in km):\n\t";
        for (const string& loc : locations) {
            cout << loc << "\t";
        }
        cout << "\n";
        for (int i = 0; i < V; i++) {
            cout << locations[i] << "\t";
            for (int j = 0; j < V; j++) {
                cout << graph[i][j] << "\t";
            }
            cout << "\n";
        }
    }

    // Implementation of Dijkstra's Algorithm
    void dijkstra(int start) {
        vector<int> dist(V, INT_MAX); // Stores shortest distances from start
        vector<bool> visited(V, false); // Keeps track of visited nodes
        vector<int> parent(V, -1); // To reconstruct the path
        dist[start] = 0;

        // Main loop of Dijkstra
        for (int count = 0; count < V - 1; count++) {
            int u = minDistance(dist, visited); // Select closest unvisited node
            visited[u] = true;

            // Update distance for neighbors of u
            for (int v = 0; v < V; v++) {
                if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
                    dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }

        int end;
        cout << "\nEnter destination node index (0 to " << V - 1 << "): ";
        cin >> end;
        cout << "\n🔍 Shortest path from " << locations[start] << " to " << locations[end] << ":\n";
        printPath(parent, end);
        cout << "\n📏 Total Distance: " << dist[end] << " km\n";
    }

    // Helper function to get the node with minimum distance
    int minDistance(vector<int>& dist, vector<bool>& visited) {
        int min = INT_MAX, min_index = -1;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }
        return min_index;
    }

    // Recursive function to print the path from source to destination
    void printPath(vector<int>& parent, int j) {
        if (parent[j] == -1) {
            cout << locations[j];
            return;
        }
        printPath(parent, parent[j]);
        cout << " -> " << locations[j];
    }
};

int main() {
    int V, choice;

    cout << "📦 Enter number of supply chain locations: ";
    cin >> V;

    SupplyChain sc(V);
    sc.inputLocations();
    sc.inputDistances();

    // Menu-driven interface
    do {
        cout << "\n--- Supply Chain Management Menu ---\n";
        cout << "1. Display Distance Matrix\n";
        cout << "2. Find Shortest Route (Dijkstra's Algorithm)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            sc.displayAdjacencyMatrix();
            break;
        case 2:
            int start;
            cout << "\nEnter starting node index (0 to " << V - 1 << "): ";
            cin >> start;
            sc.dijkstra(start);
            break;
        case 3:
            cout << "Exiting Supply Chain System...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
_____________________________________________________________________________________________________________________________________________________________________________________________
Assignment - 6A
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class BTreeNode {
public:
    vector<int> keys;
    vector<BTreeNode*> children;
    bool leaf;

    BTreeNode(bool is_leaf) : leaf(is_leaf) {}
};

class BTree {
private:
    BTreeNode* root;
    int order = 3; // Order 3: max 3 keys, 4 children

    void splitChild(BTreeNode* parent, int i) {
        BTreeNode* child = parent->children[i];
        BTreeNode* new_node = new BTreeNode(child->leaf);
        int mid = order / 2;

        parent->keys.insert(parent->keys.begin() + i, child->keys[mid]);
        parent->children.insert(parent->children.begin() + i + 1, new_node);

        new_node->keys.assign(child->keys.begin() + mid + 1, child->keys.end());
        child->keys.resize(mid);

        if (!child->leaf) {
            new_node->children.assign(child->children.begin() + mid + 1, child->children.end());
            child->children.resize(mid + 1);
        }
    }

    void insertNonFull(BTreeNode* node, int key) {
        int i = node->keys.size() - 1;
        if (node->leaf) {
            node->keys.push_back(0);
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
        } else {
            while (i >= 0 && key < node->keys[i]) i--;
            i++;
            if (node->children[i]->keys.size() == order) {
                splitChild(node, i);
                if (key > node->keys[i]) i++;
            }
            insertNonFull(node->children[i], key);
        }
    }

    int findPredecessor(BTreeNode* node) {
        BTreeNode* current = node;
        while (!current->leaf) {
            current = current->children.back();
        }
        return current->keys.back();
    }

    int findSuccessor(BTreeNode* node) {
        BTreeNode* current = node;
        while (!current->leaf) {
            current = current->children[0];
        }
        return current->keys[0];
    }

    void merge(BTreeNode* node, int i) {
        BTreeNode* child = node->children[i];
        BTreeNode* sibling = node->children[i + 1];

        child->keys.push_back(node->keys[i]);
        child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());
        child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());

        node->keys.erase(node->keys.begin() + i);
        node->children.erase(node->children.begin() + i + 1);

        delete sibling;
    }

    void borrowFromPrev(BTreeNode* node, int i) {
        BTreeNode* child = node->children[i];
        BTreeNode* sibling = node->children[i - 1];

        child->keys.insert(child->keys.begin(), node->keys[i - 1]);
        node->keys[i - 1] = sibling->keys.back();
        sibling->keys.pop_back();

        if (!child->leaf) {
            child->children.insert(child->children.begin(), sibling->children.back());
            sibling->children.pop_back();
        }
    }

    void borrowFromNext(BTreeNode* node, int i) {
        BTreeNode* child = node->children[i];
        BTreeNode* sibling = node->children[i + 1];

        child->keys.push_back(node->keys[i]);
        node->keys[i] = sibling->keys[0];
        sibling->keys.erase(sibling->keys.begin());

        if (!child->leaf) {
            child->children.push_back(sibling->children[0]);
            sibling->children.erase(sibling->children.begin());
        }
    }

    void fixNode(BTreeNode* node, int i) {
        if (i > 0 && node->children[i - 1]->keys.size() >= order / 2 + 1) {
            borrowFromPrev(node, i);
        } else if (i < node->children.size() - 1 && node->children[i + 1]->keys.size() >= order / 2 + 1) {
            borrowFromNext(node, i);
        } else {
            if (i < node->children.size() - 1) {
                merge(node, i);
            } else {
                merge(node, i - 1);
            }
        }
    }

    void deleteKey(BTreeNode* node, int key) {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i]) i++;

        if (i < node->keys.size() && node->keys[i] == key) {
            if (node->leaf) {
                node->keys.erase(node->keys.begin() + i);
            } else {
                deleteFromInternal(node, i);
            }
        } else if (!node->leaf) {
            fixNode(node, i);
            if (i < node->children.size()) {
                deleteKey(node->children[i], key);
            }
        } else {
            cout << "Key " << key << " not found\n";
        }
    }

    void deleteFromInternal(BTreeNode* node, int i) {
        int key = node->keys[i];
        BTreeNode* pred = node->children[i];
        BTreeNode* succ = node->children[i + 1];

        if (pred->keys.size() >= order / 2 + 1) {
            int pred_key = findPredecessor(pred);
            node->keys[i] = pred_key;
            deleteKey(pred, pred_key);
        } else if (succ->keys.size() >= order / 2 + 1) {
            int succ_key = findSuccessor(succ);
            node->keys[i] = succ_key;
            deleteKey(succ, succ_key);
        } else {
            merge(node, i);
            deleteKey(node->children[i], key);
        }
    }

public:
    BTree() {
        root = new BTreeNode(true);
    }

    void insert(int key) {
        if (root->keys.size() == order) {
            BTreeNode* new_root = new BTreeNode(false);
            new_root->children.push_back(root);
            root = new_root;
            splitChild(new_root, 0);
            insertNonFull(new_root, key);
        } else {
            insertNonFull(root, key);
        }
    }

    void deleteKey(int key) {
        if (!root->keys.size() && root->leaf) {
            cout << "Tree is empty\n";
            return;
        }

        deleteKey(root, key);

        if (!root->keys.size() && !root->leaf) {
            BTreeNode* temp = root;
            root = root->children[0];
            delete temp;
        }
    }

    void levelOrderDisplay() {
        if (!root->keys.size() && !root->children.size()) {
            cout << "Tree is empty\n";
            return;
        }

        queue<BTreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int level_size = q.size();
            for (int i = 0; i < level_size; i++) {
                BTreeNode* node = q.front();
                q.pop();

                for (int key : node->keys) {
                    cout << key << " ";
                }
                cout << "| ";

                for (BTreeNode* child : node->children) {
                    q.push(child);
                }
            }
            cout << "\n";
        }
    }
};

int main() {
    BTree btree;
    int choice, key;

    cout << "\nB-Tree Menu:\n";
    cout << "1. Insert\n";
    cout << "2. Delete\n";
    cout << "3. Display (Level-order)\n";
    cout << "4. Exit\n";

    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter key to insert: ";
            cin >> key;
            btree.insert(key);
            break;
        case 2:
            cout << "Enter key to delete: ";
            cin >> key;
            btree.deleteKey(key);
            break;
        case 3:
            cout << "Level-order display:\n";
            btree.levelOrderDisplay();
            break;
        case 4:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
}
__________________________________________________________________________________________________________________________________________________________________
Assignment - 6B

#include <iostream>
#include <string>
using namespace std;

enum Color { RED, BLACK };

class Node {
public:
    string directory;
    Color color;
    Node* left, *right, *parent;

    Node(string dir) : directory(dir), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    Node* root;

    void rotateLeft(Node*& root, Node*& pt) {
        Node* rightChild = pt->right;
        pt->right = rightChild->left;

        if (pt->right != nullptr) pt->right->parent = pt;

        rightChild->parent = pt->parent;

        if (pt->parent == nullptr) root = rightChild;
        else if (pt == pt->parent->left) pt->parent->left = rightChild;
        else pt->parent->right = rightChild;

        rightChild->left = pt;
        pt->parent = rightChild;
    }

    void rotateRight(Node*& root, Node*& pt) {
        Node* leftChild = pt->left;
        pt->left = leftChild->right;

        if (pt->left != nullptr) pt->left->parent = pt;

        leftChild->parent = pt->parent;

        if (pt->parent == nullptr) root = leftChild;
        else if (pt == pt->parent->left) pt->parent->left = leftChild;
        else pt->parent->right = leftChild;

        leftChild->right = pt;
        pt->parent = leftChild;
    }

    void fixViolation(Node*& root, Node*& pt) {
        Node* parent = nullptr;
        Node* grandParent = nullptr;

        while (pt != root && pt->color == RED && pt->parent->color == RED) {
            parent = pt->parent;
            grandParent = parent->parent;

            if (parent == grandParent->left) {
                Node* uncle = grandParent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    grandParent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    pt = grandParent;
                } else {
                    if (pt == parent->right) {
                        rotateLeft(root, parent);
                        pt = parent;
                        parent = pt->parent;
                    }
                    rotateRight(root, grandParent);
                    swap(parent->color, grandParent->color);
                    pt = parent;
                }
            } else {
                Node* uncle = grandParent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    grandParent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    pt = grandParent;
                } else {
                    if (pt == parent->left) {
                        rotateRight(root, parent);
                        pt = parent;
                        parent = pt->parent;
                    }
                    rotateLeft(root, grandParent);
                    swap(parent->color, grandParent->color);
                    pt = parent;
                }
            }
        }

        root->color = BLACK;
    }

    void inorder(Node* root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << (root->color == RED ? "[RED] " : "[BLACK] ") << root->directory << endl;
        inorder(root->right);
    }

public:
    RBTree() {
        root = nullptr;
    }

    void insert(string dir) {
        Node* pt = new Node(dir);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (pt->directory < x->directory)
                x = x->left;
            else
                x = x->right;
        }

        pt->parent = y;

        if (y == nullptr)
            root = pt;
        else if (pt->directory < y->directory)
            y->left = pt;
        else
            y->right = pt;

        fixViolation(root, pt);
    }

    void display() {
        cout << "File System (Inorder Traversal):\n";
        inorder(root);
    }
};

int main() {
    RBTree fs;
    int choice;
    string dir;

    do {
        cout << "\nFile System Menu:\n";
        cout << "1. Create Directory\n";
        cout << "2. Display Directory Structure\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter directory name: ";
                cin >> dir;
                fs.insert(dir);
                break;
            case 2:
                fs.display();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }

    } while (choice != 3);

    return 0;
}
________________________________________________________________________________________________________________________________________________________
Min-Heap
#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void heapifyUp(int i) {
        while (i > 0 && heap[i] < heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int size = heap.size();
        int smallest = i;
        int l = left(i), r = right(i);
        if (l < size && heap[l] < heap[smallest]) smallest = l;
        if (r < size && heap[r] < heap[smallest]) smallest = r;
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
        cout << "Inserted " << val << " into Min-Heap.\n";
    }

    void deleteRoot() {
        if (heap.empty()) {
            cout << "Heap is empty.\n";
            return;
        }
        cout << "Deleted root: " << heap[0] << "\n";
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    void display() {
        cout << "Min-Heap: ";
        for (int val : heap)
            cout << val << " ";
        cout << "\n";
    }
};

int main() {
    MinHeap h;
    int choice, val;

    do {
        cout << "\n--- Min-Heap Menu ---\n";
        cout << "1. Insert\n2. Delete Root\n3. Display\n0. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: cout << "Enter value to insert: "; cin >> val; h.insert(val); break;
            case 2: h.deleteRoot(); break;
            case 3: h.display(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
_______________________________________________________________________________________________________________________
Max-Heap
#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void heapifyUp(int i) {
        while (i > 0 && heap[i] > heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int size = heap.size();
        int largest = i;
        int l = left(i), r = right(i);
        if (l < size && heap[l] > heap[largest]) largest = l;
        if (r < size && heap[r] > heap[largest]) largest = r;
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
        cout << "Inserted " << val << " into Max-Heap.\n";
    }

    void deleteRoot() {
        if (heap.empty()) {
            cout << "Heap is empty.\n";
            return;
        }
        cout << "Deleted root: " << heap[0] << "\n";
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    void display() {
        cout << "Max-Heap: ";
        for (int val : heap)
            cout << val << " ";
        cout << "\n";
    }
};

int main() {
    MaxHeap h;
    int choice, val;

    do {
        cout << "\n--- Max-Heap Menu ---\n";
        cout << "1. Insert\n2. Delete Root\n3. Display\n0. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: cout << "Enter value to insert: "; cin >> val; h.insert(val); break;
            case 2: h.deleteRoot(); break;
            case 3: h.display(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
___________________________________________________________________________________________________________________________________________________
Linked-list BST
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class LinkedListBST {
private:
    Node* root;

    void insert(Node* &node, int val) {
        if (!node) node = new Node(val);
        else if (val < node->data) insert(node->left, val);
        else insert(node->right, val);
    }

public:
    LinkedListBST() : root(nullptr) {}

    void generate(int n) {
        cout << "Enter " << n << " values: ";
        for (int i = 0; i < n; ++i) {
            int val;
            cin >> val;
            insert(root, val);
        }
    }

    void postOrder(Node* node) {
        if (!node) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }

    void postOrderTraversal() {
        cout << "Post-order Traversal: ";
        postOrder(root);
        cout << endl;
    }

    int heightNonRecursive() {
        if (!root) return 0;
        queue<Node*> q;
        q.push(root);
        int height = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                Node* temp = q.front(); q.pop();
                if (temp->left) q.push(temp->left);
                if (temp->right) q.push(temp->right);
            }
            height++;
        }
        return height;
    }
};

int main() {
    LinkedListBST bst;
    int choice, n;

    do {
        cout << "\n--- Linked List BST Menu ---\n";
        cout << "1. Generate Random BST\n2. Post-order Traversal\n3. Height (Non-Recursive)\n0. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "How many nodes? ";
                cin >> n;
                bst.generate(n);
                break;
            case 2:
                bst.postOrderTraversal();
                break;
            case 3:
                cout << "Height of BST: " << bst.heightNonRecursive() << endl;
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
______________________________________________________________________________________________________________________________________________
Array BST
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 1000;

class ArrayBST {
private:
    int tree[MAX_SIZE];

public:
    ArrayBST() {
        fill(tree, tree + MAX_SIZE, -1);
    }

    void insert(int val) {
        int i = 0;
        while (i < MAX_SIZE) {
            if (tree[i] == -1) {
                tree[i] = val;
                return;
            }
            else if (val < tree[i])
                i = 2 * i + 1;
            else
                i = 2 * i + 2;
        }
    }

    void generate(int n) {
        cout << "Enter " << n << " values: ";
        for (int i = 0; i < n; ++i) {
            int val;
            cin >> val;
            insert(val);
        }
    }

    void postOrderTraversal(int index = 0) {
        if (index >= MAX_SIZE || tree[index] == -1) return;
        postOrderTraversal(2 * index + 1);
        postOrderTraversal(2 * index + 2);
        cout << tree[index] << " ";
    }

    int heightNonRecursive() {
        int maxHeight = 0;
        for (int i = 0; i < MAX_SIZE; ++i) {
            if (tree[i] != -1) {
                int h = 0, index = i;
                while (index != 0) {
                    index = (index - 1) / 2;
                    h++;
                }
                maxHeight = max(maxHeight, h);
            }
        }
        return maxHeight + 1;
    }
};

int main() {
    ArrayBST bst;
    int choice, n;

    do {
        cout << "\n--- Array BST Menu ---\n";
        cout << "1. Generate Random BST\n2. Post-order Traversal\n3. Height (Non-Recursive)\n0. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "How many nodes? ";
                cin >> n;
                bst.generate(n);
                break;
            case 2:
                cout << "Post-order Traversal: ";
                bst.postOrderTraversal();
                cout << endl;
                break;
            case 3:
                cout << "Height of BST: " << bst.heightNonRecursive() << endl;
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
_____________________________________________________________________________________________________________________________________________________
Kruskal
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class CampusGraph {
private:
    int V;
    vector<vector<int>> graph;
    vector<string> departments;

    struct Edge {
        int u, v, weight;
        bool operator<(Edge const& other) {
            return weight < other.weight;
        }
    };

    vector<Edge> edges;

public:
    CampusGraph(int vertices) {
        V = vertices;
        graph.resize(V, vector<int>(V, 0));
        departments.resize(V);
    }

    void inputDepartments() {
        cout << "Enter names of " << V << " departments: \n";
        for (int i = 0; i < V; i++) {
            cout << "Department " << i << ": ";
            cin >> ws;
            getline(cin, departments[i]);
        }
    }

    void inputDistances() {
        cout << "\nEnter distance between departments (in meters): \n";
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                cout << "Distance between " << departments[i] << " and " << departments[j] << ": ";
                int dist;
                cin >> dist;
                graph[i][j] = graph[j][i] = dist;
                edges.push_back({i, j, dist});
            }
        }
    }

    void displayAdjacencyMatrix() {
        cout << "\nAdjacency Matrix:\n\t";
        for (int i = 0; i < V; i++) cout << departments[i] << "\t";
        cout << endl;
        for (int i = 0; i < V; i++) {
            cout << departments[i] << "\t";
            for (int j = 0; j < V; j++) {
                cout << graph[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void kruskalMST() {
        sort(edges.begin(), edges.end());

        vector<int> parent(V), rank(V, 0);
        for (int i = 0; i < V; i++)
            parent[i] = i;

        int totalWeight = 0;
        vector<Edge> result;

        for (Edge& e : edges) {
            int setU = findSet(e.u, parent);
            int setV = findSet(e.v, parent);

            if (setU != setV) {
                result.push_back(e);
                totalWeight += e.weight;
                unionSets(setU, setV, parent, rank);
            }
        }

        // Display result
        cout << "\nMinimum Spanning Tree using Kruskal's Algorithm:\n";
        cout << "Edge\t\tDistance (meters)\n";
        for (auto& e : result) {
            cout << departments[e.u] << " - " << departments[e.v] << "\t" << e.weight << " m\n";
        }
        cout << "Total Distance: " << totalWeight << " meters\n";
    }

    int findSet(int v, vector<int>& parent) {
        if (v == parent[v])
            return v;
        return parent[v] = findSet(parent[v], parent);
    }

    void unionSets(int a, int b, vector<int>& parent, vector<int>& rank) {
        a = findSet(a, parent);
        b = findSet(b, parent);
        if (a != b) {
            if (rank[a] < rank[b])
                parent[a] = b;
            else if (rank[a] > rank[b])
                parent[b] = a;
            else {
                parent[b] = a;
                rank[a]++;
            }
        }
    }
};

int main() {
    int V, choice;

    cout << "Enter number of departments: ";
    cin >> V;

    CampusGraph campus(V);
    campus.inputDepartments();
    campus.inputDistances();

    cout << "\n--- College Campus Graph Menu ---\n";
    cout << "1. Display Adjacency Matrix\n";
    cout << "2. Find MST using Kruskal's Algorithm\n";
    cout << "3. Exit\n";

    do {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            campus.displayAdjacencyMatrix();
            break;
        case 2:
            campus.kruskalMST();
            break;
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}


