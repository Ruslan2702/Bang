//
// Created by Андрей on 16.12.18.
//

#ifndef BANG_DATABASEMANAGER_H
#define BANG_DATABASEMANAGER_H

#include <libpq-fe.h>
#include "../logic/Step.h"
#include <queue>

class DataBaseManager {
public:
    DataBaseManager() = default;
    explicit DataBaseManager(const std::string &host,
                             const std::string &port,
                             const std::string &dbname,
                             const std::string &connect_timeout,
                             const std::string &password,
                             const std::string &user,
                             const std::string &step_stable);
    ~DataBaseManager();

    void InsertStep(Step step);

public: /// это только пока
    std::string StepToSQLQuery(Step step);

    PGconn     *conn;
    std::queue<std::string> queue;
    std::string steps_table;
};

#endif //BANG_DATABASEMANAGER_H
