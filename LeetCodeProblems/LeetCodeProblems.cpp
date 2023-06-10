//3. Longest Substring Without Repeating Characters
//Given a string s, find the length of the longest substring without repeating characters.

#include <array>
#include <iostream>
#include <unordered_set>
#include <string>
#include <cassert>

using std::string;
using std::cout;
using std::unordered_set;
using std::array;

int lengthOfLongestSubstring_1(string s) {
    if (s.size() == 0)
        return 0;

    int maxLen = 1;

    std::unordered_set<char> characters;

    size_t left = 0;

    for (size_t right = 1; right <= s.size(); ++right) {
        auto [pos, isInserted] = characters.insert(s[right - 1]);

        if (!isInserted) {
            // s[right-1] is a duplicate
            char duplicate = s[right - 1];

            // Somewhere in the substring [left, right-1) is the first
            // occurrence of the duplicate character, say as index i.
            // Need to set left = i+1.
            for (auto j = left; j < right; ++j) {
                if (s[j] == duplicate) {
                    left = j + 1;
                    break;
                }
                else {
                    characters.erase(s[j]);
                }
            }
        }
        else {
            int currentLen = static_cast<int>(right - left);
            maxLen = std::max(maxLen, currentLen);
        }

        // string consisting of characters s[left], s[left + 1] ... s[right-1]
        // has no repeating characters.
    }

    return maxLen;
}

int lengthOfLongestSubstring_2(string s) {
    if (s.size() == 0)
        return 0;

    array<int, 256> character_to_index;
    character_to_index.fill(-1);

    size_t left = 0;
    int maxLen = 1;

    // Current window is s[left], s[left + 1] ... s[right - 1]h
    for (size_t right = 1; right <= s.size(); ++right) {
        const unsigned char newChar = s[right - 1];
        const int newCharIndex = character_to_index[newChar];

        auto isDuplicate = (left <= newCharIndex) && (newCharIndex < right);

        if (isDuplicate) {
            // s[right-1] is a duplicate
            const unsigned char duplicate = newChar;
            left = 1 + character_to_index[duplicate];
        }
        else {
            const int currentLen = static_cast<int>(right - left);
            maxLen = std::max(maxLen, currentLen);
        }

        // string consisting of characters s[left], s[left + 1] ... s[right-1]
        // has no repeating characters.
        character_to_index[newChar] = static_cast<int>(right - 1);
    }

    return maxLen;
}

int lengthOfLongestSubstring(string s) {
    return lengthOfLongestSubstring_2(s);
}

void expect(bool condition, const string& message) {
    if (condition) {
        cout << "Success " << message << "\n";
    }
    else {
        cout << "Expected " << message << "\n";
    }
}

int main()
{
    auto r1 = lengthOfLongestSubstring("abcabcbb");
    expect(3 == r1, "r1 == 3");

    auto r2 = lengthOfLongestSubstring("ab");
    expect(r2 == 2, "r2 == 2");

    auto r3 = lengthOfLongestSubstring("abcbdefg");
    expect(r3 == 4, "r3 == 4");

    auto r4 = lengthOfLongestSubstring("tmmzuxt");
    expect(r4 == 5, "r4 == 5");
}

