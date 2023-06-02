#include "Dactyl.KChunkParser.h"
#include "Dactyl.KResult.h"

namespace Dactyl::Application
{
    KResult KChunkParser::parseChunks(std::vector<std::shared_ptr<KChunk>>& inputChunks)
    {
        KResult result;

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
                KChunkParser::parseMaterial(*chunk, result);
            }

            if (type == "NODE")
            {
                KChunkParser::parseNode(*chunk, result);
            }

            if (type == "ELEMENT_SHELL")
            {

            }
            
            if(type == "END" || type == "MAT_THERMAL_ISOTROPIC" || 
               type == "KEYWORD" || type == "TITLE")
            {
                // Do nothing
            }
        }

        return result;
    }

    // Material Parser
    void KChunkParser::parseMaterial(KChunk& inputChunk, KResult& result)
    {
        auto subChunks = inputChunk.getSubChunks();

        for(auto chunk : subChunks)
        {           
            auto type = chunk->getType();
            if (type == "DATA")
            {
                auto data = chunk->getData();
                auto values = Utils::split_string(data);
                
                const int maxParams = 7; // Max count of *MAT_ELASTIC params

                // Check container
                if (values.size() <= 0 || values.size() > maxParams)
                    continue;

                // Elastic Material Params Mapping
                // Hard code mapping (*MAT_ELASTIC or MAT1/MAT4) 
                auto materialID             = Utils::to_int(values[0]);
                auto density                = Utils::to_double(values[1]);
                auto elasticModulus         = Utils::to_double(values[2]);
                auto poissonRatio           = Utils::to_double(values[3]);
                //auto axialDampingFactor     = Utils::to_double(values[4]);
                //auto bendingDampingFactor   = Utils::to_double(values[5]);
                //auto bulkModulus            = Utils::to_double(values[6]);

                KMaterial material = { materialID, density, elasticModulus, poissonRatio };
                result.setMaterial(material);
            }
        }
    }
    
    // Node Parser
    void KChunkParser::parseNode(KChunk& inputChunk, KResult& result)
    {
        auto subChunks = inputChunk.getSubChunks();

        for(auto chunk : subChunks)
        {           
            auto type = chunk->getType();
            if (type == "DATA")
            {
                auto data = chunk->getData();
                auto values = Utils::split_string(data);

                const int maxParams = 6; // Max count of *NODE params

                // Check container
                if (values.size() <= 0 || values.size() > maxParams)
                    continue;

                // Node Mapping
                auto nodeID = Utils::to_int(values[0]);
                auto xCoord = Utils::to_double(values[1]);
                auto yCoord = Utils::to_double(values[2]);
                auto zCoord = Utils::to_double(values[3]);

                KNode node = { nodeID, xCoord, yCoord, zCoord };
                result.setNode(node);
            }
        }
    }


}
