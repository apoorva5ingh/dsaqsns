class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {

        unordered_set<int> st;

        int low = 0;

        for (int high = 0; high < nums.size(); high++) {

            
            if (high - low > k) {
                st.erase(nums[low]);
                low++;
            }

            
            if (st.find(nums[high]) != st.end()) {
                return true;
            }

           
            st.insert(nums[high]);
        }

        return false;
    }
};