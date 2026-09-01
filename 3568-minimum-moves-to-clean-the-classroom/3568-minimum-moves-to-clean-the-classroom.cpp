class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sx, sy;
        vector<pair<int, int>> litter;
        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sx = i;
                    sy = j;
                } else if (classroom[i][j] == 'L') {
                    id[i][j] = litter.size();
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();
        int fullMask = (1 << k) - 1;

        vector<vector<int>> best(
            m * n,
            vector<int>(1 << k, -1)
        );

        queue<array<int, 4>> q;

        int startPos = sx * n + sy;
        best[startPos][0] = energy;
        q.push({sx, sy, 0, energy});

        int moves = 0;

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [x, y, mask, currEnergy] = q.front();
                q.pop();

                if (mask == fullMask)
                    return moves;

                if (currEnergy == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                        continue;

                    if (classroom[nx][ny] == 'X')
                        continue;

                    int newEnergy = currEnergy - 1;
                    int newMask = mask;

                    if (classroom[nx][ny] == 'L')
                        newMask |= (1 << id[nx][ny]);

                    if (classroom[nx][ny] == 'R')
                        newEnergy = energy;

                    int pos = nx * n + ny;

                    if (best[pos][newMask] >= newEnergy)
                        continue;

                    best[pos][newMask] = newEnergy;
                    q.push({nx, ny, newMask, newEnergy});
                }
            }

            moves++;
        }

        return -1;
    }
};