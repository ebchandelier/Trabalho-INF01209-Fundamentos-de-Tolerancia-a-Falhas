destDir = /tmp/gauss_seidel

all: move_to_tmp

move_to_tmp: generate_gold_output
	mkdir -p $(destDir)
	# cp pi.py gold $(destDir)
	cp gauss_seidel gold $(destDir)
	# chmod 777 $(destDir)/pi.py
	@echo "All Done, executables and gold file should be in the $(destDir)"

generate_gold_output: compile
	# chmod 777 pi.py
	# python pi.py gold
	./gauss_seidel gold

compile:
	gcc metodo_gauss_seidel.c -o gauss_seidel -lm
