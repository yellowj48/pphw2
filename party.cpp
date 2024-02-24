#include <iostream>
#include <thread>
#include <mutex>
#include <unordered_set>
#include <vector>

std::mutex mtx; // Mutex for protecting the showroom and visitedGuests set
bool showroomAvailable = true;
std::unordered_set<int> visitedGuests;

void attemptToShowroom(int guestId) {
    while (true) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            // Check if the guest has visited already
            if (visitedGuests.find(guestId) != visitedGuests.end()) {
                return; // Guest has already visited, no further attempts
            }
            if (showroomAvailable) {
                // Mark the showroom as busy and record the visit
                showroomAvailable = false;
                visitedGuests.insert(guestId);
                std::cout << "Guest " << guestId << " enters the showroom." << std::endl;
            } else {
                // The showroom is busy, try again later
                continue;
            }
        }
        // Simulate the visit duration
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Exiting the showroom
        {
            std::lock_guard<std::mutex> lock(mtx);
            showroomAvailable = true;
            std::cout << "Guest " << guestId << " exits the showroom." << std::endl;
        }
        break; // Exit the loop after visiting
    }
}

int main() {
    int n;
    std::cout << "Enter the number of guests: ";
    std::cin >> n;

    std::vector<std::thread> guests;
    for (int i = 1; i <= n; ++i) {
        guests.emplace_back(attemptToShowroom, i);
    }

    for (auto& guest : guests) {
        guest.join();
    }

    return 0;
}