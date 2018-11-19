#ifndef UNTITLED_SITUATIONPARSER_H
#define UNTITLED_SITUATIONPARSER_H

#include <iostream>
#include "../logic/GameSituation.h"
#include "boost/test"

class SituationParser {
public:
    GameSituation DecodeStep(std::string) noexcept(false);
    std::string EncodeStep(GameSituation step) noexcept(false);
};


#endif //UNTITLED_SITUATIONPARSER_H
