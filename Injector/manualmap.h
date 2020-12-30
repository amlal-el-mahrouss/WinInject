#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>

#define FAILURE 1
#define SUCCESS 0

/*
* Purpose : Wrap the PE Handling
* Made by : \mfw 
*/

// DIRTY CODE NEED TO CLEAN
class CWrapPE
{
public:
	template <typename T>
	CWrapPE(T& image, int mode)
	{
		switch (mode)
		{
		case 1:
			m_pOldNtHeader = image;
			break;
		case 2:
			m_pOldOptionalHeader = image;
			break;
		case 3:
			m_pOldFileHeader = image;
			break;
		}

		m_mode = mode;
	}

	template <typename T>
	static T Get() noexcept
	{
		switch (m_mode)
		{
		case 1:
			return m_pOldNtHeader;
		case 2:
			return m_pOldOptionalHeader;
		case 3:
			return m_pOldFileHeader;
		}
	}

	~CWrapPE() noexcept
	{
		switch (m_mode)
		{
		case 1:
			delete m_pOldNtHeader;
			break;
		case 2:
			delete m_pOldOptionalHeader;
			break;
		case 3:
			delete m_pOldFileHeader;
			break;
		}
	}

private:
	IMAGE_NT_HEADERS* m_pOldNtHeader = nullptr;
	IMAGE_OPTIONAL_HEADER* m_pOldOptionalHeader = nullptr;
	IMAGE_FILE_HEADER* m_pOldFileHeader = nullptr;
	int m_mode;

};

/*
* Loads the library using these tools in this file
*/
struct CLibraryLoader
{
	static DWORD ReturnProcId(std::string processName);
	static bool WINAPI LoadLib(HANDLE hProc, std::string dllPath);
};

/*
* Made by : \mfw
* Purpose: handles the processes snapshot
*/
class CHandleWrap
{
public:
	CHandleWrap()
	{
		ProcSnapshot();
	}

	CHandleWrap(HANDLE handle)
		: m_hHandle(handle)
	{}

	void ProcSnapshot()
	{
		m_hHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	}

	template <typename T>
	void SetHandleFunc(std::function<T> func)
	{
		m_hHandle = func();
	}

	~CHandleWrap() noexcept
	{
		CloseHandle(m_hHandle);
	}

public:
	HANDLE m_hHandle;

};