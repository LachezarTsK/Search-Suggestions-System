
import java.util.ArrayList;
import java.util.List;

public class Solution {

    static final int ALPHABET = 26;
    static final int MAX_SUGGESTED_WORDS_TO_DISPLAY = 3;

    class TrieNode {

        boolean isEndOfWord;
        TrieNode[] branches;

        public TrieNode() {
            branches = new TrieNode[ALPHABET];
        }
    }

    public List<List<String>> suggestedProducts(String[] products, String searchWord) {

        TrieNode root = new TrieNode();
        StringBuilder prefix = new StringBuilder();

        List<List<String>> suggestedWordsForEachEntry = new ArrayList<>();
        createDictionary(root, products);
        int size = searchWord.length();

        TrieNode nodeFormostRecentEntryOfPrefix = root;
        for (int i = 0; i < size; i++) {

            char nextChar = searchWord.charAt(i);
            prefix.append(nextChar);
            nodeFormostRecentEntryOfPrefix = getNodeForMostRecentEntryOfPrefix(nodeFormostRecentEntryOfPrefix, nextChar);

            List<String> suggestedWords = new ArrayList<>();

            searchTrie(suggestedWords, nodeFormostRecentEntryOfPrefix, prefix);
            suggestedWordsForEachEntry.add(suggestedWords);
        }
        return suggestedWordsForEachEntry;
    }

    public void searchTrie(List<String> suggestedWords, TrieNode node, StringBuilder word) {

        if (node == null || suggestedWords.size() == MAX_SUGGESTED_WORDS_TO_DISPLAY) {
            return;
        }
        if (node.isEndOfWord) {
            suggestedWords.add(word.toString());
        }

        for (char letter = 'a'; letter <= 'z'; letter++) {
            if (node.branches[letter - 'a'] != null) {
                word.append(letter);
                searchTrie(suggestedWords, node.branches[letter - 'a'], word);
                word.deleteCharAt(word.length() - 1);
            }
        }
    }

    public void createDictionary(TrieNode root, String[] products) {
        int size = products.length;
        for (int i = 0; i < size; i++) {
            addWordToTrie(root, products[i]);
        }
    }

    public void addWordToTrie(TrieNode root, String word) {

        TrieNode current = root;
        int size = word.length();

        for (int i = 0; i < size; i++) {
            int index = word.charAt(i) - 'a';
            if (current.branches[index] == null) {
                current.branches[index] = new TrieNode();
            }
            current = current.branches[index];
        }
        current.isEndOfWord = true;
    }

    public TrieNode getNodeForMostRecentEntryOfPrefix(TrieNode current, char nextPrefixLetter) {
        if (current == null || current.branches[nextPrefixLetter - 'a'] == null) {
            return null;
        }
        return current.branches[nextPrefixLetter - 'a'];
    }
}
