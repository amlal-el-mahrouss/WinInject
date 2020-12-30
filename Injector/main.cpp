#include "core.hpp"


int main()
{
	std::string    dllPath;
	std::string	targetProgram = "csgo.exe";

	DWORD           procId        = LoadLibraryC::ReturnProcId(targetProgram);

	std::unique_ptr<CHandleWrap> ptrHandle = std::make_unique<CHandleWrap>();
	ptrHandle->OpenProc(procId);

	if (FAILED(ptrHandle->Get()))
	{
		MessageBoxExW(nullptr, L"Assertion failed!", L"Uh oh..", MB_ICONEXCLAMATION, MB_OK);
		throw std::exception("Failed to open the proccess!");
	}

	if (!LoadLibraryC::LoadLibCustom(ptrHandle->Get(), dllPath))
	{
		MessageBoxExW(nullptr, L"Assertion failed!", L"Uh oh..", MB_ICONEXCLAMATION, MB_OK);
		throw std::exception("Failed to Load Library!");
		// throw std::libexception();
	}
}