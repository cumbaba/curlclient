#ifndef CURLCLIENT_H
#define CURLCLIENT_H

#include <iostream>
#include <string>
#include <sstream>
#include <list>

#include <json/json.h>
#include <json/value.h>

#include "HttpRequestType.hpp"

typedef std::map<std::string, std::string> Options;

class CurlClient
{

    public:
        CurlClient();
        CurlClient(const std::string& aUser, const std::string& aPassword);

        Json::Value executeGetJson(const std::string& aURI,
                                   const Options& anOptions = Options(), const std::string& anAuthToken = std::string(),
                                   const std::string& aBody = std::string());
        std::string executeGet(const std::string& aURI,
                               const Options& anOptions = Options(), const std::string& anAuthToken = std::string(),
                               const std::string& aBody = std::string());


        bool hasLoginCredentials();
        std::string getPassword() const;
        void setPassword(const std::string& value);

        std::string getUser() const;
        void setUser(const std::string& value);

    private:

        std::string perform(const std::string& aURI,
                            const Options& anOptions = Options(), const std::string& anAuthToken = std::string(),
                            const std::string& aBod = std::string(),
                            const HttpRequestType::Type& aHttpRequestType = HttpRequestType::Type::GET);

        std::list<std::string> prepareAuthToken(const std::string& anAuthToken);
        std::string prepareOptions(const Options& anOptions);
        bool replaceAll(std::string &str, const std::string& aFrom, const std::string& aTo);
        std::string user;
        std::string password;

};

#endif // CURLCLIENT_H
