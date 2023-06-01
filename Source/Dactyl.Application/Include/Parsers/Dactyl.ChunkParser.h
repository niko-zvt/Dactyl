#pragma once
#ifndef _Dactyl_ChunkParser_h_
#define _Dactyl_ChunkParser_h_

#include <vector>
#include "Dactyl.ParserResult.h"
#include "Dactyl.FEMChunk.h"

namespace Dactyl::Application
{
    class ChunkParser
    {
        public:
            static ParserResult parseChunks(std::vector<std::shared_ptr<FEMChunk>>& inputChunks);
    };
}

#endif /* _Dactyl.ChunkParser.h_ */