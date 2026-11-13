class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        deque<int> dq;
        long long cost = 0;
        long long ans = 0;

        int r = n - 1;

        for (int l = n - 1; l >= 0; --l) {

           
            while (!dq.empty() && nums[dq.back()] < nums[l]) {
                int x = dq.back();
                dq.pop_back();

                int right = dq.empty() ? r + 1 : dq.back();

                cost += 1LL * (right - x) *
                        (nums[l] - nums[x]);
            }

            dq.push_back(l);

            
            while (cost > k) {
                cost -= nums[dq.front()] - nums[r];

                if (dq.front() == r)
                    dq.pop_front();

                r--;
            }
            ans += r - l + 1;
        }

        return ans;
    }
};