class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();

        if (k == 1) {
            unordered_map<int, int> freq;
            for (int num : nums) {
                freq[num]++;
            }
            int ans = -1;
            for (auto& [num, count] : freq) {
                if (count == 1) {
                    ans = max(ans, num);
                }
            }
            return ans;
        }

        if (k == n) {
            int ans = -1;
            for (int num : nums) {
                ans = max(ans, num);
            }
            return ans;
        }

        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }

        int ans = -1;
        if (freq[nums[0]] == 1) {
            ans = max(ans, nums[0]);
        }
        if (freq[nums[n - 1]] == 1) {
            ans = max(ans, nums[n - 1]);
        }

        return ans;
    }
};