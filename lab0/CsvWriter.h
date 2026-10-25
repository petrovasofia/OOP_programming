#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <string>
#include <vector>

class CsvWriter {
public:
    bool write(const std::string& outputFile,
               const std::string& header,
               const std::vector<std::string>& lines) const;
};

#endif