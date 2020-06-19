//
//  assetbundler.h
//  tomatenquark
//
//  Created by Lennard Berger on 28.03.20.
//

#ifndef assetbundler_h
#define assetbundler_h

#include <thread>
#include <chrono>
#include <regex>
#ifdef __GNUC__
#include <experimental/filesystem>
#else
#include <filesystem>
#endif

#ifdef __GNUC__
namespace fs = std::experimental::filesystem;
#else
namespace fs = std::filesystem;
#endif

#include <curl/curl.h>

/// Describes which status the download is currently in.
enum STATUS {
    DOWNLOAD_ABORTED = -1,
    DOWNLOAD_PROGRESS = 0,
    DOWNLOAD_FINISHED = 1
};

namespace assetbundler {
    /// Starts a download and returns the destination zip.
    ///
    /// Arguments
    /// - servercontent - the server that content will be downloaded from e.g http://localhost:8080
    /// - map - the map that will be downloaded e.g `curvedm`
    ///
    /// Call get_status continuously until the status is either ABORTED or FINISHED
    /// Downloads a map
    ///
    /// Arguments
    /// - servercontent (the URL to download from) e.g http://localhost:8000
    /// - map (the map to download) e.g curvedm
    /// - homedir (the home directory to download to)
    /// - status (a pointer to the status for async operations)
    /// - current (a pointer to the amount of currently downloaded files)
    /// - total (a pointer to the amount of total downloaded files)
    void download_map(char* servercontent, char* map, char* serverdir, int* status, int* current, int *total);
};

#endif /* assetbundler_h */
