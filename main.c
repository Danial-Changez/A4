#include "graph.h"

int main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    Graph *graph = readGraph(argv[1]);
    // Check if graph can be read
    if (!graph)
    {
        fprintf(stderr, "Error: Unable to read graph from file %s\n", argv[1]);
        return 1;
    }

    // Generate the adjacency list from the adjacency matrix
    createAdjacencyList(graph);

    int choice;
    int startVertex = 1; // Default starting vertex (1-based indexing)

    do
    {
        // Display the menu options
        prompt();

        // Get the user's choice
        printf("Enter a Choice: ");
        scanf("%d", &choice);
        printf("\n");

        // Perform an action based on the user's choice
        switch (choice)
        {
        case 1:
            // Display the adjacency list
            displayAdjacencyList(graph);
            break;

        case 2:
            // Perform Breadth-First Search (BFS)
            bfs(graph, startVertex);
            break;

        case 3:
            // Perform Depth-First Search (DFS)
            dfs(graph, startVertex);
            break;

        case 4:
            // Find the shortest paths from (startVertex - 1) using Dijkstra's algorithm and 0-based indexing
            dijkstra(graph, startVertex - 1);
            break;

        case 5:
            // Exit the program, freeing any allocated resources
            printf("Exiting...\n");
            freeGraph(graph);
            return 0;

        default:
            // Handle invalid menu options
            printf("Invalid choice, please select a valid option\n");
            break;
        }
    } while (1);

    return 0;
}
