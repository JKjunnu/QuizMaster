#include "service/AuthService.h"
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/connection.h>

import DBConn;
import Hashing;


//register implementations

bool AuthServiceClass::addUserToDB(const std::string& fullName, const std::string& username, const std::string& password) {
    // under construction
    try {
        sql::Connection* con = connectToDB();
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO users(fullname, username, password) VALUES(?,?,?)");
        pstmt->setString(1, fullName);
        pstmt->setString(2, username);
        pstmt->setString(3, sha256(password));
        pstmt->execute();
        delete pstmt;
        delete con;
        return true;
    }
    catch (sql::SQLException e) {
        std::cout << "Could not execute query: " << e.what() << std::endl;
        return false;

    }
    
}

//login implementations



authenticated AuthServiceClass::authenticateUser(const std::string& username, const std::string& password) {
    authenticated authResult;
    sql::Connection* con = connectToDB();
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT password, role FROM users WHERE username=?");
    pstmt->setString(1, username);

    sql::ResultSet* res = pstmt->executeQuery();
    if (res->next()) {
        std::string storedPassword = res->getString("password");
        std::string role = res->getString("role");
        delete res;
        delete pstmt;
        delete con;

        std::string hashedPassword = sha256(password);
        if (storedPassword == hashedPassword) {
            authResult.isAuthenticated = true;
            authResult.role = role;
        }
        else {
            authResult.isAuthenticated = false;
            authResult.role = "";
        }
    }
    else {
        delete res;
        delete pstmt;
        delete con;
        authResult.isAuthenticated = false;
        authResult.role = "";
    }

    return authResult;
}