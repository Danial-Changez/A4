# CIS2520-F24-A4

## Student Information 
Name: Danial Changez  

Student Number: 1232341  

## Assignment Overview
This assignment implements a program to represent and manipulate graphs using adjacency matrices and lists. The program provides functionality to:

1. **Display** the adjacency list of a graph.
2. Perform **Breadth-First Search (BFS)** starting from a given vertex.
3. Perform **Depth-First Search (DFS)** starting from a given vertex.
4. Find the shortest path from a starting vertex to all other vertices using **Dijkstra's algorithm**.
5. **Exiting** upon request.

The primary purpose of the program is to practice and apply graph representations and traversal techniques. It is designed to read an adjacency matrix from a file, convert it into an adjacency list, and allow users to interact with the graph through a menu-based interface.

## Resources
The following resources were used to complete this assignment:
- Class notes and lectures on graph theory and algorithms.
- [GeeksforGeeks - Graph and Its Representations](https://www.geeksforgeeks.org/graph-and-its-representations/)

## Implementation and Testing
The assignment is complete and implements all the required functionality, including:

- Reading a graph from a file and constructing its adjacency matrix and list.
- Converting the adjacency matrix into an adjacency list.
- Displaying the adjacency list.
- Performing BFS and DFS traversals starting from a given vertex.
- Implementing Dijkstra's algorithm for finding the shortest paths from a starting vertex.
- Exiting upon request.

All parts of the assignment have been tested and validated against sample input files on school servers, and the outputs match the expected results as per the assignment instructions. 

## Valgrind Testing
- After testing with Valgrind, no memory leaks were detected.
    - Command:
    ```
    valgrind --leak-check=full --track-origins=yes ./a4
    ```

    - Output confirmed all heap memory was freed:
    ```
    All heap blocks were freed -- no leaks are possible
    ```