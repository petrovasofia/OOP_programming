#include <iostream>
#include "FileReader.h"
#include "WordSorter.h"
#include "CsvWriter.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0]
                  << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    const std::string inputFile  = argv[1];
    const std::string outputFile = argv[2];

    FileReader reader;
    if (!reader.read(inputFile)) {
        return 1;
    }

    WordSorter sorter;
    sorter.sort(reader.getWordFrequency());

    CsvWriter writer;
    if (!writer.write(outputFile, sorter.getSortedWords(), reader.getTotalWords())) {
        return 1;
    }

    std::cout << "Total words: " << reader.getTotalWords()
              << ", unique: " << reader.getWordFrequency().size() << std::endl;
    return 0;
}