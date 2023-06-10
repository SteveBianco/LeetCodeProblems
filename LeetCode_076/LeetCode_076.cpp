//Given two strings sand t of lengths mand n respectively, 
//return the minimum window substring of s such that every character 
//in t(including duplicates) is included in the window.If there is 
//no such substring, return the empty string "".

#include <array>
#include <iostream>
#include <unordered_map>
#include <string>
#include <cassert>

using std::string;
using std::cout;
using std::unordered_map;
using std::array;

struct CharCounts
{
    unordered_map<char, int> counts;

    void add(char c)
    {
        ++counts[c];
    }

    void remove(char c)
    {
        auto it = counts.find(c);

        if (it != counts.end() && it->second > 0)
        {
            --it->second;
        }
    }

    int get(char c) const
    {
        auto it = counts.find(c);

        if (it != counts.end())
            return it->second;

        return 0;
    }
};

bool checkCounts(const CharCounts& source, const CharCounts& target)
{
    for (const auto& targetCharCount : target.counts)
    {
        if (targetCharCount.second > target.get(targetCharCount.first))
            return false;
    }

    return true;
}


string minWindow(string s, string t)
{
    int leftR = -1, rightR = -1;

    // Track character counts for string t.
    unordered_map<char, int> tc;

    for (char c : t)
    {
        tc[c]++;
    }

    // dynamically track character counts for substring [left, right) of s.
    array<int, 256> sc = {};
    int left = 0;

    for (int right = 1; right < s.size(); ++right)
    {
        // update count of new character
        ++sc[s[right - 1]];

        if (right - left >= t.size())
        {
            if (checkCounts(tc, sc))
            {
                if (leftR == -1 || (right - left < rightR - leftR))
                {
                    leftR = left;
                    rightR = right;
                }

                --sc[s[left]];
                ++left;
            }
        }
    }

    return s.substr(leftR, rightR - leftR);
}


void test(const string& s, const string& t, const string& r)
{
    auto result = minWindow(s, t);

    if (result == r)
    {
        cout << "Success\n";
    }
    else
    {
        cout << "Expected " + r + "\tGot " + result + "\n";
    }
}

int main()
{
    CharCounts count;
    count.add('a');
    count.add('a');
    count.add('a');
    count.add('b');
    count.add('b');

    cout << count.get('a') << "\n";

    count.remove('a');
    cout << count.get('a') << "\n";

    count.remove('a');
    cout << count.get('a') << "\n";

    count.remove('a');
    cout << count.get('a') << "\n";

    count.remove('a');
    cout << count.get('a') << "\n";

    test("ADOBECODEBANC", "ABC", "BANC");
}

