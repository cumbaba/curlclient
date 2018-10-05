#ifndef HTTPREQUESTTYPE_H
#define HTTPREQUESTTYPE_H

#include <iostream>

class HttpRequestType
{
    public:
        enum Type
        {
            GET = 0,
            PUT = 1,
            POST = 2,
            DELETE = 3
        };

        static std::string toString(const Type& aType)
        {
            std::string type = "";

            switch (aType)
            {
                case GET:
                    type = "GET";
                    break;

                case PUT:
                    type = "PUT";
                    break;

                case POST:
                    type = "POST";
                    break;

                case DELETE:
                    type = "DELETE";
                    break;

                default:
                    break;
            }

            return type;
        }
};

#endif // HTTPREQUESTTYPE_H
