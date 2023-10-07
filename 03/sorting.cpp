#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#define SIZE 100

// Used code from https://sortingsearching.com/2015/09/26/radix-sort.html

void radix_sort(std::vector<int>& data) {
    constexpr int word_bits = std::numeric_limits<int>::digits;

    int max_bits = 1;
    while ((size_t(1) << (3 * (max_bits + 1))) <= data.size()) {
        ++max_bits;
    }
    const int num_groups = (word_bits + max_bits - 1) / max_bits;

    std::vector<size_t> count;
    std::vector<int> new_data(data.size());

    // current bit range
    for (int group = 0; group < num_groups; ++group) {
        const int start = group * word_bits / num_groups;
        const int end = (group+1) * word_bits / num_groups;
        const int mask = (size_t(1) << (end - start)) - int(1);

        // Count the values in the current bit range.
        count.assign(size_t(1) << (end - start), 0);
        for (const int &x : data) ++count[(x >> start) & mask];
        // Compute prefix sums in count.
        size_t sum = 0;
        for (size_t &c : count) {
            size_t new_sum = sum + c;
            c = sum;
            sum = new_sum;
        }
        // Shuffle data elements
        for (const int &x : data) {
            size_t &pos = count[(x >> start) & mask];
            new_data[pos++] = x;
        }

        // Move the data to the original array
        data.swap(new_data);
    }
}


int main(int argc, char **argv) {
    std::vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

    // Print table header
    std::cout << "n\tstd::sort\tradix_sort\tWinner" << std::endl;

    for (int n : sizes) {
        // Generate random data with a limited range
        std::vector<int> data(n);
        int max = n * 10; // Adjust the range to be favorable for radix_sort
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, max);
        for (int& i : data) {
            i = distr(gen);
        }

        // Measure std::sort time
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> stdSort = data;
        std::sort(stdSort.begin(), stdSort.end());
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds_sort = end - start;

        // Measure radix_sort time
        std::vector<int> radixSort = data;
        start = std::chrono::high_resolution_clock::now();
        radix_sort(radixSort);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds_sort2 = end - start;

        // Determine the winner
        std::string winner = (elapsed_seconds_sort2 < elapsed_seconds_sort) ? "radix_sort" : "std::sort";

        // Print results in tabular format
        std::cout << n << "\t" << elapsed_seconds_sort.count() << " s\t"
                  << elapsed_seconds_sort2.count() << " s\t" << winner << std::endl;
    }

    return 0;

}
