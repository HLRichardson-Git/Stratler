
#include "table.h"


std::vector<size_t> Table::calculateColumnWidths() const {
    std::vector<size_t> columnWidths;

    for (const auto& row : rows) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (columnWidths.size() <= i) {
                columnWidths.push_back(row[i].length());
            } else {
                columnWidths[i] = std::max(columnWidths[i], row[i].length());
            }
        }
    }

    return columnWidths;
}

std::string Table::toString(float value) const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << value;
    return oss.str();
}

void Table::addHeader(const std::string& header, const std::vector<std::string>& values) {
    std::vector<std::string> row;
    row.push_back(header);

    for (const auto& value : values) {
        row.push_back(value);
    }

    rows.push_back(row);
}

void Table::addRow(const std::string& header, const std::vector<float>& values) {
    std::vector<std::string> row;
    row.push_back(header);

    for (const auto& value : values) {
        row.push_back(toString(value));
    }

    rows.push_back(row);
}

void Table::print() const {
    std::vector<size_t> columnWidths = calculateColumnWidths();

    for (const auto& row : rows) {
        for (size_t i = 0; i < row.size(); ++i) {
            std::cout << std::setw(columnWidths[i] + 2) << std::left << row[i];
        }
        std::cout << std::endl;
    }
}