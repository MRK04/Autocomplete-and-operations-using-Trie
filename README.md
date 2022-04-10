# [Autocomplete-and-operations-using-Trie](https://github.com/MRK04/Autocomplete-and-operations-using-Trie/blob/main/Autocomplete%26OperationsOfTrie.cpp)

- Autocomplete or Word Completion is a feature of suggesting possible extensions to a partially written text and is widely used in search engine.
- Implemented it using a basic TRIE Data Structure for Autocomplete. 

## Trie Data Structure:
- TRIE Data Structure is a tree data structure used for locating specific keys from within a set. Basically, it is used for efficient retrieval of a key in a huge set of strings. 
- The nodes in the TRIE Data Structure are used for storing the associate keys of strings and values that are being stored in the TRIE. 
- In order to access a key, the trie is traversed depth-first, following the links between nodes, which represent each character in the key.

## Problem Statement:
- We are given a Trie with a set of strings stored in it. Now the user types in a prefix of his search query, we need to give him all recommendations to auto-complete his query based on the strings stored in the Trie.

- **Example:** \
 ``
 If the Trie store {“abc”, “abcd”, “aa”, “abbbaba”} and the User types in “ab” then he must be shown {“abc”, “abcd”, “abbbaba”}.
 ``
## Solution:
- Implemented a basic TRIE Data Structure for Autocomplete. 
- The primary aim is that, the program should return a list of words if it is given a simple query.
- Given a query prefix, we search for all words having this query. 

```
1. Search for the given query using the standard Trie search algorithm. 
2. If the query prefix itself is not present, return -1 to indicate the same. 
3. If the query is present and is the end of a word in Trie, print query.  
4. If the last matching node of the query has no children, return. 
5. Else recursively print all nodes under a subtree of last matching node. 

```

## Operations Performed:
1. Adding a word to the Trie
2. Deleting a word from a Trie
3. Search by word
4. Displaying list of words in Trie
5. Fetching word list for a prefix

## Time Complexity:
- Trie is a very efficient method used for auto suggesting. Using Trie, search complexities can be brought to optimal limit (key length). If we store keys in binary search tree, a well-balanced BST will need time proportional to M * log N, where M is maximum string length and N is number of keys in tree. Where, the auxiliary space requirement of trie is constant as we do not use any extra space in trie. The run time complexity of adding a word is proportional to the length of the word to be added. Using Trie, we can search the key in O(M) time.
