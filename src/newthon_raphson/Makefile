CC = g++
CC_FLAGS = -Wall -Wextra -Werror -g

destDir = /tmp/newton_raphson

all: gen_bin gen_data mv_bin

gen_bin: newton_raphson.cpp
	$(CC) $(CC_FLAGS) newton_raphson.cpp -o newton_raphson

gen_data: gen_bin
	./newton_raphson gold.txt

mv_bin: gen_data
	mkdir -p $(destDir)
	mv newton_raphson gold.txt $(destDir)
	@echo "All Done, executables should be in the $(destDir)"
