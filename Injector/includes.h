#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>

#define WIN32_LEAN_AND_MEAN

#pragma region Globals
std::string dll_path;
std::string program_to_attach = "notepad++.exe";
DWORD dw_main_process_id = 0x00;

DWORD Win32ReturnProcessId(PCHAR pProcess_name)
{
	HANDLE hToolHelper = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0x00);
	PROCESSENTRY32 p32ProcessEntry = { 0 };
	p32ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	if (hToolHelper != 0)
	{

	}
}