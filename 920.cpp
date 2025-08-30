#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define MAX_NODES 501

// Using global or class members for Tarjan's algorithm state
std::vector<int> adj[MAX_NODES]; // Adjacency list
int dfn[MAX_NODES], low[MAX_NODES];
bool is_ap[MAX_NODES];                       // To mark articulation points
std::vector<std::pair<int, int>> edge_stack; // Stack for edges during BCC finding
std::vector<std::set<int>> bcc_list;         // Stores nodes of each BCC
int timer;
int max_node_id;

void find_aps_and_bccs_tarjan(int u, int p_node)
{
    dfn[u] = low[u] = ++timer;
    int children_for_root_ap_check = 0;

    for (int v : adj[u])
    {
        if (v == p_node)
            continue;

        if (dfn[v] != 0)
        { // v is already visited
            if (dfn[v] < dfn[u])
            { // (u,v) is a back-edge to an ancestor
                edge_stack.push_back({u, v});
                low[u] = std::min(low[u], dfn[v]);
            }
        }
        else
        { // v is not visited
            edge_stack.push_back({u, v});
            children_for_root_ap_check++;
            find_aps_and_bccs_tarjan(v, u);
            low[u] = std::min(low[u], low[v]);

            // Articulation Point check
            if ((p_node != 0 && low[v] >= dfn[u]) || (p_node == 0 && children_for_root_ap_check > 1))
            {
                is_ap[u] = true;
            }

            // BCC found
            if (low[v] >= dfn[u])
            {
                std::set<int> current_bcc_nodes;
                std::pair<int, int> popped_edge;
                do
                {
                    popped_edge = edge_stack.back();
                    edge_stack.pop_back();
                    current_bcc_nodes.insert(popped_edge.first);
                    current_bcc_nodes.insert(popped_edge.second);
                } while (!((popped_edge.first == u && popped_edge.second == v) ||
                           (popped_edge.first == v && popped_edge.second == u)));
                if (!current_bcc_nodes.empty())
                {
                    bcc_list.push_back(current_bcc_nodes);
                }
            }
        }
    }
}

void solve(int case_num)
{
    // 0. Reset global states for the current test case
    for (int i = 0; i <= max_node_id; ++i)
    { // Clear up to previous max_node_id
        adj[i].clear();
        dfn[i] = 0;
        low[i] = 0;
        is_ap[i] = false;
    }
    edge_stack.clear();
    bcc_list.clear();
    timer = 0;
    max_node_id = 0;

    int N_edges;
    std::cin >> N_edges;
    if (N_edges == 0)
        exit(0); // Terminator for all test cases

    std::set<int> distinct_nodes_in_case;
    for (int i = 0; i < N_edges; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        max_node_id = std::max({max_node_id, u, v});
        distinct_nodes_in_case.insert(u);
        distinct_nodes_in_case.insert(v);
    }

    // 1. Run Tarjan's algorithm
    // Graph is connected, so one call from an existing node is sufficient.
    // Iterate 1 to max_node_id; if dfn[i]==0 and node i exists (adj[i] not empty), call Tarjan.
    for (int i = 1; i <= max_node_id; ++i)
    {
        if (dfn[i] == 0 && !adj[i].empty())
        {                                   // Check adj[i].empty() for robustness, though problem implies 1..n are used
            find_aps_and_bccs_tarjan(i, 0); // 0 as dummy parent for root
        }
    }
    // If after all DFS calls, edge_stack is not empty, it means the remaining component (often the whole graph if biconnected) is a single BCC.
    if (!edge_stack.empty())
    {
        std::set<int> last_bcc_nodes;
        while (!edge_stack.empty())
        {
            std::pair<int, int> popped_edge = edge_stack.back();
            edge_stack.pop_back();
            last_bcc_nodes.insert(popped_edge.first);
            last_bcc_nodes.insert(popped_edge.second);
        }
        if (!last_bcc_nodes.empty())
        {
            bcc_list.push_back(last_bcc_nodes);
        }
    }

    // 2. Count total APs
    int num_total_aps = 0;
    for (int i = 1; i <= max_node_id; ++i)
    {
        if (is_ap[i])
        {
            num_total_aps++;
        }
    }

    unsigned long long final_min_exits;
    unsigned long long final_num_ways;

    // 3. Apply decision logic
    if (num_total_aps == 0)
    {
        final_min_exits = 2;
        // Number of nodes for Nchoose2. Problem implies nodes 1 to max_node_id are part of the graph.
        // Using max_node_id for node count.
        if (max_node_id < 2)
        {                       // Should not happen given N_edges >= 1
            final_num_ways = 0; // Or handle as error/specific definition
        }
        else
        {
            final_num_ways = (unsigned long long)max_node_id * (max_node_id - 1) / 2;
        }
        // Special case: if graph is just two nodes and one edge (N=1), max_node_id=2. Result is 2 exits, 1 way.
        // Nchoose2 for N=2 is 2*1/2 = 1. This is correct.
    }
    else
    { // num_total_aps > 0
        unsigned long long calculated_min_exits = 0;
        unsigned long long calculated_num_ways = 1;

        if (bcc_list.empty() && N_edges > 0)
        {
            // This scenario (APs exist but no BCCs found) should ideally not happen if Tarjan is correct.
            // A graph with APs must have at least two BCCs.
            // If it occurs, might indicate an issue or a very specific graph type (e.g. star graph, where center is AP, each edge is BCC).
            // For a single edge (N_edges=1), num_total_aps is 0, handled above.
        }

        for (const auto &bcc_nodes_set : bcc_list)
        {
            int aps_in_this_bcc = 0;
            for (int node : bcc_nodes_set)
            {
                if (is_ap[node])
                {
                    aps_in_this_bcc++;
                }
            }

            if (aps_in_this_bcc == 1)
            { // Leaf block
                calculated_min_exits++;
                // A BCC with only 1 AP must have at least one other node (non-AP) to be a leaf block.
                // So bcc_nodes_set.size() >= 2. Thus (bcc_nodes_set.size() - 1) >= 1.
                if (bcc_nodes_set.size() > 1)
                {
                    calculated_num_ways *= (bcc_nodes_set.size() - 1);
                }
                else
                {
                    // This implies BCC of size 1. A single node BCC cannot have 1 AP and be a leaf block.
                    // It might mean num_ways becomes 0 if not careful, but size > 1 check handles it.
                }
            }
        }

        if (calculated_min_exits == 0)
        { // APs exist, but no leaf blocks (e.g., cycle of BCCs)
            final_min_exits = 2;
            final_num_ways = (unsigned long long)max_node_id * (max_node_id - 1) / 2;
        }
        else
        {
            final_min_exits = calculated_min_exits;
            final_num_ways = calculated_num_ways;
        }
    }

    // Smallest graph: N_edges=1, say 1-2. max_node_id=2. No APs.
    // final_min_exits=2, final_num_ways = 2*(1)/2 = 1. This seems correct.

    std::cout << "Case " << case_num << ": " << final_min_exits << " " << final_num_ways << std::endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int case_num = 1;
    // The solve function itself handles the N=0 termination.
    // An alternative is to peek N in main, but problem structure allows N inside solve.
    while (true)
    {
        solve(case_num++);
    }
    return 0;
}