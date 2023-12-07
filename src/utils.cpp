#include <iostream>
#include <cstring>

namespace command {
    void solve(const int argc, const char* const argv[]) {

    }

    void play(const int argc, const char* const argv[]) {
       // if (argc < 3) unknownCommand();

        // 1:name , 2:command so look at 3
       // if (argc == 3) { /*Generate random grid and do it*/ }
        // 4th item is flags like --custom
      //  else if(argc == 4 && strings_equal(argv[3],"--custom")) { /*Input strings to make grid*/ }
     //   else if(argc == 5 && strings_equal(argv[3],"--new")) {
     //       if (argc != 4)
      //  }*/
    }

    void help() { 
	    std::cout << 
        "Usage: soduko[EXE] [OPTIONS]\n"
        "Options:\n" 
        "  play                     Launch new interactive mode\n"
        "  play --custom            Launch new interactive mode with custom grid\n"
        "  play --new <FILE_DIR>    Launch interactive mode from saved game (.soduko files)\n"
        "  solve --custom           Launch solve mode with custom grid\n"
        "  solve --new <FILE_DIR>   Launch solve mode from .soduko file\n"
        << std::endl;
    }

    void unknownCommand() {
        std::cout << "Unknown command\n";
		help();
        exit(1);
    }
}

bool strings_equal(char* str,char const *cond) {
    return strcmp(str,cond) == 0;
}