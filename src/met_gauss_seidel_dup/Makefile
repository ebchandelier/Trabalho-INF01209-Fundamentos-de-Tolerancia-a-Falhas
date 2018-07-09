destDir = /tmp/gauss_seidel_dup

all: move_to_tmp

move_to_tmp: generate_gold_output
	mkdir -p $(destDir)
	# cp pi.py gold $(destDir)
	cp gauss_seidel_dup gold $(destDir)
	# chmod 777 $(destDir)/pi.py
	@echo "All Done, executables and gold file should be in the $(destDir)"

generate_gold_output: compile
	# chmod 777 pi.py
	# python pi.py gold
	./gauss_seidel_dup gold

compile:
	gcc met_gauss_seidel_dup.c -o gauss_seidel_dup -lm
