#include "fileContent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initFileContent(fileContent **content) {
  *content = (fileContent *)malloc(sizeof(fileContent));
  (*content)->len = 0;
  (*content)->capacity = INIT_CAPACITY;
  (*content)->text = (char *)malloc(sizeof(char) * INIT_CAPACITY);
  (*content)->text[0] = '\0';
}

void freeFileContent(fileContent *fileContent) {
  free(fileContent->text);
  free(fileContent);
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

        // Only bigger cap is acceptable, not equal
        if (textContent->capacity > textContent->len) {
          strcat(textContent->text, line);
        } else {
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
