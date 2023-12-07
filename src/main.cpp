#include "./sudoku.hpp"
#include "./utils.cpp"

// TODO : Rename .exe to soduko.exe as final thing

int main(int argc, char** argv){
	std::cout << "HELLO\n" << SudokoGrid::random();

	/*if (argc < 2) {
		command::help();
		return 1;
	};

	char* command = argv[1];
	
	if (strings_equal(command,"play")) command::play(argc,argv);
	else if (strings_equal(command,"solve")) command::solve(argc,argv);
	else command::unknownCommand();*/

	return 0;
}