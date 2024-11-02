#include <iostream>
#include <vector>

const int ALPHABET_SIZE = 26;

class Trie
{
    struct TrieNode
    {
        TrieNode *childNode[ALPHABET_SIZE];
        bool wordEnd;

        TrieNode() : wordEnd(false)
        {
            for (int i = 0; i < ALPHABET_SIZE; i++)
                childNode[i] = nullptr;
        }
    };

    TrieNode *root;

    bool isEmpty(TrieNode *node)
    {
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            if (node->childNode[i])
                return false;
        }
        return true;
    }

public:
    Trie()
    {
        root = new TrieNode();
    }

    void insert(const std::string &s)
    {
        TrieNode *current = root;
        for (char c : s)
        {
            int index = c - 'a';

            if (current->childNode[index] == nullptr)
                current->childNode[index] = new TrieNode();
            current = current->childNode[index];
        }
        current->wordEnd = true;
    }

    bool search(const std::string &s)
    {
        TrieNode *current = root;
        for (char c : s)
        {
            int index = c - 'a';
            if (current->childNode[index] == nullptr)
                return false;
            current = current->childNode[index];
        }
        return current != nullptr && current->wordEnd;
    }

    void remove(const std::string &s)
    {
        removeHelper(root, s, 0);
    }

    TrieNode *removeHelper(TrieNode *node, const std::string &s, int depth)
    {
        if (node == nullptr)
            return nullptr;

        if (depth == s.size())
        {
            if (node->wordEnd)
                node->wordEnd = false;
            if (isEmpty(node))
            {
                delete node;
                return nullptr;
            }
            return node;
        }

        int index = s[depth] - 'a';
        node->childNode[index] = removeHelper(node->childNode[index], s, depth + 1);

        if (isEmpty(node) && !node->wordEnd)
        {
            delete node;
            return nullptr;
        }
        return node;
    }

    ~Trie()
    {
        deleteTrie(root);
    }

    void deleteTrie(TrieNode *node)
    {
        if (node == nullptr)
            return;

        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            if (node->childNode[i])
                deleteTrie(node->childNode[i]);
        }

        delete node;
    }
};
