run: compile

compile:
	rm -rf build/
	mkdir -p build/
	rsync -r * build/  --exclude 'build' --exclude 'screenshot' --exclude '.git' --exclude 'Makefile' --exclude 'README.md'
	gcc -lm build/main.c -o build/sokoban
	rm -rf build/lib build/src build/*.c
