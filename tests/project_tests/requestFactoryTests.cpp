#include "tests.hpp"
#include "RequestFactory.hpp"
#include <utility>
#include <vector>

static std::pair<std::string, std::string> create_header_pair(
    std::string const &key,
    std::string const &value)
{
    return std::pair<std::string, std::string>(key, value);
}

static std::string create_request_line(
    std::string const &method,
    std::string const &path,
    std::string const &httpVersion)
{
    return method + " " + path + " " + httpVersion + "\r\n";
}

static std::string create_header_section(
    std::vector<std::pair<std::string, std::string>> pairs)
{
    std::string headerSection;

    for (size_t i = 0; i < pairs.size(); i++)
    {
        headerSection += pairs[i].first + ": " + pairs[i].second + "\r\n";
    }
    headerSection += "\r\n";
    return headerSection;
}

static void create_should_returnValidRequestFactory_when_standartGetRequestIsProcessed()
{
    // Arrange
    std::string method = "GET";
    std::string path = "/hello.html";
    std::string httpVersion = "HTTP/1.1";
    auto requestLine = create_request_line(method, path, httpVersion);

    std::vector<std::pair<std::string, std::string>> headerList
    {
        create_header_pair("User-Agent", "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)"),
        create_header_pair("Host", "www.tutorialspoint.com"),
        create_header_pair("Accept-Language", "en-us"),
        create_header_pair("Accept-Encoding", "gzip, deflate")
    };
    auto headerSection = create_header_section(headerList);

    auto httpRequest = requestLine +
		headerSection;

    auto *fact = new RequestFactory();
    auto *request = fact->create(httpRequest);
}

void    test_reqeust_factory(void)
{
    SUBCASE("test_reqeust_factory")
    {
        SUBCASE("create() should return valid request model when standart GET request is processed")
            create_should_returnValidRequestFactory_when_standartGetRequestIsProcessed();

    }
}
