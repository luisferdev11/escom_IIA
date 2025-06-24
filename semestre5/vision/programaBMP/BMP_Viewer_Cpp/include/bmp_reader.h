#ifndef BMP_READER_H
#define BMP_READER_H

#include "bmp.h"
#include <string>
#include <memory>

class BMPReader {
public:
    static std::unique_ptr<BMPImage> read(const std::string& filename);
};

#endif //BMP_READER_H 