/*
    Author: Steve Ward
    Course: CSC 360 Operating Systems
    Project #5 Simulation of Page Replacement Strategies
    Due Date: 2025-07-13
    Instructor: Dr. Siming Liu
*/


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "pager.h"
/*
    Main Function:

    This function reads input from standard input, parses,the page reference string, frame count, and algorithm mnemonics.
    It then executes each selected page replacement algorithm and prints the number of page faults per algorithm.

    Return Value:
    -int  : Returns 0 on successful execution.

    Value Parameters:
    None

    Reference:
    None

    Local Variable Data Dictionary:
    -line : std::string : A string to hold each line of input.
    -page_refs : std::vector<int> : A vector to store the page reference string
    -num_frames : int : An integer to store the number of frames available.
    -algorithms : std::vector<std::string> : A vector to store the algorithm mnemonics.
*/
int main() {
    std::string line;
    std::vector<int> page_refs;
    int num_frames;
    std::vector<std::string> algorithms;
    // Read the first line: page reference string
    if (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        int num;
        while (iss >> num) {
            page_refs.push_back(num);
        }
    }
    // Read the second line: number of frames
    if (std::getline(std::cin, line)) {
        num_frames = std::stoi(line);
    }
    // Read the remaining lines: algorithm mnemonics
    while (std::getline(std::cin, line)) {
        if (!line.empty()) {
            algorithms.push_back(line);
        }
    }
    // Output the page reference string and number of frames
    std::cout << "Page Reference String:\n";
    for (size_t i = 0; i < page_refs.size(); ++i) {
        std::cout << page_refs[i] << " ";
        if ((i + 1) % 20 == 0) std::cout << "\n";
    }
    std::cout << "\nNumber of Frames: " << num_frames << "\n";
    //Execute selected algorithms
    for (const std::string& algo : algorithms) {
        int faults = 0;
        if (algo == "FIFO") {
            faults = fifo(page_refs, num_frames);
        } else if (algo == "LRU") {
            faults = lru(page_refs, num_frames);
        } else if (algo == "OPT") {
            faults = opt(page_refs, num_frames);
        } else if (algo == "RAND") {
            faults = rand_repl(page_refs, num_frames);
        } else {
            std::cerr << "Unknown algorithm: " << algo << "\n";
            continue;
        }
        std::cout << algo << ": " << faults << "\n";
    }

    return 0;
}
