class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs,
                             int x, vector<int>& queries) {
        
        sort(logs.begin(), logs.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        vector<pair<int, int>> q;
        for (int i = 0; i < queries.size(); i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());

        vector<int> freq(n + 1, 0);
        vector<int> ans(queries.size());

        int left = 0, right = 0;
        int activeServers = 0;

        for (auto [time, index] : q) {

            // Add logs with time <= query
            while (right < logs.size() && logs[right][1] <= time) {
                int server = logs[right][0];

                if (freq[server] == 0)
                    activeServers++;

                freq[server]++;
                right++;
            }

            // Remove logs with time < query - x
            while (left < right && logs[left][1] < time - x) {
                int server = logs[left][0];

                freq[server]--;

                if (freq[server] == 0)
                    activeServers--;

                left++;
            }

            ans[index] = n - activeServers;
        }

        return ans;
    }
};