//
// Created by jaken on 16-12-17.
//
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>

#include "packet.hpp"
#ifndef NETCAPTURE_MYSQLWRITER_HPP
#define NETCAPTURE_MYSQLWRITER_HPP


class MySqlWriter{
public:
    MySqlWriter(const std::string netlocation,const std::string username,std::string passwd,const std::string database);
    bool tryToWriteData(struct packet const *elemp);
    ~MySqlWriter();
private:

    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
};


MySqlWriter::MySqlWriter(const std::string netlocation,const std::string username,std::string passwd, const std::string database)
{
    driver = get_driver_instance();
    con = driver->connect(netlocation.c_str(), username.c_str(), passwd.c_str());
    con->setSchema(database.c_str());
    pstmt = con->prepareStatement("INSERT INTO packets(type,srcip,desip,comments,size) VALUES (?,?,?,?,?)");
}

bool MySqlWriter::tryToWriteData(struct packet const *elemp) {
    pstmt->setString(1,elemp->type);
    pstmt->setString(2,elemp->srcip);
    pstmt->setString(3,elemp->desip);
    pstmt->setString(4,elemp->comment);
    pstmt->setInt(5,elemp->size);
    try {
        pstmt->executeUpdate();
    }catch (sql::SQLException & e)
    {
        std::cout<<e.what()<<" "<<e.getErrorCode()<<" "<<e.getErrorCode()<<std::endl;
        return false;
    }
    return true;
}

MySqlWriter::~MySqlWriter() {
    delete  pstmt;
    delete con;
}


#endif //NETCAPTURE_MYSQLWRITER_HPP
