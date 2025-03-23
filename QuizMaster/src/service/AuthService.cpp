#include "service/AuthService.h"

import DBConn;
import Hashing;


//register implementations

bool AuthService::addUserToDB(const std::string& fullName, const std::string& username, const std::string& password) {
    
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
        std::cout << "******************************" << std::endl;
        std::cout << "Could not execute query: " << e.what() << std::endl;
        std::cout << "******************************" << std::endl;
        return false;

    }
    
}

//login implementations



UserDetails AuthService::authenticateUser(const std::string& username, const std::string& password) {
    UserDetails userDetails;
    sql::Connection* con = connectToDB();
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM users WHERE username=?");
    pstmt->setString(1, username);

    sql::ResultSet* res = pstmt->executeQuery();
    if (res->next()) {
        std::string storedPassword = res->getString("password");
        std::string role = res->getString("role");
        std::string username = res->getString("username");
        std::string fullName = res->getString("fullname");
        int userId = res->getInt("user_id");
        delete res;
        delete pstmt;
        delete con;

        std::string hashedPassword = sha256(password);
        if (storedPassword == hashedPassword) {
            userDetails.isAuthenticated = true;
            userDetails.role = role;
            userDetails.username = username;
            userDetails.fullName = fullName;
            userDetails.userId = userId;
        }
        else {
            userDetails.isAuthenticated = false;
            userDetails.role = "";
            userDetails.username = "";
            userDetails.fullName = "";
        }
    }
    else {
        delete res;
        delete pstmt;
        delete con;
        userDetails.isAuthenticated = false;
        userDetails.role = "";
        userDetails.username = "";
        userDetails.fullName = "";
    }

    return userDetails;
}