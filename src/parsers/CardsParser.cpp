#include "CardsParser.h"

void Parse(string filename, std::vector<int>*role, std::vector<int>*card) {
    vector<vector<string>> data;

    // Открываем файл
    ifstream in;
    in.open(filename);

    if (!in.is_open()) {
        throw "File can't be opened";
    }

    string line;



    in.close();

    return data;
}

/*
Card CardParser::DecodeCard(std::string str) {
    Card card;
    std::cmatch result;
    std::regex regular("[\\w]+"     // CARD -> string name_card
                       "[\\s]{1}"
                       "[\\w]+");   // CARD -> string description

    if (std::regex_match(str.c_str(), result, regular)) {
        card.name_card = result[1];
        card.description = result[2];
    }

    return card; /// dummy
}

std::string CardParser::EncodeCard(Card card) {
    std::string resStr = "";
    resCard = card.name_card + " " + card.description;
    return resCard; /// dummy
}*/