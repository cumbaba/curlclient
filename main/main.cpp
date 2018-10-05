#include <iostream>

#include <CurlClient.hpp>

using namespace std;

int main(int argc, char* argv[])
{

    CurlClient client("cumhursayan", "4815162342");

    Json::Value result = client.executeGetJson("http://api.plos.org/search?q=title:DNA");
    Json::Value value2 = result["response"]["numFound"];

    cout << value2.asString() << endl;

    return 0;
}
