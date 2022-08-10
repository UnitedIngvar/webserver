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
		return FileNotFound;
	}
	if (access(_pathToFile.c_str(), R_OK | X_OK) != 0)
	{
		return AccessDenied;
	}

	_stream.open(_pathToFile, std::fstream::in);
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

FileOperationResult	File::createFile()
{
	_stream.open(_pathToFile, std::fstream::out);
	//todo: сделать проверку на возможность поиска?
	if (!_stream.is_open())
	{
		_stream.clear();
		return OpenFailed;
	}

	_stream.close();
	return Success;
}

FileOperationResult	File::deleteFile()
{
	if (access(_pathToFile.c_str(), F_OK) != 0)
	{
		return FileNotFound;
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

FileOperationResult	File::writeToFile(std::string const &content)
{
	if (access(_pathToFile.c_str(), F_OK) != 0)
	{
		return FileNotFound;
	}
	if (access(_pathToFile.c_str(), W_OK) != 0)
	{
		return AccessDenied;
	}

	_stream.open(_pathToFile, std::fstream::out);
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

FileOperationResult	File::appendToFile(std::string const &content)
{
	if (access(_pathToFile.c_str(), F_OK) != 0)
	{
		return FileNotFound;
	}
	if (access(_pathToFile.c_str(), W_OK) != 0)
	{
		return AccessDenied;
	}

	_stream.open(_pathToFile.c_str(), std::fstream::in | std::fstream::app);

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

FileOperationResult File::checkCanBeAccessed()
{
	if (access(_pathToFile.c_str(), F_OK) != 0)
	{
		return FileNotFound;
	}
	if (access(_pathToFile.c_str(), R_OK) != 0)
	{
		return AccessDenied;
	}
	return Success;
}

std::string File::getResultStringFormat(FileOperationResult result)
{
	switch (result)
	{
		case Success:
			return "Success";
		case FileNotFound:
			return "Not Found";
		case AccessDenied:
			return "Access Denied";
		case OpenFailed:
			return "Open Failed";
		case DeleteFailed:
			return "Delete Failed";
		case DeletePostponed:
			return "Delete Postponed";
		default:
			return "Unknown result code";
	}
}
