#include <bits/stdc++.h>
using namespace std;

void dfs(int node, int parent, int &timer, vector<int> &discovery, vector<int> &low,
         vector<vector<int>> &result, unordered_map<int, list<int>> &adj, unordered_map<int, bool> &vis) {

    vis[node] = true;
    discovery[node] = low[node] = timer++;

    for(auto nbr: adj[node]){
        if(nbr == parent)
            continue;

        if(!vis[nbr]){
            // Recursively call dfs on the unvisited neighbor
            dfs(nbr, node, timer, discovery, low, result, adj, vis);
            low[node] = min(low[node], low[nbr]);

            // Check bridge condition
            if(low[nbr] > discovery[node]){
                vector<int> ans;
                ans.push_back(node);
                ans.push_back(nbr);
                result.push_back(ans);
            }
        }
        else{
            // Back edge
            low[node] = min(low[node], discovery[nbr]);
        }
    }

}

int main() {

    // Create an adjacency list to represent the graph
    unordered_map<int, list<int>> adj;

    int nodes;
    std::cout << "Enter the number of nodes: ";
    cin >> nodes;

    int edges;
    std::cout << "Enter the number of edges: ";
    cin >> edges;

    int direction = 0;
    for(int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;

        // Create an undirected graph by adding edges in both directions
        adj[u].push_back(v);
        if(direction == 0){
            adj[v].push_back(u);
        }
    }

    int timer = 0;
    vector<int> discovery(nodes+1); // Time when that node was visited
    vector<int> low(nodes+1); // Earliest possible time to visit that node

    int parent = -1;

    unordered_map<int, bool> vis;

    // Initialize discovery and low arrays
    for(int i = 1; i <= nodes; i++){
        discovery[i] = -1;
        low[i] = -1;
    }

    vector<vector<int>> result; // Store the bridges

    // Perform DFS to find bridges
    for(int i = 1; i <= nodes; i++){
        if(!vis[i]){
            dfs(i, parent, timer, discovery, low, result, adj, vis);
        }
    }

    // Print the bridges
    for(int i = 0; i < result.size(); i++){
        std::cout << "Bridges are present in between: ";
        for(int j = 0; j < result[i].size(); j++){
            std::cout << result[i][j] << " ";
        }
        std::cout << endl;
    }

    return 0;
}
