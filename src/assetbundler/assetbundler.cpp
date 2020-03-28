#include <string>
#include <fstream>
#include <vector>

#include "assetbundler.h"

namespace assetbundler {
    /// Implements start_download functionality
    const char* start_download(char* servercontent, char* map) {
        return std::string("hey").c_str();
    }

    /// Implements get_status functionality
    int get_status(char* archive) {
        return -1;
    }
}
