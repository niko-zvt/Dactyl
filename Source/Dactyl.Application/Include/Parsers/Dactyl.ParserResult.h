#pragma once
#ifndef _Dactyl_ParserResult_h_
#define _Dactyl_ParserResult_h_

#include <string>
#include <vector>

namespace Dactyl::Application
{
    class ParserResult
    {
        public:
            ParserResult() {};

        private:
            std::vector<int> _nodes;
    };
}

#endif /* _Dactyl.ParserResult.h_ */