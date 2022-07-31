/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestFactoryTests.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcrakeha <hcrakeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:06:52 by hcrakeha          #+#    #+#             */
/*   Updated: 2022/07/31 17:44:03 by hcrakeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include "RequestFactory.hpp"
#include <iostream> // todo: erase
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
    delete request;
    delete factory;
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
    delete request;
    delete factory;
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
    delete request;
    delete factory;
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
    delete request;
    delete factory;
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
    delete request;
    delete factory;
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
    delete request;
    delete factory;
}

static void create_should_returnValidRequestModelAndNotCrush_when_RequestMethodIsEmpty()
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
    delete request;
    delete factory;
}

static void create_should_returnValidRequestModelAndNotCrush_when_HttpVersionIsEmpty()
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
    delete request;
    delete factory;
}

static void create_should_returnValidRequestModelAndNotCrush_when_headerSectionIsEmpty()
{
    // Arrange
    std::string method = "GET";
    std::string path = "/hello/world/test";
    std::string query = "testVal=10";
    std::string url = create_url(path, query);
    std::string httpVersion = "HTTP/1.1";
    auto requestLine = create_request_line(method, url, httpVersion);

    auto headerSection = "\r\n";

    std::string body = "There are no headers between me and request line";

    auto httpRequest = requestLine +
		headerSection +
        "\r\n" +
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
    REQUIRE_EQ(request->getHeaders().empty(), true);
    delete request;
    delete factory;
}

static void create_should_returnValidRequestModelAndNotCrush_when_headerSectionANDhttpVersionsAreEmpty()
{
    // Arrange
    std::string method = "GET";
    std::string path = "/hello/world/test";
    std::string query = "testVal=10";
    std::string url = create_url(path, query);
    std::string httpVersion = "";
    auto requestLine = create_request_line(method, url, httpVersion);

    auto headerSection = "\r\n";

    std::string body = "There are no headers between me and request line";

    auto httpRequest = requestLine +
		headerSection +
        "\r\n" +
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
    REQUIRE_EQ(request->getHeaders().empty(), true);
    delete request;
    delete factory;
}

static void create_should_returnValidRequestModelAndNotCrush_when_AllSectionsAreEmpty()
{
    // Arrange
    std::string method = "";
    std::string path = "";
    std::string query = "";
    std::string url = create_url(path, query);
    std::string httpVersion = "";
    auto requestLine = create_request_line(method, url, httpVersion);

    auto headerSection = "\r\n";

    std::string body = "";

    auto httpRequest = requestLine +
		headerSection +
        "\r\n" +
        body;

    // Act
    auto *factory = new RequestFactory();
    auto *request = factory->create(httpRequest);

    // Assert
    REQUIRE_EQ(request->getMethod(), INVALID);
    REQUIRE_EQ(request->getUrl().getFullUrl(), "/");
    REQUIRE_EQ(request->getUrl().getPath(), "/");
    REQUIRE_EQ(request->getUrl().getQuery(), query);
    REQUIRE_EQ(request->getHttpVersion(), httpVersion);
    REQUIRE_EQ(request->getMessageBody(), body);
    REQUIRE_EQ(request->getHeaders().empty(), true);
    delete request;
    delete factory;
}

static void create_should_returnInvalidRequestModelAndNotCrush_when_EmptyStringIsPassed()
{
    // Arrange
    auto httpRequest = "";

    // Act
    RequestFactory *factory = new RequestFactory();
    Request *request = factory->create(httpRequest);

    // Assert
    std::string expected = "";
    REQUIRE_EQ(request->getMethod(), INVALID);
    REQUIRE_EQ(request->getUrl().getFullUrl(), expected);
    REQUIRE_EQ(request->getUrl().getPath(), expected);
    REQUIRE_EQ(request->getUrl().getQuery(), expected);
    REQUIRE_EQ(request->getHttpVersion(), expected);
    REQUIRE_EQ(request->getMessageBody(), expected);
    REQUIRE_EQ(request->getHeaders().empty(), true);
    delete request;
    delete factory;
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
        SUBCASE("create() should return valid request model and not crush when request method is empty")
            create_should_returnValidRequestModelAndNotCrush_when_RequestMethodIsEmpty();
        SUBCASE("create() should return valid request model and not crush when http version is empty")
            create_should_returnValidRequestModelAndNotCrush_when_RequestMethodIsEmpty();
        SUBCASE("create() should return valid request model and not crush when header section is empty")
            create_should_returnValidRequestModelAndNotCrush_when_headerSectionIsEmpty();
        SUBCASE("create() should return valid request model and not crush when header section and http vsrions are empty")
            create_should_returnValidRequestModelAndNotCrush_when_headerSectionANDhttpVersionsAreEmpty();
        SUBCASE("create() should return valid request model and not crush when all sections are empty")
            create_should_returnValidRequestModelAndNotCrush_when_AllSectionsAreEmpty();
        SUBCASE("create() should return valid request model and not crush when empty string is passed")
            create_should_returnInvalidRequestModelAndNotCrush_when_EmptyStringIsPassed();
    }
}
