//
// Created by Pavel Kral on 11/05/2021.
//

#ifndef CPP_SEM_APPLICATION_H
#define CPP_SEM_APPLICATION_H


#include <iostream>
#include "cellular_solver/BaseCellularSolver.h"
#include "image_loader/PNGImageLoader.h"
#include "output_processor/PNGOutputProcessor.h"
#include "pattern_matcher/BasePatternMatcher.h"
#include "constants.h"

using namespace std;

class Application {
public:
    Application(string input_image, string output_directory, string & pattern_directory, int number_of_steps);
/**
 * Run the cellular automata
 * @param solver_type type of cellular automata
 */
    void run(SolverType solver_type);

    virtual ~Application();

private:
    const string pattern_directory;
    int number_of_steps;
    PNGImageLoader png_loader;
    PNGOutputProcessor png_output;
/**
 * Return prepared solver of given type
 * @param solver_type solver to prepare
 * @return solver
 */
    BaseCellularSolver * get_solver(SolverType solver_type);
/**
 * Helper method to generate list of paths to pattern images
 * @param dir_name name of the pattern
 * @param num_files number of files to be generated
 * @return generated paths
 */
    vector<string> get_pattern_files(const string & dir_name, size_t num_files);
    vector<BasePatternMatcher *> all_matchers;
};


#endif //CPP_SEM_APPLICATION_H
