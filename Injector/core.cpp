#include "core.h"
/*
Manually Map your DLL
Do not use public downloads and source codes
Write everything yourself, do not share your hack

The MDW
*/

DWORD CLibraryLoader::ReturnProcId(std::string processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	std::unique_ptr<CHandleWrap> ptrHandle = std::make_unique<CHandleWrap>();

	if (ptrHandle->m_hHandle == INVALID_HANDLE_VALUE)
	{
		std::cout << "Invalid HANDLE value (Press any key to exit)\n";
		std::cin.get();
		std::terminate();
	}


	Process32First(ptrHandle->m_hHandle, &processInfo);
	if (processName.compare(processInfo.szExeFile))
	{
		return processInfo.th32ProcessID;
	}

	while (Process32Next(ptrHandle->m_hHandle, &processInfo))
	{
		if (processName.compare(processInfo.szExeFile))
		{
			return processInfo.th32ProcessID;
		}
	}

	return 0;
}

/*
bool WINAPI CLibraryLoader::LoadLib(HANDLE hProc, std::string dllPath)
{
	std::unique_ptr<BYTE> pSrcData;
	IMAGE_NT_HEADERS* pOldNtHeader = nullptr;
	IMAGE_OPTIONAL_HEADER* pOldOptionalHeader = nullptr;
	IMAGE_FILE_HEADER* pOldFileHeader = nullptr;
	std::unique_ptr<BYTE> pTargetBase;

	// Error Handling
	if (!GetFileAttributes(dllPath.c_str()))
	{
		std::cerr << "File doesn't exist!\n";
		return false;
	}

	std::ifstream file(dllPath, std::ios::binary | std::ios::ate);

	if (file.fail())
	{
		std::cout << "Failed to open the file" << (DWORD)file.rdstate() << std::endl;
		return false;
	}

	std::size_t fileSize = file.tellg();

	if (fileSize < 0x1000)
	{
		std::cout << "FATAL: filesize is invalid.\n";
		file.close();
		return false;
	}

	pSrcData = std::make_unique<BYTE>(static_cast<UINT_PTR>(fileSize));

	file.seekg(0, std::ios::beg);
	file.read(reinterpret_cast<char*>(pSrcData.get()), fileSize);
	file.close();


	if (reinterpret_cast<IMAGE_DOS_HEADER*>(pSrcData.get())->e_magic != 0x5A4D) // Executable MZ (MS-DOS)
	{
		std::cout << "Invalid file\n";
		pSrcData = nullptr;
		return false;
	}

	pOldNtHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(pSrcData.get() + reinterpret_cast<IMAGE_DOS_HEADER*>(pSrcData.get())->e_lfanew);

	pOldOptionalHeader = &pOldNtHeader->OptionalHeader;
	pOldFileHeader = &pOldNtHeader->FileHeader;

#ifdef _WIN64
	if (pOldFileHeader->Machine != IMAGE_FILE_MACHINE_AMD64)
	{
		std::cout << "Invalid platform\n";
		return false;
	}
#else
	if (pOldFileHeader->Machine != IMAGE_FILE_MACHINE_I386)
	{
		std::cout << "Invalid platform\n";
		return false;
	}
#endif

}
*/