#pragma once

#include <string>
#include <vector>
#include "tcmp/common/token.hpp"

namespace tcmp
{
    class Scanner
    {
    private:
        std::string m_fname;

    public:
        Scanner(const std::string &fname);
        std::vector<Token> scan();
    };
}