destDir = /tmp/gravity_simulator
CC_FLAGS = -lm -g#-Wall #-Wextra -Werror -g

all: move_to_tmp

move_to_tmp: generate_gold_output
	mkdir -p $(destDir)
	cp gravity_simulator gold $(destDir)
	@echo "All Done, executables and gold file should be in the $(destDir)"

generate_gold_output: compile
	./gravity_simulator gold

compile:
	g++ $(CC_FLAGS) gravity_simulator.cpp -o gravity_simulator