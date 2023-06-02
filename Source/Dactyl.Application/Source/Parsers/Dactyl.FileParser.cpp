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

    KResult FileParser::parseFromFile(std::string filePath)
    {
        std::vector<std::string> lines;
        std::ifstream file(filePath);
        std::string currentLine;

        while (std::getline(file, currentLine))
        {
            lines.push_back(currentLine);
        }

        return parseLines(lines);
    }

    KResult FileParser::parseLines(std::vector<std::string> lines)
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

        return parseKLines(kLines);
    }   

    KResult FileParser::parseKLines(const std::vector<KLine>& kLines)
    {
        // Aliasing constructor for std::shared_ptr (Псевдонимный конструктор)
        // Some magic
        std::shared_ptr<KChunkSet> chunkSet(std::make_shared<KChunkSet>());
        std::shared_ptr<std::vector<std::shared_ptr<KChunk>>> link(chunkSet, &chunkSet->getChunks());
        auto isSuccsses = getChunks(kLines, *chunkSet);

        //if (chunkSet == nullptr)
        //{ 
        //    int i = 0;
        //    WTF?!
        //}

        if (link == nullptr)
        {
            int i = 0;
            // WTF^2 ?!
        }

        auto result = KChunkParser::parseChunks(*link);

        return result;
    }
    
    bool FileParser::getChunks(const std::vector<KLine>& kLines, KChunkSet& chunkSet)
    {
        auto kChunkLevels = std::make_shared<KChunkLevels>();
        
        for(KLine kLine : kLines)
        {
            auto chunk = std::make_shared<KChunk>(kLine);

            if (kLine.getLevel() == 0)
            {
                chunkSet.insertChunk(chunk);
            }
            else
            {
                auto parent = kChunkLevels->getParentChunk(chunk);
                if(parent != nullptr)
                {
                    chunk->setParentChunk(parent);
                    parent->getSubChunks().push_back(chunk);
                }
            }

            kChunkLevels->set(chunk);
        }

        return true;
    }
}
