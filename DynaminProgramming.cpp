#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

int soccer_dyn_prog(const vector<vector<char>>& F) {
    int r = F.size();
    int c = F[0].size();
    
    // Corner case: if the initial cell is impassable
    if (F[0][0] == 'X') {
        return 0;
    }
    
    // DP matrix A to store the number of ways to reach each cell
    vector<vector<int>> A(r, vector<int>(c, 0));
    
    // Base case: Start at (0,0)
    A[0][0] = 1;
    
    // Fill the DP matrix
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            // Skip the starting cell, as we have already set A[0][0] = 1
            if (i == 0 && j == 0) continue;
            
            // If the current cell is blocked, there is no way to reach it
            if (F[i][j] == 'X') {
                A[i][j] = 0;
                continue;
            }

            int above = 0, left = 0;

            // Check if the cell above (i-1, j) is reachable
            if (i > 0 && F[i-1][j] != 'X') {
                above = A[i-1][j];
            }

            // Check if the cell to the left (i, j-1) is reachable
            if (j > 0 && F[i][j-1] != 'X') {
                left = A[i][j-1];
            }

            // The number of ways to reach A[i][j] is the sum of ways from above and left
            A[i][j] = above + left;
        }
    }

    // The result is in the bottom-right corner of the matrix
    return A[r-1][c-1];
}

int main() {
    // Define a starting point for empirical analysis
    vector<int> grid_sizes = {5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000};  // Example sizes (n)
    
    // Loop through each grid size
    for (int n : grid_sizes) {
        // Dynamically create a grid of size n x n
        vector<vector<char>> F(n, vector<char>(n, '.'));  // Initialize grid with all open cells

        // Optionally, add some blocked cells to make it more interesting
        // For simplicity, we'll keep it simple here, but you could randomly block cells
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || j == 0 || i == n-1 || j == n-1) {
                    F[i][j] = '.';  // Open edge cells
                } else {
                    F[i][j] = rand() % 2 == 0 ? '.' : 'X';  // Randomly block cells inside
                }
            }
        }

        // Start timing the execution
        auto start = high_resolution_clock::now();

        // Call the dynamic programming function
        int result = soccer_dyn_prog(F);

        // End timing the execution
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        // Output the result and the time taken
        cout << "Grid size: " << n << "x" << n << " - Number of valid paths: " << result << endl;
        cout << "Time taken: " << duration.count() << " microseconds" << endl;
    }

    return 0;
}

