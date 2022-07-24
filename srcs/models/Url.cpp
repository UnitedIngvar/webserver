#include "Url.hpp"

Url::Url(std::string fullUrl,
	std::string path,
	std::string query) :
	_fullUrl(fullUrl),
	_path(path),
	_query(query)
{

}

Url::~Url()
{

}

std::string	Url::getFullUrl() const { return _fullUrl; }
std::string	Url::getPath() const { return _path; }
std::string	Url::getQuery() const { return _query; }
