#pragma once

#include "def.hpp"
#define WIN32_LEAN_AND_MEAN



/*
* type: struct
* name: LoadLibraryC
* Made by: \mfw
* Purpose: Loads the library using the manual mapping technique
*/
struct LoadLibraryC 
{
public:
	static std::uint32_t ReturnProcId(std::string processName);
	static bool WINAPI LoadLibC(HANDLE hProc, std::string dllPath);

private:
	std::unique_ptr<Byte> m_pSourceData;
	IMAGE_NT_HEADERS* pOldNtHeader = nullptr;
	IMAGE_OPTIONAL_HEADER* pOldOptionalHeader = nullptr;
	IMAGE_FILE_HEADER* pOldFileHeader = nullptr;
	BYTE* pTargetBase = nullptr;

};

/*
* Made by: \mfw
* name: CHandleWrap
* Purpose: handles the processes snapshot
*/
class CHandle
{
public:
	CHandle() = delete;

	CHandle(HANDLE handle)
		: m_hHandle(handle)
	{}

	~CHandle() noexcept
	{
		if (m_hHandle)
			CloseHandle(m_hHandle);
	}

public:
	void OpenProc(DWORD procId)
	{
		m_hHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
	}

	void ProcSnapshot()
	{
		m_hHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	}

	HANDLE Get() noexcept
	{
		return m_hHandle;
	}

private:
	HANDLE m_hHandle;

};