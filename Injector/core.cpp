#include "core.hpp"
std::uint32_t LoadLibraryC::ReturnProcId(std::string processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	std::unique_ptr<CHandle> m_ptrHandle = std::make_unique<CHandle>();
	m_ptrHandle->ProcSnapshot();

	if (m_ptrHandle->Get() == INVALID_HANDLE_VALUE)
	{
		std::cout << "Invalid HANDLE value (Press any key to exit)\n";
		std::cin.get();
		std::terminate();
	}


	Process32First(m_ptrHandle->Get(), &processInfo);
	if (processName.compare(processInfo.szExeFile))
	{
		return processInfo.th32ProcessID;
	}

	while (Process32Next(m_ptrHandle->Get(), &processInfo))
	{
		if (processName.compare(processInfo.szExeFile))
		{
			return processInfo.th32ProcessID;
		}
	}

	return 0;
}

bool WINAPI LoadLibraryC::LoadLibC(HANDLE hProc, std::string dllPath)
{
	if (!GetFileAttributesA(dllPath.c_str()))
	{
		MessageBoxExW(nullptr, L"File doesn't exist!", L"Uh oh..", MB_ICONEXCLAMATION, MB_OK);
		return false;
	}
}