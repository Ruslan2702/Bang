//
// Created by Андрей on 07.11.18.
//

#include "StepParser.h"

Step StepParser::DecodeStep(std::string) {
    Step step;
    step.action = "[???]";
    return step; /// dummy
}

std::string StepParser::EncodeStep(Step step) {
    return ""; /// dummy
}
