#include <Windows.h>
#include "WinFile.h"
#include "CMem.h"

#pragma comment(lib, "ntdll.lib")

typedef struct FileInfo
{
	ULONG Offset;
	ULONG Length;
}FileInfo, *pFileInfo;

typedef struct HeaderPair
{
	ULONG Offset;
	ULONG Length;
}HeaderPair;

typedef struct SSHeader
{
	ULONG szZiped;
	ULONG szOrigianl;
}SSHeader;

typedef struct SceneHeader
{
	ULONG headerLength;
	HeaderPair varInfo;
	HeaderPair varNameIndex;
	HeaderPair varName;
	HeaderPair cmdInfo;
	HeaderPair cmdNameIndex;
	HeaderPair cmdName;
	HeaderPair SceneNameIndex;
	HeaderPair SceneName;
	HeaderPair SceneInfo;
	HeaderPair SceneData;
	ULONG ExtraKeyUse;
	ULONG SourceHeaderLength;
}SceneHeader;


typedef struct CompressHeader
{
	ULONG CompSize;
	ULONG OriSize;
}CompressHeader, *pCompressHeader;


//dynamic
BYTE key1[] =
{
	0x5E, 0x30, 0xBD, 0x1C, 0x45, 0xD0, 0x7D, 0xDB, 0xD5, 0x7F, 0xC2, 0x02, 0xCB, 0x40, 0x83, 0x17,
	0xCA, 0x66, 0xEC, 0x76, 0xE8, 0xE7, 0x12, 0x00, 0xA8, 0x05, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00
};

//const

BYTE key2[] =
{
	0x70, 0xF8, 0xA6, 0xB0, 0xA1, 0xA5, 0x28, 0x4F, 0xB5, 0x2F, 0x48, 0xFA, 0xE1, 0xE9, 0x4B, 0xDE,
	0xB7, 0x4F, 0x62, 0x95, 0x8B, 0xE0, 0x03, 0x80, 0xE7, 0xCF, 0x0F, 0x6B, 0x92, 0x01, 0xEB, 0xF8,
	0xA2, 0x88, 0xCE, 0x63, 0x04, 0x38, 0xD2, 0x6D, 0x8C, 0xD2, 0x88, 0x76, 0xA7, 0x92, 0x71, 0x8F,
	0x4E, 0xB6, 0x8D, 0x01, 0x79, 0x88, 0x83, 0x0A, 0xF9, 0xE9, 0x2C, 0xDB, 0x67, 0xDB, 0x91, 0x14,
	0xD5, 0x9A, 0x4E, 0x79, 0x17, 0x23, 0x08, 0x96, 0x0E, 0x1D, 0x15, 0xF9, 0xA5, 0xA0, 0x6F, 0x58,
	0x17, 0xC8, 0xA9, 0x46, 0xDA, 0x22, 0xFF, 0xFD, 0x87, 0x12, 0x42, 0xFB, 0xA9, 0xB8, 0x67, 0x6C,
	0x91, 0x67, 0x64, 0xF9, 0xD1, 0x1E, 0xE4, 0x50, 0x64, 0x6F, 0xF2, 0x0B, 0xDE, 0x40, 0xE7, 0x47,
	0xF1, 0x03, 0xCC, 0x2A, 0xAD, 0x7F, 0x34, 0x21, 0xA0, 0x64, 0x26, 0x98, 0x6C, 0xED, 0x69, 0xF4,
	0xB5, 0x23, 0x08, 0x6E, 0x7D, 0x92, 0xF6, 0xEB, 0x93, 0xF0, 0x7A, 0x89, 0x5E, 0xF9, 0xF8, 0x7A,
	0xAF, 0xE8, 0xA9, 0x48, 0xC2, 0xAC, 0x11, 0x6B, 0x2B, 0x33, 0xA7, 0x40, 0x0D, 0xDC, 0x7D, 0xA7,
	0x5B, 0xCF, 0xC8, 0x31, 0xD1, 0x77, 0x52, 0x8D, 0x82, 0xAC, 0x41, 0xB8, 0x73, 0xA5, 0x4F, 0x26,
	0x7C, 0x0F, 0x39, 0xDA, 0x5B, 0x37, 0x4A, 0xDE, 0xA4, 0x49, 0x0B, 0x7C, 0x17, 0xA3, 0x43, 0xAE,
	0x77, 0x06, 0x64, 0x73, 0xC0, 0x43, 0xA3, 0x18, 0x5A, 0x0F, 0x9F, 0x02, 0x4C, 0x7E, 0x8B, 0x01,
	0x9F, 0x2D, 0xAE, 0x72, 0x54, 0x13, 0xFF, 0x96, 0xAE, 0x0B, 0x34, 0x58, 0xCF, 0xE3, 0x00, 0x78,
	0xBE, 0xE3, 0xF5, 0x61, 0xE4, 0x87, 0x7C, 0xFC, 0x80, 0xAF, 0xC4, 0x8D, 0x46, 0x3A, 0x5D, 0xD0,
	0x36, 0xBC, 0xE5, 0x60, 0x77, 0x68, 0x08, 0x4F, 0xBB, 0xAB, 0xE2, 0x78, 0x07, 0xE8, 0x73, 0xBF,
	0xD8, 0x29, 0xB9, 0x16, 0x3D, 0x1A, 0x76, 0xD0, 0x87, 0x9B, 0x2D, 0x0C, 0x7B, 0xD1, 0xA9, 0x19,
	0x22, 0x9F, 0x91, 0x73, 0x6A, 0x35, 0xB1, 0x7E, 0xD1, 0xB5, 0xE7, 0xE6, 0xD5, 0xF5, 0x06, 0xD6,
	0xBA, 0xBF, 0xF3, 0x45, 0x3F, 0xF1, 0x61, 0xDD, 0x4C, 0x67, 0x6A, 0x6F, 0x74, 0xEC, 0x7A, 0x6F,
	0x26, 0x74, 0x0E, 0xDB, 0x27, 0x4C, 0xA5, 0xF1, 0x0E, 0x2D, 0x70, 0xC4, 0x40, 0x5D, 0x4F, 0xDA
};


void XOR1(PBYTE Buffer, ULONG Size)
{
	for (ULONG iPos = 0; iPos < Size; iPos++)
	{
		Buffer[iPos] ^= Buffer[iPos % 32];
	}
}

void XOR2(PBYTE Buffer, ULONG Size)
{
	for (ULONG iPos = 0; iPos < Size; iPos++)
	{
		Buffer[iPos] ^= Buffer[iPos % 256];
	}
}

void LzssUnzip(PBYTE CompData, PBYTE DecompStart, PBYTE DecompEnd)
{
	__asm
	{
			mov esi, CompData
			mov edi, DecompStart
			xor edx, edx
			cld
		L1 :
			mov dl, byte ptr[esi]
			inc esi
			mov dh, 0x8

		L2 :
		   cmp edi, DecompEnd
		   je L5
		   test dl, 1
		   je L3
		   movsb
		   jmp L4

	   L3 :
			xor eax, eax
			lods word ptr[esi]
			mov ecx, eax
			shr eax, 4
			and ecx, 0xF
			add ecx, 0x2
			mov ebx, esi
			mov esi, edi
			sub esi, eax
			rep movsb
			mov esi, ebx

		L4 :
			shr dl, 1
			dec dh
			jnz L2
			jmp L1

		L5 :
	}
}


int wmain(int argc, WCHAR* argv[])
{
	WinFile        File;
	WinFile        OutFile;
	ULONG          FileSize;
	PBYTE          FileBuffer;
	WCHAR          scFileName[MAX_PATH];
	WCHAR          InfoString[128];
	SceneHeader*   Header;
	HeaderPair*    SceneNameLength;
	WCHAR*         SceneNameString;
	HeaderPair*    SceneDataInfo;
	PBYTE          SceneData;
	CompressHeader CompHeader;
	PBYTE          CompData;
	PBYTE          DecompBuff;
	PBYTE          DecompEnd;

	RtlZeroMemory(scFileName, MAX_PATH * 2);
	Header = nullptr;
	SceneNameLength = nullptr;
	SceneNameString = nullptr;
	SceneDataInfo = nullptr;
	SceneData = nullptr;
	FileBuffer = nullptr;
	CompData = nullptr;
	FileSize = 0;

	if (argc != 2)
	{
		return 0;
	}
	
	if (FAILED(File.Open(argv[1], WinFile::FileRead)))
	{
		return 0;
	}
	FileSize = File.GetSize32();
	FileBuffer = (PBYTE)CMem::Alloc(FileSize);
	if (FileBuffer == nullptr)
	{
		return 0;
	}
	File.Read(FileBuffer, FileSize);
	File.Release();

	Header = (SceneHeader*)FileBuffer;
	SceneNameLength = (HeaderPair*)&FileBuffer[Header->SceneNameIndex.Offset];
	SceneNameString = (WCHAR*)&FileBuffer[Header->SceneName.Offset];
	SceneDataInfo = (HeaderPair*)&FileBuffer[Header->SceneInfo.Offset];
	SceneData = (PBYTE)&FileBuffer[Header->SceneData.Offset];

	for (ULONG i = 0; i<Header->SceneNameIndex.Length; i++)
	{
		RtlZeroMemory(InfoString, 256);
		RtlCopyMemory(scFileName, 0, MAX_PATH);
		lstrcpynW(scFileName, &SceneNameString[SceneNameLength[i].Offset], SceneNameLength[i].Length);
		
		wsprintfW(InfoString, L"_%d", i);
		lstrcatW(scFileName, InfoString);
		lstrcatW(scFileName, L".ss");
		CompData = &SceneData[SceneDataInfo[i].Offset];
		XOR1(CompData, SceneDataInfo[i].Length);
		XOR2(CompData, SceneDataInfo[i].Length);

		RtlCompareMemory(&CompHeader, CompData, sizeof(CompHeader));

		DecompBuff = (PBYTE)CMem::Alloc(CompHeader.OriSize);
		DecompEnd = DecompBuff + CompHeader.OriSize;

		RtlZeroMemory(DecompBuff, CompHeader.CompSize);
		RtlCopyMemory(DecompBuff, CompData + 8, CompHeader.OriSize);

		LzssUnzip(CompData + sizeof(CompHeader), DecompBuff, DecompEnd);

		if (!FAILED(OutFile.Open(scFileName, WinFile::FileWrite)))
		{
			OutFile.Write(DecompBuff, CompHeader.OriSize);
			OutFile.Release();
		}

		CMem::Free(DecompBuff);
	}
	return 0;
}
