/************************************************ 
EXERCISE      : Trie
Implmented by : Snir Holland
Reviewed by   : 
Date          : 22/6/23
File          : trie.h
*************************************************/

#ifndef __TRIE_H__
#define __TRIE_H__

enum trie_status
{
    TRIE_SUCCESS,
    TRIE_MEMORY_ERROR,
    TRIE_NOT_FOUND,
    TRIE_NO_FREE_PATH
};

typedef struct trie trie_t;

trie_t *TrieCreate(size_t height);	

void TrieDestroy(trie_t *trie);

int TrieInsert(trie_t *trie, unsigned char *host, unsigned char *result);

int TrieRemove(trie_t *trie ,unsigned char *host);

size_t TrieCount(trie_t *trie);

void TrieTrint2D(trie_t *trie);

#endif /*__TRIE_H__*/
	
