#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "fileContent.h"

typedef char *wordToken;

typedef struct {
  int n;
  int capacity;
  wordToken *words;
} lineToken;

typedef struct {
  int n;
  int capacity;
  lineToken *lines;
} fileTokens;

fileTokens *createFileTokens(fileContent content);
void freeFileTokens(fileTokens *tokens);
void initLineTokens(lineToken **tokens, int initSize);
void reallocWordTokens(lineToken *tokens);
void reallocLineTokens(fileTokens *tokens);
void addWordToken(lineToken *tokens, wordToken word);
void addLineToken(fileTokens *tokens, lineToken line);
lineToken *createLineTokens(char *line);
void initFileTokens(fileTokens **tokens, int initSize);
void freeFileTokens(fileTokens *tokens);
fileTokens *createTokens(fileContent content);

#endif
