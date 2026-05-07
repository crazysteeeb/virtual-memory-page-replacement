#ifndef PAGER_H
#define PAGER_H

#include <vector>
// Simulation of page replacement algorithms

int fifo(const std::vector<int>& pages, int frames);
int lru(const std::vector<int>& pages, int frames);
int opt(const std::vector<int>& pages, int frames);
int rand_repl(const std::vector<int>& pages, int frames);

#endif
