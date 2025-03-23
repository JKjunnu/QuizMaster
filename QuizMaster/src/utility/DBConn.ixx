
#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

export module DBConn;

export sql::Connection* connectToDB() {

    //for demonstration only. never save your password in the code!
    const std::string server = "tcp://127.0.0.1:3306";
    const std::string username = "root";
    const std::string password = "1234";


    sql::Driver* driver;
    sql::Connection* con;
    /*sql::Statement* stmt;
    sql::PreparedStatement* pstmt;*/


    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }

    
    con->setSchema("quizmasterdb");

    return con;

}