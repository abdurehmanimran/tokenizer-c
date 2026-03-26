#include "fileContent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *wordToken;
// typedef wordToken *lineToken;

typedef struct {
  int n;
  int capacity;
  wordToken *words;
} lineToken;
// typedef lineToken *fileTokens;

typedef struct {
  int n;
  int capacity;
  lineToken *lines;
} fileTokens;

fileTokens *createTokens(fileContent content);
void freeFileTokens(fileTokens *tokens);

int main(int argc, char **argv) {
  fileContent *fileText;
  char *filePath;

  // Argument Management
  if (argc < 2) {
    printf("Please provide the path for text file!!");
    return 1;
  }
  filePath = argv[1];

  if ((fileText = readFromFile(filePath)) == NULL)
    printf("Error Opening the File!!\n");

#ifndef CAT

  fileTokens *tokens = NULL;

  printf("» Content Length: %d\n» Content Capacity: %d\n", fileText->len,
         fileText->capacity);
  tokens = createTokens(*fileText);
  if (tokens != NULL)
    freeFileTokens(tokens);

#else

  printf("%s", fileText->text);
  puts("\n________________________________________________");
  printf("» Content Length: %d\n» Content Capacity: %d\n", fileText->len,
         fileText->capacity);

#endif

  freeFileContent(fileText);
  return 0;
}

void initLineTokens(lineToken **tokens, int initSize) {
  *tokens = (lineToken *)malloc(sizeof(lineToken));
  (*tokens)->n = 0;
  (*tokens)->capacity = initSize;
  (*tokens)->words = (wordToken *)malloc(sizeof(wordToken) * initSize);
}

void freeLineTokens(lineToken *tokens) { free(tokens->words); }

void reallocWordTokens(lineToken *tokens) {
  tokens->capacity *= 2;

  if (tokens->words == NULL) {
    printf("Error: Failed to realloc the lineTokens!!\n");
    exit(1);
  }
  wordToken *tempTokens =
      (wordToken *)realloc(tokens->words, sizeof(wordToken) * tokens->capacity);

  tokens->words = tempTokens;
}

void reallocLineTokens(fileTokens *tokens) {
  tokens->capacity *= 2;

  lineToken *tempTokens =
      realloc(tokens->lines, sizeof(lineToken) * tokens->capacity);

  if (tempTokens == NULL) {
    printf("Error: Failed to realloc the lineTokens!!\n");
    exit(1);
  }

  tokens->lines = tempTokens;
}

void addWordToken(lineToken *tokens, wordToken word) {
  tokens->n++;

  if (tokens->capacity > tokens->n) {
  } else {
    reallocWordTokens(tokens);
  }

  tokens->words[tokens->n - 1] = word;
}

void addLineToken(fileTokens *tokens, lineToken line) {
  tokens->n++;

  if (tokens->n > tokens->capacity) {
    reallocLineTokens(tokens);
  }

  tokens->lines[tokens->n - 1] = line;
}

lineToken *createLineTokens(char *line) {
  lineToken *tokens;
  initLineTokens(&tokens, 8); // 8 Words

  char *partOfLine;
  char *tok_ptr;

  partOfLine = strtok_r(line, " ", &tok_ptr);

  while (partOfLine != NULL) {
    addWordToken(tokens, strdup(partOfLine));
    partOfLine = strtok_r(NULL, " ", &tok_ptr);
  }
  return tokens;
}

void initFileTokens(fileTokens **tokens, int initSize) {
  (*tokens) = (fileTokens *)malloc(sizeof(fileTokens));
  (*tokens)->n = 0;
  (*tokens)->capacity = initSize;
  (*tokens)->lines = malloc(sizeof(lineToken) * initSize);
}

void freeFileTokens(fileTokens *tokens) {

  for (int i = 0; i < tokens->n; i++) {

    for (int j = 0; j < tokens->lines[i].n; j++)
      free(tokens->lines[i].words[j]);

    free(tokens->lines[i].words);
  }

  free(tokens->lines);
  free(tokens);
}

fileTokens *createTokens(fileContent content) {
  fileTokens *tokens;
  initFileTokens(&tokens, 16);

  char *line;
  char *line_tok_ptr;

  line = strtok_r(content.text, "\n", &line_tok_ptr);

  while (line != NULL) {
    // Temporary, to be cleared because its memory is copied in the
    // addLineToken() func
    lineToken *lineToken = createLineTokens(line);
    addLineToken(tokens, *lineToken);
    free(lineToken);
    line = strtok_r(NULL, "\n", &line_tok_ptr);
  }

  return tokens;
}
