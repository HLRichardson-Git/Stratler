#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <type_traits>

class Table {
private:
    std::vector<std::vector<std::string>> rows;

    // Function to calculate the maximum width of each column
    std::vector<size_t> calculateColumnWidths() const;

    // Utility function to convert a float to a string with fixed precision
    std::string toString(float value) const;

public:
    // Function to add a row to the table
    void addHeader(const std::string& header, const std::vector<std::string>& values);
    void addRow(const std::string& header, const std::vector<float>& values);

    // Function to print the table
    void print() const;
};