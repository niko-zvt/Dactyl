#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include "Dactyl.FileParser.h"
#include "Dactyl.KChunkParser.h"
#include "Dactyl.KResult.h"
#include "Dactyl.KLine.h"
#include "Dactyl.KChunk.h"

namespace Dactyl::Application
{

    bool FileParser::parseFile(const std::string& filePath, KResult* kResult)
    {
        std::vector<std::string> lines;
        std::ifstream file(filePath);
        std::string currentLine;

        while (std::getline(file, currentLine))
        {
            lines.push_back(currentLine);
        }

        auto result = parseLines(lines, kResult);
        return result;
    }

    bool FileParser::parseLines(const std::vector<std::string>& lines, KResult* kResult)
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

        auto result = parseKLines(kLines, kResult);
        return result;
    }   

    bool FileParser::parseKLines(const std::vector<KLine>& kLines, KResult* kResult)
    {
        KChunkSet chunks;
        bool result1 = getChunks(kLines, &chunks);
        bool result2 = KChunkParser::parseChunks(chunks.getChunks(), kResult);
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
