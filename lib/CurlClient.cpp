#include "CurlClient.hpp"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

CurlClient::CurlClient()
{
}
CurlClient::CurlClient(const std::string& aUser, const std::string& aPassword):
    user(aUser),
    password(aPassword)
{
}

Json::Value CurlClient::executeGetJson(const std::string& aURI, bool& isSuccessfull)
{
    Json::Value root;
    std::string errors;

    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();

    std::string response = this->executeGet(aURI, isSuccessfull);
    reader->parse(response.c_str(), response.c_str() + response.size(), &root, &errors);

    if (!errors.empty())
    {
        std::cout << errors << std::endl;
    }

    delete reader;
    return root;
}

std::string CurlClient::executeGet(const std::string& aURI, bool& isSuccessfull)
{
    std::string response;
    isSuccessfull = perform(aURI, response, HttpRequestType::GET);
    return response;
}

bool CurlClient::perform(const std::string& aURI, std::string& aResult, const HttpRequestType::Type& aHttpRequestType)
{
    if (aHttpRequestType == HttpRequestType::GET)
    {
        try
        {
            curlpp::Cleanup cleanup;
            std::stringstream resultStream;
            curlpp::Easy easy;

            easy.setOpt<curlpp::options::Url>(aURI);
            easy.setOpt<cURLpp::Options::WriteStream>(&resultStream);

            if (hasLoginCredentials())
            {
                easy.setOpt<curlpp::options::UserPwd>(user + ":" + password);
            }

            easy.perform();
            aResult = resultStream.str();
            return true;
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
    }

    return false;
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
