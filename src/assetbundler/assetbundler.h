//
//  assetbundler.h
//  tomatenquark
//
//  Created by Lennard Berger on 28.03.20.
//

#ifndef assetbundler_h
#define assetbundler_h

namespace assetbundler {
    /// Describes which status the download is currently in.
    enum STATUS {
        ABORTED = -1,
        PROGRESS = 0,
        FINISHED = 1
    };

    /// Starts a download and returns the destination zip.
    ///
    /// Arguments
    /// - servercontent - the server that content will be downloaded from e.g http://localhost:8080
    /// - map - the map that will be downloaded e.g `curvedm`
    ///
    /// Call get_status continuously until the status is either ABORTED or FINISHED
    extern const char* start_download(char* servercontent, char* map);

    /// Returns the archive's download status.
    ///
    /// Arguments
    /// archive - the path of the archive
    extern int get_status(char* archive);
};

#endif /* assetbundler_h */
