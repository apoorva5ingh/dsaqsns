class Solution {
public:
    const long long MOD = 1e9 + 7;
    long long C[1001][1001];

    long long solve(vector<int>& nums) {
        int n = nums.size();

        if (n <= 2)
            return 1;

        vector<int> left, right;

        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[0])
                left.push_back(nums[i]);
            else
                right.push_back(nums[i]);
        }

        long long leftWays = solve(left);
        long long rightWays = solve(right);

        long long waysToMerge = C[left.size() + right.size()][left.size()];

        return ((waysToMerge * leftWays) % MOD * rightWays) % MOD;
    }

    int numOfWays(vector<int>& nums) {
        int n = nums.size();

        // Precompute combinations
        C[0][0] = 1;

        for (int i = 1; i <= n; i++) {
            C[i][0] = C[i][i] = 1;

            for (int j = 1; j < i; j++) {
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
            }
        }

        return (solve(nums) - 1 + MOD) % MOD;
    }
};