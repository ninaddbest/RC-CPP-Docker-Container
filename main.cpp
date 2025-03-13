#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <string>
#include <sstream>
#include <stdexcept>

template<typename T>
std::vector<T> readDataFile(const std::string& filename, unsigned int& width, unsigned int& height) {
    std::ifstream file(filename);
    
    // Check if file is open
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file " + filename);
    }
    
    std::string line;
    
    // Read dimensions
    if (!std::getline(file, line)) {
        throw std::runtime_error("Error: File is empty or corrupted");
    }
    
    std::istringstream dim_stream(line);
    if (!(dim_stream >> width >> height)) {
        throw std::runtime_error("Error: Invalid dimensions format");
    }
    
    if (width <= 0 || height <= 0) {
        throw std::runtime_error("Error: Invalid dimensions. Width and height must be positive");
    }
    
    // Read number of data points
    if (!std::getline(file, line)) {
        throw std::runtime_error("Error: Missing data count");
    }
    
    size_t dataCount;
    try {
        dataCount = std::stoul(line);
    } catch (const std::exception&) {
        throw std::runtime_error("Error: Invalid data count format");
    }
    
    if (dataCount <= 0) {
        throw std::runtime_error("Error: Data count must be positive");
    }
    
    // Read data
    std::vector<T> data;
    data.reserve(dataCount);
    
    size_t lineCount = 0;
    while (std::getline(file, line) && lineCount < dataCount) {
        std::istringstream data_stream(line);
        
        if constexpr (std::is_same_v<T, std::complex<double>>) {
            // Handle complex data
            double real, imag;
            if (!(data_stream >> real >> imag)) {
                throw std::runtime_error("Error: Invalid complex number format at line " + 
                                          std::to_string(lineCount + 3));
            }
            data.push_back(std::complex<double>(real, imag));
        } else {
            // Handle real data
            T value;
            if (!(data_stream >> value)) {
                throw std::runtime_error("Error: Invalid number format at line " + 
                                          std::to_string(lineCount + 3));
            }
            data.push_back(value);
        }
        
        lineCount++;
    }
    
    // Check if we have the expected number of data points
    if (lineCount < dataCount) {
        throw std::runtime_error("Error: Insufficient data. Expected " + std::to_string(dataCount) + 
                                 " data points, but found only " + std::to_string(lineCount));
    }
    
    // Check if there's extra data
    if (std::getline(file, line)) {
        // There's more data than expected
        throw std::runtime_error("Error: File contains more data than specified");
    }
    
    return data;
}