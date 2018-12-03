//
// Created by Андрей on 07.11.18.
//

#include "StepParser.h"
#include <stdio.h>
#include <stdlib.h>

Step StepParser::DecodeStep(std::string str) {
    Step step;
    std::cmatch result;
    std::regex regular("<STEP (\\[\\w+\\]) (\\[\\w+\\]) \\[(\\d+)\\] \\[(\\d+)\\] STEP>");

    if (std::regex_match(str.c_str(), result, regular)) {
        Card card;
        card.name_card = result[1].str();
        step.card = card;
        step.action = result[2].str();
        step.from_player = std::stoi(result[3].str());
        step.to_player = std::stoi(result[4].str());
    }

    return step; /// dummy
}

std::string StepParser::EncodeStep(Step step) {
    std::string resStr = "";
    resStr = "<STEP " + step.card.name_card + " " + step.action + " "
             + std::to_string(step.from_player) +
             " " + std::to_string(step.to_player) + " STEP>";
    return resStr; /// dummy
}
