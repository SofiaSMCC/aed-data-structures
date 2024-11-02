#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node
{
public:
    Node *children[26];
    int prefix_count;

    Node() : prefix_count(0)
    {
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

    void insert(const string &str)
    {
        Node *node = root;
        for (char c : str)
        {
            if (!node->children[c - 'a'])
                node->children[c - 'a'] = new Node();
            node = node->children[c - 'a'];
            node->prefix_count++;
        }
    }

    int getPrefixCount(const string &str)
    {
        Node *node = root;
        for (char c : str)
        {
            if (!node->children[c - 'a'])
                return 0;
            node = node->children[c - 'a'];
        }
        return node->prefix_count;
    }
};

class Solution
{
public:
    vector<int> sumPrefixScores(vector<string> &words)
    {
        Trie trie;
        vector<int> scores;

        for (const string &word : words)
            trie.insert(word);

        for (const string &word : words)
        {
            int score = 0;
            for (int i = 1; i <= word.size(); i++)
                score += trie.getPrefixCount(word.substr(0, i));
            scores.push_back(score);
        }

        return scores;
    }
};

int main()
{
    Solution solution;
    vector<string> words = {"abc", "ab", "bc", "b"};
    vector<int> scores = solution.sumPrefixScores(words);

    cout << "Output: ";
    for (int score : scores)
    {
        cout << score << " ";
    }
    cout << endl;

    vector<string> w2 = {"abcd"};
    vector<int> s2 = solution.sumPrefixScores(w2);

    cout << "Output: ";
    for (int s : s2)
    {
        cout << s << " ";
    }
    cout << endl;
    return 0;
}
