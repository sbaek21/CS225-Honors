import matplotlib.pyplot as plt

# Input sizes
sizes = [10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000]

# Execution times for std::sort (replace with actual data)
std_sort_times = [3.292e-06, 4.167e-06, 4.7458e-05, 0.000661166, 0.00896088, 0.0482429, 0.567945, 6.59429]

# Execution times for radix_sort (replace with actual data)
radix_sort_times = [3.7125e-05, 8.2917e-05, 0.000507375, 0.00344888, 0.0145286, 0.0710429, 0.620731, 5.22024]

# Calculate performance ratios
performance_ratios = [std_time / radix_time for std_time, radix_time in zip(std_sort_times, radix_sort_times)]

# Create a line chart
plt.plot(sizes, performance_ratios, marker='o', linestyle='-')
plt.xlabel("Input Size")
plt.ylabel("Performance Ratio (std_sort / radix_sort)")
plt.title("Relative Performance of std::sort vs. radix_sort")
plt.grid(True)

# Show the chart
plt.show()