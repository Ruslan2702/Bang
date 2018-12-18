//
// Created by Андрей on 16.12.18.
//

#ifndef BANG_DATABASEMANAGER_H
#define BANG_DATABASEMANAGER_H

#include <libpq-fe.h>
#include "../logic/Step.h"
#include <queue>

std::string GetDataBaseConf();

class DataBaseManager {
public:
    explicit DataBaseManager();

    ~DataBaseManager();

    void InsertStep(Step step);
    void CreateTable();
    int GetLastGameId();
    void WriteFutureIndexGame();

private:
    std::string StepToSQLQuery(Step step);

    PGconn     *conn;
    std::queue<std::string> queue;
    std::string steps_table;
};

#endif //BANG_DATABASEMANAGER_H
