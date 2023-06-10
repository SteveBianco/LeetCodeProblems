

/* Given an integer n, return the number of strings of length n that 
   consist only of vowels(a, e, i, o, u) and are lexicographically sorted.
*/

#include <iostream>
#include <unordered_map>

using std::unordered_map;
using std::pair;


template <> struct std::hash<std::pair<int, int>> {
    inline size_t operator()(const std::pair<int, int>& v) const {
        std::hash<int> int_hasher;
        return int_hasher(v.first) ^ 3 * int_hasher(v.second);
    }
};

class Solution {
    unordered_map<pair<int, int>, int> cache;

    int countVowelStrings(int n, int nVowels) {
        auto findIt = cache.find({ n, nVowels });

        if (findIt != cache.end())
            return findIt->second;

        if (nVowels == 0)
            return 0;

        if (n == 1)
            return nVowels;

        int result = 0;

        for (int k = 0; k <= n; ++k) {
            result += (n - k > 0) ? countVowelStrings(n - k, nVowels - 1) : 1;
        }

        cache.insert({ {n, nVowels}, result });
        return result;
    }

public:
    int countVowelStrings(int n) {
        return countVowelStrings(n, 5);
    }
};

int main()
{
    Solution solution;
    auto result = solution.countVowelStrings(33);
    std::cout << result << "\n";

    return 0;
}

