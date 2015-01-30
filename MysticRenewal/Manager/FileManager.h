#pragma once
#include "Stdafx.h"

class CFileManager
{
private:
	static CFileManager* Singleten;
	CFileManager();
public:
	static CFileManager* GetInstance();

	virtual ~CFileManager();


	virtual std::string fullPathForFilename(const std::string &filename);

	virtual bool isAbsolutePath(const std::string& path) const;

	virtual std::string getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath);

	virtual std::string getFullPathForDirectoryAndFilename(const std::string& directory, const std::string& filename);

	virtual bool isFileExistInternal(const std::string& strFilePath) const;

	virtual CData getDataFromFile(const std::string& filename);

	virtual std::string getNewFilename(const std::string &filename) const;


	std::string _defaultResRootPath;
	std::unordered_map<std::string, std::string> _fullPathCache;
	CValueMap _filenameLookupDict;
	std::vector<std::string> _searchPathArray;
	std::vector<std::string> _searchResolutionsOrderArray;

};

