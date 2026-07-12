class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int > f;
        int low =0;
        int high =0;
        int res =-1;
        for(; high<fruits.size(); high++)
        {
            
            f[fruits[high]]++; //add high to the information 
            while(f.size() > 2){ //there's no wrong case , so no if statement 
                 f[fruits[low]]--;
                 if(f[fruits[low]]==0)
                 f.erase(fruits[low]);
                 low++;
            }
            int len=high-low+1;
            res = max(res,len);
            
        }
        return res;
    }
};