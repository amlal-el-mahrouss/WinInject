#include "core.hpp"


int main()
{
	try
	{
		std::string    dllPath;

		std::cout << "Please put a valid dll path:";
		std::cin >> dllPath;

		std::string	targetProgram = "csgo.exe";

		DWORD           procId = LoadLibraryC::ReturnProcId(targetProgram);

		std::unique_ptr<CHandleWrap> ptrHandle = std::make_unique<CHandleWrap>();
		ptrHandle->OpenProc(procId);

		if (FAILED(ptrHandle->Get()))
		{
			MessageBoxExW(nullptr, L"Assertion failed!", L"Uh oh..", MB_ICONEXCLAMATION, MB_OK);
			throw std::exception("Failed to open the proccess!");
		}

		if (!IsWindows10OrGreater() && !LoadLibraryC::LoadLibC(ptrHandle->Get(), dllPath))
		{
			throw std::exception("Failed to Load Library!");
			// throw std::libexception();
		}
	}
	catch (std::exception exp)
	{
		std::cerr << "Exception thrown: " << exp.what() << std::endl;
	}
}