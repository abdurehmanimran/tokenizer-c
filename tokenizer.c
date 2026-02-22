#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define INIT_CAPACITY 512

typedef struct {
  int len;
  int capacity;
  char *text;
} fileContent;

typedef char ***linesArray;

typedef struct {
  int len;
  int capacity;
  linesArray lines;
} tokens;

fileContent *readFromFile(char *filePath);
void initFileContent(fileContent **content);
void freeFileContent(fileContent *fileContent);

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

void freeFileContent(fileContent *fileContent) {
  free(fileContent->text);
  free(fileContent);
}

void initFileContent(fileContent **content) {
  *content = (fileContent *)malloc(sizeof(fileContent));
  (*content)->len = 0;
  (*content)->capacity = INIT_CAPACITY;
  (*content)->text = (char *)malloc(sizeof(char) * INIT_CAPACITY);
}

int readLine(FILE *file, char **buffer) {
  char *line = (char *)malloc(sizeof(char) * MAX_LINE);
  if (fgets(line, MAX_LINE, file) == NULL) {
    free(line);
    return 0;
  }
  *buffer = line;
  return 1;
}

fileContent *readFromFile(char *filePath) {
  fileContent *textContent;
  // Opening a File for Reading
  FILE *file = fopen(filePath, "r");

  if (file == NULL) {
    return NULL;
  } else {
    // Initializing the Content Struct
    initFileContent(&textContent);

    // Reading the file line by line
    while (1) {
      char *line;
      if (readLine(file, &line)) {
        textContent->len += strlen(line);
        if (textContent->capacity > textContent->len)
          strcat(textContent->text, line);
        else {
          textContent->capacity *= 2;
          char *temp;
          if ((temp = (char *)realloc(textContent->text,
                                      sizeof(char) * textContent->capacity)) !=
              NULL) {
            textContent->text = temp;

          } else {
            printf("Error while reallocating the content text!!");
            break;
          }
          strcat(textContent->text, line);
        }
        free(line);
      } else
        break;
    }
  }
  return textContent;
}
