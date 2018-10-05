#include "CurlClient.hpp"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

#include "ClientException.hpp"

CurlClient::CurlClient()
{
}

CurlClient::CurlClient(const std::string& aUser, const std::string& aPassword):
    user(aUser),
    password(aPassword)
{
}

Json::Value CurlClient::executeGetJson(const std::string& aURI, const Options& anOptions,
                                       const std::string& anAuthToken, const std::string& aBody)
{
    Json::Value root;
    std::string errors;

    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();

    std::string response = this->executeGet(aURI, anOptions, anAuthToken, aBody);
    reader->parse(response.c_str(), response.c_str() + response.size(), &root, &errors);

    if (!errors.empty())
    {
        std::cerr << errors << std::endl;
    }

    delete reader;
    return root;
}

std::string CurlClient::executeGet(const std::string& aURI, const Options& anOptions, const std::string& anAuthToken,
                                   const std::string& aBody)
{
    return perform(aURI, anOptions, anAuthToken, aBody, HttpRequestType::GET);
}

std::string CurlClient::perform(const std::string& aURI, const Options& anOptions, const std::string& anAuthToken,
                                const std::string& aBody,
                                const HttpRequestType::Type& aHttpRequestType)
{
    std::string result;

    try
    {
        curlpp::Cleanup cleanup;
        std::stringstream resultStream;
        curlpp::Easy easy;

        easy.setOpt<curlpp::options::Url>(aURI + prepareOptions(anOptions));
        easy.setOpt<curlpp::options::Verbose>(true);
        easy.setOpt<curlpp::options::SslVerifyPeer>(false);
        easy.setOpt<curlpp::options::CustomRequest>(HttpRequestType::toString(aHttpRequestType));
        easy.setOpt<curlpp::options::WriteStream>(&resultStream);

        if (!anAuthToken.empty())
        {
            easy.setOpt<curlpp::options::HttpHeader>(prepareAuthToken(anAuthToken));
        }
        else if (hasLoginCredentials())
        {
            easy.setOpt<curlpp::options::UserPwd>(user + ":" + password);
        }

        if (!aBody.empty())
        {
            easy.setOpt<curlpp::options::PostFields>(aBody);
        }

        easy.perform();

        int statusCode = static_cast<int>(curlpp::infos::ResponseCode::get(easy));

        // TODO check max valid status code
        if (statusCode < 200 || statusCode > 204)
        {
            throw ClientException("Request has been responded with invalid status code: [" + std::to_string(statusCode) + "]");
        }

        result = resultStream.str();
    }
    catch (const curlpp::RuntimeError& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const curlpp::LogicError& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return result;
}

std::list<std::string> CurlClient::prepareAuthToken(const std::string& anAuthToken)
{
    std::list<std::string> headers;
    headers.push_back("Content-Type: application/json");

    std::string authContent = "Authorization: Bearer " + anAuthToken;
    headers.push_back(authContent);

    return headers;
}

std::string CurlClient::prepareOptions(const Options& anOptions)
{
    if (anOptions.empty())
    {
        return std::string("");
    }

    std::string urlExtension;

    urlExtension += "?";

    for (auto option : anOptions)
    {
        urlExtension += option.first + "=" + option.second + '&';
    }

    replaceAll(urlExtension, " ", "%20");

    return urlExtension;
}

bool CurlClient::replaceAll(std::string& aString, const std::string& aFrom, const std::string& aTo)
{
    try
    {
        size_t startIndex = 0;

        while ((startIndex = aString.find(aFrom, startIndex)) != std::string::npos)
        {
            aString.replace(startIndex, aFrom.length(), aTo);
            startIndex += aTo.length();
        }

        return true;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return false;
    }
}

bool CurlClient::hasLoginCredentials()
{
    return !user.empty() && !password.empty();
}

std::string CurlClient::getPassword() const
{
    return password;
}

void CurlClient::setPassword(const std::string& value)
{
    password = value;
}

std::string CurlClient::getUser() const
{
    return user;
}

void CurlClient::setUser(const std::string& value)
{
    user = value;
}
