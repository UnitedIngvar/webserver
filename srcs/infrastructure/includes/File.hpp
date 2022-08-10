#ifndef FILE_HPP
# define FILE_HPP

# include <string>
# include <fstream>
# include <iostream>

typedef enum FileOperationResult
{
	Success = 1,
	FileNotFound = 2,
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
	FileOperationResult checkCanBeAccessed();
	static std::string getResultStringFormat(FileOperationResult result);

};

#endif
