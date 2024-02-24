#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> queue;
bool showroomAvailable = true;
int guestsToVisit;

void visitShowroom(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    queue.push(id);
    cv.wait(lock, [id] { return showroomAvailable && !queue.empty() && queue.front() == id; });
    
    // Entering showroom
    showroomAvailable = false;
    std::cout << "Guest " << id << " is viewing the vase." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate time spent in showroom
    
    // Exiting showroom
    showroomAvailable = true;
    queue.pop();
    std::cout << "Guest " << id << " has finished viewing the vase." << std::endl;
    lock.unlock();
    cv.notify_all();

    if (--guestsToVisit <= 0) {
        std::cout << "All guests have visited the showroom." << std::endl;
    }
}

int main() {
    int n;
    std::cout << "Enter the number of guests: ";
    std::cin >> n;
    guestsToVisit = n;

    std::vector<std::thread> threads;
    for (int i = 0; i < n; ++i) {
        threads.push_back(std::thread(visitShowroom, i + 1));
    }

    for (auto& th : threads) {
        th.join();
    }

    return 0;
}