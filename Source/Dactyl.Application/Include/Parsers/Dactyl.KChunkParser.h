#pragma once
#ifndef _Dactyl_KChunkParser_h_
#define _Dactyl_KChunkParser_h_

#include <vector>
#include "Dactyl.KResult.h"
#include "Dactyl.KChunk.h"

namespace Dactyl::Application
{
    class KChunkParser
    {
        public:
            static KResult parseChunks(std::vector<std::shared_ptr<KChunk>>& inputChunks);

        private:
            static void parseProperty(KChunk& inputChunk, KResult& result);
            static void parseSection(KChunk& inputChunk, KResult& result);
            static void parseMaterial(KChunk& inputChunk, KResult& result);
            static void parseNode(KChunk& inputChunk, KResult& result);
            static void parseElement(KChunk& inputChunk, KResult& result);
    };
}

#endif /* _Dactyl.KChunkParser.h_ */