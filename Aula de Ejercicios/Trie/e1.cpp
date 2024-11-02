#include <iostream>
#include <vector>
using namespace std;

class StreamChecker
{
public:
    struct Node
    {
        Node *links[26];
        bool flag = false;
        bool isContains(char ch)
        {
            return links[ch - 'a'] != NULL;
        }
        void put(char ch, Node *node)
        {
            links[ch - 'a'] = node;
        }
        Node *get(char ch)
        {
            return links[ch - 'a'];
        }
        void setEnd()
        {
            flag = true;
        }
        bool isEnd()
        {
            return flag;
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
            for (int i = str.size() - 1; i >= 0; i--)
            {
                if (!node->isContains(str[i]))
                {
                    node->put(str[i], new Node());
                }
                node = node->get(str[i]);
            }
            node->setEnd();
        }
        bool check(string &str)
        {
            Node *node = root;
            for (int i = str.size() - 1; i >= 0; i--)
            {
                if (node->isContains(str[i]))
                {
                    node = node->get(str[i]);
                    if (node->isEnd())
                        return true;
                }
                else
                    return false;
            }
            return false;
        }
    };

    Trie *trie;
    string str;
    StreamChecker(vector<string> &words)
    {
        trie = new Trie();
        for (int i = 0; i < words.size(); i++)
        {
            trie->insert(words[i]);
        }
        str = "";
    }
    bool query(char letter)
    {
        str += letter;
        if (trie->check(str))
            return true;
        return false;
    }
};

int main()
{
    vector<string> words = {"cd", "f", "kl"};
    StreamChecker streamChecker(words);
    cout << streamChecker.query('a') << endl; // return False
    cout << streamChecker.query('b') << endl; // return False
    cout << streamChecker.query('c') << endl; // return False
    cout << streamChecker.query('d') << endl; // return True, ’cd’ is in the wordlist
    cout << streamChecker.query('e') << endl; // return False
    cout << streamChecker.query('f') << endl; // return True, ’f’ is in the wordlist
    cout << streamChecker.query('g') << endl; // return False
    cout << streamChecker.query('h') << endl; // return False
    cout << streamChecker.query('i') << endl; // return False
    cout << streamChecker.query('j') << endl; // return False
    cout << streamChecker.query('k') << endl; // return False
    cout << streamChecker.query('l') << endl; // return True, ’kl’ is in the wordlistStreamChecker streamChecker = new StreamChecker(["cd","f","kl"])
}