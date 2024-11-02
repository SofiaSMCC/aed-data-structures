#include <vector>
#include <string>

using namespace std;

class TrieNode
{
public:
    TrieNode *children[26];
    int count;

    TrieNode()
    {
        for (int i = 0; i < 26; ++i)
            children[i] = nullptr;
        count = 0;
    }
};

class Trie
{
public:
    TrieNode *root;

    Trie()
    {
        root = new TrieNode();
    }

    void insert(const string &word)
    {
        TrieNode *node = root;
        for (char c : word)
        {
            if (node->children[c - 'a'] == nullptr)
                node->children[c - 'a'] = new TrieNode();
            node = node->children[c - 'a'];
        }
        node->count++;
    }
};

class Solution
{
public:
    vector<string> topKFrequent(vector<string> &words, int k)
    {
        Trie trie;
        for (const string &word : words)
            trie.insert(word);

        vector<pair<string, int>> wordFreq;
        dfs(trie.root, "", wordFreq);

        sortCustom(wordFreq);

        vector<string> result;
        for (int i = 0; i < k; ++i)
            result.push_back(wordFreq[i].first);
        return result;
    }

private:
    void dfs(TrieNode *node, string word, vector<pair<string, int>> &wordFreq)
    {
        if (node == nullptr)
            return;

        if (node->count > 0)
            wordFreq.push_back({word, node->count});

        for (int i = 0; i < 26; ++i)
        {
            if (node->children[i] != nullptr)
                dfs(node->children[i], word + char('a' + i), wordFreq);
        }
    }

    void sortCustom(vector<pair<string, int>> &wordFreq)
    {
        for (size_t i = 0; i < wordFreq.size() - 1; ++i)
        {
            for (size_t j = i + 1; j < wordFreq.size(); ++j)
            {
                if (wordFreq[i].second < wordFreq[j].second || (wordFreq[i].second == wordFreq[j].second && wordFreq[i].first > wordFreq[j].first))
                    swap(wordFreq[i], wordFreq[j]);
            }
        }
    }
};
