#include "graph.h"

/* function will display the primary user interface
    This is already done for you */
void prompt(void)
{
    printf("\nMenu:\n");
    printf("1. Display Adjacency List\n");
    printf("2. Perform Breadth-First Search (BFS)\n");
    printf("3. Perform Depth-First Search (DFS)\n");
    printf("4. Find Shortest Path using Dijkstra's Algorithm\n");
    printf("5. Exit\n");
}

/**
 * Reads a graph from a file and constructs the graph structure.
 * @param filename The name of the file containing the adjacency matrix.
 * @return Pointer to the created Graph structure, or NULL if an error occurs.
 */
Graph *readGraph(const char *filename)
{
    int j;
    char buffer[1024];
    FILE *file = fopen(filename, "r");

    // Check if the file was successfully opened
    if (!file)
    {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return NULL;
    }

    // Allocate memory for the Graph structure
    Graph *graph = malloc(sizeof(Graph));
    if (!graph)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // Initialize adjacency list pointers to NULL and count lines
    graph->numVertices = 0;
    while (fgets(buffer, sizeof(buffer), file))
    {
        if (graph->numVertices >= MAX_VERTICES)
        {
            fprintf(stderr, "Error: Number of vertices exceeds MAX_VERTICES.\n");
            free(graph);
            fclose(file);
            return NULL;
        }

        char *token = strtok(buffer, " ");
        for (j = 0; token != NULL; j++)
        {
            if (j >= MAX_VERTICES)
            {
                fprintf(stderr, "Error: Adjacency matrix row exceeds MAX_VERTICES.\n");
                free(graph);
                fclose(file);
                return NULL;
            }
            graph->adjMatrix[graph->numVertices][j] = atoi(token);
            token = strtok(NULL, " ");
        }

        graph->adjList[graph->numVertices] = NULL; // Initialize adjacency list
        graph->numVertices++;
    }

    fclose(file);
    return graph;
}

/**
 * Creates a new node for the adjacency list.
 * @param vertex The vertex number that this node will represent.
 * @return Pointer to the newly created Node structure.
 */
Node *createNode(int vertex)
{
    Node *newNode = malloc(sizeof(Node));
    if (!newNode)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void createAdjacencyList(Graph *graph)
{
    int i, j;
    for (i = 0; i < graph->numVertices; i++)
    {
        for (j = 0; j < graph->numVertices; j++)
        {
            if (graph->adjMatrix[i][j] != 0) // Check for an edge
            {
                Node *newNode = createNode(j + 1);
                if (graph->adjList[i + 1] == NULL)
                    graph->adjList[i + 1] = newNode; // If the list is empty, make it the head
                else
                {
                    Node *temp = graph->adjList[i + 1];
                    while (temp->next != NULL) // Traverse to the end of the list
                        temp = temp->next;

                    temp->next = newNode;
                }
            }
        }
    }
}

/**
 * Displays the adjacency list of the graph with edge weights.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph)
{
    printf("Adjacency List:\n");
    for (int i = 1; i <= graph->numVertices; i++)
    {
        printf("Vertex %d: ", i);

        Node *temp = graph->adjList[i]; // Access the adjacency list for the current vertex
        while (temp)
        {
            printf("-> %d (%d) ", temp->vertex, graph->adjMatrix[i - 1][temp->vertex - 1]); // Adjust indices
            temp = temp->next;
        }

        printf("NULL\n"); // Add NULL to the end of each adjacency list
    }
}

/**
 * Performs Breadth-First Search (BFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which BFS starts (0-based index).
 */
void bfs(Graph *graph, int startVertex)
{
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES], front = 0, back = 0;

    // Enqueue the start vertex and mark it as visited
    queue[back++] = startVertex;
    visited[startVertex] = true;

    printf("Final BFS Order %d:\n", startVertex);
    while (front < back)
    {
        // Dequeue the current vertex
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Traverse all adjacent vertices
        Node *temp = graph->adjList[currentVertex];
        while (temp)
        {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex])
            {
                queue[back++] = adjVertex; // Enqueue the adjacent vertex
                visited[adjVertex] = true; // Mark it as visited
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

/**
 * Performs Depth-First Search (DFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which DFS starts (0-based index).
 */
void dfs(Graph *graph, int startVertex)
{
    bool visited[MAX_VERTICES] = {false};
    dfsRecursion(graph, startVertex, visited);
    printf("\n");
}

/**
 * Performs Depth-First Search (DFS) recursively.
 * @param graph Pointer to the Graph structure.
 * @param vertex The current vertex.
 * @param visited Boolean array to track visited vertices.
 */
void dfsRecursion(Graph *graph, int vertex, bool visited[])
{
    visited[vertex] = true; // Mark the current vertex as visited
    printf("%d ", vertex);  // Print the current vertex

    Node *temp = graph->adjList[vertex];
    while (temp)
    {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex])
            dfsRecursion(graph, adjVertex, visited); // Recur for unvisited vertex

        temp = temp->next;
    }
}

/**
 * Finds the shortest path from the start vertex to all other vertices using Dijkstra's algorithm.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which to start the algorithm (0-based index).
 */
void dijkstra(Graph *graph, int startVertex)
{
    int distance[MAX_VERTICES];
    bool visited[MAX_VERTICES] = {false};

    // Initialize distances to infinity and set all vertices as unvisited
    for (int i = 0; i < graph->numVertices; i++)
        distance[i] = INT_MAX;
    distance[startVertex] = 0;

    // Process each vertex
    for (int i = 0; i < graph->numVertices - 1; i++)
    {
        // Find the unvisited vertex with the smallest distance
        int min = INT_MAX, currentVertex = -1;
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (!visited[j] && distance[j] < min)
            {
                min = distance[j];
                currentVertex = j;
            }
        }

        // Mark the chosen vertex as visited
        visited[currentVertex] = true;

        // Update distances to neighboring vertices
        Node *temp = graph->adjList[currentVertex + 1];
        while (temp)
        {
            int adjVertex = temp->vertex - 1;
            if (!visited[adjVertex] && graph->adjMatrix[currentVertex][adjVertex] != 0)
            {
                int new = distance[currentVertex] + graph->adjMatrix[currentVertex][adjVertex];
                if (new < distance[adjVertex])
                    distance[adjVertex] = new;
            }
            temp = temp->next;
        }
    }

    for (int i = 0; i < graph->numVertices; i++)
        printf("Shortest distance from vertex %d to vertex %d: %d\n", startVertex, i + 1, distance[i]);
}

/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure to be freed.
 */
void freeGraph(Graph *graph)
{
    int i;
    for (i = 1; i <= graph->numVertices; i++)
    {
        Node *current = graph->adjList[i];
        while (current)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph);
}
