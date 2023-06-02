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
            static bool parseFile(const std::string& filePath, KResult* kResult);
            static bool parseLines(const std::vector<std::string>& lines, KResult* kResult);
        
        private:
            static bool parseKLines(const std::vector<KLine>& kLines, KResult* kResult);
            static bool getChunks(const std::vector<KLine>& femLines, KChunkSet* chunkSet);
    };
}

#endif /* _Dactyl.FileParser.h_ */