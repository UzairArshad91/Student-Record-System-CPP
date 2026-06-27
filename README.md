# Student Record System — C++

A console-based student record management system built in C++ that stores and manages student data across **8 synchronized data structures** simultaneously. Every insert and delete operation reflects across all structures in real time.

Built as a semester project for **CSC-232 Data Structures** at COMSATS University Islamabad.

---

## Features

- **Real-time sync** — insert or delete a student and all 8 structures update instantly
- **Undo system** — undo last insert or last delete using two independent stacks
- **At-risk detection** — identifies students with attendance below 70% using a Min Heap
- **Fast lookup** — O(1) average student search via Hash Table
- **Balanced search** — AVL Tree provides O(log n) search and sorted traversal by score
- **Graph analysis** — score-based similarity graph with Dijkstra, Prim's, and Kruskal's
- **4 sorting algorithms** — Bubble, Selection, Insertion, and Merge Sort with comparison and swap counts
- **No STL containers** — all data structures implemented from scratch

---

## Data Structures Used

=> Doubly Linked List = Main storage of all student records 
=> Stack (x2) = Undo last insert / undo last delete 
=> AVL Tree = Balanced search and retrieval by overall score 
=> Min Heap = At-risk student detection by attendance percentage 
=> Hash Table = O(1) lookup by student ID (chaining, size 53) 
=> Graph (Adjacency Matrix) = Score-based similarity between students 


## Algorithms

=> Linear Search = O(n) search by student ID in DLL 
=> Binary Search = O(log n) search by score in sorted array 
=> Bubble Sort = O(n²) comparisons and swaps shown 
=> Selection Sort = O(n²) comparisons and swaps shown 
=> Insertion Sort = O(n²) comparisons and swaps shown 
=> Merge Sort = O(n log n) comparisons and swaps shown 
=> Dijkstra's = Shortest path between students by score difference 
=> Prim's MST = Minimum spanning tree of student graph 
=> Kruskal's MST = MST using sorted edges and Union-Find 


## Dataset

The system reads from `excel.csv` with the following fields:
  
   Field   |   Type   |   Description   

 student_id               |   int           |    Unique identifier 
 gender                   |   string        |    Male / Female 
 grade                    |   char          |    A, B, C, D, F 
 overall_score            |   int           | Score out of 100 
 attendance_percentage    |   float         | 0.0 – 100.0 
 extra_classes            | bool            | Yes / No 


## How to Run

```bash
g++ -std=c++17 -o student_system final.cpp
./student_system
```

Make sure `excel.csv` is in the same directory as the executable.


## Menu Options


1.  Display All Students
2.  Insert New Student
3.  Delete Student
4.  Undo Last Insert
5.  Undo Last Delete
6.  Show Undo Stacks
7.  AVL Tree (In-order / Search by Score)
8.  Min Heap (At-Risk Students)
9.  Hash Table Lookup
10. Graph Display
11. Dijkstra
12. Prim's MST
13. Kruskal's MST
14. Linear Search
15. Binary Search
16. Bubble Sort
17. Selection Sort
18. Insertion Sort
19. Merge Sort
0.  Exit



## Project Info

- **Course:** CSC-232 Data Structures
- **University:** COMSATS University Islamabad
- **Semester:** Spring 2025 — 3rd Semester
- **Language:** C++ (no STL containers, no `<algorithm>`, no `<queue>`, no `<iomanip>`)
