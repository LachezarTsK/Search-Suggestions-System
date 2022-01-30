
#include<vector>
using namespace std;

class Solution {
    
    static const size_t ALPHABET = 26;
    static const int MAX_SUGGESTED_WORDS_TO_DISPLAY = 3;

    struct TrieNode {
        bool isEndOfWord = false;
        vector<TrieNode*> branches{ ALPHABET, nullptr};
    };

public:

    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {

        TrieNode* root = new TrieNode();
        string prefix;

        vector<vector < string>> suggestedWordsForEachEntry;
        createDictionary(root, products);

        TrieNode* nodeForMostRecentEntryOfPrefix = root;
        for (const auto& letter : searchWord) {

            prefix.push_back(letter);
            nodeForMostRecentEntryOfPrefix = getNodeForMostRecentEntryOfPrefix(nodeForMostRecentEntryOfPrefix, letter);

            vector<string> suggestedWords;
            searchTrie(suggestedWords, nodeForMostRecentEntryOfPrefix, prefix);
            suggestedWordsForEachEntry.push_back(suggestedWords);
        }

        nodeForMostRecentEntryOfPrefix = nullptr;
        delete nodeForMostRecentEntryOfPrefix;

        root = nullptr;
        delete root;

        return suggestedWordsForEachEntry;
    }

    void searchTrie(vector<string>& suggestedWords, TrieNode* node, string& word) {

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

    void createDictionary(TrieNode* root, const vector<string>& products) {
        for (const auto& product : products) {
            addWordToTrie(root, product);
        }
    }

    void addWordToTrie(TrieNode* root, const string& word) {

        TrieNode* current = root;

        for (const auto& letter : word) {
            int index = letter - 'a';
            if (current->branches[index] == nullptr) {
                current->branches[index] = new TrieNode();
            }
            current = current->branches[index];
        }
        current->isEndOfWord = true;

        current = nullptr;
        delete current;
    }

    TrieNode* getNodeForMostRecentEntryOfPrefix(TrieNode* current, char nextPrefixLetter) {
        if (current == nullptr || current->branches[nextPrefixLetter - 'a'] == nullptr) {
            return nullptr;
        }
        return current->branches[nextPrefixLetter - 'a'];
    }
};
