#include "manualmap.h"

int main()
{
	std::string dllPath;
	std::string	targetProgram = "csgo.exe";

	DWORD procId = CLibraryLoader::ReturnProcId(targetProgram);

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);


	if (FAILED(hProc))
	{
		DWORD err = GetLastError();
		MessageBoxExW(nullptr, L"Assertion failed!", L"Uh oh..", MB_ICONEXCLAMATION, MB_OK);
		throw std::exception("Failed to open the proccess!");
	}

	if (!CLibraryLoader::LoadLib(hProc, dllPath))
	{
		CloseHandle(hProc);
		MessageBoxExW(nullptr, L"Assertion failed!", L"Uh oh..", MB_ICONEXCLAMATION, MB_OK);
		throw std::exception("Failed to Load Library!");
		// throw std::libexception();
	}

	CloseHandle(hProc);
}