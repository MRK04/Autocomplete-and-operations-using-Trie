#include <iostream>
#include <stdlib.h>

using namespace std;

const int ALPHABET_SIZE = 26;

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node
struct trieNode
{
    struct trieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};

// new trie node initialized to NULL
struct trieNode *getNode(void)
{
    struct trieNode *pNode = new trieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

void insert(struct trieNode *root, string key)
{
    struct trieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = CHAR_TO_INDEX(key[i]);
        if (!pCrawl->children[index]) //if(!null) -> if(true)
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // Marking last node as leaf
    pCrawl->isEndOfWord = true;
}

// Return true is key is present else false
bool search(struct trieNode *root, string key)
{
    struct trieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = CHAR_TO_INDEX(key[i]);
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

// returns true if root has no children, else false
bool isEmpty(trieNode *root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

// recursive function to delete a key from trie
trieNode *remove(trieNode *root, string key, int depth = 0)
{
    // if trie is empty
    if (!root)
        return NULL;

    // if last character of key is being processed
    if (depth == key.size())
    {
        // this node is no more endOfWord after removal of key
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // if given is not prefix of any other word
        if (isEmpty(root))
        {
            delete (root);
            root = NULL;
        }
        return root;
    }

    // if not last character, recur for the child obtained using ASCII value
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // if root does not have any child, and it is not endOf another word
    if (isEmpty(root) && root->isEndOfWord == false)
    {
        delete (root);
        root = NULL;
    }

    return root;
}

// to check if current node is leaf node
bool isLeafNode(struct trieNode *root)
{
    return root->isEndOfWord != false;
}

// function to display
void display(struct trieNode *root, char str[], int level)
{
    /* if node is a leaf node, it indicates end
    of string, so a null character is added
    and string is displayed*/
    if (isLeafNode(root))
    {
        str[level] = '\0';
        cout << str << endl;
    }

    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        /* if non NULL child is found add parent
        key to str and call the display function
        recursively for child node*/
        if (root->children[i])
        {
            str[level] = i + 'a';
            display(root->children[i], str, level + 1);
        }
    }
}

bool isLastNode(struct trieNode *root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}

// Recursive function to print auto-suggestions for given
// node.
void suggestionsRec(struct trieNode *root, string currPrefix)
{
    // found a string in Trie with the given prefix
    if (root->isEndOfWord)
    {
        cout << currPrefix;
        cout << endl;
    }

    // All children struct node pointers are NULL
    if (isLastNode(root))
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            // append current character to currPrefix string
            currPrefix.push_back(97 + i);

            // recur over the rest
            suggestionsRec(root->children[i], currPrefix);
            // remove last character
            currPrefix.pop_back();
        }
    }
}

// print suggestions for given query prefix.
int printAutoSuggestions(trieNode *root, const string query)
{
    struct trieNode *pCrawl = root;

    // Check if prefix is present and find the
    // the node (of last level) with last character
    // of given string.
    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = CHAR_TO_INDEX(query[level]);

        // no string in the Trie has this prefix
        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }

    // If prefix is present as a word.
    bool isWord = (pCrawl->isEndOfWord == true);

    // If prefix is last node of tree (has no
    // children)
    bool isLast = isLastNode(pCrawl);

    // If prefix is present as a word, but
    // there is no subtree below the last
    // matching node.
    if (isWord && isLast)
    {
        cout << query << endl;
        return -1;
    }

    // If there are are nodes below last
    // matching character.
    if (!isLast)
    {
        string prefix = query;
        suggestionsRec(pCrawl, prefix);
        return 1;
    }
}

// driver
int main()
{
    int level = 0, choice, trieSize = 0;
    string keys, removeKey;

    // Already inserted words
    string words[] = {"hello", "hi", "the", "their", "there",
                      "they", "those", "help", "helping",
                      "answer", "any", "by", "bye", "them"};
    int n = sizeof(words) / sizeof(words[0]);

    struct trieNode *root = getNode();

    // Construct trie
    for (int i = 0; i < n; i++)
    {
        insert(root, words[i]);
        trieSize++;
    }

    cout << "\n";

    while (1)
    {
        cout << "\nSelect an Option\n";
        cout << "\n1 - Insert";
        cout << "\n2 - Delete";
        cout << "\n3 - Search by word";
        cout << "\n4 - Autosugesstion/Search by prefix";
        cout << "\n5 - Display";
        cout << "\n6 - Exit";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "\nEnter the string to be inserted: ";
            cin >> keys;
            insert(root, keys);
            trieSize++;
            break;
        }

        case 2:
        {
            cout << "\nEnter the string to be deleted: ";
            cin >> keys;
            remove(root, keys);
            trieSize--;
            break;
        }

        case 3:
        {
            cout << "\nEnter the string to be searched: ";
            cin >> keys;
            search(root, keys) ? cout << "\nString found.\n" : cout << "\nString not found\n";
            break;
        }

        case 4:
        {
            cout << "\nEnter prefix: ";
            cin >> keys;
            cout << "\nSugesstions: ";
            int comp = printAutoSuggestions(root, keys);

            if (comp == -1)
                cout << "No other strings found with this prefix\n";

            else if (comp == 0)
                cout << "No string found with this prefix\n";
            break;
        }

        case 5:
        {
            char str[trieSize];
            cout << "\nContents of Trie: " << endl;
            display(root, str, level);
            break;
        }

        case 6:
        {
            cout << "\nExiting";
            exit(1);
            break;
        }

        default:
        {
            cout << "\nIncorrect choice. Try again.";
            break;
        }
        }
    }
    return 0;
}
