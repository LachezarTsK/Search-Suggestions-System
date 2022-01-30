
#include<vector>
using namespace std;

class Solution {
    
    static const size_t ALPHABET = 26;
    static const int MAX_SUGGESTED_WORDS_TO_DISPLAY = 3;

    struct TrieNode {
        bool isEndOfWord = false;
        vector<shared_ptr<TrieNode>> branches {ALPHABET};
    };

public:

    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {

        shared_ptr<TrieNode> root(new TrieNode());
        string prefix;

        vector<vector < string>> suggestedWordsForEachEntry;
        createDictionary(root, products);

        shared_ptr<TrieNode> nodeForMostRecentEntryOfPrefix(root);
        for (const auto& letter : searchWord) {

            prefix.push_back(letter);
            nodeForMostRecentEntryOfPrefix = getNodeForMostRecentEntryOfPrefix(nodeForMostRecentEntryOfPrefix, letter);

            vector<string> suggestedWords;
            searchTrie(suggestedWords, nodeForMostRecentEntryOfPrefix, prefix);
            suggestedWordsForEachEntry.push_back(suggestedWords);
        }

        return suggestedWordsForEachEntry;
    }

    void searchTrie(vector<string>& suggestedWords, shared_ptr<TrieNode> node, string& word) {

        if (node == nullptr || suggestedWords.size() == MAX_SUGGESTED_WORDS_TO_DISPLAY) {
            return;
        }
        if (node->isEndOfWord) {
            suggestedWords.push_back(word);
        }

        for (char letter = 'a'; letter <= 'z'; letter++) {
            if (node->branches[letter - 'a'] != nullptr) {
                word.push_back(letter);
                searchTrie(suggestedWords, node->branches[letter - 'a'], word);
                word.pop_back();
            }
        }
    }

    void createDictionary(shared_ptr<TrieNode> root, const vector<string>& products) {
        for (const auto& product : products) {
            addWordToTrie(root, product);
        }
    }

    void addWordToTrie(shared_ptr<TrieNode> root, const string& word) {

        shared_ptr<TrieNode> current(root);

        for (const auto& letter : word) {
            int index = letter - 'a';
            if (current->branches[index] == nullptr) {
                current->branches[index] = shared_ptr<TrieNode>(new TrieNode());
            }
            current = current->branches[index];
        }
        current->isEndOfWord = true;
    }

    shared_ptr<TrieNode> getNodeForMostRecentEntryOfPrefix(shared_ptr<TrieNode> current, char nextPrefixLetter) {
        if (current == nullptr || current->branches[nextPrefixLetter - 'a'] == nullptr) {
            return nullptr;
        }
        return current->branches[nextPrefixLetter - 'a'];
    }
};
