#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

typedef std::pair<unsigned, unsigned> edge;

std::vector<unsigned> dijkstra(const std::vector<std::vector<edge>>& graph, const unsigned start, std::vector<unsigned>* prev = nullptr) {
    std::vector<unsigned> dist(graph.size(), INT_MAX);
    dist[start] = 0;

    if (prev != nullptr) {
        *prev = std::vector<unsigned>(graph.size(), INT_MAX);
    }

    std::priority_queue<edge, std::vector<edge>, std::greater<edge>> pq;
    pq.push({ dist[start], start });

    while (!pq.empty()) {
        unsigned v = pq.top().second;
        unsigned d = pq.top().first;
        pq.pop();

        if (d > dist[v]) {
            continue;
        }

        for (const edge& neighbour : graph[v]) {
            d = dist[v] + neighbour.second;
            
            if (d < dist[neighbour.first]) {
                dist[neighbour.first] = d;
                pq.push({ d, neighbour.first });

                if (prev != nullptr) {
                    (*prev)[neighbour.first] = v;
                }
            }
        }
    }

    return dist;
}

int main() {
    std::vector<std::vector<edge>> graph(5);

    graph[0].push_back({1, 10});
    graph[0].push_back({2, 3});

    graph[1].push_back({2, 1});
    graph[1].push_back({3, 2});

    graph[2].push_back({1, 4});
    graph[2].push_back({3, 8});
    graph[2].push_back({4, 2});

    graph[3].push_back({4, 7});

    graph[4].push_back({3, 9});

    for (unsigned i = 0; i < graph.size(); i++) {
        std::cout << "Node " << i << ": ";

        for (edge& edge : graph[i]) {
            std::cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        
        std::cout << "\n";
    }

    std::vector<unsigned> prev;
    std::vector<unsigned> dist = dijkstra(graph, 0, &prev);

    for (unsigned i = 0; i < dist.size(); ++i) {
        std::cout << i << ": " << dist[i] << ", reversed path: ";
        unsigned v = i;

        while (v != INT_MAX) {
            std::cout << v << " ";
            v = prev[v];
        }

        std::cout << '\n';
    }

    return 0;
}