//
// Created by Андрей on 17.11.18.
//

#include <gtest/gtest.h>
#include "../StepParser.h"
#include "../../logic/Card.h"
#include "../../logic/Step.h"
#include "../../logic/GameSituation.h"

const bool operator == (GameSituation left_situaiton, GameSituation right_situaiton) {

    return false; /// gummy
}

const bool operator == (Card left_card, Card right_card) {
    if(left_card.name_card != right_card.name_card)
        return false;
    return true;
}

const bool operator == (Step left_step, Step right_step) {


    if (left_step.from_player != right_step.from_player)
        return false;

    if (left_step.to_player != right_step.to_player)
        return false;

    if (!(left_step.card == right_step.card))
        return false;

    if (left_step.action != right_step.action)
        return false;

    return true; /// gummy
}

TEST(TestsForStepParser, simple_decode_01) {
    std::string row_str = "<STEP [GUN] [USE] [1] [1] STEP>";

    Card dummy_card;
    dummy_card.name_card = "[GUN]";

    Step expected;
    expected.action = "[USE]";
    expected.card = dummy_card;
    expected.from_player = 1;
    expected.to_player = 1;

    StepParser parser;

    Step real_step = parser.DecodeStep(row_str);

    std::cout << real_step.action << " " << expected.action << std::endl;

    EXPECT_TRUE(real_step == expected);
}

TEST(TestsForStepParser, simple_decode_02) {
    std::string row_str = "<STEP [BANG] [USE] [1] [1] STEP>";

    Card dummy_card;
    dummy_card.name_card = "[GUN]";

    Step expected;
    expected.action = "[USE]";
    expected.card = dummy_card;
    expected.from_player = 1;
    expected.to_player = 1;

    StepParser parser;
    Step real_step = parser.DecodeStep(row_str);

    EXPECT_FALSE(real_step == expected);
}

TEST(TestsForStepParser, simple_decode_03) {
    std::string row_str = "<STEP [BANG] [USE] [1] [2] STEP>";

    Card dummy_card;
    dummy_card.name_card = "[BANG]";

    Step expected;
    expected.action = "[USE]";
    expected.card = dummy_card;
    expected.from_player = 1;
    expected.to_player = 2;

    StepParser parser;
    Step real_step = parser.DecodeStep(row_str);

    EXPECT_TRUE(real_step == expected);
}

TEST(TestsForStepParser, simple_decode_04) {
    std::string row_str = "<STEP [BANG] [DROP] [1] [1] STEP>";

    Card dummy_card;
    dummy_card.name_card = "[BANG]";

    Step expected;
    expected.action = "[DROP]";
    expected.card = dummy_card;
    expected.from_player = 1;
    expected.to_player = 1;

    StepParser parser;
    Step real_step = parser.DecodeStep(row_str);

    EXPECT_TRUE(real_step == expected);
}


/*
 * Тут когда нибудь наверно но скорее всего нет будут тесты для братного превращение
 * структуры
 */

/*
 * Тесты для структур тоже когда то буду, но боже, как
 * же мне лень это набирать руками
 */


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}