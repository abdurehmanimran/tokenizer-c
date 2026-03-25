#include "fileContent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *wordToken;
typedef wordToken *lineToken;
typedef lineToken *fileTokens;

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
  printf("%s", fileText->text);
  puts("\n________________________________________________");
  printf("» Content Length: %d\n» Content Capacity: %d\n", fileText->len,
         fileText->capacity);
  freeFileContent(fileText);
  return 0;
}
