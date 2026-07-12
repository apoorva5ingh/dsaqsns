class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> sorted = arr;
        sort(sorted.begin(), sorted.end());

        unordered_map<int, int> rank;
        int currRank = 1;

        for (int num : sorted) {
            if (rank.find(num) == rank.end()) {
                rank[num] = currRank++;
            }
        }

        for (int &num : arr) {
            num = rank[num];
        }

        return arr;
    }
};