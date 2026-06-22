class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<string> seen;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {

                if (board[i][j] == '.')
                    continue;

                string num(1, board[i][j]);

                string row = num + "row" + to_string(i);
                string col = num + "col" + to_string(j);
                string box = num + "box" + to_string(i / 3) + to_string(j / 3);

                if (seen.count(row) ||
                    seen.count(col) ||
                    seen.count(box))
                    return false;

                seen.insert(row);
                seen.insert(col);
                seen.insert(box);
            }
        }

        return true;
    }
};