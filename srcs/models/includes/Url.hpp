#ifndef URL_HPP
# define URL_HPP

# include <string>

class Url
{
private:
	std::string	_fullUrl;
	std::string	_path;
	std::string	_query;

public:
	Url(std::string fullUrl,
		std::string path,
		std::string query);
	~Url();

	std::string	getFullUrl() const;
	std::string	getPath() const;
	std::string	getQuery() const;
};

#endif
