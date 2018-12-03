#include "SituationParser.h"

std::string SituationParser::EncodeStep(GameSituation step) {
    std::string resStr = "";
    /*resStr = step.player_list[0] + " " + step.player_list[1] + " " +
             step.player_list[2] + " " + step.player_list[3] + " " +
             step.is_end + " " + step.is_sherif + " " + step.is_renigan + " " +
             step.count_bandits + " " + step.count_sherifs_helpers + " " +
             step.WINNER;*/
    return resStr; /// dummy
}
GameSituation SituationParser::DecodeStep(std::string str) {
    GameSituation dummy_situation;
    std::vector<std::shared_ptr<PlayerInfo>> player_list;

    std::cmatch result;   // Пока что кол-во игроков статично и = 4
    std::regex regular("[\\w]+"  // GameSituation -> player_list 1
                       "[\\s]{1}"
                       "[\\w]+"  // GameSituation -> player_list 2
                       "[\\s]{1}"
                       "[\\w]+"  // GameSituation -> player_list 3
                       "[\\s]{1}"
                       "[\\w]+"  // GameSituation -> player_list 4
                       "[\\s]{1}"
                       "[\\d]{1}"  // GameSituation -> bool is_end
                       "[\\s]{1}"
                       "[\\d]{1}"  // GameSituation -> bool is_sherif
                       "[\\s]{1}"
                       "[\\d]{1}"  // GameSituation -> bool is_renigan
                       "[\\s]{1}"
                       "[\\d]{1}"  // GameSituation ->  int count_bandits
                       "[\\s]{1}"
                       "[\\d]{1}"  // GameSituation ->  int count_sherifs_helpers
                       "[\\s]{1}"
                       "[\\w]+");  // GameSituation ->  string WINNER
    //"[\\s]");

    if (std::regex_match(str.c_str(), result, regular)) {

        std::shared_ptr<PlayerInfo> player1 = std::make_shared<PlayerInfo>();
        (*player1).HP = 1;



        /*dummy_situation.player_list.push_back();
        dummy_situation.player_list = result[1];    // Непонятно, как заполнять std::vector<std::shared_ptr<PlayerInfo>>
        dummy_situation.player_list = result[2];
        dummy_situation.player_list = result[3];
        dummy_situation.player_list = result[4];*/

        dummy_situation.is_end = (result[5] != 0);
        dummy_situation.is_sherif = (result[6] != 0);
        dummy_situation.is_renigan = (result[7] != 0);
        dummy_situation.count_bandits = std::stoi(result[8]);
        dummy_situation.count_sherifs_helpers = std::stoi(result[9]);
        dummy_situation.WINNER = result[10];
    }
    return dummy_situation; /// dummy
}