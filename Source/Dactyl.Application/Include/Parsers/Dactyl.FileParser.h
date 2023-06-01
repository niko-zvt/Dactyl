#pragma once
#ifndef _Dactyl_FileParser_h_
#define _Dactyl_FileParser_h_

#include <string>
#include "Dactyl.FEMChunk.h"
#include "Dactyl.FEMLine.h"
#include "Dactyl.ParserResult.h"

namespace Dactyl::Application
{
    class FileParser
    {
        public:
            static ParserResult parseFromFile(std::string filePath);
            static ParserResult parseLines(std::vector<std::string> lines);
        
        private:
            static ParserResult parseFEMLines(const std::vector<FEMLine>& femLines);
            static bool FileParser::getChunks(const std::vector<FEMLine>& femLines, FEMChunkSet& chunkSet);
    };
}

#endif /* _Dactyl.FileParser.h_ */