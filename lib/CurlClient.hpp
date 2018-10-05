#ifndef CURLCLIENT_H
#define CURLCLIENT_H

#include <iostream>
#include <string>
#include <sstream>

#include <json/json.h>
#include <json/value.h>

#include "HttpRequestType.hpp"

typedef std::map<std::string, std::string> Options;

class CurlClient
{

    public:
        CurlClient();
        CurlClient(const std::string& aUser, const std::string& aPassword);

        Json::Value executeGetJson(const std::string& aURI, const std::string& anAuthToken,
                                   const Options& anOptions = Options());
        std::string executeGet(const std::string& aURI, const std::__cxx11::string& anAuthToken,
                               const Options& anOptions = Options());


        bool hasLoginCredentials();
        std::string getPassword() const;
        void setPassword(const std::string& value);

        std::string getUser() const;
        void setUser(const std::string& value);

    private:
        std::string perform(const std::string& aURI, const std::__cxx11::string& anAuthToken,
                            const Options& anOptions = Options(),
                            const HttpRequestType::Type& aHttpRequestType = HttpRequestType::Type::GET);
        std::string user;
        std::string password;

};

#endif // CURLCLIENT_H
