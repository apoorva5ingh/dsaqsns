class Solution {
public:
    int LOG = 17;
    vector<vector<int>> g, up;
    vector<int> tin, tout, dep, bit;
    int timer = 0;

    void dfs(int u, int p) {
        tin[u] = ++timer;
        up[u][0] = p;

        for (int i = 1; i < LOG; i++)
            up[u][i] = up[up[u][i - 1]][i - 1];

        for (int v : g[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }

        tout[u] = timer;
    }

    void add(int x, int val, int n) {
        for (; x <= n; x += x & -x)
            bit[x] ^= val;
    }

    void rangeXor(int l, int r, int val, int n) {
        add(l, val, n);
        add(r + 1, val, n);
    }

    int get(int x) {
        int res = 0;
        for (; x; x -= x & -x)
            res ^= bit[x];
        return res;
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v])
            swap(u, v);

        int d = dep[u] - dep[v];

        for (int i = 0; i < LOG; i++)
            if (d & (1 << i))
                u = up[u][i];

        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }

        return up[u][0];
    }

    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                 string s, vector<string>& queries) {
        string suneravilo = s;

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        g.assign(n, {});
        up.assign(n, vector<int>(LOG));
        tin.resize(n);
        tout.resize(n);
        dep.assign(n, 0);
        bit.assign(n + 2, 0);

        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        dfs(0, 0);

        for (int i = 0; i < n; i++) {
            int mask = 1 << (s[i] - 'a');
            rangeXor(tin[i], tout[i], mask, n + 1);
        }

        vector<bool> ans;

        for (auto &q : queries) {
            stringstream ss(q);
            string type;
            int u, v;
            char c;

            ss >> type >> u;

            if (type == "update") {
                ss >> c;

                int oldMask = 1 << (s[u] - 'a');
                int newMask = 1 << (c - 'a');

                rangeXor(tin[u], tout[u], oldMask ^ newMask, n + 1);
                s[u] = c;
            } 
            else {
                ss >> v;

                int w = lca(u, v);

                int mask = get(tin[u]) ^ get(tin[v])
                         ^ (1 << (s[w] - 'a'));

                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};