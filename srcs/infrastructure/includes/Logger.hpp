#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <string>
# include <pthread.h>
# include "File.hpp"

// todo: продумать метод регистрации и удаления синглтона в рамках всей программы.

class Logger
{
private:
	static Logger			*_loggerPtr;
	static pthread_mutex_t	_mutex;
	File					_logFile;

	Logger(std::string const &logFilePath);

	void			log(
		std::string const &level,
		std::string const &message,
		std::string const &colorCode);
	void			writeToFile(
		std::string const &level,
		std::string const &timestamp,
		std::string const &message);
	void			writeToTerminal(
		std::string const &level,
		std::string const &timestamp,
		std::string const &message,
		std::string const &colorCode);

public:
	~Logger();

	static Logger	*getInstance(std::string const &logFilePath);

	void			logInfo(std::string const &message);
	void			logWarning(std::string const &message);
	void			logError(std::string const &message);
	void			logCriticalError(std::string const &message);
};

#endif
