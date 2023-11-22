build:
	g++ *.cc

gost:
	find . -name *.cc | xargs clang-format -i --style=google
