//
// Created by Андрей on 07.11.18.
//

#ifndef BANG_STEPPARSER_H
#define BANG_STEPPARSER_H

#include "../logic/Step.h"
#include <iostream>

class StepParser {
public:
    Step DecodeStep(std::string) noexcept(false);
    std::string EncodeStep(Step step) noexcept(false);
};

#endif //BANG_STEPPARSER_H
