#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
using namespace std;


//util funcs

void prntFlot(float f) {
    int whole = (int)f;
    int dec   = (int)((f - whole) * 10 + 0.5f);
    if (dec == 10) { whole++; dec = 0; }
    cout << whole << "." << dec;
}


// void rev(vector<int>& v, int lo, int hi) {
//     while (lo < hi) { int tmp = v[lo]; v[lo] = v[hi]; v[hi] = tmp; lo++; hi--; }
// }


struct Edge { int u, v, w; };
void edgeInsertionSort(vector<Edge>& edges) {
    int n = edges.size();
    for (int i = 1; i < n; i++) {
        Edge key = edges[i];
        int j = i - 1;
        while (j >= 0 && edges[j].w > key.w) {
            edges[j+1] = edges[j];
            j--;
        }
        edges[j+1] = key;
    }
}



//stu struct
struct Student {
    int    stuID;
    string gender;
    char   grade;
    int    ovrScore;
    float  attendance;
    bool   exClass;
};

void printStudent(const Student& s) {
    cout << "  ID:" << s.stuID
         << " | "   << s.gender
         << " | Gr:"<< s.grade
         << " | Score:" << s.ovrScore
         << " | Att:";
    prntFlot(s.attendance);
    cout << "%"
         << " | Extra:" << (s.exClass ? "Yes" : "No")
         << "\n";
}


void studentSortByScore(vector<Student>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        Student key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].ovrScore > key.ovrScore) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

//dll
struct dllNode {
    Student data;
    dllNode* prev;
    dllNode* next;
    dllNode(Student s) {
    data = s;
    prev = nullptr;
    next = nullptr; }
};

struct DoublyLinkedList {
    dllNode* head;
    int size;
    DoublyLinkedList(){
        head=nullptr; size=0;
    }

    void append(Student s) {
        dllNode* n = new dllNode(s);
        if (!head) { head = n; }
        else {
            dllNode* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = n;
            n->prev   = cur;
        }
        size++;
    }

    bool remove(int id) {
        dllNode* cur = head;
        while (cur) {
            if (cur->data.stuID == id) {
                if (cur->prev) cur->prev->next = cur->next;
                else            head = cur->next;
                if (cur->next) cur->next->prev = cur->prev;
                delete cur; size--; return true;
            }
            cur = cur->next;
        }
        return false;
    }

    bool exists(int id) {
        dllNode* cur = head;
        while (cur) { if (cur->data.stuID == id) return true; cur = cur->next; }
        return false;
    }

    void display() {
        if (!head) { cout << "dll empty\n"; return; }
        dllNode* cur = head;
        int i = 1;
        while (cur) { cout << "  [" << i++ << "]"; printStudent(cur->data); cur = cur->next; }
        cout << "  Total nodes: " << size << "\n";
    }

    vector<Student> toVector() {
        vector<Student> v;
        dllNode* cur = head;
        while (cur) { v.push_back(cur->data); cur = cur->next; }
        return v;
    }
};

//stack
struct stkNode {
    Student data;
    stkNode* next;
    stkNode(Student s){
        data=s;
        next=nullptr;
    }
};

struct Stack {
    stkNode* top;
    int size;
    string name;

    
    Stack() : top(nullptr), size(0), name("") {}
    Stack(string n) {
        top=nullptr; size=0; name=n;
    }

    void push(Student s) {
        stkNode* n = new stkNode(s);
        n->next = top;
        top = n;
        size++;
    }

    bool isEmpty() { return top == nullptr; }

    Student pop() {
        Student s = top->data;
        stkNode* tmp = top;
        top = top->next;
        delete tmp;
        size--;
        return s;
    }

    Student peek() { return top->data; }

    // Remove a specific stuID from stack
    void removeId(int id) {
        stkNode temp(Student{}); temp.next = top;
        stkNode* prev = &temp;
        stkNode* cur  = top;
        while (cur) {
            if (cur->data.stuID == id) {
                prev->next = cur->next;
                if (cur == top) top = cur->next;
                delete cur;
                size--;
                cur = prev->next;
            } else {
                prev = cur;
                cur  = cur->next;
            }
        }
        top = temp.next;
    }

    void display() {
        if (!top) { cout << "  [" << name << " is empty]\n"; return; }
        cout << "  " << name << " (top -> bottom):\n";
        stkNode* cur = top;
        while (cur) { cout << "   "; printStudent(cur->data); cur = cur->next; }
    }
};

//avl tree sorted by overall sore
struct AVLNode {
    Student data;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(Student s) {
    data   = s;
    height = 1;
    left   = nullptr;
    right  = nullptr;
    }   
};

int avlHeight(AVLNode* n) { return n ? n->height : 0; }
int avlBF(AVLNode* n)     { return n ? avlHeight(n->left) - avlHeight(n->right) : 0; }
int avlMax(int a, int b)  { return a > b ? a : b; }
void avlUpdateH(AVLNode* n) {
    if (n) n->height = 1 + avlMax(avlHeight(n->left), avlHeight(n->right));
}

AVLNode* avlRotateRight(AVLNode* y) {
    AVLNode* x  = y->left;
    AVLNode* T2 = x->right;
    x->right = y; y->left = T2;
    avlUpdateH(y); avlUpdateH(x);
    return x;
}
AVLNode* avlRotateLeft(AVLNode* x) {
    AVLNode* y  = x->right;
    AVLNode* T2 = y->left;
    y->left = x; x->right = T2;
    avlUpdateH(x); avlUpdateH(y);
    return y;
}

AVLNode* avlInsert(AVLNode* node, Student s, int& rotations) {
    if (!node) return new AVLNode(s);
    if (s.ovrScore < node->data.ovrScore)
        node->left  = avlInsert(node->left,  s, rotations);
    else
        node->right = avlInsert(node->right, s, rotations);

    avlUpdateH(node);
    int bf = avlBF(node);

    if (bf > 1 && s.ovrScore < node->left->data.ovrScore)   //ll
        { rotations++; return avlRotateRight(node); }
    if (bf < -1 && s.ovrScore > node->right->data.ovrScore) //rr
        { rotations++; return avlRotateLeft(node); }
    if (bf > 1 && s.ovrScore > node->left->data.ovrScore)   //lr
        { rotations++; node->left = avlRotateLeft(node->left); return avlRotateRight(node); }
    if (bf < -1 && s.ovrScore < node->right->data.ovrScore) //rl
        { rotations++; node->right = avlRotateRight(node->right); return avlRotateLeft(node); }
    return node;
}

AVLNode* avlMinNode(AVLNode* n) { while (n->left) n = n->left; return n; }

AVLNode* avlDelete(AVLNode* root, int score, int id) {
    if (!root) return nullptr;
    if (score < root->data.ovrScore)
        root->left = avlDelete(root->left, score, id);
    else if (score > root->data.ovrScore)
        root->right = avlDelete(root->right, score, id);
    else {
        if (root->data.stuID == id) {
            if (!root->left || !root->right) {
                AVLNode* tmp = root->left ? root->left : root->right;
                delete root; return tmp;
            }
            AVLNode* succ = avlMinNode(root->right);
            root->data    = succ->data;
            root->right   = avlDelete(root->right, succ->data.ovrScore, succ->data.stuID);
        } else {
            root->left  = avlDelete(root->left,  score, id);
            root->right = avlDelete(root->right, score, id);
        }
    }
    avlUpdateH(root);
    int bf = avlBF(root);
    if (bf > 1  && avlBF(root->left)  >= 0) return avlRotateRight(root);
    if (bf > 1  && avlBF(root->left)  <  0) { root->left  = avlRotateLeft(root->left);  return avlRotateRight(root); }
    if (bf < -1 && avlBF(root->right) <= 0) return avlRotateLeft(root);
    if (bf < -1 && avlBF(root->right) >  0) { root->right = avlRotateRight(root->right); return avlRotateLeft(root); }
    return root;
}

void avlSearch(AVLNode* root, int score, int& comparisons, bool& found) {
    if (!root) return;
    comparisons++;
    if (score == root->data.ovrScore) {
        found = true;
        cout << "    Found: "; printStudent(root->data);
        avlSearch(root->right, score, comparisons, found);
    } else if (score < root->data.ovrScore)
        avlSearch(root->left,  score, comparisons, found);
    else
        avlSearch(root->right, score, comparisons, found);
}

void avlInorder(AVLNode* root) {
    if (!root) return;
    avlInorder(root->left);
    printStudent(root->data);
    avlInorder(root->right);
}

//min heap acc to attendacne
struct MinHeap {
    vector<Student> heap;
    MinHeap() {}

    int parent(int i) { return (i-1)/2; }
    int left(int i)   { return 2*i+1; }
    int right(int i)  { return 2*i+2; }

    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)].attendance > heap[i].attendance) {
            Student tmp = heap[parent(i)];
            heap[parent(i)] = heap[i];
            heap[i] = tmp;
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int n = heap.size(), smallest = i;
        if (left(i)  < n && heap[left(i)].attendance  < heap[smallest].attendance) smallest = left(i);
        if (right(i) < n && heap[right(i)].attendance < heap[smallest].attendance) smallest = right(i);
        if (smallest != i) {
            Student tmp = heap[i]; heap[i] = heap[smallest]; heap[smallest] = tmp;
            heapifyDown(smallest);
        }
    }

    void insert(Student s) {
        heap.push_back(s);
        heapifyUp(heap.size()-1);
    }

    void remove(int id) {
        int idx = -1;
        for (int i = 0; i < (int)heap.size(); i++)
            if (heap[i].stuID == id) { idx = i; break; }
        if (idx == -1) return;
        heap[idx] = heap.back();
        heap.pop_back();
        if (idx < (int)heap.size()) { heapifyUp(idx); heapifyDown(idx); }
    }

    Student extractMin() {
        Student s = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return s;
    }

    void display() {
        if (heap.empty()) { cout << "  [Heap empty]\n"; return; }
        cout << "  Min Heap sorted view (by attendance %):\n";
        MinHeap tmp; tmp.heap = heap;
        int rank = 1;
        while (!tmp.heap.empty()) {
            Student s = tmp.extractMin();
            cout << "  [" << rank++ << "]"; printStudent(s);
        }
    }

    void showAtRisk() {
    if (heap.empty()) { cout << "  [Heap empty]\n"; return; }
    cout << "  At-risk students (attendance < 70%):\n";
    MinHeap tmp; tmp.heap = heap;
    int cnt = 0;
    while (!tmp.heap.empty()) {
        Student s = tmp.extractMin();
        if (s.attendance < 70) {
            cout << "  [" << ++cnt << "]"; printStudent(s);
        } else {
            break;
        }
    }
    if (cnt == 0) cout << "  No students with attendance below 70%.\n";
    }
};

//hash
const int HASH_SIZE = 53;

struct HashNode {
    Student data;
    HashNode* next;
    HashNode(Student s) : data(s), next(nullptr) {}
};

struct HashTable {
    HashNode* table[HASH_SIZE];
    HashTable() { for (int i = 0; i < HASH_SIZE; i++) table[i] = nullptr; }

    int hashFn(int id) { return id % HASH_SIZE; }

    void insert(Student s) {
        int idx = hashFn(s.stuID);
        HashNode* n = new HashNode(s);
        n->next = table[idx];
        table[idx] = n;
    }

    bool remove(int id) {
        int idx = hashFn(id);
        HashNode* cur = table[idx], *prev = nullptr;
        while (cur) {
            if (cur->data.stuID == id) {
                if (prev) prev->next = cur->next;
                else      table[idx] = cur->next;
                delete cur; return true;
            }
            prev = cur; cur = cur->next;
        }
        return false;
    }

    Student* search(int id, int& probes) {
        int idx = hashFn(id);
        HashNode* cur = table[idx];
        probes = 0;
        while (cur) {
            probes++;
            if (cur->data.stuID == id) return &cur->data;
            cur = cur->next;
        }
        return nullptr;
    }

    void display() {
        cout << "  Hash Table (non-empty buckets):\n";
        for (int i = 0; i < HASH_SIZE; i++) {
            if (table[i]) {
                cout << "  Bucket[" << i << "]: ";
                HashNode* cur = table[i];
                while (cur) {
                    cout << cur->data.stuID;
                    if (cur->next) cout << " -> ";
                    cur = cur->next;
                }
                cout << "\n";
            }
        }
    }
};

//graphs
const int MAXV = 200;

struct Graph {
    int adjMatrix[MAXV][MAXV];
    int idMap[MAXV];
    int n;

    Graph() : n(0) {
        for (int i = 0; i < MAXV; i++)
            for (int j = 0; j < MAXV; j++)
                adjMatrix[i][j] = 0;
    }

    int indexOf(int id) {
        for (int i = 0; i < n; i++) if (idMap[i] == id) return i;
        return -1;
    }

    void addVertex(Student s, DoublyLinkedList& dll) {
        int newIdx = n;
        idMap[n] = s.stuID;
        n++;
        dllNode* cur = dll.head;
        while (cur) {
            int idx = indexOf(cur->data.stuID);
            if (idx != -1 && idx != newIdx) {
                int w = cur->data.ovrScore - s.ovrScore;
                if (w < 0) w = -w;
                adjMatrix[newIdx][idx] = w;
                adjMatrix[idx][newIdx] = w;
            }
            cur = cur->next;
        }
    }

    void removeVertex(int id) {
        int idx = indexOf(id);
        if (idx == -1) return;
        for (int i = idx; i < n-1; i++) {
            idMap[i] = idMap[i+1];
            for (int j = 0; j < n; j++) adjMatrix[i][j] = adjMatrix[i+1][j];
        }
        for (int j = idx; j < n-1; j++)
            for (int i = 0; i < n; i++) adjMatrix[i][j] = adjMatrix[i][j+1];
        n--;
        for (int i = 0; i < MAXV; i++) adjMatrix[n][i] = adjMatrix[i][n] = 0;
    }

    void display() {
        if (n == 0) { cout << "  [Graph empty]\n"; return; }
        cout << "  Graph vertices: " << n << "\n";
        cout << "  Edges with weight <= 5:\n";
        int shown = 0;
        for (int i = 0; i < n; i++)
            for (int j = i+1; j < n; j++)
                if (adjMatrix[i][j] > 0 && adjMatrix[i][j] <= 5) {
                    cout << "    " << idMap[i] << " --[" << adjMatrix[i][j] << "]-- " << idMap[j] << "\n";
                    shown++;
                }
        if (shown == 0) cout << "  (No edges with weight <= 5)\n";
        cout << "  Total possible edges: " << n*(n-1)/2 << "\n";
    }

    //dijkstra
    void dijkstra(int srcId) {
        int src = indexOf(srcId);
        if (src == -1) { cout << "  Source not found.\n"; return; }

        int dist[MAXV], prev[MAXV];
        bool visited[MAXV];
        for (int i = 0; i < n; i++) { dist[i] = INT_MAX; visited[i] = false; prev[i] = -1; }
        dist[src] = 0;

        int relaxations = 0;
        for (int count = 0; count < n-1; count++) {
            int u = -1;
            for (int i = 0; i < n; i++)
                if (!visited[i] && (u == -1 || dist[i] < dist[u])) u = i;
            if (u == -1 || dist[u] == INT_MAX) break;
            visited[u] = true;

            for (int v = 0; v < n; v++) {
                if (!visited[v] && adjMatrix[u][v] && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    prev[v] = u;
                    relaxations++;
                }
            }
        }

        cout << "  Dijkstra from student " << srcId << ":\n";
        cout << "  Total relaxations: " << relaxations << "\n";
        for (int i = 0; i < n; i++) {
            if (i == src) continue;
            cout << "    -> " << idMap[i] << " | dist=";
            if (dist[i] == INT_MAX) cout << "INF"; else cout << dist[i];
            cout << " | path: ";
            // build path manually
            int path[MAXV], plen = 0, at = i;
            while (at != -1) { path[plen++] = at; at = prev[at]; }
            
            for (int a = 0, b = plen-1; a < b; a++, b--) { int t = path[a]; path[a] = path[b]; path[b] = t; }
            for (int k = 0; k < plen; k++) {
                cout << idMap[path[k]];
                if (k < plen-1) cout << " -> ";
            }
            cout << "\n";
        }
    }

    //prims
    void prims() {
        if (n == 0) return;
        int key[MAXV], parent[MAXV];
        bool inMST[MAXV];
        for (int i = 0; i < n; i++) { key[i] = INT_MAX; inMST[i] = false; parent[i] = -1; }
        key[0] = 0;
        int totalWeight = 0, edgesAdded = 0;

        for (int count = 0; count < n; count++) {
            int u = -1;
            for (int i = 0; i < n; i++)
                if (!inMST[i] && (u == -1 || key[i] < key[u])) u = i;
            inMST[u] = true;
            for (int v = 0; v < n; v++)
                if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    key[v] = adjMatrix[u][v];
                    parent[v] = u;
                }
        }

        cout << "  Prim's MST edges:\n";
        for (int i = 1; i < n; i++) {
            if (parent[i] != -1) {
                cout << "    " << idMap[parent[i]] << " -- " << idMap[i]
                     << " | weight=" << adjMatrix[parent[i]][i] << "\n";
                totalWeight += adjMatrix[parent[i]][i];
                edgesAdded++;
            }
        }
        cout << "  Total Weight: " << totalWeight << " | Edges: " << edgesAdded << "\n";
    }

    //kruskal
    int kruskalFind(int parent[], int x) {
        if (parent[x] != x) parent[x] = kruskalFind(parent, parent[x]);
        return parent[x];
    }
    bool kruskalUnion(int parent[], int rnk[], int x, int y) {
        int rx = kruskalFind(parent, x), ry = kruskalFind(parent, y);
        if (rx == ry) return false;
        if (rnk[rx] < rnk[ry]) { int t = rx; rx = ry; ry = t; }
        parent[ry] = rx;
        if (rnk[rx] == rnk[ry]) rnk[rx]++;
        return true;
    }

    void kruskals() {
        if (n == 0) return;
        vector<Edge> edges;
        for (int i = 0; i < n; i++)
            for (int j = i+1; j < n; j++)
                if (adjMatrix[i][j]) { Edge e; e.u=i; e.v=j; e.w=adjMatrix[i][j]; edges.push_back(e); }

        edgeInsertionSort(edges); 

        int par[MAXV], rnk[MAXV];
        for (int i = 0; i < n; i++) { par[i] = i; rnk[i] = 0; }

        cout << "  Kruskal's MST (edges considered: " << edges.size() << "):\n";
        int totalWeight = 0, edgesAdded = 0;
        for (int i = 0; i < (int)edges.size(); i++) {
            if (kruskalUnion(par, rnk, edges[i].u, edges[i].v)) {
                cout << "    " << idMap[edges[i].u] << " -- " << idMap[edges[i].v]
                     << " | weight=" << edges[i].w << "\n";
                totalWeight += edges[i].w;
                edgesAdded++;
                if (edgesAdded == n-1) break;
            }
        }
        cout << "  Total Weight: " << totalWeight << " | Edges: " << edgesAdded << "\n";
    }
};

//search algos
void linearSearch(DoublyLinkedList& dll, int id) {
    dllNode* cur = dll.head;
    int iter = 0;
    while (cur) {
        iter++;
        if (cur->data.stuID == id) {
            cout << "  Found after " << iter << " iteration(s):\n";
            printStudent(cur->data);
            return;
        }
        cur = cur->next;
    }
    cout << "  Not found after " << iter << " iteration(s).\n";
}

void binarySearch(DoublyLinkedList& dll, int score) {
    vector<Student> arr = dll.toVector();
    studentSortByScore(arr); 

    int lo = 0, hi = (int)arr.size()-1, iter = 0;
    bool found = false;
    while (lo <= hi) {
        iter++;
        int mid = (lo + hi) / 2;
        cout << "    Iter " << iter << ": index=" << mid
             << " score=" << arr[mid].ovrScore << "\n";
        if (arr[mid].ovrScore == score) {
            cout << "  Found at iteration " << iter << ":\n";
            printStudent(arr[mid]);
            found = true; break;
        } else if (arr[mid].ovrScore < score) lo = mid+1;
        else hi = mid-1;
    }
    if (!found) cout << "  Score " << score << " not found.\n";
    cout << "  Total iterations: " << iter << "\n";
}

//sort algo
void showSortResult(vector<Student>& arr, const string& label, long long comps, long long swaps) {
    cout << "  [" << label << "] Comparisons: " << comps << " | Swaps: " << swaps << "\n";
    cout << "  Sorted (by ovrScore):\n";
    for (int i = 0; i < (int)arr.size(); i++) { cout << "   [" << i+1 << "]"; printStudent(arr[i]); }
}

void bubbleSort(vector<Student> arr) {
    int n = arr.size();
    long long comps = 0, swaps = 0;
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++) {
            comps++;
            if (arr[j].ovrScore > arr[j+1].ovrScore) {
                Student t = arr[j]; arr[j] = arr[j+1]; arr[j+1] = t;
                swaps++;
            }
        }
    showSortResult(arr, "Bubble Sort", comps, swaps);
}

void selectionSort(vector<Student> arr) {
    int n = arr.size();
    long long comps = 0, swaps = 0;
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) { comps++; if (arr[j].ovrScore < arr[minIdx].ovrScore) minIdx = j; }
        if (minIdx != i) { Student t = arr[i]; arr[i] = arr[minIdx]; arr[minIdx] = t; swaps++; }
    }
    showSortResult(arr, "Selection Sort", comps, swaps);
}

void insertionSort(vector<Student> arr) {
    int n = arr.size();
    long long comps = 0, swaps = 0;
    for (int i = 1; i < n; i++) {
        Student key = arr[i]; int j = i-1; comps++;
        while (j >= 0 && arr[j].ovrScore > key.ovrScore) {
            comps++;
            arr[j+1] = arr[j]; swaps++; j--;
        }
        arr[j+1] = key;
    }
    showSortResult(arr, "Insertion Sort", comps, swaps);
}

long long mergeComps = 0, mergeSwaps = 0;
void mergeArr(vector<Student>& arr, int l, int m, int r) {
    int lSize = m - l + 1, rSize = r - m;
    vector<Student> L(lSize), R(rSize);
    for (int i = 0; i < lSize; i++) L[i] = arr[l+i];
    for (int i = 0; i < rSize; i++) R[i] = arr[m+1+i];
    int i = 0, j = 0, k = l;
    while (i < lSize && j < rSize) {
        mergeComps++;
        if (L[i].ovrScore <= R[j].ovrScore) arr[k++] = L[i++];
        else { arr[k++] = R[j++]; mergeSwaps++; }
    }
    while (i < lSize) arr[k++] = L[i++];
    while (j < rSize) arr[k++] = R[j++];
}
void mergeSortHelper(vector<Student>& arr, int l, int r) {
    if (l >= r) return;
    int m = (l+r)/2;
    mergeSortHelper(arr, l, m);
    mergeSortHelper(arr, m+1, r);
    mergeArr(arr, l, m, r);
}
void mergeSort(vector<Student> arr) {
    mergeComps = 0; mergeSwaps = 0;
    mergeSortHelper(arr, 0, (int)arr.size()-1);
    showSortResult(arr, "Merge Sort", mergeComps, mergeSwaps);
}

//system
struct StudentSystem {
    DoublyLinkedList dll;
    Stack insertStack;
    Stack deleteStack;
    AVLNode* avlRoot;
    MinHeap  minHeap;
    HashTable hashTable;
    Graph   graph;

    StudentSystem() : insertStack("Insert-Undo Stack"), deleteStack("Delete-Undo Stack"), avlRoot(nullptr) { }

    void insertStudent(Student s, bool fromUndo = false) {
        if (dll.exists(s.stuID)) {
            cout << "  Student ID " << s.stuID << " already exists.\n";
            return;
        }
        dll.append(s);
        int rotations = 0;
        avlRoot = avlInsert(avlRoot, s, rotations);
        cout << "  [AVL]       Inserted score=" << s.ovrScore << " | Rotations: " << rotations << "\n";
        minHeap.insert(s);
        cout << "  [MinHeap]   Inserted attendance="; prntFlot(s.attendance); cout << "%\n";
        hashTable.insert(s);
        cout << "  [HashTable] Bucket " << s.stuID % HASH_SIZE << "\n";
        graph.addVertex(s, dll);
        cout << "  [Graph]     Vertices now: " << graph.n << "\n";
        if (!fromUndo) {
            insertStack.push(s);
            cout << "  [InsertStack] Pushed " << s.stuID << "\n";
        }
        cout << "  => Student " << s.stuID << " inserted into ALL structures.\n";
    }

    void deleteStudent(int id, bool fromUndo = false) {
        dllNode* cur = dll.head;
        Student s; bool found = false;
        while (cur) { if (cur->data.stuID == id) { s = cur->data; found = true; break; } cur = cur->next; }
        if (!found) { cout << "  Student " << id << " not found.\n"; return; }

        insertStack.removeId(id); // stale undo prevention

        dll.remove(id);           cout << "  [DLL]       Removed " << id << "\n";
        avlRoot = avlDelete(avlRoot, s.ovrScore, id);
                                  cout << "  [AVL]       Deleted score=" << s.ovrScore << "\n";
        minHeap.remove(id);       cout << "  [MinHeap]   Removed " << id << "\n";
        hashTable.remove(id);     cout << "  [HashTable] Removed " << id << "\n";
        graph.removeVertex(id);   cout << "  [Graph]     Vertices now: " << graph.n << "\n";
        if (!fromUndo) {
            deleteStack.push(s);
            cout << "  [DeleteStack] Pushed " << id << " for undo\n";
        }
        cout << "  => Student " << id << " deleted from ALL structures.\n";
    }

    void undoInsert() {
        if (insertStack.isEmpty()) { cout << "  InsertStack empty: nothing to undo.\n"; return; }
        Student s = insertStack.pop();
        cout << "  Undoing insert of " << s.stuID << "...\n";
        deleteStudent(s.stuID, true);
    }

    void undoDelete() {
        if (deleteStack.isEmpty()) { cout << "  DeleteStack empty: nothing to undo.\n"; return; }
        Student s = deleteStack.pop();
        cout << "  Undoing delete of " << s.stuID << "...\n";
        insertStudent(s, true);
    }
};

// ============================================================
//  CSV LOADER
// ============================================================
Student parseRow(const string& line) {
    Student s;
    stringstream ss(line);
    string token;
    getline(ss, token, ','); s.stuID     = stoi(token);
    getline(ss, s.gender,   ',');
    getline(ss, token, ','); s.grade          = token[0];
    getline(ss, token, ','); s.ovrScore  = stoi(token);
    getline(ss, token, ','); s.attendance = stof(token);
    getline(ss, token, ','); s.exClass  = (token[0] == 'Y');
    return s;
}

// ============================================================
//  MENU
// ============================================================
void separator() { cout << "\n" << string(60, '=') << "\n"; }

void printMenu() {
    separator();
    cout << "  STUDENT DATA STRUCTURES SYSTEM\n";
    separator();
    cout << "  1.  Display All Students (DLL)\n";
    cout << "  2.  Insert New Student\n";
    cout << "  3.  Delete Student\n";
    cout << "  4.  Undo Last Insert\n";
    cout << "  5.  Undo Last Delete\n";
    cout << "  6.  Show Undo Stacks\n";
    cout << "  7.  AVL Tree (In-order / Search by Score)\n";
    cout << "  8.  Min Heap (At-Risk by Attendance)\n";
    cout << "  9.  Hash Table Lookup\n";
    cout << "  10. Graph Display\n";
    cout << "  11. Dijkstra\n";
    cout << "  12. Prim's MST\n";
    cout << "  13. Kruskal's MST\n";
    cout << "  14. Linear Search (by ID)\n";
    cout << "  15. Binary Search (by Score)\n";
    cout << "  16. Bubble Sort\n";
    cout << "  17. Selection Sort\n";
    cout << "  18. Insertion Sort\n";
    cout << "  19. Merge Sort\n";
    cout << "  0.  Exit\n";
    separator();
    cout << "  Choice: ";
}

//main
int main() {
    StudentSystem sys;

    ifstream file("excel.csv");
    if (!file) { cout << "file not found!\n"; return 1; }
    string line;
    getline(file, line); // skip header
    int loaded = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Student s = parseRow(line);
        // bulk load: silent insert into all structures
        sys.dll.append(s);
        int rot = 0;
        sys.avlRoot = avlInsert(sys.avlRoot, s, rot);
        sys.minHeap.insert(s);
        sys.hashTable.insert(s);
        sys.graph.addVertex(s, sys.dll);
        loaded++;
    }
    file.close();
    cout << "Loaded " << loaded << " students into all structures.\n";

    int choice;
    while (true) {
        printMenu();
        cin >> choice;
        separator();

        if (choice == 0) { cout << "  Exiting.\n"; break; }

        else if (choice == 1) {
            cout << "  [DOUBLY LINKED LIST]\n";
            sys.dll.display();
        }
        else if (choice == 2) {
            Student s;
            cout << "  Enter: id gender grade score attendance extra(Yes/No)\n  > ";
            string ec;
            cin >> s.stuID >> s.gender >> s.grade >> s.ovrScore >> s.attendance >> ec;
            s.exClass = (ec[0]=='Y' || ec[0]=='y');
            sys.insertStudent(s);
        }
        else if (choice == 3) {
            int id; cout << "  Enter stuID: "; cin >> id;
            sys.deleteStudent(id);
        }
        else if (choice == 4) { cout << "  [UNDO INSERT]\n"; sys.undoInsert(); }
        else if (choice == 5) { cout << "  [UNDO DELETE]\n"; sys.undoDelete(); }
        else if (choice == 6) {
            cout << "  [STACK STATE]\n";
            sys.insertStack.display(); cout << "\n";
            sys.deleteStack.display();
        }
        else if (choice == 7) {
            cout << "  [AVL TREE] a) In-order  b) Search by score\n  > ";
            char c; cin >> c;
            if (c == 'a' || c == 'A') {
                cout << "  In-order (sorted by score):\n";
                avlInorder(sys.avlRoot);
            } else {
                int sc; cout << "  Score to search: "; cin >> sc;
                int comps = 0; bool found = false;
                avlSearch(sys.avlRoot, sc, comps, found);
                cout << "  Comparisons: " << comps << "\n";
                if (!found) cout << "  Not found.\n";
            }
        }
        else if (choice == 8) {
            cout << "  [MIN HEAP] a) Display all  b) Top-k at-risk\n  > ";
            char c; cin >> c;
            if (c == 'a' || c == 'A') sys.minHeap.display();
            else {sys.minHeap.showAtRisk(); }
        }
        else if (choice == 9) {
            int id; cout << "  Enter stuID: "; cin >> id;
            int probes = 0;
            Student* s = sys.hashTable.search(id, probes);
            if (s) { cout << "  Found in " << probes << " probe(s):\n"; printStudent(*s); }
            else   cout << "  Not found. Probes: " << probes << " | Bucket: " << id%HASH_SIZE << "\n";
        }
        else if (choice == 10) { cout << "  [GRAPH]\n"; sys.graph.display(); }
        else if (choice == 11) {
            int id; cout << "  Source stuID: "; cin >> id;
            sys.graph.dijkstra(id);
        }
        else if (choice == 12) { cout << "  [PRIM'S MST]\n"; sys.graph.prims(); }
        else if (choice == 13) { cout << "  [KRUSKAL'S MST]\n"; sys.graph.kruskals(); }
        else if (choice == 14) {
            int id; cout << "  Enter stuID: "; cin >> id;
            cout << "  [LINEAR SEARCH]\n"; linearSearch(sys.dll, id);
        }
        else if (choice == 15) {
            int sc; cout << "  Enter score: "; cin >> sc;
            cout << "  [BINARY SEARCH]\n"; binarySearch(sys.dll, sc);
        }
        else if (choice == 16) { cout << "  [BUBBLE SORT]\n";    bubbleSort(sys.dll.toVector()); }
        else if (choice == 17) { cout << "  [SELECTION SORT]\n"; selectionSort(sys.dll.toVector()); }
        else if (choice == 18) { cout << "  [INSERTION SORT]\n"; insertionSort(sys.dll.toVector()); }
        else if (choice == 19) { cout << "  [MERGE SORT]\n";     mergeSort(sys.dll.toVector()); }
        else cout << "  Invalid choice.\n";
    }
    return 0;
}


// Doubly Linked List (main storage)
// Two Stacks (undo insert / undo delete)
// AVL Tree (by overall score)
// Min Heap (by attendacne &)
// Hash Table (by student id)
// Graph + Dijkstra + Prims + Kruskals
// Linear Search, Binary Search
// Bubble, Selection, Insertion, Merge Sort
 