class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        using ll = long long;

        // {weight, index}
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> available;

        // {freeTime, weight, index}
        using T = tuple<ll,int,int>;
        priority_queue<T, vector<T>, greater<T>> busy;

        for (int i = 0; i < servers.size(); i++) {
            available.push({servers[i], i});
        }

        vector<int> ans;
        ll time = 0;

        for (int i = 0; i < tasks.size(); i++) {
            time = max(time, (ll)i);

            // Move all servers that are now free
            while (!busy.empty() && get<0>(busy.top()) <= time) {
                auto [freeTime, weight, index] = busy.top();
                busy.pop();

                available.push({weight, index});
            }

            // If no server is available, jump to the next free time
            if (available.empty()) {
                time = get<0>(busy.top());

                while (!busy.empty() && get<0>(busy.top()) <= time) {
                    auto [freeTime, weight, index] = busy.top();
                    busy.pop();

                    available.push({weight, index});
                }
            }

            // Pick best available server
            auto [weight, index] = available.top();
            available.pop();

            ans.push_back(index);

            // Server becomes free after processing this task
            busy.push({time + tasks[i], weight, index});
        }

        return ans;
    }
};