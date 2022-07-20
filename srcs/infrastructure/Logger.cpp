#include "File.hpp"
#include "Logger.hpp"
#include "Colors.hpp"
#include <ctime>

pthread_mutex_t	Logger::_mutex = PTHREAD_MUTEX_INITIALIZER;
Logger			*Logger::_loggerPtr = nullptr;

Logger::Logger(std::string const &logFilePath) :
	_logFile(logFilePath)
{
	FileOperationResult result = _logFile.createFile();

	if (result != Success)
	{
		throw new File::FileOpenException(logFilePath);
	}
}

Logger::~Logger()
{
	pthread_mutex_destroy(&_mutex);
}

void			Logger::writeToFile(
	std::string const &level,
	std::string const &timestamp,
	std::string const &message)
{
	std::string log = level + " : "
		+ timestamp + " : "
		+ message + "\n";

	_logFile.appendToFile(log);
}

void	Logger::writeToTerminal(
	std::string const &level,
	std::string const &timestamp,
	std::string const &message,
	std::string const &colorCode)
{
	std::cout << colorCode << level << RESET << " : "
		<< timestamp << " : "
		<< message << std::endl;
}

Logger	*Logger::getInstance(std::string const &pathToFile)
{
	pthread_mutex_lock(&_mutex);

	if (_loggerPtr == nullptr)
	{
		_loggerPtr = new Logger(pathToFile);
	}

	pthread_mutex_unlock(&_mutex);

	return _loggerPtr;
}

void			Logger::logInfo(std::string const &message)
{
	const std::string logLevel = "[INFO]";
	const std::string colorCode = GREEN;

	std::time_t time = std::time(nullptr);
	std::string currentTime = std::ctime(&time);
	currentTime = currentTime.erase(currentTime.length() - 1, 1);

	pthread_mutex_lock(&_mutex);
	writeToTerminal(logLevel, currentTime, message, colorCode);
	writeToFile(logLevel, currentTime, message);
	pthread_mutex_unlock(&_mutex);
}

void			Logger::logWarning(std::string const &message)
{
	const std::string logLevel = "[WARN]";
	const std::string colorCode = YELLOW;

	std::time_t time = std::time(nullptr);
	std::string currentTime = std::ctime(&time);
	currentTime = currentTime.erase(currentTime.length() - 1, 1);

	pthread_mutex_lock(&_mutex);
	writeToTerminal(logLevel, currentTime, message, colorCode);
	writeToFile(logLevel, currentTime, message);
	pthread_mutex_unlock(&_mutex);
}

void			Logger::logError(std::string const &message)
{
	const std::string logLevel = "[ERR]";
	const std::string colorCode = RED;

	std::time_t time = std::time(nullptr);
	std::string currentTime = std::ctime(&time);
	currentTime = currentTime.erase(currentTime.length() - 1, 1);

	pthread_mutex_lock(&_mutex);
	writeToTerminal(logLevel, currentTime, message, colorCode);
	writeToFile(logLevel, currentTime, message);
	pthread_mutex_unlock(&_mutex);
}

void			Logger::logCriticalError(std::string const &message)
{
	const std::string logLevel = "[CRIT ERR]";
	const std::string colorCode = PURPLE;

	std::time_t time = std::time(nullptr);
	std::string currentTime = std::ctime(&time);
	currentTime = currentTime.erase(currentTime.length() - 1, 1);

	pthread_mutex_lock(&_mutex);
	writeToTerminal(logLevel, currentTime, message, colorCode);
	writeToFile(logLevel, currentTime, message);
	pthread_mutex_unlock(&_mutex);
}
