#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <queue>
#include <stdexcept>
#include <memory>

/// @class   Graph
///
/// @brief   A graph data structure implementation for Dijkstra's algorithm.
///          This class represents a directed weighted graph with a variable number of vertices.
///          It provides methods to add edges and vertices, calculate the shortest path using Dijkstra's algorithm,
///          and retrieve the adjacency list and the shortest path between two vertices.
///
/// @date    24/07/2023
namespace DijakstraAlgo {

    class Graph {
    private:
        int m_numOfVertices;
        std::unique_ptr<std::list<std::pair<int, double>>[]> m_adjacencyList;

    public:

        /// @brief Default constructor for the Graph class.
        ///
        /// Creates an empty graph with zero vertices and no edges.
        Graph();

        /// @brief Destructor for the Graph class.
        ///
        /// Frees the memory allocated for the adjacency list when the object is destroyed.
        ~Graph() = default;

        /// @brief Adds a directed weighted edge to the graph between two vertices u and v with weight w.
        ///
        /// @param u The source vertex.
        /// @param v The destination vertex.
        /// @param w The weight of the edge between u and v.
        void addEdge(int u, int v, double w);

        /// @brief Adds a new vertex to the graph.
        ///
        /// This function increases the number of vertices in the graph and expands the adjacency list to accommodate the new vertex.
        void addVertex();

        /// @brief Applies Dijkstra's algorithm to find the shortest path from a source vertex to all other vertices.
        ///
        /// @param s The source vertex from which to find the shortest paths.
        /// @return A vector containing the shortest distances from the source vertex to all other vertices.
        std::vector<double> shortestPathAlgorithm(int s) const;

        /// @brief Finds the shortest path between two vertices using Dijkstra's algorithm.
        ///
        /// @param start The starting vertex of the path.
        /// @param end The ending vertex of the path.
        /// @return A vector of integers representing the vertices in the shortest path from start to end.
        std::vector<int> getShortestPath(int start, int end) const;
    };

}



#endif // GRAPH_H
