#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>

/*
* Made by: \mfw
* Purpose: Loads the library using the manual mapping technique
*/
struct LoadLibraryC 
{
	static DWORD ReturnProcId(std::string processName);
	static bool WINAPI LoadLibCustom(HANDLE hProc, std::string dllPath);
};

/*
* Made by: \mfw
* Purpose: handles the processes snapshot
*/
class CHandleWrap
{
public:
	CHandleWrap() = delete;

	CHandleWrap(HANDLE handle)
		: m_hHandle(handle)
	{}

	~CHandleWrap() noexcept
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

	template <typename T>
	void Set(std::function<T> func)
	{
		m_hHandle = func();
	}

	HANDLE Get() noexcept
	{
		return m_hHandle;
	}

private:
	HANDLE m_hHandle;

};