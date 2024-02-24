// Problem 1
#include <iostream>
#include <vector>
#include <atomic>
#include <mutex>
#include <cstdlib>
#include <ctime>

std::mutex mtx; // Mutex for protecting shared resources
std::vector<bool> hasEaten; // Tracks whether a guest has eaten a cupcake
std::atomic<int> cupcakeReplacements(0); // Counts the cupcake replacements by the designated guest
std::atomic<bool> cupcakeAvailable(true); // Tracks the availability of the cupcake
int n; // Number of guests

void visitLabyrinth(int id) {
    std::lock_guard<std::mutex> lock(mtx); // Ensure thread safety

    // Check if the guest is the designated cupcake replacer
    if (id == 0) {
        if (!cupcakeAvailable && cupcakeReplacements < n - 1) {
            cupcakeReplacements++;
            cupcakeAvailable = true;
            std::cout << "Guest " << id << " replaces the cupcake. Replacement count: " << cupcakeReplacements.load() << "\n";
        }
    } else {
        if (cupcakeAvailable && !hasEaten[id]) {
            hasEaten[id] = true;
            cupcakeAvailable = false;
            std::cout << "Guest " << id << " eats the cupcake.\n";
        } else if (!cupcakeAvailable) {
            std::cout << "Guest " << id << " finds the plate empty and leaves it as is.\n";
        }
    }
}

int main() {
    std::cout << "Enter the number of guests (N): ";
    std::cin >> n;

    hasEaten.resize(n, false);

    // Initialize random seed
    srand(static_cast<unsigned int>(time(0)));

    while (cupcakeReplacements < n - 1) {
        int selectedGuest = rand() % n; // Randomly select a guest
        visitLabyrinth(selectedGuest);
    }

    std::cout << "The simulation ends as all guests have visited the labyrinth at least once.\n";
    return 0;
}