class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k);
        vector<long long> dp(k);

        for (int num : nums) {
            int x = num % k;
            vector<long long> next(k);

            next[x]++;

            for (int r = 0; r < k; r++) {
                int nr = (r * x) % k;
                next[nr] += dp[r];
            }

            for (int r = 0; r < k; r++) {
                ans[r] += next[r];
            }

            dp = next;
        }

        return ans;
    }
};