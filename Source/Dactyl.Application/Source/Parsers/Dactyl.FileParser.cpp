#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include "Dactyl.FileParser.h"
#include "Dactyl.ChunkParser.h"
#include "Dactyl.ParserResult.h"
#include "Dactyl.FEMLine.h"
#include "Dactyl.FEMChunk.h"

namespace Dactyl::Application
{

    ParserResult FileParser::parseFromFile(std::string filePath)
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

    ParserResult FileParser::parseLines(std::vector<std::string> lines)
    {
        std::vector<FEMLine> femLines;

        int chunkID = 0;
        for (std::string line : lines)
        {
            auto femLine = FEMLine::parse(chunkID, line);
            
            if(femLine == nullptr)
                continue;

            if (femLine->getType() != "DATA" &&
                femLine->getData() == "")
            {
                ++chunkID;
            }

            femLines.push_back(*femLine);
        }

        return parseFEMLines(femLines);
    }   

    ParserResult FileParser::parseFEMLines(const std::vector<FEMLine>& femLines)
    {
        // Aliasing constructor for std::shared_ptr (Псевдонимный конструктор)
        // Some magic
        std::shared_ptr<FEMChunkSet> chunkSet(std::make_shared<FEMChunkSet>());
        std::shared_ptr<std::vector<std::shared_ptr<FEMChunk>>> link(chunkSet, &chunkSet->getChunks());
        auto isSuccsses = getChunks(femLines, *chunkSet);

        if (chunkSet == nullptr)
        { 
            int i = 0;
            // WTF?!
        }

        if (link == nullptr)
        {
            int i = 0;
            // WTF^2 ?!
        }

        auto result = ChunkParser::parseChunks(*link);

        return result;
    }
    
    bool FileParser::getChunks(const std::vector<FEMLine>& femLines, FEMChunkSet& chunkSet)
    {
        auto femChunkLevels = std::make_shared<FEMChunkLevels>();
        
        for(FEMLine femLine : femLines)
        {
            auto chunk = std::make_shared<FEMChunk>(femLine);

            if (femLine.getLevel() == 0)
            {
                chunkSet.insertChunk(chunk);
            }
            else
            {
                auto parent = femChunkLevels->getParentChunk(chunk);
                if(parent != nullptr)
                {
                    chunk->setParentChunk(parent);
                    parent->getSubChunks().push_back(chunk);
                }
            }

            femChunkLevels->set(chunk);
        }

        return true;
    }
}
