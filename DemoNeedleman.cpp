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

void needleman_wunsch(const string& sequence1, const string& sequence2) {
    int rows = sequence1.length() + 1;
    int cols = sequence2.length() + 1;

    vector<vector<int>> matrix(rows, vector<int>(cols, 0));

    // Initialize the first row and column
    for (int i = 1; i < rows; ++i) {
        matrix[i][0] = matrix[i - 1][0] + gap_penalty;
    }
    for (int j = 1; j < cols; ++j) {
        matrix[0][j] = matrix[0][j - 1] + gap_penalty;
    }

    // Fill in the matrix
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            int match = matrix[i - 1][j - 1] + (sequence1[i - 1] == sequence2[j - 1] ? match_score : mismatch_score);
            int deleteOp = matrix[i - 1][j] + gap_penalty;
            int insertOp = matrix[i][j - 1] + gap_penalty;
            matrix[i][j] = max3(match, deleteOp, insertOp);
        }
    }

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

int main() {
    string sequence1 = "AGTACGCA";
    string sequence2 = "TATGC";
    needleman_wunsch(sequence1, sequence2);

    return 0;
}

