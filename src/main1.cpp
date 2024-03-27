//##########################################################################################
//parser

#include "../include/scop.hpp"

int main(int argc, char **argv)
{
	std::vector<Vec> vec;
	// int i = 0;

	// Check if a filename was provided
    if (argc < 2) {
        std::cerr << "Please provide a filename as an argument.\n";
        return 1;
    }

    // Open the file
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

   // Read the file line by line
std::string line;
while (std::getline(file, line)) {
    // Check if the line starts with 'v'
    if (line.substr(0, 2) == "v ") {
        // Parse the line into x, y, z
        char* lineCStr = new char[line.length() + 1];
        std::strcpy(lineCStr, line.c_str());
        char* token = std::strtok(lineCStr, " ");
        if (token == nullptr) {
            std::cerr << "Failed to parse line: " << line << '\n';
            delete[] lineCStr;
            continue;
        }
        token = std::strtok(nullptr, " ");
        float x = std::stof(token ? token : "0");
        token = std::strtok(nullptr, " ");
        float y = std::stof(token ? token : "0");
        token = std::strtok(nullptr, " ");
        float z = std::stof(token ? token : "0");

        // Add the vertex to the vector
        vec.push_back(Vec(x, y, z));
        delete[] lineCStr;
    }
}

	std::cout << "Read " << vec.size() << " vertices.\n";
	std::cout << "vec.size = " << vec.size() << '\n';
	for (int i = 0; i < vec.size(); i++)
    	std::cout << vec[i] << '\n';
    return 0;
}