//
// Created by Андрей on 16.12.18.
//

#include "DataBaseManager.h"
#include <string>
#include <string>
#include <sstream>

template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss<< val;
    return oss.str();
}

static void exit_nicely(PGconn *conn) { PQfinish(conn); }

DataBaseManager::DataBaseManager(const std::string &host,
                                 const std::string &port,
                                 const std::string &dbname,
                                 const std::string &connect_timeout,
                                 const std::string &password,
                                 const std::string &user,
                                 const std::string &step_stable)
{
    std::string conninfo = "host=" + host + " port=" + port + " dbname=" + dbname + " connect_timeout=" +
            connect_timeout + " password="  + password + " user=" + user;
    conn = PQconnectdb(conninfo.c_str());

    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s",
                PQerrorMessage(conn));
        exit_nicely(conn);
    } else {
        std::cout << "SUCCESS, DB - OK!" << std::endl;
    }

    steps_table = step_stable;
}

DataBaseManager::~DataBaseManager() {
    PQfinish(conn);
}

std::string DataBaseManager::StepToSQLQuery(Step step) {
    std::string query;

    query = "insert into " + steps_table +  "(who, card, action, dest) values(" + toString(step.from_player) + ", '" +
            step.card.name_card  + "', '" + step.action + "', " + toString(step.to_player) + ")";

    return query;
}

void DataBaseManager::InsertStep(Step step) {
    std::string query = StepToSQLQuery(step);

    std::cout << query << std::endl;

    PQexec(conn, query.c_str());
}
