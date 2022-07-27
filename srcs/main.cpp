#include <string>
#include <iostream>
#include "RequestFactory.hpp"

int main(int argc, char **argv)
{
	std::string httpRequest;

	httpRequest + "GET /hello.htm HTTP/1.1" + "\r\n" +
		"User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)" + "\r\n" +
		"Host: www.tutorialspoint.com" + "\r\n" +
		"Accept-Language: en-us" + "\r\n" +
		"Accept-Encoding: gzip, deflate" + "\r\n" +
		"Connection: Keep-Alive" + "\r\n" +
		"\r\n" +
		"Hi there, I'm body!";

	RequestFactory *fact = new RequestFactory();
	Request *request = fact->create(httpRequest);
}
