#include "Stdafx.h"

CFileManager * CFileManager::Singleten = NULL;

CFileManager * CFileManager::GetInstance()
{
	if (Singleten == NULL)
		Singleten = new CFileManager();

	return Singleten;
}


CFileManager::CFileManager()
{
}

CFileManager::~CFileManager(void)
{
}

std::string CFileManager::fullPathForFilename(const std::string &filename)
{
	if (isAbsolutePath(filename))
	{
		return filename;
	}

	// Already Cached ?
	auto cacheIter = _fullPathCache.find(filename);
	if (cacheIter != _fullPathCache.end())
	{
		return cacheIter->second;
	}

	// Get the new file name.
	const std::string newFilename(getNewFilename(filename));

	std::string fullpath;

	for (auto searchIt = _searchPathArray.cbegin(); searchIt != _searchPathArray.cend(); ++searchIt)
	{
		for (auto resolutionIt = _searchResolutionsOrderArray.cbegin(); resolutionIt != _searchResolutionsOrderArray.cend(); ++resolutionIt)
		{
			fullpath = this->getPathForFilename(newFilename, *resolutionIt, *searchIt);

			if (fullpath.length() > 0)
			{
				// Using the filename passed in as key.
				_fullPathCache.insert(std::make_pair(filename, fullpath));
				return fullpath;
			}
		}
	}

	Log("cocos2d: fullPathForFilename: No file found at %s. Possible missing file.", filename.c_str());

	// XXX: Should it return nullptr ? or an empty string ?
	// The file wasn't found, return the file name passed in.
	return filename;

}

bool CFileManager::isAbsolutePath(const std::string& path) const
{
	return (path[0] == '/');
}

std::string CFileManager::getNewFilename(const std::string &filename) const
{
	std::string newFileName;

	// in Lookup Filename dictionary ?
	auto iter = _filenameLookupDict.find(filename);

	if (iter == _filenameLookupDict.end())
	{
		newFileName = filename;
	}
	else
	{
		newFileName = iter->second.asString();
	}
	return newFileName;

}

std::string CFileManager::getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath)
{
	std::string file = filename;
	std::string file_path = "";
	size_t pos = filename.find_last_of("/");
	if (pos != std::string::npos)
	{
		file_path = filename.substr(0, pos + 1);
		file = filename.substr(pos + 1);
	}

	// searchPath + file_path + resourceDirectory
	std::string path = searchPath;
	path += file_path;
	path += resolutionDirectory;

	path = getFullPathForDirectoryAndFilename(path, file);

	//CCLOG("getPathForFilename, fullPath = %s", path.c_str());
	return path;
}

static CData getData(const std::string& filename, bool forString)
{
	if (filename.empty())
	{
		return CData::Null;
	}

	CData ret;
	unsigned char* buffer = nullptr;
	ssize_t size = 0;
	const char* mode = nullptr;
	if (forString)
		mode = "rt";
	else
		mode = "rb";

	do
	{
		// Read the file from hardware
		std::string fullPath = CFileManager::GetInstance()->fullPathForFilename(filename);
		FILE *fp;// = fopen(fullPath.c_str(), mode);
		fopen_s(&fp,fullPath.c_str(), mode);
		if (!fp) break;
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		if (forString)
		{
			buffer = (unsigned char*)malloc(sizeof(unsigned char)* (size + 1));
			buffer[size] = '\0';
		}
		else
		{
			buffer = (unsigned char*)malloc(sizeof(unsigned char)* size);
		}

		size = fread(buffer, sizeof(unsigned char), size, fp);
		fclose(fp);
	} while (0);

	if (nullptr == buffer || 0 == size)
	{
		std::string msg = "Get data from file(";
		msg.append(filename).append(") failed!");
		Log("%s", msg.c_str());
	}
	else
	{
		ret.fastSet(buffer, size);
	}

	return ret;
}

CData CFileManager::getDataFromFile(const std::string& filename)
{
	return getData(filename, false);
}

std::string CFileManager::getFullPathForDirectoryAndFilename(const std::string& directory, const std::string& filename)
{
	// get directory+filename, safely adding '/' as necessary 
	std::string ret = directory;
	if (directory.size() && directory[directory.size() - 1] != '/'){
		ret += '/';
	}
	ret += filename;

	// if the file doesn't exist, return an empty string
	if (!isFileExistInternal(ret)) {
		ret = "";
	}
	/*
	bool FileUtilsWin32::isFileExistInternal(const std::string& strFilePath) const

	*/
	return ret;
}

bool CFileManager::isFileExistInternal(const std::string& strFilePath) const
{
	if (0 == strFilePath.length())
	{
		return false;
	}

	std::string strPath = strFilePath;
	if (!isAbsolutePath(strPath))
	{ // Not absolute path, add the default root path at the beginning.
		strPath.insert(0, _defaultResRootPath);
	}

	WCHAR utf16Buf[512] = { 0 };
	MultiByteToWideChar(CP_UTF8, 0, strPath.c_str(), -1, utf16Buf, sizeof(utf16Buf) / sizeof(utf16Buf[0]));

	DWORD attr = GetFileAttributesW(utf16Buf);
	if (attr == INVALID_FILE_ATTRIBUTES || (attr & FILE_ATTRIBUTE_DIRECTORY))
		return false;   //  not a file
	return true;

}
