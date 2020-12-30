#include "core.hpp"
DWORD LoadLibraryC::ReturnProcId(std::string processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	std::unique_ptr<CHandleWrap> ptrHandle = std::make_unique<CHandleWrap>();
	ptrHandle->ProcSnapshot();

	if (ptrHandle->Get() == INVALID_HANDLE_VALUE)
	{
		std::cout << "Invalid HANDLE value (Press any key to exit)\n";
		std::cin.get();
		std::terminate();
	}


	Process32First(ptrHandle->Get(), &processInfo);
	if (processName.compare(processInfo.szExeFile))
	{
		return processInfo.th32ProcessID;
	}

	while (Process32Next(ptrHandle->Get(), &processInfo))
	{
		if (processName.compare(processInfo.szExeFile))
		{
			return processInfo.th32ProcessID;
		}
	}

	return 0;
}
