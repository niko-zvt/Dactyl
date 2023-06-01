#include "Dactyl.ChunkParser.h"
#include "Dactyl.ParserResult.h"

namespace Dactyl::Application
{
    ParserResult ChunkParser::parseChunks(std::vector<std::shared_ptr<FEMChunk>>& inputChunks)
    {
        auto result = std::make_shared<ParserResult>();

        for(auto chunk : inputChunks)
        {           
            auto type = chunk->getType();
            
            if (type == "PART")
            {

            }
            
            if (type == "SECTION_SHELL")
            {

            }

            if (type == "MAT_ELASTIC")
            {

            }

            if (type == "NODE")
            {

            }

            if (type == "ELEMENT_SHELL")
            {

            }
            
            if(type == "END" || type == "MAT_THERMAL_ISOTROPIC" || 
               type == "KEYWORD" || type == "TITLE")
            {

            }

        }

        return *result;
    }
}
