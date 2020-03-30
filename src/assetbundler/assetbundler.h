//
//  assetbundler.h
//  tomatenquark
//
//  Created by Lennard Berger on 28.03.20.
//

#ifndef assetbundler_h
#define assetbundler_h

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
    void download_map(char* servercontent, char* map, char* homedir, int* status);
};

#endif /* assetbundler_h */
