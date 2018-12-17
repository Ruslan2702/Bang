#ifndef UNTITLED_SITUATIONPARSER_H
#define UNTITLED_SITUATIONPARSER_H

#include <iostream>
#include "../logic/GameSituation.h"
#include "../../include/json.hpp"
#include <regex>

using namespace nlohmann;

class SituationParser {
public:
    GameSituation DecodeStep(std::string step) noexcept(false);
    std::string EncodeStep(GameSituation step) noexcept(false);
};


#endif //UNTITLED_SITUATIONPARSER_H
