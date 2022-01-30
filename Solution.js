
/**
 * @param {string[]} products
 * @param {string} searchWord
 * @return {string[][]}
 */
var suggestedProducts = function (products, searchWord) {

    this.ALPHABET = 26;
    this.ASCII_SMALL_CASE_A = 97;
    this.MAX_SUGGESTED_WORDS_TO_DISPLAY = 3;

    const root = new TrieNode();
    const suggestedWordsForEachEntry = [];
    const size = searchWord.length;

    createDictionary(root, products);

    const prefix = [];
    let nodeForMostRecentEntryOfPrefix = root;

    for (let i = 0; i < size; i++) {

        let nextChar = searchWord.charAt(i);
        prefix.push(nextChar);
        nodeForMostRecentEntryOfPrefix = getNodeForMostRecentEntryOfPrefix(nodeForMostRecentEntryOfPrefix, nextChar);

        let suggestedWords = [];

        searchTrie(suggestedWords, nodeForMostRecentEntryOfPrefix, prefix);
        suggestedWordsForEachEntry.push(suggestedWords);
    }

    return suggestedWordsForEachEntry;
};

function TrieNode() {
    this.ALPHABET = 26;
    this.isEndOfWord = false;
    this.branches = new Array(this.ALPHABET).fill(null);
}

/**
 * @param {string[]} suggestedWords
 * @param {TrieNode} node
 * @param {string} word
 */
function searchTrie(suggestedWords, node, word) {

    if (node === null || suggestedWords.length === this.MAX_SUGGESTED_WORDS_TO_DISPLAY) {
        return;
    }
    if (node.isEndOfWord) {
        suggestedWords.push(word.join(''));
    }

    for (let i = 0; i < this.ALPHABET; i++) {
        if (node.branches[i] !== null) {
            let letter = String.fromCodePoint(i + this.ASCII_SMALL_CASE_A);
            word.push(letter);
            searchTrie(suggestedWords, node.branches[i], word);
            word.splice(word.length - 1);
        }
    }
}

/**
 * @param {TrieNode} root
 * @param {string} products
 */
function createDictionary(root, products) {
    let size = products.length;
    for (let i = 0; i < size; i++) {
        addWordToTrie(root, products[i]);
    }
}

/**
 * @param {TrieNode} root
 * @param {string} word
 */
function addWordToTrie(root, word) {

    let current = root;
    let size = word.length;

    for (let i = 0; i < size; i++) {
        let index = word.codePointAt(i) - this.ASCII_SMALL_CASE_A;
        if (current.branches[index] === null) {
            current.branches[index] = new TrieNode();
        }
        current = current.branches[index];
    }
    current.isEndOfWord = true;
}

/**
 * @param {TrieNode} current
 * @param {character} nextPrefixLetter
 * @return {TrieNode}
 */
function getNodeForMostRecentEntryOfPrefix(current, nextPrefixLetter) {
    let index = nextPrefixLetter.codePointAt(0) - this.ASCII_SMALL_CASE_A;
    if (current === null || current.branches[index] === null) {
        return null;
    }
    return current.branches[index];
}
