#include "./command.cpp"
// TODO : Rename .exe to soduko.exe as final thing

int main(int argc, char** argv){
	if (argc < 2) {
		help();
		return 1;
	};

	char* command = argv[1];

	if (strings_equal(command,"play")) play(argc,argv);
	else if (strings_equal(command,"solve")) solve(argc,argv);
	else unknownCommand();

	return 0;
}