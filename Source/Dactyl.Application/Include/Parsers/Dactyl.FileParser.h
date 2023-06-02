#pragma once
#ifndef _Dactyl_FileParser_h_
#define _Dactyl_FileParser_h_

#include <string>
#include "Dactyl.KChunk.h"
#include "Dactyl.KLine.h"
#include "Dactyl.KResult.h"

namespace Dactyl::Application
{
    class FileParser
    {
        public:
            static KResult parseFromFile(std::string filePath);
            static KResult parseLines(std::vector<std::string> lines);
        
        private:
            static KResult parseKLines(const std::vector<KLine>& kLines);
            static bool getChunks(const std::vector<KLine>& femLines, KChunkSet& chunkSet);
    };
}

#endif /* _Dactyl.FileParser.h_ */