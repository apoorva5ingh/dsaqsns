class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;
        vector<int> diff(n);
        int mx = 0;
        long long sum = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            mx = max(mx, diff[i]);
            sum += diff[i];
        }

        if (sum <= k) return 0;

        vector<long long> freq(mx + 1, 0);
        for (int d : diff) {
            freq[d]++;
        }

        for (int d = mx; d > 0 && k > 0; d--) {
            long long count = freq[d];
            if (count == 0) continue;

            long long next = freq[d - 1];
            long long cost = count;

            if (k >= cost) {
                k -= cost;
                freq[d - 1] += count;
                freq[d] = 0;
            } else {
                long long full = k / count;
                long long rem = k % count;

                freq[d] -= count;
                freq[d - full] += count - rem;
                if (rem > 0) {
                    freq[d - full - 1] += rem;
                }
                k = 0;
            }
        }

        long long ans = 0;
        for (int d = 1; d <= mx; d++) {
            ans += freq[d] * d * d;
        }

        return ans;
    }
};