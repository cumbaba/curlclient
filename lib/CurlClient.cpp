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

Json::Value CurlClient::executeGetJson(const std::string& aURI, const std::string& anAuthToken,
                                       const Options& anOptions)
{
    Json::Value root;
    std::string errors;

    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();

    std::string response = this->executeGet(aURI, anAuthToken, anOptions);
    reader->parse(response.c_str(), response.c_str() + response.size(), &root, &errors);

    if (!errors.empty())
    {
        std::cerr << errors << std::endl;
    }

    delete reader;
    return root;
}

std::string CurlClient::executeGet(const std::string& aURI, const std::string& anAuthToken, const Options& anOptions)
{
    return perform(aURI, anAuthToken, anOptions, HttpRequestType::GET);
}

// TODO authToken and options
std::string CurlClient::perform(const std::string& aURI, const std::string& anAuthToken, const Options& anOptions,
                                const HttpRequestType::Type& aHttpRequestType)
{
    std::string result;

    try
    {
        curlpp::Cleanup cleanup;
        std::stringstream resultStream;
        curlpp::Easy easy;

        easy.setOpt<curlpp::options::Url>(aURI);
        easy.setOpt<curlpp::options::Verbose>(true);
        easy.setOpt<curlpp::options::SslVerifyPeer>(false);
        easy.setOpt<curlpp::options::CustomRequest>(HttpRequestType::toString(aHttpRequestType));
        easy.setOpt<cURLpp::Options::WriteStream>(&resultStream);

        if (hasLoginCredentials())
        {
            easy.setOpt<curlpp::options::UserPwd>(user + ":" + password);
        }

        easy.perform();
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
