class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char,int>f;
        int low =0;
        int high =0;
        int res =-1;

        for(; high<s.size(); high++)
        {
            f[s[high]]++;
            int len = high-low+1;
            int max_count=0;
            for(auto &it : f)
            {
                max_count = max (max_count , it.second);
            }
            int diff= len-max_count;

            while(diff>k)
            {
                f[s[low]]--;
                low++;
                int max_count=0;
            for(auto &it : f)
            {
                max_count = max (max_count , it.second);
            }
                len=high-low+1;
                diff=len-max_count;
            }

            len = high-low+1;
            res=max(res,len);

        }
        return res;
    }
};