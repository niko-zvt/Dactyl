#pragma once
#ifndef _Dactyl_KChunk_h_
#define _Dactyl_KChunk_h_

#include <map>
#include <string>
#include <vector>
#include "Dactyl.KLine.h"

namespace Dactyl::Application
{
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

            void setParentChunk(std::shared_ptr<KChunk>& parent)
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

            std::vector<std::shared_ptr<KChunk>>& getSubChunks()
            {
                return _subChunks;
            };

        private:
            int _level = -1;
            int _id = -1;
            std::string _type = "";
            std::string _data = "";
            std::string _ref = "";
            std::shared_ptr<KChunk> _parent;
            std::vector<std::shared_ptr<KChunk>> _subChunks;
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
            void set(std::shared_ptr<KChunk>& kChunk)
            {
                auto level = kChunk->getLevel();
                auto iter = currentLevelChunks.find(level);
                if(iter != currentLevelChunks.end())
                {
                    currentLevelChunks.erase(iter);
                }
                currentLevelChunks.insert({level, kChunk});
            };

            std::shared_ptr<KChunk>& getParentChunk(std::shared_ptr<KChunk>& kChunk)
            {
                auto level = kChunk->getLevel();
                auto chunk = currentLevelChunks[level - 1];
                return chunk;
            };

        private:
            std::map<int, std::shared_ptr<KChunk>> currentLevelChunks;
    };
}

#endif /* _Dactyl.KChunk.h_ */