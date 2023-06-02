#pragma once
#ifndef _Dactyl_KChunk_h_
#define _Dactyl_KChunk_h_

#include <map>
#include <string>
#include <vector>
#include "Dactyl.KLine.h"

namespace Dactyl::Application
{
    class KChunk;
    using KChunkPtr = std::shared_ptr<KChunk>;

    class KChunk
    {
        public:
            KChunk(KLine kLine)
            {
                _level = kLine.Level;
                _id = kLine.Id;
                _data = kLine.Data;
                _type = kLine.Type;
                _ref = kLine.Ref;
                _parent = nullptr;
            };

            void insertSubChunk(KChunkPtr* child)
            {
                _subChunks.push_back(*child);
            };

            void setParentChunk(KChunkPtr* parent)
            {
                _parent = *parent;
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

            std::vector<KChunkPtr>& getSubChunks()
            {
                return _subChunks;
            };

        private:
            int _level = -1;
            int _id = -1;
            std::string _type = "";
            std::string _data = "";
            std::string _ref = "";
            KChunkPtr _parent;
            std::vector<KChunkPtr> _subChunks;
    };

    class KChunkSet
    {
        public:
            KChunkSet() {};

            std::vector<std::shared_ptr<KChunk>>& getChunks()
            {
                return _chunks;
            };

            void insertChunk(const std::shared_ptr<KChunk>& chunk)
            {
                _chunks.push_back(chunk);
            };

        private:
            std::vector<std::shared_ptr<KChunk>> _chunks;
    };

    class KChunkLevels
    {
        public:
            void set(KChunkPtr& kChunk)
            {
                auto level = kChunk->getLevel();
                auto iter = currentLevelChunks.find(level);
                if(iter != currentLevelChunks.end())
                {
                    currentLevelChunks.erase(iter);
                }
                currentLevelChunks.insert({level, kChunk});
            };

            bool getParentChunk(KChunkPtr* child, KChunkPtr* parent)
            {
                auto level = (*child)->getLevel();
                if(level == 0)
                {
                    parent = nullptr;
                    return false;
                }

                parent = &currentLevelChunks[level - 1];
                return true;
            };

        private:
            std::map<int, KChunkPtr> currentLevelChunks;
    };
}

#endif /* _Dactyl.KChunk.h_ */