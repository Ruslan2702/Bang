//
// Created by Андрей on 16.12.18.
//

#include "DataBaseManager.h"
#include <string>
#include <string>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <cassert>

template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss<< val;
    return oss.str();
}

std::string GetDataBaseConf() {
    std::ifstream in("src/conf/db_conf");

    std::regex re_host("host = (\\w+)");
    std::regex re_port("port = (\\d+)");
    std::regex re_dbname("dbname = (\\w+)");
    std::regex re_connect_timeout("connect_timeout = (\\d+)");
    std::regex re_password("password = (\\w+)");
    std::regex re_user("user = (\\w+)");

    std::string host;
    std::string port;
    std::string dbname;
    std::string connect_timeout;
    std::string password;
    std::string user;

    std::string line;
    std::smatch match;

    if(in.is_open()) {
        int count = 0;

        getline(in, line);
        std::regex_search(line, match, re_host);
        host = match[1];

        getline(in, line);
        std::regex_search(line, match, re_port);
        port = match[1];

        getline(in, line);
        std::regex_search(line, match, re_dbname);
        dbname = match[1];

        getline(in, line);
        std::regex_search(line, match, re_connect_timeout);
        connect_timeout = match[1];

        getline(in, line);
        std::regex_search(line, match, re_password);
        password = match[1];

        getline(in, line);
        std::regex_search(line, match, re_user);
        user = match[1];
    }


    std::string conninfo = "host=" + host + " port=" + port + " dbname=" + dbname + " connect_timeout=" +
                           connect_timeout + " password="  + password + " user=" + user;

    return conninfo;
}

static void exit_nicely(PGconn *conn) { PQfinish(conn); }

DataBaseManager::DataBaseManager()
{
    std::string conninfo = GetDataBaseConf();

    conn = PQconnectdb(conninfo.c_str());

    if (PQstatus(conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s",
                PQerrorMessage(conn));
        exit_nicely(conn);
    } else {
        std::cout << "SUCCESS, DB - OK!" << std::endl;
    }
    int index_table = GetLastGameId();
    steps_table = "game_xx" + toString(index_table) + "_steps";
    WriteFutureIndexGame();
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

int DataBaseManager::GetLastGameId() {
    std::ifstream in("src/conf/lastgame");
    std::regex re_last("LAST GAME - (\\d+)");
    std::string line;

    if(in.is_open()) {
        int count = 0;

        getline(in, line);
        std::smatch match;

        if (std::regex_search(line, match, re_last)) {
            count =  std::stoi(match[1]);
            return count;
        } else return 0;
    }
    in.close();
}

void DataBaseManager::CreateTable() {
    std::string query = "create table " + steps_table + " (\n"
                        "  id serial not null,\n"
                        "  who varchar(20) not null,\n"
                        "  card varchar(20) not null ,\n"
                        "  action varchar(20) not null,\n"
                        "  dest integer not null\n"
                        ")";

    PQexec(conn, query.c_str());
}

void DataBaseManager::WriteFutureIndexGame() {
    int last = GetLastGameId() + 1;

    std::ofstream out("src/conf/lastgame");
    std::string out_str = "LAST GAME - " + toString(last);

    if(out.is_open()) {
        out << out_str;
    }

    out.close();
}
