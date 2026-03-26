FILES := src/tokenizer.c src/fileContent.c
BINARY := bin/tokenizer
DEBUG_FLAGS := -g -fsanitize=address

tokenizer: $(FILES)
	mkdir -p bin
	gcc $(FILES) -o $(BINARY) $(DEBUG_FLAGS)
