#include "CardsParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "vector"
#include <cassert>
#include <algorithm>

std::vector<Card> CardParserConst::GetCardsDec() {
    std::vector<Card> dec(count_card, {});

    int number = 0;

    for (int i = 0; i < count_bang; ++i) {
        dec[number].name_card = "[BANG]";
        ++number;
    }

    for (int i = 0; i < count_beer; ++i) {
        dec[number].name_card = "[BEER]";
        ++number;
    }

    for (int i = 0; i < count_miss; ++i) {
        dec[number].name_card = "[MISS]";
        ++number;
    }

    std::random_shuffle(dec.begin(), dec.end());

    for (int i = 0; i < count_card; ++i) {
        auto g = dec[i].name_card;
        std::cout << g << std::endl;
    }

    return dec;
}


std::vector<Card> CardParserTxt::GetCardsDec() {
    std::string line;

    std::ifstream in("src/conf/cards.txt");
    std::regex re_total("total - (\\d+)");
    std::regex re_miss("MISS - (\\d+)");
    std::regex re_bang("BANG - (\\d+)");
    std::regex re_beer("BEER - (\\d+)");

    if(in.is_open()) {
        std::cout << "SUCCSESS, file is ok!\n";

        int count = 0;

        getline(in, line);
        std::smatch match;

        if (std::regex_search(line, match, re_total)) {
            std::cout << match[1] << std::endl;
        } else assert(false);

        std::vector<Card> dec(std::stoi(match[1]));

        getline(in, line);

        if (std::regex_search(line, match, re_miss)) {
            std::cout << match[1] << std::endl;
        } else assert(false);

        for (int i = 0; i < std::stoi(match[1]); ++i) {
            Card card;
            card.name_card = "[MISS]";
            dec.push_back(card);
        }

        getline(in, line);

        if (std::regex_search(line, match, re_bang)) {
            std::cout << match[1] << std::endl;
        } else assert(false);

        for (int i = 0; i < std::stoi(match[1]); ++i) {
            Card card;
            card.name_card = "[BANG]";
            dec.push_back(card);
        }

        getline(in, line);

        if (std::regex_search(line, match, re_beer)) {
            std::cout << match[1] << std::endl;
        } else assert(false);

        for (int i = 0; i < std::stoi(match[1]); ++i) {
            Card card;
            card.name_card = "[BEER]";
            dec.push_back(card);
        }



        for (int i = 90; i < 90; ++i) {
            auto card1 = dec[i].name_card;
                    std::cout << dec[i].name_card << std::endl;
        }


        std::random_shuffle(dec.begin(), dec.end());

        for (int i = 90; i < 90; ++i) std::cout << dec[i].name_card << std::endl;

        in.close();

    } else std::cerr << "Can not open file src/conf/cards.txt!\n";
}

