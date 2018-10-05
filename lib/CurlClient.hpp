#ifndef CURLCLIENT_H
#define CURLCLIENT_H

#include <iostream>
#include <string>
#include <sstream>

#include <json/json.h>
#include <json/value.h>

#include "HttpRequestType.hpp"

class CurlClient
{

    public:
        CurlClient();
        CurlClient(const std::string& aUser, const std::string& aPassword);

        Json::Value executeGetJson(const std::string& aURI, bool& isSuccessfull= *(new bool(false)));
        std::string executeGet(const std::string& aURI, bool& isSuccessfull = *(new bool(false)));


        bool hasLoginCredentials();
        std::string getPassword() const;
        void setPassword(const std::string& value);

        std::string getUser() const;
        void setUser(const std::string& value);

    private:
        bool perform(const std::string& aURI, std::string& aResponse,
                     const HttpRequestType::Type& aHttpRequestType = HttpRequestType::Type::GET);
        std::string user;
        std::string password;

};

#endif // CURLCLIENT_H
