destDir = /tmp/gravity_simulator

all: move_to_tmp

move_to_tmp: generate_gold_output
	mkdir -p $(destDir)
	# cp pi.py gold $(destDir)
	cp gravity_simulator gold $(destDir)
	# chmod 777 $(destDir)/pi.py
	@echo "All Done, executables and gold file should be in the $(destDir)"

generate_gold_output: compile
	# chmod 777 pi.py
	# python pi.py gold
	./gravity_simulator gold

compile:
	g++ gravity_simulator.c -o gravity_simulator