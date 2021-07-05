class Solution {
public:
     vector<int> grayCode(int n) {
        vector<int> result;
        result.push_back(0);

        // 1st Approach - iterative find pattern
        // O(2^n)
        //pattern(result, n);

        // 2nd Approach - naive recursion + backtracking
        // O(n * 2 ^ n) 
        // Keeps track of the numbers present in the current sequence.
        unordered_set<int> isPresent;

        // All Gray code sequence starts with 0
        isPresent.insert(0);
        recur(result, n, isPresent);

        return result;
    }

    void pattern(vector<int>& result, int n) {
        for (int i = 1; i <= n; i++) {
            int previousSequenceLength = result.size();
            int mask = 1 << (i - 1); // (2 ^ (i - 1))
            
            // adding current mask to all previous elements
            for (int j = previousSequenceLength - 1; j >= 0; j--) {
                result.push_back(mask + result[j]);
            }
        }
    }
    
    bool recur(vector<int> &result, int n, unordered_set<int> &isPresent) {
        if (result.size() == (1 << n)) 
            return true;

        int current = result.back();
        
        for (int i = 0; i < n; i++) {
            // toggle every ith bit
            int next = current ^ (1 << i);
            if (isPresent.find(next) == isPresent.end()) {
                isPresent.insert(next);
                result.push_back(next);
                
            // If valid sequence found no need to search any further
                if (recur(result, n, isPresent)) 
                    return true;
            
            // If no valid sequence found delete the last added number and continue the search.
                isPresent.erase(next);
                result.pop_back();
            }
        }
        
        return false;
    }
};
