all:
	@rm -rf build; mkdir -p build
	cd build; cmake ../
	cd build; make
	valgrind ./build/stack-test

.PHONY: all
