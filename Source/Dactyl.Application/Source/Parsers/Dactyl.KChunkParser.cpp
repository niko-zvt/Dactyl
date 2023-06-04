#include "Dactyl.KChunkParser.h"
#include "Dactyl.KData.h"

using Dactyl::Model::KData;

namespace Dactyl::Application
{
    bool KChunkParser::parseChunks(const std::vector<std::shared_ptr<KChunk>>& inputChunks, KData* kData)
    {
        for(auto chunk : inputChunks)
        {           
            auto type = chunk->getType();
            
            if (type == "PART")
            {
                KChunkParser::parseProperty(*chunk, kData);
            }
            
            if (type == "SECTION_SHELL")
            {
                KChunkParser::parseSection(*chunk, kData);
            }

            if (type == "MAT_ELASTIC")
            {
                KChunkParser::parseMaterial(*chunk, kData);
            }

            if (type == "MAT_THERMAL_ISOTROPIC")
            {
                // Do nothing

                // MAP FOR *MAT_THERMAL_ISOTROPIC
                // +------+-----+-------+--------+---+---+---+---+
                // | TMID | TRO | TGRLC | TGMULT | - | - | - | - |
                // +------+-----+-------+--------+---+---+---+---+
                // | HC   | TC  | ----- | ------ | - | - | - | - |
                // +------+-----+-------+--------+---+---+---+---+
                
                // Card 1
                //
                // TMID     - id
                // TRO      - thermal density (structural density)
                // TGRLC    - thermal generation rate curve number
                // TGMULT   - thermal generation rate multiplier

                // Card 2
                // HC       - heat capacity
                // TC       - thermal conductivity
            }

            if (type == "NODE")
            {
                KChunkParser::parseNode(*chunk, kData);
            }

            if (type == "ELEMENT_SHELL")
            {
                KChunkParser::parseElement(*chunk, kData);
            }
            
            if(type == "END" || type == "KEYWORD" || type == "TITLE")
            {
                // Do nothing
            }
        }

        return true;
    }

    // Property Parser
    void KChunkParser::parseProperty(KChunk& inputChunk, KData* kData)
    {
        auto cards = inputChunk.getSubChunks();

        std::string head = "";
        int propertyID = -1;
        int sectionID = -1;
        int materialID = -1;
        int thermalMaterialID = -1;

        int cardIndex = 0;
        for(auto card : cards)
        {
            cardIndex++;

            auto type = card->getType();
            if (type != "DATA")
                continue;

            auto data = card->getData();
            auto values = Utils::split_string(data);

            // Card 1 - HEADING
            if(cardIndex == 1)
            {
                // MAP FOR CARD 1
                // HEADING - Heading for the part
                head = data;
            }

            // Card 2 - PID, SECID, MID, EOSID, HGID, GRAV, ADPOPT, TMID
            if(cardIndex == 2)
            {
                // MAP FOR CARD 2
                // PID      - Property ID (Part ID)
                // SECID    - Section ID
                // MID      - Material ID
                // EOSID    - Equation of state ID
                // HGID     - Hourglass/bulk viscosity ID
                // GRAV     - Gravity loading
                // ADPOPT   - Indicate if this part is adapted or not
                // TMID     - Thermal material ID

                // Check container
                int maxParams = 8;
                if (values.size() <= 0 || values.size() > maxParams)
                    continue;

                propertyID          = Utils::to_int(values[0]);
                sectionID           = Utils::to_int(values[1]);
                materialID          = Utils::to_int(values[2]);
                thermalMaterialID   = Utils::to_int(values[7]);
            }

            // Card 3, 4, ...
            if(cardIndex > 2)
            {
                // Do nothing
            }
        }

        Dactyl::Model::KProperty property = { head, propertyID, sectionID, materialID, thermalMaterialID };
        kData->insertProperty(property);
    }

    // Section Parser
    void KChunkParser::parseSection(KChunk& inputChunk, KData* kData)
    {
        auto cards = inputChunk.getSubChunks();

        int sectionID = -1;
        double thickness1 = 0.0;
        double thickness2 = 0.0;
        double thickness3 = 0.0;
        double thickness4 = 0.0;

        int cardIndex = 0;
        for(auto card : cards)
        {
            cardIndex++;
            
            auto type = card->getType();
            if (type != "DATA")
                continue;

            auto data = card->getData();
            auto values = Utils::split_string(data);
            
            // Card 1 - SECID, ELFORM, SHRF, NIP, PROPT, QR/IRID, ICOMP, SETYP
            if(cardIndex == 1)
            {
                // MAP FOR CARD 1
                // SECID    - Section ID
                // ELFORM   - Element formulation options
                // SHRF     - Shear corection factor
                // NIP      - Number of through thickness integration points
                // PROPT    - Printout option
                // QR/IRID  - Quadrature rule or Integration rule ID
                // ICOMP    - Flag for ortho-/anisotropic layered composite model
                // SETYP    - 2D solid element type

                // Check container
                int maxParams = 8;
                if (values.size() <= 0 || values.size() > maxParams)
                    continue;

                sectionID = Utils::to_int(values[0]);
            }

            // Card 2 - T1, T2, T3, T4, NLOC, MAREA
            if(cardIndex == 2)
            {
                // MAP FOR CARD 2
                // T1    - Thickness at Node 1
                // T2    - Thickness at Node 2
                // T3    - Thickness at Node 3
                // T4    - Thickness at Node 4
                // NLOC  - Location of reference surface
                // MAREA - Non-structural mass per unit area

                // Check container
                int maxParams = 8;
                if (values.size() <= 0 || values.size() > maxParams)
                    continue;

                thickness1 = Utils::to_double(values[0]);
                thickness2 = Utils::to_double(values[1]);
                thickness3 = Utils::to_double(values[2]);
                thickness4 = Utils::to_double(values[3]);
            }  
        
            // Card 3, 4, ... - B1, B2, B3, Bi, ...
            if(cardIndex > 2)
            {
                // MAP FOR CARD 3, 4, ...
                // Bi - Beta_{i}, material angle at i integration point
                
                // Do nothing
            }
        }

        Dactyl::Model::KSection section = { sectionID, thickness1, thickness2, thickness3, thickness4 };
        kData->insertSection(section);
    }

    // Material Parser
    void KChunkParser::parseMaterial(KChunk& inputChunk, KData* kData)
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
                auto axialDampingFactor     = Utils::to_double(values[4]);
                auto bendingDampingFactor   = Utils::to_double(values[5]);
                auto bulkModulus            = Utils::to_double(values[6]);

                auto materialType = "elastic_isotropic";
                auto materialName = "";

                Dactyl::Model::KMaterial material = { materialID, density, elasticModulus, poissonRatio, materialType, materialName };
                kData->insertMaterial(material);
            }
        }
    }
    
    // Node Parser
    void KChunkParser::parseNode(KChunk& inputChunk, KData* kData)
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

                Dactyl::Model::KNode node = { nodeID, xCoord, yCoord, zCoord };
                kData->insertNode(node);
            }
        }
    }

    // Element Parser
    void KChunkParser::parseElement(KChunk& inputChunk, KData* kData)
    {
        auto subChunks = inputChunk.getSubChunks();

        for(auto chunk : subChunks)
        {           
            auto type = chunk->getType();
            if (type == "DATA")
            {
                auto data = chunk->getData();
                auto values = Utils::split_string(data);

                const int maxParams = 10; // Max count of *ELEMENT_SHELL params

                // Check container
                if (values.size() <= 0 || values.size() > maxParams)
                    continue;

                // Element Mapping
                auto elementID = Utils::to_int(values[0]);
                auto propertyID = Utils::to_int(values[1]);
                auto node1 = Utils::to_int(values[2]);
                auto node2 = Utils::to_int(values[3]);
                auto node3 = Utils::to_int(values[4]);
                auto node4 = Utils::to_int(values[5]);

                Dactyl::Model::KElement element = { elementID, propertyID, node1, node2, node3, node4 };
                kData->insertElement(element);
            }
        }
    }
}
