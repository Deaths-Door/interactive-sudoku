#include "./utils.cpp"

void help() { 
    std::cout << 
    "Usage: soduko[EXE] [OPTIONS]\n"
    "Options:\n" 
    "  play <N>                 Launch new interactive mode with N numbers missing\n"
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

void play(const int argc, const char* const argv[]) {
    if (argc < 4) unknownCommand();

    auto thirdItem = argv[3];

    // 1:name , 2:command so look at 3
    SudokoGrid grid; 
    if(strings_equal(thirdItem,"--custom")) grid = requestGridFromUser();
    else if(argc == 5 && strings_equal(thirdItem,"--new")) grid = requestGridFromFile();
    else grid = SudokoGrid::random(std::stoi(thirdItem));

    startInteractiveMode(grid);
}

void solve(const int argc, const char* const argv[]) {
    if (argc < 4) unknownCommand();

    auto thirdItem = argv[3];

    // 1:name , 2:command so look at 3
    SudokoGrid grid; 
    if(strings_equal(thirdItem,"--custom")) grid = requestGridFromUser();
    else if(argc == 5 && strings_equal(thirdItem,"--new")) grid = requestGridFromFile();

    grid.solve();
}