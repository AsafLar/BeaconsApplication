#include "Graph.hpp"


DijakstraAlgo::Graph::Graph() : m_numOfVertices(0) , m_adjacencyList(nullptr)
{

}

void
DijakstraAlgo::Graph::addEdge(int u, int v, double w)
{
    // Check if vertices u and v are within the current range
    if (u >= m_numOfVertices || v >= m_numOfVertices)
    {
        throw std::out_of_range("Invalid vertex index - Out Of Range");
    }

    m_adjacencyList[u].push_back(std::make_pair(v, w));
    m_adjacencyList[v].push_back(std::make_pair(u, w));
}

void
DijakstraAlgo::Graph::addVertex()
{
    m_numOfVertices += 1;
    m_adjacencyList = std::make_unique<std::list<std::pair<int, double>>[]>(m_numOfVertices);
}

std::vector<double>
DijakstraAlgo::Graph::shortestPathAlgorithm(int src) const
{
    std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, std::greater<std::pair<int, double>> > pq;
    std::vector<double> dist(m_numOfVertices, std::numeric_limits<double>::infinity());

    pq.push(std::make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty())
    {
        int u = pq.top().first;
        pq.pop();

        std::list<std::pair<int, double>>::iterator it;
        for (it = m_adjacencyList[u].begin(); it != m_adjacencyList[u].end(); ++it)
        {
            int v = (*it).first;
            double weight = (*it).second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(v, dist[v]));
            }
        }
    }

    return dist;
}

std::vector<int>
DijakstraAlgo::Graph::getShortestPath(int start, int end) const
{
    std::vector<double> shortestPathAlgoReuslt = shortestPathAlgorithm(start);
    std::vector<int> resultPath;

    if (shortestPathAlgoReuslt[end] != std::numeric_limits<double>::infinity())
    {
        int current = end;
        resultPath.push_back(current);

        while (current != start) {
            for (const auto& edge : m_adjacencyList[current])
            {
                int prev = edge.first;
                double weight = edge.second;

                if (shortestPathAlgoReuslt[prev] + weight == shortestPathAlgoReuslt[current]) {
                    resultPath.push_back(prev);
                    current = prev;
                    break;
                }
            }
        }

        reverse(resultPath.begin(), resultPath.end());
    }

    return resultPath;
}
