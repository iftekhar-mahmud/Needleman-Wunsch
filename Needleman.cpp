//Coded by Iftekhar Mahmud
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int match_score = 1;
int mismatch_score = -1;
int gap_penalty = -2;

int max3(int a, int b, int c) {
    return max(a, max(b, c));
}
//max3 is a helper function that returns the maximum of three integers a, b, and c using the max function from the <algorithm> library.
void needleman_wunsch(const string& sequence1, const string& sequence2) {
    int rows = sequence1.length() + 1;
    int cols = sequence2.length() + 1;

    vector<vector<int>> matrix(rows, vector<int>(cols, 0));
//needleman_wunsch is the main function implementing the Needleman-Wunsch algorithm. It takes two input sequences as strings. The function initializes the number of rows and columns for the matrix based on the lengths of the sequences.
    //A 2D vector named matrix is created with dimensions (rows, cols) and initialized with zeros. This matrix will store the scores for each alignment position.
    // Initialize the first row and column
    for (int i = 1; i < rows; ++i) {
        matrix[i][0] = matrix[i - 1][0] + gap_penalty;
    }
    for (int j = 1; j < cols; ++j) {
        matrix[0][j] = matrix[0][j - 1] + gap_penalty;
    }
   //These loops initialize the first row and first column of the matrix using gap penalties. The scores are calculated based on the scores from adjacent cells in the matrix.
    
    // Fill in the matrix
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            int match = matrix[i - 1][j - 1] + (sequence1[i - 1] == sequence2[j - 1] ? match_score : mismatch_score);
            int deleteOp = matrix[i - 1][j] + gap_penalty;
            int insertOp = matrix[i][j - 1] + gap_penalty;
            matrix[i][j] = max3(match, deleteOp, insertOp);
        }
    }
  //These nested loops fill in the rest of the matrix using the Needleman-Wunsch dynamic programming approach. For each cell (i, j), three possible operations are considered: match/mismatch, delete (gap in sequence1), and insert (gap in sequence2).
  //The match score is calculated based on the previous diagonal cell score, either adding match_score for a match or mismatch_score for a mismatch.
  //The deleteOp score is based on the score above the current cell, adding the gap penalty.
  //The insertOp score is based on the score left of the current cell, adding the gap penalty.
  //The maximum of these three scores is taken using the max3 function and stored in the current cell (i, j).
    
    // Backtrack to find the optimal alignment
    string alignment1 = "";
    string alignment2 = "";
    int i = rows - 1;
    int j = cols - 1;
    while (i > 0 && j > 0) {
        if (matrix[i][j] == matrix[i - 1][j - 1] + (sequence1[i - 1] == sequence2[j - 1] ? match_score : mismatch_score)) {
            alignment1 = sequence1[i - 1] + alignment1;
            alignment2 = sequence2[j - 1] + alignment2;
            --i;
            --j;
        } else if (matrix[i][j] == matrix[i - 1][j] + gap_penalty) {
            alignment1 = sequence1[i - 1] + alignment1;
            alignment2 = "-" + alignment2;
            --i;
        } else {
            alignment1 = "-" + alignment1;
            alignment2 = sequence2[j - 1] + alignment2;
            --j;
        }
    }

//This loop performs the traceback step to reconstruct the optimal alignment by backtracking through the matrix from the bottom-right corner (rows-1, cols-1) to the top-left corner (0, 0).
//Depending on the maximum score in the current cell, the algorithm determines whether the optimal path involved a match/mismatch, a gap in sequence1, or a gap in sequence2. The corresponding characters are added to alignment1 and alignment2.
    
    while (i > 0) {
        alignment1 = sequence1[i - 1] + alignment1;
        alignment2 = "-" + alignment2;
        --i;
    }
    while (j > 0) {
        alignment1 = "-" + alignment1;
        alignment2 = sequence2[j - 1] + alignment2;
        --j;
    }

    cout << "Alignment 1: " << alignment1 << endl;
    cout << "Alignment 2: " << alignment2 << endl;
}
//After the traceback, any remaining characters in either sequence are added to the alignments, representing gaps.
//The final alignments are printed to the console.
int main() {
    string sequence1 = "AGTACGCA";
    string sequence2 = "TATGC";
    needleman_wunsch(sequence1, sequence2);

    return 0;
}
//The main function initializes the input sequences and calls the needleman_wunsch function with them.
//It returns 0 to indicate successful execution.
