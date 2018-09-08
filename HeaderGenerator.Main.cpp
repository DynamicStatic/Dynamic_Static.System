
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#define DYNAMIC_STATIC_CORE_GLM_DISABLED
#include "Dynamic_Static.Core.hpp"

#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class File final
{
public:
    std::vector<std::string> dstIncludes;
    std::vector<std::string> nonDstIncludes;
    std::vector<std::string> lines;

public:
    File(
        const std::string& filePath,
        bool skipNonDstIncludeExtraction
    )
    {
        bool pragmaOnceFound = false;
        for (const auto& line : dst::File::read_all_lines(filePath)) {
            if (line == "#pragma once") {
                pragmaOnceFound = true;
                continue;
            }
            if (pragmaOnceFound) {
                if (line.find("#include") != std::string::npos) {
                    if (line.find("Dynamic_Static/System/") != std::string::npos) {
                        auto include = dst::remove(dst::remove(line, "#include "), '"');
                        dstIncludes.push_back(include);
                    } else {
                        if (skipNonDstIncludeExtraction) {
                            lines.push_back(line);
                        } else {
                            nonDstIncludes.push_back(line);
                        }
                    }
                } else {
                    lines.push_back(line);
                }
            }
        }
        for (auto itr = lines.begin(); itr != lines.end(); ++itr) {
            if (itr->empty()) {
                auto jtr = itr + 1;
                while (jtr != lines.end() && jtr->empty()) {
                    lines.erase(jtr);
                    jtr = itr + 1;
                }
            }
        }
    }
};

void process_file(
    std::unordered_map<std::string, File>& unprocessedFiles,
    std::set<std::string>& processedFilePaths,
    std::vector<File>& processedFiles,
    const std::string& filePath,
    const File& file
)
{
    for (const auto& include : file.dstIncludes) {
        if (processedFilePaths.find(include) == processedFilePaths.end()) {
            auto dependency = unprocessedFiles.find(include);
            process_file(
                unprocessedFiles,
                processedFilePaths,
                processedFiles,
                dependency->first,
                dependency->second
            );
            if (processedFilePaths.insert(dependency->first).second) {
                processedFiles.push_back(dependency->second);
            }
        }
    }
    if (processedFilePaths.insert(filePath).second) {
        processedFiles.push_back(file);
    }
}

int main()
{
    static const std::set<std::string> ForceDefineSymbol {
        // "#define _USE_MATH_DEFINES"
    };
    static const std::set<std::string> SkipNonDstIncludeExtraction {
        // "Dynamic_Static/Core/Math/Defines.hpp",
        // "Dynamic_Static/Core/Memory.hpp",
        // "Dynamic_Static/Core/Win32LeanAndMean.hpp",
    };
    static const std::vector<std::string> ForceIncludeOrder {
        // "Dynamic_Static/Core/Defines.hpp",
        // "Dynamic_Static/Core/Math/Defines.hpp",
        // "Dynamic_Static/Core/Win32LeanAndMean.hpp",
        // "Dynamic_Static/Core/Memory.hpp",
    };
    std::ofstream dstSys(
        DYNAMIC_STATIC_SYSTEM_INCLUDE_DIRECTORY DYNAMIC_STATIC ".System.ex.hpp"
    );
    dstSys <<
R"(
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

)";
    for (const auto& symbol : ForceDefineSymbol) {
        dstSys << symbol << std::endl;
    }
    std::unordered_map<std::string, File> unprocessedFiles;
    std::set<std::string> stdIncludes;
    auto directoryPath = DYNAMIC_STATIC_SYSTEM_INCLUDE_DIRECTORY DYNAMIC_STATIC;
    for (const auto& directoryEntry : dst::filesystem::recursive_directory_iterator(directoryPath)) {
        if (dst::filesystem::is_regular_file(directoryEntry)) {
            std::string fullPath = directoryEntry.path().string();
            auto relativePath = dst::scrub_path(fullPath);
            relativePath = dst::remove(relativePath, DYNAMIC_STATIC_SYSTEM_INCLUDE_DIRECTORY);
            bool skipStdIncludeExtraction = SkipNonDstIncludeExtraction.find(relativePath) != SkipNonDstIncludeExtraction.end();
            auto& file = unprocessedFiles.insert({ relativePath, File(fullPath, skipStdIncludeExtraction) }).first->second;
            for (const auto& stdInclude : file.nonDstIncludes) {
                stdIncludes.insert(stdInclude);
            }
        }
    }
    for (const auto& stdInclude : stdIncludes) {
        dstSys << stdInclude << std::endl;
    }
    std::set<std::string> processedFilePaths;
    std::vector<File> processedFiles;
    for (const auto& filePath : ForceIncludeOrder) {
        auto itr = unprocessedFiles.find(filePath);
        processedFilePaths.insert(itr->first);
        processedFiles.push_back(itr->second);
    }
    for (auto itr : unprocessedFiles) {
        process_file(
            unprocessedFiles,
            processedFilePaths,
            processedFiles,
            itr.first,
            itr.second
        );
    }
    for (const auto& file : processedFiles) {
        bool populated = false;
        std::stringstream strStrm;
        for (const auto& line : file.lines) {
            if (ForceDefineSymbol.find(line) == ForceDefineSymbol.end()) {
                strStrm << line << std::endl;
            }
            if (!line.empty()) {
                populated = true;
            }
        }
        if (populated) {
            dstSys << strStrm.str();
        }
    }
    return 0;
}
