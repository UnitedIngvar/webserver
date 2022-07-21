#ifndef FILE_HPP
# define FILE_HPP

# include <string>
# include <fstream>
# include <iostream>

typedef enum FileOperationResult
{
	Success = 1,
	NotFound = 2,
	AccessDenied = 3,
	OpenFailed = 4,
	DeleteFailed = 5,
	DeletePostponed = 6
} FileOperationResult;

class File
{
private:
	std::fstream	_stream;
	std::string		_pathToFile;

public:
	File(std::string const &pathToFile);
	~File();

	std::string			getPathToFile() const;

	FileOperationResult	readFile(std::string &outContent);
	FileOperationResult	createFile();
	FileOperationResult	deleteFile();
	FileOperationResult	writeToFile(std::string const &content);
	FileOperationResult	appendToFile(std::string const &content);

	class FileOpenException : public std::exception
	{
	private:
		std::string			_filePath;

	public:
		FileOpenException(std::string const &filePath);
		virtual ~FileOpenException() throw();

		virtual const char	*what() const throw();
	};
};

#endif
