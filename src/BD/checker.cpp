//
// Created by Андрей on 16.12.18.
//

#include "DataBaseManager.h"

int main() {
    Step step;
    step.from_player = 1;
    step.to_player = 2;
    step.action = "USE";
    step.card.name_card = "BANG";

    const std::string host = "localhost";
    const std::string port = "5432";
    const std::string dbname = "bang";
    const std::string connect_timeout = "10";
    const std::string password = "2017";
    const std::string user = "postgres";
    const std::string step_stable = "game_xx0_steps";

    DataBaseManager manager = DataBaseManager(host, port, dbname, connect_timeout,
                                              password, user, step_stable);
    manager.InsertStep(step);

    return 0;
}
