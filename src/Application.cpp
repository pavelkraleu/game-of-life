//
// Created by Pavel Kral on 11/05/2021.
//

#include "Application.h"
#include "cellular_solver/BaseCellularSolver.h"
#include "image_loader/PNGImageLoader.h"
#include "cellular_solver/GoLCellularSolver.h"
#include "pattern_matcher/BasePatternMatcher.h"
#include "pattern_matcher/RandomExplodePatternMatcher.h"
#include "pattern_matcher/ColorizePatternMatcher.h"
#include <limits>

using namespace std;

Application::Application(string input_image, string output_directory, string & pattern_directory, int number_of_steps) : pattern_directory(pattern_directory), number_of_steps(number_of_steps), png_loader(input_image){
    if (!png_loader.load()) {
        cerr << "Unable to load file " << input_image << endl;
        exit(EXIT_FAILURE);
    }

    png_output = PNGOutputProcessor(output_directory, COLOR_ID);
}

void Application::run(SolverType solver_type) {
    BaseCellularSolver * solver = get_solver(solver_type);

    // Render initial state
    png_output.process_matrix(solver->get_matrix(), nullptr);

    if(number_of_steps < 0){
        number_of_steps = numeric_limits<int>::max();
    }

    for(int i=0; i<number_of_steps; i++){
        cout << "Step : " << to_string(i) << endl;

        const clock_t begin_time = clock();
        solver->next();
        png_output.process_matrix(solver->get_matrix(), solver->get_pattern_matrix());

        float total_time = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
        cout << "Processing time " << to_string(total_time) << " s" << endl;
    }

    delete solver;
}

BaseCellularSolver *Application::get_solver(SolverType solver_type) {
    vector<string> small_star_patterns = get_pattern_files("star_small", 2);
    vector<string> big_star_patterns = get_pattern_files("star_big", 2);

    vector<string> glider_a_patterns = get_pattern_files("glider_a", 4);
    vector<string> glider_b_patterns = get_pattern_files("glider_b", 4);
    vector<string> glider_c_patterns = get_pattern_files("glider_c", 4);
    vector<string> glider_d_patterns = get_pattern_files("glider_d", 4);

    vector<BasePatternMatcher *> explode_matchers = {
            new RandomExplodePatternMatcher(STAR_BIG_ID, 1, big_star_patterns),
            new RandomExplodePatternMatcher(STAR_SMALL_ID, 3, small_star_patterns)
    };

    vector<BasePatternMatcher *> colorize_matchers = {
            new ColorizePatternMatcher(GLIDER_ID_A, glider_a_patterns),
            new ColorizePatternMatcher(GLIDER_ID_B, glider_b_patterns),
            new ColorizePatternMatcher(GLIDER_ID_C, glider_c_patterns),
            new ColorizePatternMatcher(GLIDER_ID_D, glider_d_patterns),
            new ColorizePatternMatcher(STAR_SMALL_ID, small_star_patterns),
            new ColorizePatternMatcher(STAR_BIG_ID, big_star_patterns)
    };

    all_matchers = explode_matchers;
    all_matchers.insert(all_matchers.end(), colorize_matchers.begin(), colorize_matchers.end());

    if (solver_type == standard){
        cout << "Initializing standard Game of Life" << endl;
        return new GoLCellularSolver(png_loader.get_matrix(), colorize_matchers);
    } else if (solver_type == custom){
        cout << "Initializing custom Game of Life" << endl;
        return new GoLCellularSolver(png_loader.get_matrix(), all_matchers);
    } else {
        throw out_of_range("Unsupported solver type");
    }
}

vector<string> Application::get_pattern_files(const string & dir_name, size_t num_files) {
    vector<string> output;

    for(size_t i = 1; i <= num_files; i++){
        string dir = pattern_directory + "/" + dir_name + "/" + to_string(i)+ ".png";
        output.push_back(dir);
    }

    return output;
}

Application::~Application() {
    for(auto matcher: all_matchers){
        delete matcher;
    }
}
