#pragma once
#ifndef _Dactyl_FEMChunk_h_
#define _Dactyl_FEMChunk_h_

#include <map>
#include <string>
#include <vector>
#include "Dactyl.FEMLine.h"

namespace Dactyl::Application
{
    class FEMChunk
    {
        public:
            FEMChunk(FEMLine femLine)
            {
                _level = femLine.Level;
                _id = femLine.Id;
                _data = femLine.Data;
                _type = femLine.Type;
                _ref = femLine.Ref;
                _parent = nullptr;
            };

            void setParentChunk(std::shared_ptr<FEMChunk>& parent)
            {
                _parent = parent;
            };

            int getLevel()
            { 
                return _level;
            };

            int getID()
            { 
                return _id;
            };

            std::string getType()
            {
                return _type;
            };

            std::string getData()
            {
                return _data;
            };

            std::string Ref()
            {
                return _ref;
            };

            std::vector<std::shared_ptr<FEMChunk>>& getSubChunks()
            {
                return _subChunks;
            };

        private:
            int _level = -1;
            int _id = -1;
            std::string _type = "";
            std::string _data = "";
            std::string _ref = "";
            std::shared_ptr<FEMChunk> _parent;
            std::vector<std::shared_ptr<FEMChunk>> _subChunks;
    };

    class FEMChunkSet
    {
        public:
            FEMChunkSet() {};

            std::vector<std::shared_ptr<FEMChunk>>& getChunks()
            {
                return _chunks;
            };

            void insertChunk(const std::shared_ptr<FEMChunk>& chunk)
            {
                _chunks.push_back(chunk);
            };

        private:
            std::vector<std::shared_ptr<FEMChunk>> _chunks;
    };

    class FEMChunkLevels
    {
        public:
            void set(std::shared_ptr<FEMChunk>& femChunk)
            {
                auto level = femChunk->getLevel();
                auto iter = currentLevelChunks.find(level);
                if(iter != currentLevelChunks.end())
                {
                    currentLevelChunks.erase(iter);
                }
                currentLevelChunks.insert({level, femChunk});
            };

            std::shared_ptr<FEMChunk>& getParentChunk(std::shared_ptr<FEMChunk>& femChunk)
            {
                auto level = femChunk->getLevel();
                auto chunk = currentLevelChunks[level - 1];
                return chunk;
            };

        private:
            std::map<int, std::shared_ptr<FEMChunk>> currentLevelChunks;
    };
}

#endif /* _Dactyl.FEMChunk.h_ */