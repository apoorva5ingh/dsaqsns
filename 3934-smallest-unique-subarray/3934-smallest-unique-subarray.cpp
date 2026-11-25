class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        using ll = long long;
        const ll M1 = 1000000007, M2 = 1000000009;
        const ll B = 100003;
        int n = nums.size();

        vector<ll> h1(n + 1), h2(n + 1);
        vector<ll> p1(n + 1, 1), p2(n + 1, 1);

        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] * B + nums[i]) % M1;
            h2[i + 1] = (h2[i] * B + nums[i]) % M2;
            p1[i + 1] = p1[i] * B % M1;
            p2[i + 1] = p2[i] * B % M2;
        }

        auto check = [&](int len) {
            unordered_map<unsigned long long, int> freq;
            freq.reserve(n - len + 1);

            for (int i = 0; i + len <= n; i++) {
                ll a = (h1[i + len] - h1[i] * p1[len] % M1 + M1) % M1;
                ll b = (h2[i + len] - h2[i] * p2[len] % M2 + M2) % M2;

                unsigned long long key =
                    (static_cast<unsigned long long>(a) << 32) |
                    static_cast<unsigned long long>(b);

                freq[key]++;
            }

            for (const auto& entry : freq) {
                if (entry.second == 1) return true;
            }
            return false;
        };

        int low = 1, high = n;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (check(mid))
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};