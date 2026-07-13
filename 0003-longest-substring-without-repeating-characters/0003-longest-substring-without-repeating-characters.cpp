class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int> f;
        int low =0;
        int high =0;
        int res =0;
        for(; high<s.size(); high++)
        {
            f[s[high]]++; // add information to high 
            int k= high-low+1;

            while(f[s[high]]>1)
            {
                f[s[low]]--;
                if(f[s[low]]==0)
                    f.erase(s[low]);
                    low++;
                    k=high-low+1;
            }
            int len = high - low +1 ;
            res= max (res, len);
        }
        return res ;
    }
};