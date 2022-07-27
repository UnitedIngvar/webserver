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
	Url(std::string const &fullUrl,
		std::string const &path,
		std::string const &query);
	~Url();

	std::string	const &getFullUrl() const;
	std::string	const &getPath() const;
	std::string	const &getQuery() const;
};

#endif
