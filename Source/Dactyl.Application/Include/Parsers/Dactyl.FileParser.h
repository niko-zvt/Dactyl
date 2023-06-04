#pragma once
#ifndef _Dactyl_FileParser_h_
#define _Dactyl_FileParser_h_

#include <string>
#include "Dactyl.KChunk.h"
#include "Dactyl.KLine.h"
#include "Dactyl.KData.h"

namespace Dactyl::Application
{
    class FileParser
    {
        public:
            static bool tryParseKFile(Dactyl::Model::KData* kData);
        
        private:
            static bool parseFile(const std::string& filePath, Dactyl::Model::KData* kData);
            static bool parseLines(const std::vector<std::string>& lines, Dactyl::Model::KData* kData);
            static bool parseKLines(const std::vector<KLine>& kLines, Dactyl::Model::KData* kData);

            static bool getChunks(const std::vector<KLine>& femLines, KChunkSet* chunkSet);
    };
}

#endif /* _Dactyl.FileParser.h_ */