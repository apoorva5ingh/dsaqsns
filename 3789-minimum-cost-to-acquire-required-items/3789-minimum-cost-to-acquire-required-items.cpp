class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth,
                          int need1, int need2) {
        long long costA = 1LL * need1 * cost1
                        + 1LL * need2 * cost2;

        long long costB = 1LL * max(need1, need2) * costBoth;

        int mn = min(need1, need2);

        long long costC = 1LL * mn * costBoth
                        + 1LL * (need1 - mn) * cost1
                        + 1LL * (need2 - mn) * cost2;

        return min({costA, costB, costC});
    }
};