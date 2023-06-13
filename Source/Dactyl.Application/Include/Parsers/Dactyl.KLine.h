#pragma once
#ifndef _Dactyl_KLine_h_
#define _Dactyl_KLine_h_

#include "Dactyl.Utils.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Dactyl::Application
{
    class KLine
    {
        public:
            int getLevel()          { return Level; };
            int getID()             { return Id; };
            std::string getType()   { return Type; };
            std::string getData()   { return Data; };
            std::string getRef()    { return Ref; };

            KLine(int lvl, int id, std::string type, std::string data, std::string ref)
            {
                Level = lvl;
                Id = id;
                Type = type;
                Data = data;
                Ref = ref;
            };

            static std::shared_ptr<KLine> parse(int index, std::string line)
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

                auto l = std::make_shared<KLine>(level, id, type, data, ref);
                return l;
            }

        private:
            KLine() { /* Do nothing */ };

            int Level = -1;
            int Id = -1;
            std::string Type = "";
            std::string Data = "";
            std::string Ref = "";

            friend class KChunk;
            friend class KChunkLevels;
    };
}

#endif /* _Dactyl.KLine.h_ */