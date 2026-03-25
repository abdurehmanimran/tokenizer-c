#ifndef FILE_CONTENT_H
#define FILE_CONTENT_H

#define MAX_LINE 5126
#define INIT_CAPACITY 512

typedef struct {
  int len;
  int capacity;
  char *text;
} fileContent;

void initFileContent(fileContent **content);
void freeFileContent(fileContent *fileContent);
fileContent *readFromFile(char *filePath);

#endif
