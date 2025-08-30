#include <stdio.h>
#include <string.h> // For memset
#include <stdlib.h> 
#include <limits.h> // For INT_MAX, LLONG_MAX

#define N_MAX 505 // Max villages + buffer for 1-based indexing if needed, here 0-based
#define M_MAX 505 // Max wells

// Global arrays for convenience in recursive function
int adj_dist[N_MAX -1];
int pos[N_MAX];
long long pos_prefix_sum[N_MAX + 1]; // pos_prefix_sum[k] = sum of pos[0]..pos[k-1]
int cost_1_well[N_MAX][N_MAX];       // cost_1_well[p][q] = min cost for villages p..q with one well

// Memoization table
// memo[idx][k_wells] = min cost to supply villages idx..n-1 using k_wells
int memo[N_MAX][M_MAX + 1]; 
int n_villages_global; // To easily access n in the recursive function

// Function prototype for the recursive solver
int dp_solve(int current_start_idx, int wells_to_place);

int main() {
    int m_wells_total;
    scanf("%d %d", &n_villages_global, &m_wells_total);

    for (int i = 0; i < n_villages_global - 1; ++i) {
        scanf("%d", &adj_dist[i]);
    }

    pos[0] = 0;
    for (int i = 1; i < n_villages_global; ++i) {
        pos[i] = pos[i - 1] + adj_dist[i - 1];
    }

    pos_prefix_sum[0] = 0;
    for (int i = 0; i < n_villages_global; ++i) {
        pos_prefix_sum[i + 1] = pos_prefix_sum[i] + pos[i];
    }

    for (int p = 0; p < n_villages_global; ++p) {
        for (int q = p; q < n_villages_global; ++q) {
            long long min_total_dist_for_segment = LLONG_MAX;
            for (int well_loc_idx = p; well_loc_idx <= q; ++well_loc_idx) {
                long long cost_left_part = (long long)(well_loc_idx - p + 1) * pos[well_loc_idx] -
                                           (pos_prefix_sum[well_loc_idx + 1] - pos_prefix_sum[p]);
                long long cost_right_part = (pos_prefix_sum[q + 1] - pos_prefix_sum[well_loc_idx + 1]) -
                                            (long long)(q - well_loc_idx) * pos[well_loc_idx];
                long long current_sum_dist = cost_left_part + cost_right_part;
                if (current_sum_dist < min_total_dist_for_segment) {
                    min_total_dist_for_segment = current_sum_dist;
                }
            }
            cost_1_well[p][q] = (int)min_total_dist_for_segment;
        }
    }

    memset(memo, -1, sizeof(memo)); // Initialize memoization table with -1

    int result = dp_solve(0, m_wells_total);
    printf("%d\n", result);

    return 0;
}

// current_start_idx: current village index to start covering (0 to n_villages_global-1)
// wells_to_place: number of wells remaining to be placed
int dp_solve(int current_start_idx, int wells_to_place) {
    // Base Case 1: No wells left to place
    if (wells_to_place == 0) {
        // If all villages are covered (current_start_idx == n_villages_global), cost is 0.
        // Else, villages remain but no wells, impossible (cost is INT_MAX).
        return (current_start_idx == n_villages_global) ? 0 : INT_MAX;
    }

    // Base Case 2: All villages covered (current_start_idx == n_villages_global)
    // If wells_to_place > 0, it's fine, we have wells to spare. Cost is 0 for covering no more villages.
    if (current_start_idx == n_villages_global) {
        return 0;
    }
    
    // Optimization: If number of wells >= number of remaining villages,
    // we can place one well per village, so the cost for this subproblem is 0.
    if (wells_to_place >= (n_villages_global - current_start_idx)) {
        return 0;
    }

    // Check memoization table
    if (memo[current_start_idx][wells_to_place] != -1) {
        return memo[current_start_idx][wells_to_place];
    }

    int min_cost_for_this_state = INT_MAX;

    // Iterate over 'j', the end village index for the segment covered by the *current* well.
    // This well covers villages from 'current_start_idx' to 'j'.
    // The loop for 'j' must ensure that there are enough villages left for the remaining wells.
    // Remaining villages: n_villages_global - (j + 1)
    // Remaining wells: wells_to_place - 1
    // We need (n_villages_global - (j + 1)) >= (wells_to_place - 1) if wells_to_place -1 > 0
    // (each of the remaining wells should cover at least one village ideally, or this implies
    //  that we'd have more wells than villages in the recursive call, which is handled by optimization)
    // This simplifies to: j <= n_villages_global - wells_to_place.
    for (int j = current_start_idx; j <= n_villages_global - wells_to_place; ++j) {
        int cost_for_current_segment = cost_1_well[current_start_idx][j];
        
        int cost_for_remaining_part = dp_solve(j + 1, wells_to_place - 1);

        if (cost_for_remaining_part != INT_MAX) { // If the subproblem is solvable
            long long current_total_cost = (long long)cost_for_current_segment + cost_for_remaining_part;
            if (current_total_cost < min_cost_for_this_state) {
                min_cost_for_this_state = (int)current_total_cost;
            }
        }
    }

    // Store and return the result
    return memo[current_start_idx][wells_to_place] = min_cost_for_this_state;
}
