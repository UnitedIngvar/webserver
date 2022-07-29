#include <string>
#include <iostream>
#include "RequestFactory.hpp"

int main(int argc, char **argv)
{
	std::string httpRequest;

	httpRequest = httpRequest + "GET /hello.html HTTP/1.1" + "\r\n" +
		"User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)" + "\r\n" +
		"Host: www.tutorialspoint.com" + "\r\n" +
		"Accept-Language: en-us" + "\r\n" +
		"Accept-Encoding: gzip, deflate" + "\r\n" +
		"Connection: Keep-Alive" + "\r\n" +
		"\r\n" +
		"Hi there, I'm body!";

	RequestFactory *fact = new RequestFactory();
	Request *request = fact->create(httpRequest);

	std::cout << request->getUrl().getFullUrl().compare("/hello.html") << std::endl;
	std::cout << request->getUrl().getPath().compare("/hello.html") << std::endl;
	std::cout << request->getUrl().getQuery().compare("") << std::endl;
	std::cout << request->getHttpVersion().compare("HTTP/1.1") << std::endl;
	std::map<std::string, std::string> map = request->getHeaders();

	for (std::map<std::string, std::string>::iterator it = map.begin(); it != map.end(); it++)
	{
		std::string key = it->first;
		std::string value = it->second;
		std::cout << "key: " << key << std::endl;
		std::cout << "value: " << value << std::endl;
	}

	std::cout << request->getMessageBody() << std::endl;
}
