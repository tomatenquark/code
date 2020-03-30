#include <fstream>
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <sstream>
#include <map>
#ifdef __linux__ 
#include <experimental/filesystem>
#else
#include <filesystem>
#endif

#include <curl/curl.h>

#include "assetbundler.h"

#ifdef __linux__ 
namespace fs = std::experimental::filesystem;
#else
namespace fs = std::filesystem;
#endif

namespace download {
    // Writes data from stream to disk
    static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
        return fwrite(ptr, size, nmemb, (FILE *) stream);
    }

    // Downloads a file using curl_easy_setup
    void download_file(std::string url, fs::path destination) {
        if (!fs::exists(destination)) {
            /* open the file */
            auto resource = fopen((const char*)destination.c_str(), "wb");

            /* init the curl session */
            auto curl_handle = curl_easy_init();

            /* set URL to get here */
            curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());

            /* Switch on full protocol/debug output while testing */
            curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

            /* send all data to this function  */
            curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

            if (resource) {
                /* write the page body to this file handle */
                curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, resource);

                /* get it! */
                curl_easy_perform(curl_handle);

                /* close the header file */
                fclose(resource);
            }

            /* cleanup curl stuff */
            curl_easy_cleanup(curl_handle);
        }
    }
};

namespace config {
    using namespace std;

    /// Whitelist contains all valid ICOMMAND instructions in map configs
    array<const string, 82> command_whitelist = {
        "ambient",
        "autograss",
        "base_1",
        "base_10",
        "base_2",
        "base_3",
        "base_4",
        "base_5",
        "base_6",
        "base_7",
        "base_8",
        "base_9",
        "blurlms",
        "blurskylight",
        "causticmillis",
        "causticscale",
        "cloudalpha",
        "cloudbox",
        "cloudboxcolour",
        "cloudcolour",
        "cloudfade",
        "cloudheight",
        "cloudlayer",
        "cloudscale",
        "cloudscrollx",
        "cloudscrolly",
        "exec",
        "fog",
        "fogcolour",
        "fogdomecap",
        "fogdomeclip",
        "fogdomeclouds",
        "fogdomecolour",
        "fogdomeheight",
        "fogdomemax",
        "fogdomemin",
        "grassalpha",
        "lightprecision",
        "lmshadows",
        "loadsky",
        "mapmodel",
        "mapmodelreset",
        "mapmsg",
        "mapsound",
        "maptitle",
        "minimapclip",
        "minimapcolour",
        "minimapheight",
        "mmodel",
        "mmodelfile",
        "setshader",
        "setshaderparam",
        "shadowmapambient",
        "shadowmapangle",
        "skybox",
        "skyboxcolour",
        "skylight",
        "skytexture",
        "skytexturelight",
        "spinclouds",
        "spinsky",
        "sunlight",
        "sunlightpitch",
        "sunlightscale",
        "sunlightyaw",
        "texalpha",
        "texcolor",
        "texffenv",
        "texlayer",
        "texoffset",
        "texrotate ",
        "texscale",
        "texscroll",
        "texture",
        "texturereset",
        "water2colour",
        "water2fog",
        "watercolour",
        "waterfallcolour",
        "waterfog",
        "waterspec",
        "yawsky"
    };

    /// Maps the relation between ICOMMAND and the parameters it takes (file path)
    map<const string, int> command_mapping = {
        {"texture", 2},
        {"mmodelfile", 1},
        {"mapsound", 1},
        {"skybox", 1},
        {"exec", 1},
        {"cloudlayer", 1}
    };

    /// Check for any characters before processing the line
    std::regex bad_characters("(;|\\(|\\[)");

    /// A config resource is represented by a property and a path.
    struct Resource {
        string command;
        string path;
    };

    /// Reads a config file returns it's resources.
    void parse_lines(vector<string> *in, vector<Resource> *out) {
        for (const auto& line: *in) {
            // Skip empty lines
            if (line.empty()) continue;

            // Split string up
            vector<string> fields;
            istringstream line_stream(line);
            copy(istream_iterator<std::string>(line_stream), istream_iterator<string>(), back_inserter(fields));

            // Check if command is a resource
            string& command = fields.at(0);
            if (command_mapping.find(command) != command_mapping.end()) {
                int& commandIndex = command_mapping.at(command);
                // Check if command is valid
                if ((fields.size() - 1) >= commandIndex) {
                    string path = fields.at(commandIndex);
                    // Replace leading and trailing " characters
                    path.erase(remove(path.begin(), path.end(), '\"'), path.end());
                    out->push_back(Resource{command, path});
                }
            }
        }
    }

    /// Filters the lines of a configuration and removes lines not on the command_whitelist or bad lines.
    void filter_lines(vector<string> *in, vector<string> *out) {
        copy_if(in->begin(), in->end(), back_inserter(*out), [](const string& line) {
           return (!regex_search(line, bad_characters) && (
              line.empty() ||
              line.rfind("//", 0) == 0 ||
              any_of(command_whitelist.begin(), command_whitelist.end(), [&line](const string& command) {
                  return line.rfind(command, 0) == 0;
              })
           ));
        });
    }
};

namespace resources {
    /// Downloads and filters a config file and inserts it's resources to the specified resources vector
    void download_and_filter_config(std::string config_url, fs::path destination, std::vector<config::Resource>* resources) {
        // Create a temporary file path
        fs::path temp_config_path(fs::temp_directory_path());
        char buffer [L_tmpnam];
        std::tmpnam(buffer);
        std::string tmpnam(buffer);
        temp_config_path.append(tmpnam);
        // Download config file to this temporary path
        download::download_file(config_url, temp_config_path.string());
        // Read the config file
        std::ifstream config_file (temp_config_path.string());
        std::vector<std::string> lines;
        std::string line;
        if (config_file.is_open())
        {
            while ( std::getline (config_file, line) ) lines.push_back(line);
            config_file.close();
        }
        // Filter config and append it's resources
        std::vector<std::string> filtered_lines;
        config::filter_lines(&lines, &filtered_lines);
        config::parse_lines(&filtered_lines, resources);
        // Write the filtered file to disk
        std::ofstream filtered_config_file(destination);
        fs::create_directories(destination.parent_path());
        for (const auto& l: filtered_lines) filtered_config_file << l << std::endl;
        //filtered_config_file.close(); // This prevents writing some configs to disk. Figure out why.
    }

    /// Returns all configs from a resource vector
    void get_configs(std::vector<config::Resource>* in, std::vector<config::Resource>* out) {
        copy_if(in->begin(), in->end(), back_inserter(*out), [](const config::Resource& resource) {
            return resource.command == "exec";
        });
    }

    /// Iterates through all the config files found in name and adds their resources respectively.
    void collect(std::string url, std::string name, std::vector<config::Resource>* resources, fs::path server_directory) {
        std::stringstream start_url;
        start_url << url << "/packages/base/" << name << ".cfg";
        fs::path start_path(server_directory);
        start_path.append("packages/base/");
        name.append(".cfg");
        start_path.append(name);
        fs::create_directories(start_path.parent_path());
        download_and_filter_config(start_url.str(), start_path, resources);

        std::vector<config::Resource> configs;
        std::vector<std::string> processed_configs;
        // Get configs declared in map config
        get_configs(resources, &configs);

        while (!configs.empty()) {
            // Pop the config from configs "stack"
            auto config = configs.back();
            configs.pop_back();
            // Never process a config twice
            if (std::any_of(processed_configs.begin(), processed_configs.end(), [&config](const std::string& conf) {
                return conf == config.path;
            })) continue;
            // Remove the config from the resources otherwise it will be overwritten
            std::remove_if(resources->begin(), resources->end(), [&config](const config::Resource& resource) {
                return resource.path == config.path;
            });
            // Create URL and destination
            std::stringstream config_url;
            config_url << url << "/" << config.path;
            fs::path config_path(server_directory);
            config_path.append(config.path);
            // Download and repeat the process
            std::vector<config::Resource> config_resources;
            download_and_filter_config(config_url.str(), config_path, &config_resources);
            get_configs(&config_resources, &configs);
            processed_configs.push_back(config.path);
            std::copy(config_resources.begin(), config_resources.end(), std::back_inserter(*resources));
        }
        // TODO: Set status to aborted if there are no resources
    }

    std::string get_command_prefix(std::string command) {
        std::string prefix = "packages";
        if (command == "map") prefix.append("/base");
        if (command == "mapsound") prefix.append("/sounds");
        if (command == "mmodelfile") prefix.append("/models");
        return prefix;
    }

    /// Download all the resources to their specified paths
    void download(std::string url, fs::path server_directory, std::vector<config::Resource> resources, int* status) {
        for (const auto& resource: resources) {
            std::stringstream resource_url;
            std::string prefix = get_command_prefix(resource.command);
            resource_url << url << "/" << prefix << "/" << resource.path;
            fs::path resource_path(server_directory);
            resource_path.append(prefix);
            resource_path.append(resource.path);
            fs::create_directories(resource_path.parent_path());
            download::download_file(resource_url.str(), resource_path);
        }
        // NOTE: CAUTION This is not thread-safe and should not be attempted with multiple calls to download
        *status = DOWNLOAD_FINISHED;
    }
};

namespace assetbundler {
    /// Implementation for download_map
    void download_map(char* servercontent, char* map, char* serverdir, int* status) {
        // Prepare download paths
        std::string url(servercontent);
        // TODO: Remove trailing comma if there are any
        std::string server_map(map);
        std::string server_directory(serverdir);
        // Initialize resources vector
        std::vector<config::Resource> resources;
        // NOTE: This assumes that curl_global_init has already been called
        // Collects all the resources from the map
        resources::collect(url, map, &resources, server_directory);
        // If there are no resources something went wrong with the download. Abort
        if (resources.empty()) {
            *status = DOWNLOAD_ABORTED;
            return;
        }
        // Add missing map files
        std::array<std::string, 3> map_resources = {"ogz", "wpt", "jpg"};
        server_map += ".";
        for (const auto& map_resource: map_resources) resources.push_back(config::Resource{"map", server_map + map_resource});
        // Start download in a dedicated thread
        std::thread download_thread(resources::download, url, server_directory, resources, status);
        download_thread.detach();
        *status = DOWNLOAD_PROGRESS;
    }
};
