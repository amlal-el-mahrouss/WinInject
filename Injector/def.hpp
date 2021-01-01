#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <cassert>
#include <optional>
#include <VersionHelpers.h>
#include <fstream>
#include <functional>
#include <string>
#include <cstdlib>
#include <TlHelp32.h>
#include <winerror.h>

#ifdef _WIN64
using Long = std::int64_t;
using ULong = std::uint64_t;
using LongPtr = std::int64_t*;
using ULongPtr = std::uint64_t*;
#else
using Long = std::int32_t;
using ULong = std::uint32_t;
using LongPtr = std::int32_t*;
using ULongPtr = std::uint32_t*;
#endif // _WIN64
using Byte = std::int8_t;
using WByte = std::int16_t;
using IntPtr = std::intptr_t;
using UByte = std::uint8_t;
using UWByte = std::uint16_t;
using UIntPtr = std::intptr_t;

using MBString = std::wstring;
