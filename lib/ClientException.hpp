#ifndef CLIENTEXCEPTION_H
#define CLIENTEXCEPTION_H

#include <exception>
#include <sstream>
#include <string.h>

class ClientException : public std::exception
{
    public:

        ClientException(const std::string& anExceptionLog): exceptionLog(anExceptionLog)
        {}

        virtual const char* what() const throw()
        {
            char* what = (char*) calloc(exceptionLog.length(), sizeof(char));
            strcpy(what, exceptionLog.c_str());
            return what;
        }
    private:
        std::string exceptionLog;
};

#endif
