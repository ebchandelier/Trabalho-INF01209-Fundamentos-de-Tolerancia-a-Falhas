CC = g++
CC_FLAGS = -Wall -Wextra -Werror -g -std=c++17

destDir = /tmp/newton_raphson

all: gen_bin gen_data mv_bin

dup: all gen_bin_dup

hardned: all gen_bin_hardned

gen_bin: newton_raphson.cpp
	$(CC) $(CC_FLAGS) newton_raphson.cpp -o newton_raphson

gen_bin_dup: newton_raphson_dup.cpp
	$(CC) $(CC_FLAGS) newton_raphson_dup.cpp -o newton_raphson_dup
	mv newton_raphson_dup $(destDir)

gen_bin_hardned: newton_raphson_hardned.cpp
	$(CC) $(CC_FLAGS) newton_raphson_hardned.cpp -o newton_raphson_hardned
	mv newton_raphson_hardned $(destDir)

gen_data: gen_bin
	./newton_raphson gold.txt

mv_bin: gen_data
	mkdir -p $(destDir)
	mv newton_raphson gold.txt $(destDir)
	@echo "All Done, executables should be in the $(destDir)"
