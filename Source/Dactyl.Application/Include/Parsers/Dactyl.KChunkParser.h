#pragma once
#ifndef _Dactyl_KChunkParser_h_
#define _Dactyl_KChunkParser_h_

#include <vector>
#include "Dactyl.KData.h"
#include "Dactyl.KChunk.h"

namespace Dactyl::Application
{
    class KChunkParser
    {
        public:
            static bool parseChunks(const std::vector<std::shared_ptr<KChunk>>& inputChunks, Dactyl::Model::KData& kData);

        private:
            static void parseProperty(KChunk& inputChunk, Dactyl::Model::KData& kData);
            static void parseSection(KChunk& inputChunk, Dactyl::Model::KData& kData);
            static void parseMaterial(KChunk& inputChunk, Dactyl::Model::KData& kData);
            static void parseNode(KChunk& inputChunk, Dactyl::Model::KData& kData);
            static void parseElement(KChunk& inputChunk, Dactyl::Model::KData& kData);
    };
}

#endif /* _Dactyl.KChunkParser.h_ */