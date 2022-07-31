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

static std::string create_url(
    std::string const &path,
    std::string const &query)
{
    if (query.length() > 0)
        return path + "?" + query;

    return path;
}

static void create_should_returnValidRequestModel_when_standartGetRequestIsProcessed()
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

    std::string body = "";

    auto httpRequest = requestLine +
		headerSection +
        body;

    // Act
    auto *factory = new RequestFactory();
    auto *request = factory->create(httpRequest);

    // Assert
    REQUIRE_EQ(request->getMethod(), GET);
    REQUIRE_EQ(request->getUrl().getFullUrl(), path);
    REQUIRE_EQ(request->getUrl().getPath(), path);
    REQUIRE_EQ(request->getUrl().getQuery(), "");
    REQUIRE_EQ(request->getHttpVersion(), httpVersion);
    REQUIRE_EQ(request->getMessageBody(), body);
    for (size_t i = 0; i < headerList.size(); i++)
    {
        REQUIRE_EQ(request->getHeaders().at(headerList[i].first), headerList[i].second);
    }
}

static void create_should_returnValidRequestModel_when_standartPostWithBodyRequestIsProcessed()
{
    // Arrange
    std::string method = "POST";
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

    std::string body = "This is a test \n \r \r\n \t \t \t \v body {}";

    auto httpRequest = requestLine +
		headerSection +
        body;

    // Act
    auto *factory = new RequestFactory();
    auto *request = factory->create(httpRequest);

    // Assert
    REQUIRE_EQ(request->getMethod(), POST);
    REQUIRE_EQ(request->getUrl().getFullUrl(), path);
    REQUIRE_EQ(request->getUrl().getPath(), path);
    REQUIRE_EQ(request->getUrl().getQuery(), "");
    REQUIRE_EQ(request->getHttpVersion(), httpVersion);
    REQUIRE_EQ(request->getMessageBody(), body);
    for (size_t i = 0; i < headerList.size(); i++)
    {
        REQUIRE_EQ(request->getHeaders().at(headerList[i].first), headerList[i].second);
    }
}

static void create_should_returnValidRequestModel_when_UrlHasQueryString()
{
    // Arrange
    std::string method = "GET";
    std::string path = "/hello.html";
    std::string query = "std=Ccross98test";
    std::string url = create_url(path, query);
    std::string httpVersion = "HTTP/1.1";
    auto requestLine = create_request_line(method, url, httpVersion);

    std::vector<std::pair<std::string, std::string>> headerList
    {
        create_header_pair("User-Agent", "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)"),
        create_header_pair("Host", "www.tutorialspoint.com"),
        create_header_pair("Accept-Language", "en-us"),
        create_header_pair("Accept-Encoding", "gzip, deflate")
    };
    auto headerSection = create_header_section(headerList);

    std::string body = "";

    auto httpRequest = requestLine +
		headerSection +
        body;

    // Act
    auto *factory = new RequestFactory();
    auto *request = factory->create(httpRequest);

    // Assert
    REQUIRE_EQ(request->getMethod(), GET);
    REQUIRE_EQ(request->getUrl().getFullUrl(), url);
    REQUIRE_EQ(request->getUrl().getPath(), path);
    REQUIRE_EQ(request->getUrl().getQuery(), query);
    REQUIRE_EQ(request->getHttpVersion(), httpVersion);
    REQUIRE_EQ(request->getMessageBody(), body);
    for (size_t i = 0; i < headerList.size(); i++)
    {
        REQUIRE_EQ(request->getHeaders().at(headerList[i].first), headerList[i].second);
    }
}

static void create_should_returnValidRequestModel_when_UrlHasEmptyQueryString()
{
    // Arrange
    std::string method = "GET";
    std::string path = "/hello.html";
    std::string query = "";
    std::string url = create_url(path, query);
    std::string httpVersion = "HTTP/1.1";
    auto requestLine = create_request_line(method, url, httpVersion);

    std::vector<std::pair<std::string, std::string>> headerList
    {
        create_header_pair("User-Agent", "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)"),
        create_header_pair("Host", "www.tutorialspoint.com"),
        create_header_pair("Accept-Language", "en-us"),
        create_header_pair("Accept-Encoding", "gzip, deflate")
    };
    auto headerSection = create_header_section(headerList);

    std::string body = "";

    auto httpRequest = requestLine +
		headerSection +
        body;

    // Act
    auto *factory = new RequestFactory();
    auto *request = factory->create(httpRequest);

    // Assert
    REQUIRE_EQ(request->getMethod(), GET);
    REQUIRE_EQ(request->getUrl().getFullUrl(), url);
    REQUIRE_EQ(request->getUrl().getPath(), path);
    REQUIRE_EQ(request->getUrl().getQuery(), query);
    REQUIRE_EQ(request->getHttpVersion(), httpVersion);
    REQUIRE_EQ(request->getMessageBody(), body);
    for (size_t i = 0; i < headerList.size(); i++)
    {
        REQUIRE_EQ(request->getHeaders().at(headerList[i].first), headerList[i].second);
    }
}

static void create_should_returnValidRequestModelAndDecodeTheUrl_when_urlPathIsEncoded()
{
    // Arrange
    std::string method = "GET";
    std::string path = "/hello/Hello+G%C3%BCnter";
    std::string decodedPath = "/hello/Hello Günter";
    std::string query = "";
    std::string url = create_url(path, query);
    std::string httpVersion = "HTTP/1.1";
    auto requestLine = create_request_line(method, url, httpVersion);

    std::vector<std::pair<std::string, std::string>> headerList
    {
        create_header_pair("User-Agent", "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)"),
        create_header_pair("Host", "www.tutorialspoint.com"),
        create_header_pair("Accept-Language", "en-us"),
        create_header_pair("Accept-Encoding", "gzip, deflate")
    };
    auto headerSection = create_header_section(headerList);

    std::string body = "";

    auto httpRequest = requestLine +
		headerSection +
        body;

    // Act
    auto *factory = new RequestFactory();
    auto *request = factory->create(httpRequest);

    // Assert
    REQUIRE_EQ(request->getMethod(), GET);
    REQUIRE_EQ(request->getUrl().getFullUrl(), decodedPath);
    REQUIRE_EQ(request->getUrl().getPath(), decodedPath);
    REQUIRE_EQ(request->getUrl().getQuery(), query);
    REQUIRE_EQ(request->getHttpVersion(), httpVersion);
    REQUIRE_EQ(request->getMessageBody(), body);
    for (size_t i = 0; i < headerList.size(); i++)
    {
        REQUIRE_EQ(request->getHeaders().at(headerList[i].first), headerList[i].second);
    }
}

static void create_should_returnValidRequestModelWithUnemptyPath_when_urlIsEmpty()
{
    // Arrange
    std::string method = "GET";
    std::string path = "";
    std::string expectedPath = "/";
    std::string query = "";
    std::string url = create_url(path, query);
    std::string httpVersion = "HTTP/1.1";
    auto requestLine = create_request_line(method, url, httpVersion);

    std::vector<std::pair<std::string, std::string>> headerList
    {
        create_header_pair("User-Agent", "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)"),
        create_header_pair("Host", "www.tutorialspoint.com"),
        create_header_pair("Accept-Language", "en-us"),
        create_header_pair("Accept-Encoding", "gzip, deflate")
    };
    auto headerSection = create_header_section(headerList);

    std::string body = "";

    auto httpRequest = requestLine +
		headerSection +
        body;

    // Act
    auto *factory = new RequestFactory();
    auto *request = factory->create(httpRequest);

    // Assert
    REQUIRE_EQ(request->getMethod(), GET);
    REQUIRE_EQ(request->getUrl().getFullUrl(), expectedPath);
    REQUIRE_EQ(request->getUrl().getPath(), expectedPath);
    REQUIRE_EQ(request->getUrl().getQuery(), query);
    REQUIRE_EQ(request->getHttpVersion(), httpVersion);
    REQUIRE_EQ(request->getMessageBody(), body);
    for (size_t i = 0; i < headerList.size(); i++)
    {
        REQUIRE_EQ(request->getHeaders().at(headerList[i].first), headerList[i].second);
    }
}

static void create_should_returnInvalidRequestModelAndNotCrush_when_RequestMethodIsEmpty()
{
    // Arrange
    std::string method = "";
    std::string path = "";
    std::string expectedPath = "/";
    std::string query = "";
    std::string url = create_url(path, query);
    std::string httpVersion = "HTTP/1.1";
    auto requestLine = create_request_line(method, url, httpVersion);

    std::vector<std::pair<std::string, std::string>> headerList
    {
        create_header_pair("User-Agent", "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)"),
        create_header_pair("Host", "www.tutorialspoint.com"),
        create_header_pair("Accept-Language", "en-us"),
        create_header_pair("Accept-Encoding", "gzip, deflate")
    };
    auto headerSection = create_header_section(headerList);

    std::string body = "";

    auto httpRequest = requestLine +
		headerSection +
        body;

    // Act
    auto *factory = new RequestFactory();
    auto *request = factory->create(httpRequest);

    // Assert
    REQUIRE_EQ(request->getMethod(), INVALID);
    REQUIRE_EQ(request->getUrl().getFullUrl(), expectedPath);
    REQUIRE_EQ(request->getUrl().getPath(), expectedPath);
    REQUIRE_EQ(request->getUrl().getQuery(), query);
    REQUIRE_EQ(request->getHttpVersion(), httpVersion);
    REQUIRE_EQ(request->getMessageBody(), body);
    for (size_t i = 0; i < headerList.size(); i++)
    {
        REQUIRE_EQ(request->getHeaders().at(headerList[i].first), headerList[i].second);
    }
}

static void create_should_returnInvalidRequestModelAndNotCrush_when_HttpVersionIsEmpty()
{
    // Arrange
    std::string method = "GET";
    std::string path = "";
    std::string expectedPath = "/";
    std::string query = "";
    std::string url = create_url(path, query);
    std::string httpVersion = "";
    auto requestLine = create_request_line(method, url, httpVersion);

    std::vector<std::pair<std::string, std::string>> headerList
    {
        create_header_pair("User-Agent", "Mozilla/4.0 (compatible; MSIE5.01; Windows NT)"),
        create_header_pair("Host", "www.tutorialspoint.com"),
        create_header_pair("Accept-Language", "en-us"),
        create_header_pair("Accept-Encoding", "gzip, deflate")
    };
    auto headerSection = create_header_section(headerList);

    std::string body = "";

    auto httpRequest = requestLine +
		headerSection +
        body;

    // Act
    auto *factory = new RequestFactory();
    auto *request = factory->create(httpRequest);

    // Assert
    REQUIRE_EQ(request->getMethod(), GET);
    REQUIRE_EQ(request->getUrl().getFullUrl(), expectedPath);
    REQUIRE_EQ(request->getUrl().getPath(), expectedPath);
    REQUIRE_EQ(request->getUrl().getQuery(), query);
    REQUIRE_EQ(request->getHttpVersion(), httpVersion);
    REQUIRE_EQ(request->getMessageBody(), body);
    for (size_t i = 0; i < headerList.size(); i++)
    {
        REQUIRE_EQ(request->getHeaders().at(headerList[i].first), headerList[i].second);
    }
}

void    test_reqeust_factory(void)
{
    SUBCASE("test reqeust factory")
    {
        SUBCASE("create() should return valid request model when standart GET request is processed")
            create_should_returnValidRequestModel_when_standartGetRequestIsProcessed();
        SUBCASE("create() should return valid request model when standart POST with body request is processed")
            create_should_returnValidRequestModel_when_standartPostWithBodyRequestIsProcessed();
        SUBCASE("create() should return valid request model when url has query string")
            create_should_returnValidRequestModel_when_UrlHasQueryString();
        SUBCASE("create() should return valid request model when url has empty query string")
            create_should_returnValidRequestModel_when_UrlHasEmptyQueryString();
        SUBCASE("create() should return valid request model and decode the url when url has hexadecimal encoded chars")
            create_should_returnValidRequestModelAndDecodeTheUrl_when_urlPathIsEncoded();
        SUBCASE("create() should return valid request model with unempty path when url is empty")
            create_should_returnValidRequestModelWithUnemptyPath_when_urlIsEmpty();
        SUBCASE("create() should return invalid request model and not crush when request method is empty")
            create_should_returnInvalidRequestModelAndNotCrush_when_RequestMethodIsEmpty();
        SUBCASE("create() should return invalid request model and not crush when http version is empty")
            create_should_returnInvalidRequestModelAndNotCrush_when_RequestMethodIsEmpty();
    }
}
