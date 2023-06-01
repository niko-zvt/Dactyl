#pragma once
#ifndef _Dactyl_FEMLine_h_
#define _Dactyl_FEMLine_h_

#include "Dactyl.Utils.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Dactyl::Application
{
    class FEMLine
    {
        private:
            FEMLine() {};

            int Level;
            int Id;
            std::string Type;
            std::string Data;
            std::string Ref;

        public:
            const int getLevel() { return Level; };
            const int getID() { return Id; };
            std::string getType() { return Type; };
            std::string getData() { return Data; };
            std::string getRef() { return Ref; };

            FEMLine(int lvl, int id, std::string type, std::string data, std::string ref)
            {
                Level = lvl;
                Id = id;
                Type = type;
                Data = data;
                Ref = ref;
            };

            static std::shared_ptr<FEMLine> parse(int index, std::string line)
            {
                // Parse
                int level = 0;
                int id = index; 
                std::string type = "";
                std::string data = "";
                std::string ref = "";

                // 1. Split string
                auto words = Utils::split_string(line);

                // 2. Get first word and check it
                if (words.size() <= 0)
                    return nullptr;
                auto firstWord = words.front();

                // 3. Check first char
                if(firstWord.empty())
                    return nullptr;
                auto firstChar = firstWord.front();

                switch (firstChar)
                {
                case '*':
                    level = 0;
                    type = firstWord.erase(0, 1);
                    data = "";
                    break;
                
                case '$':
                    return nullptr;
                    break;
                    
                default:
                    level = 1;
                    id = index - 1;
                    type = "DATA";
                    for (const auto &piece : words) data += piece + " "; // Collect data
                    data.pop_back(); // Delete last ' ' char 
                    break;
                }

                auto l = std::make_shared<FEMLine>(level, id, type, data, ref);
                return l;
            }

            friend class FEMChunk;
            friend class FEMChunkLevels;
    };
}

#endif /* _Dactyl.FEMLine.h_ */