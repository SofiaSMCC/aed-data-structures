#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    Node *children[26];
    bool isEnd;

    Node()
    {
        isEnd = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

class Trie
{
public:
    Node *root;

    Trie()
    {
        root = new Node();
    }

    void insert(string &str)
    {
        Node *node = root;
        for (char c : str)
        {
            if (!node->children[c - 'a'])
            {
                node->children[c - 'a'] = new Node();
            }
            node = node->children[c - 'a'];
        }
        node->isEnd = true;
    }

    string findCommonPrefix(vector<string> &strs)
    {
        if (strs.empty())
            return "";

        for (string &str : strs)
        {
            insert(str);
        }

        string prefix = "";
        Node *node = root;
        while (true)
        {
            int childCount = 0;
            char ch = '\0';
            for (int i = 0; i < 26; i++)
            {
                if (node->children[i])
                {
                    childCount++;
                    ch = 'a' + i;
                }
            }
            if (childCount == 1 && !node->isEnd)
            {
                prefix += ch;
                node = node->children[ch - 'a'];
            }
            else
            {
                break;
            }
        }
        return prefix;
    }
};

class Solution
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        Trie trie;
        return trie.findCommonPrefix(strs);
    }
};

int main()
{
    Solution solution;
    vector<string> strs1 = {"flower", "flow", "flight"};
    cout << "Input: [";
    for (int i = 0; i < strs1.size(); i++)
    {
        cout << "'" << strs1[i] << "'";
        if (i < strs1.size() - 1)
            cout << ",";
    }
    cout << "]" << endl;
    cout << "Output: '" << solution.longestCommonPrefix(strs1) << "'" << endl;

    vector<string> strs2 = {"dog", "racecar", "car"};
    cout << "Input: [";
    for (int i = 0; i < strs2.size(); i++)
    {
        cout << "'" << strs2[i] << "'";
        if (i < strs2.size() - 1)
            cout << ",";
    }
    cout << "]" << endl;
    cout << "Output: '" << solution.longestCommonPrefix(strs2) << "'" << endl;

    return 0;
}