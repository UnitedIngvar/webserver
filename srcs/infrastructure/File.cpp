#include "File.hpp"
#include <sys/stat.h>
#include <unistd.h>

File::File(std::string const &pathToFile) :
	_pathToFile(pathToFile)
{

}

File::~File()
{
	if (_stream.is_open())
	{
		_stream.close();
	}
}


std::string	File::getPathToFile() const { return _pathToFile; }


FileOperationResult	File::readFile(std::string &outContent)
{
	if (access(_pathToFile.c_str(), F_OK) != 0)
	{
		return NotFound;
	}
	if (access(_pathToFile.c_str(), R_OK | X_OK) != 0)
	{
		return AccessDenied;
	}

	_stream.open(_pathToFile);
	if (!_stream.is_open())
	{
		_stream.clear();
		return OpenFailed;
	}

	std::string line;
	while (!_stream.eof())
	{
		std::getline(_stream, line);
		outContent.append(line);
	}

	_stream.clear();
	_stream.close();
	return Success;
}

FileOperationResult			File::createFile()
{
	_stream.open(_pathToFile);

	//todo: сделать проверку на возможность поиска?
	if (_stream.is_open())
	{
		_stream.clear();
		return OpenFailed;
	}

	_stream.close();
	return Success;
}

FileOperationResult			File::deleteFile()
{
	if (access(_pathToFile.c_str(), F_OK) != 0)
	{
		return NotFound;
	}
	if (access(_pathToFile.c_str(), W_OK | X_OK) != 0)
	{
		return AccessDenied;
	}


	if (std::remove(_pathToFile.c_str()) != 0)
	{
		return DeleteFailed;
	}
	if (access(_pathToFile.c_str(), F_OK) == 0)
	{
		return DeletePostponed;
	}

	return Success;
}

FileOperationResult			File::writeToFile(std::string content)
{
	if (access(_pathToFile.c_str(), F_OK) != 0)
	{
		return NotFound;
	}
	if (access(_pathToFile.c_str(), W_OK | X_OK) != 0)
	{
		return AccessDenied;
	}

	_stream.open(_pathToFile);
	if (!_stream.is_open())
	{
		_stream.clear();
		return OpenFailed;
	}

	_stream << content;

	_stream.clear();
	_stream.close();
	return Success;
}
