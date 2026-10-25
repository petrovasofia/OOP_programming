#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "FileReader.h"
#include "WordCounter.h"
#include "WordSorter.h"
#include "CsvWriter.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    const std::string inputFile  = argv[1];
    const std::string outputFile = argv[2];

    FileReader reader;
    std::vector<std::string> words = reader.readWords(inputFile);
    if (words.empty()) {
        std::cerr << "No words found or file couldn't be read." << std::endl;
        return 1;
    }

    WordCounter counter;
    auto frequencies = counter.countWords(words);

    int totalWords = words.size();

    WordSorter sorter;
    auto sortedWords = sorter.sort(frequencies);

    std::vector<std::string> csvLines;
    for (const auto& pair : sortedWords) {
        double percent = totalWords > 0 ? 100.0 * pair.second / totalWords : 0.0;

        std::ostringstream oss;
        oss << pair.first << "," << pair.second << "," << percent;
        csvLines.push_back(oss.str());
    }

    CsvWriter writer;
    std::string header = "Word,Frequency,Frequency (%)";
    if (!writer.write(outputFile, header, csvLines)) {
        return 1;
    }

    std::cout << "Total words: " << totalWords
              << ", unique: " << frequencies.size() << std::endl;
    return 0;
}