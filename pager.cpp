#include "pager.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>

/*
    FIFO (First In First Out) Page Replacement Algorithm

    This function simulates the FIFO page replacement algorithm.
    It tracks which pages were loaded first and evicts the oldest page when a new page needs to be loaded.

    Return Value:
    -int  : The number of page faults that occurred during the simulation.

    Value Parameters:
    -Page : std::vector<int> : A vector containing the sequence of page references.
    -Frames : int : The number of frames available in memory.

    Reference:
    none

    Local Variable Data Dictionary:
    -memory : std::unordered_set<int> : A set to keep track of currently loaded
    order : std::queue<int> : A queue to maintain the order of page loading
    faults : int : Counter for the number of page faults
*/
int fifo(const std::vector<int>& pages, int frames) {
    std::unordered_set<int> memory;
    std::queue<int> order;
    int faults = 0;

    for (int page : pages) {
        if (memory.find(page) == memory.end()) {
            faults++;
            if (memory.size() == frames) {
                memory.erase(order.front());
                order.pop();
            }
            memory.insert(page);
            order.push(page);
        }
    }
    return faults;
}
/*
    LRU (Least Recently Used) Page Replacement Algorithm

    This function simulates the LRU page replacement algorithm.
    It keeps track of the last used time of each page and evicts the least recently used page when a new page needs to be loaded.

    Return Value:
    -int  : The number of page faults that occurred during the simulation.

    Value Parameters:
    -Page : std::vector<int> : A vector containing the sequence of page references.
    -Frames : int : The number of frames available in memory.

    Reference:
    none

    Local Variable Data Dictionary:
    -memory : std::unordered_set<int> : A set to keep track of currently loaded
    -last_used : std::unordered_map<int, int> : A map to track the
    -faults : int : Counter for the number of page faults
*/
int lru(const std::vector<int>& pages, int frames) {
    std::unordered_set<int> memory;
    std::unordered_map<int, int> last_used;
    int faults = 0;

    for (int i = 0; i < pages.size(); ++i) {
        int page = pages[i];
        if (memory.find(page) == memory.end()) {
            faults++;
            if (memory.size() == frames) {
                int lru_page = *memory.begin();
                for (int m : memory) {
                    if (last_used[m] < last_used[lru_page]) {
                        lru_page = m;
                    }
                }
                memory.erase(lru_page);
            }
            memory.insert(page);
        }
        last_used[page] = i;
    }
    return faults;
}
/*
    OPT (Optimal Page Replacement Algorithm)

    This function simulates the Optimal page replacement algorithm.
    It replaces the page that will not be used for the longest period of time in the future
    It always evicts the page that will not be used for the longest time in the future.

    Return Value:
    -int  : The number of page faults that occurred during the simulation.

    value Parameters:
    -Page : std::vector<int> : A vector containing the sequence of page references.
    -Frames : int : The number of frames available in memory.

    Reference:
    none

    Local Variable Data Dictionary:
    -memory : std::unordered_set<int> : A set to keep track of currently loaded
    -farthest : int : The farthest distance a page is used in the future
    -victim : int : The page that will be replaced
    -faults : int : Counter for the number of page faults
*/
int opt(const std::vector<int>& pages, int frames) {
    std::unordered_set<int> memory;
    int faults = 0;

    for (int i = 0; i < pages.size(); ++i) {
        int page = pages[i];
        if (memory.find(page) == memory.end()) {
            faults++;
            if (memory.size() == frames) {
                int farthest = -1, victim = -1;
                for (int m : memory) {
                    auto it = std::find(pages.begin() + i + 1, pages.end(), m);
                    int dist = (it == pages.end()) ? INT_MAX : it - pages.begin();
                    if (dist > farthest) {
                        farthest = dist;
                        victim = m;
                    }
                }
                memory.erase(victim);
            }
            memory.insert(page);
        }
    }
    return faults;
}
/*
    RAND (Random Page Replacement Algorithm)

    This function simulates the Random page replacement algorithm.
    It randomly selects a page to evict when a new page needs to be loaded.

    Return Value:
    -int  : The number of page faults that occurred during the simulation.

    Value Parameters:
    -Page : std::vector<int> : A vector containing the sequence of page references.
    -Frames : int : The number of frames available in memory.

    Reference:
    none

    Local Variable Data Dictionary:
    -memory : std::vector<int> : A vector to keep track of currently loaded pages
    -faults : int : Counter for the number of page faults
    -victim_index : int : Index of the page to be replaced 
*/
int rand_repl(const std::vector<int>& pages, int frames) {
    std::srand(std::time(nullptr));
    std::vector<int> memory;
    int faults = 0;

    for (int page : pages) {
        if (std::find(memory.begin(), memory.end(), page) == memory.end()) {
            faults++;
            if (memory.size() == frames) {
                int victim_index = std::rand() % frames;
                memory[victim_index] = page;
            } else {
                memory.push_back(page);
            }
        }
    }
    return faults;
}
