#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include "Dactyl.ContextLocator.h"
#include "Dactyl.FileParser.h"
#include "Dactyl.KChunkParser.h"
#include "Dactyl.KData.h"
#include "Dactyl.KLine.h"
#include "Dactyl.KChunk.h"

using Dactyl::Model::KData;

namespace Dactyl::Application
{
    bool FileParser::tryParseKFile(KData& kData)
    {
        // Get context
        Dactyl::Application::IContext& context = Dactyl::Application::ContextLocator::getContext();
        auto path = context.getPathToKFile();

        if(path.empty())
            return false;
        
        auto result = parseFile(path, kData);

        return result;
    }

    bool FileParser::parseFile(const std::string& filePath, KData& kData)
    {
        std::vector<std::string> lines;
        std::ifstream file(filePath);
        std::string currentLine;

        auto result = false;

        if (file.good())
        {
            while (std::getline(file, currentLine))
            {
                lines.push_back(currentLine);
            }
            result = parseLines(lines, kData);
        }

        return result;
    }

    bool FileParser::parseLines(const std::vector<std::string>& lines, KData& kData)
    {
        std::vector<KLine> kLines;

        int chunkID = 0;
        for (std::string line : lines)
        {
            auto kLine = KLine::parse(chunkID, line);
            
            if(kLine == nullptr)
                continue;

            if (kLine->getType() != "DATA" &&
                kLine->getData() == "")
            {
                ++chunkID;
            }

            kLines.push_back(*kLine);
        }

        auto result = parseKLines(kLines, kData);
        return result;
    }   

    bool FileParser::parseKLines(const std::vector<KLine>& kLines, KData& kData)
    {
        KChunkSet chunks;
        bool result1 = getChunks(kLines, &chunks);
        bool result2 = KChunkParser::parseChunks(chunks.getChunks(), kData);
        return result1 && result2;
    }
    
    bool FileParser::getChunks(const std::vector<KLine>& kLines, KChunkSet* chunkSet)
    {
        auto kChunkLevels = std::make_shared<KChunkLevels>();
        
        for(KLine kLine : kLines)
        {
            auto chunk = std::make_shared<KChunk>(kLine);

            if (kLine.getLevel() == 0)
            {
                chunkSet->insertChunk(chunk);
            }
            else
            {
                KChunkPtr parent = std::make_shared<KChunk>();
                parent = *(kChunkLevels->getParentChunk(&chunk));
                if(parent != nullptr)
                {
                    chunk->setParentChunk(&parent);
                    (*&parent)->insertSubChunk(&chunk);
                }
            }

            kChunkLevels->set(chunk);
        }

        return true;
    }
}
