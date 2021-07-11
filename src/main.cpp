#include <iostream>
#include "Application.h"
#include "constants.h"

void print_usage(){
    cerr << "Usage: img2gol INPUT_IMAGE PATTERNS_DIR OUTPUT_DIR NUM_STEPS SOLVER" << endl << endl;
    cerr << "Program that loads a PNG image, converts it to a binary form and runs Game of Life on it." << endl << endl;
    cerr << "Arguments:" << endl;
    cerr << "INPUT_IMAGE   - PNG file to be loaded. Can be RGB or RGBA" << endl;
    cerr << "PATTERNS_DIR  - Directory where are stored pattern files provided with the software" << endl;
    cerr << "OUTPUT_DIR    - Directory where will be stored files of each step of Game of Life" << endl;
    cerr << "NUM_STEPS     - How many steps program should run Game of Life" << endl;
    cerr << "SOLVER        - 0 for standard Conway's Game of Life. 1 for Custom Game of Life algorithm" << endl << endl;
    cerr << "Custom Game of Life algorithm :" << endl;
    cerr << "Custom Game of Life algorithm runs standard Conway's Game of Life with new concept of stars." << endl;
    cerr << "Star is a repeating pattern in shape of a star. There are two types of stars in my algorithm." << endl;
    cerr << "Star can explode at any time. When star explodes it changes its surrounding to a random state." << endl;
}

int number_from_string_argument(const string& argument, const string& argument_name){
    int number;
    try {
        number = std::stoi(argument);
    }
    catch (...) {
        cerr << argument_name << " must be a number" << endl;
        print_usage();
        exit(EXIT_FAILURE);
    }

    if(number < 0){
        cerr << argument_name << " must be positive number" << endl;
    }

    return number;
}

int main(int argc, char* argv[]) {
    if(argc < 6){
        print_usage();
        exit(EXIT_FAILURE);
    }

    string test_file = argv[1];
    string pattern_dir = argv[2];
    string output_dir = argv[3];
    int num_steps = number_from_string_argument(argv[4], "NUM_STEPS");
    int solver_type = number_from_string_argument(argv[5], "SOLVER");

    if(solver_type != 0 && solver_type != 1){
        cerr << "SOLVER must be 0 or 1" << endl;
        print_usage();
        exit(EXIT_FAILURE);
    }

    SolverType solver;
    if(solver_type == 0){
        solver = standard;
    } else {
        solver = custom;
    }

    cout << "----------------------------" << endl;
    cout << "Input file         - " << test_file << endl;
    cout << "Pattern directory  - " << pattern_dir << endl;
    cout << "Output directory   - " << output_dir << endl;
    cout << "Number of steps    - " << to_string(num_steps) << endl;
    cout << "Solver type        - " << to_string(solver_type) << endl;
    cout << "----------------------------" << endl;

    Application app = Application(test_file, output_dir, pattern_dir, num_steps);
    app.run(solver);

    return 0;
}
