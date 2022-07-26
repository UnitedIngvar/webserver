#include "Url.hpp"

Url::Url(
	std::string const &fullUrl,
	std::string const &path,
	std::string const &query,
	std::string const &cgiExtension) :
	_fullUrl(fullUrl),
	_path(path),
	_query(query),
	_cgiExtension(cgiExtension)
{

}

Url::~Url()
{

}

std::string	const &Url::getFullUrl() const { return _fullUrl; }
std::string	const &Url::getPath() const { return _path; }
std::string	const &Url::getQuery() const { return _query; }
std::string	const &Url::getCgiExtension() const { return _cgiExtension; }
