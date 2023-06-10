// LeetCode_1456.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_set>
#include <string>
#include <cassert>

using namespace std;

class Counter {
    static constexpr int N = 26;
    int counts[N] = { 0 };

public:
    void add(char c) {
        const int idx = c - 'a';
        assert(0 <= idx && idx < N);
        ++counts[idx];
    }

    void remove(char c) {
        const int idx = c - 'a';
        assert(0 <= idx && idx < N);
        if (counts[idx] > 0) {
            --counts[idx];
        }
    }

    int getCount(char c) const {
        const int idx = c - 'a';
        assert(0 <= idx && idx < N);
        return counts[idx];
    }

    int countVowels() const {
        return getCount('a')
            + getCount('e')
            + getCount('i')
            + getCount('o')
            + getCount('u');
    }
};

class Solution {
public:
    int maxVowels(string s, int k) {
        if (k > s.size())
            return 0;

        // count vowels in first substring of length k
        Counter counter;

        for (int i = 0; i < k; ++i) {
            counter.add(s[i]);
        }

        int result = counter.countVowels();

        for (int right = k; right < s.size(); ++right) {
            counter.add(s[right]);

            const int left = right - k;
            counter.remove(s[left]);

            const int nVowels = counter.countVowels();

            result = max(result, nVowels);
        }

        return result;
    }
};

int main()
{
    auto res = Solution{}.maxVowels("leetcode", 8);
    std::cout << res << "\n";
}