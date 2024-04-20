//Esrat Jahan, Lab Assignment 10, COP 3502 Sec 5, LAB SEC 38, 04/19/2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the trie node structure
struct Trie {
    struct Trie *children[26];
    int count;
};

// Insert a word into the trie
void insert(struct Trie **ppTrie, char *word) {
    // If the trie doesn't exist, create a new node
    if (*ppTrie == NULL) {
        *ppTrie = malloc(sizeof(struct Trie));
        memset((*ppTrie)->children, 0, sizeof((*ppTrie)->children));
        (*ppTrie)->count = 0;
    }
    struct Trie *pTrie = *ppTrie;
    // Traverse the trie to the appropriate node for the word
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            pTrie->children[index] = malloc(sizeof(struct Trie));
            memset(pTrie->children[index]->children, 0, sizeof(pTrie->children[index]->children));
            pTrie->children[index]->count = 0;
        }
        pTrie = pTrie->children[index];
    }
    // Increment the count for the final node of the word
    pTrie->count++;
}

// Find the number of occurrences of a word in the trie
int numberOfOccurrences(struct Trie *pTrie, char *word) {
    // Traverse the trie to the appropriate node for the word
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            return 0;
        }
        pTrie = pTrie->children[index];
    }
    // Return the count for the final node of the word
    return pTrie->count;
}

// Deallocate the trie and all of its nodes
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie != NULL) {
        for (int i = 0; i < 26; i++) {
            if (pTrie->children[i] != NULL) {
                deallocateTrie(pTrie->children[i]);
            }
        }
        free(pTrie);
    }
    return NULL;
}

int main(void) {
    // Read the number of words in the dictionary
    int n;
    scanf("%d", &n);

    // Parse each word and insert it into the trie
    struct Trie *trie = NULL;
    char word[101];
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        insert(&trie, word);
    }

    // Check the number of occurrences of each word in the trie
    char *pWords[] = {"not", "note", "ucf", "notaword", "notawordeither", "notaword", "ucf", "note", "ucf", "notawordeithereither", "not", "ucf", "notaword"};
    for (int i = 0; i < 13; i++) {
        printf("%s: %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }

    // Deallocate the trie and check for errors
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }

    // Return 0 to indicate successful program execution
    return 0;
}
