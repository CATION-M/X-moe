//For sono hana1 Only

#include "stdafx.h"
#include <Windows.h>
#include <stdexcept>
#include <string>

//extern "C"
//{
#include "md5.h"
//}

#pragma comment(lib,"libmd5.lib")

using std::string;

//MD5 Decode Key
//From GAMECLASS
//その花びらにくちづけを
static byte key_string[] = { 0x82, 0xBB, 0x82, 0xCC, 0x89, 0xD4, 0x82, 0xD1,  
0x82, 0xE7, 0x82, 0xC9, 0x82, 0xAD, 0x82, 0xBF,
0x82, 0xC3, 0x82, 0xAF, 0x82, 0xF0, 0 };

void Decode(byte* in, size_t size)
{
	//size += 16;
	DWORD loop = (size + 31) & ~31;
	DWORD curbyte = 0;
	for (DWORD i = 0; i < loop; i++)
	{
		char buf[MAX_PATH] = {0};
		md5byte digest[16];
		char xor[32];
		char *p;
		struct MD5Context ctx;

		wsprintfA(buf, "%s%d", key_string, i);
		//printf("%02x %02x %02x\n", key_string[0], key_string[1], key_string[2]);

		MD5Init(&ctx);
		MD5Update(&ctx, (BYTE *)buf, strlen(buf));
		MD5Final(digest, &ctx);

		p = xor;
		DWORD k;
		for ( k= 0; k < 16; k++)
		{
			_snprintf(p, 2, "%02x", digest[k]);
			p += 2;
		}

		for (k = 0; k < 32; k++)
		{
			if (curbyte >= size)
			{
				//MessageBoxW(NULL, L"Fatal Error", L"MSDDecoder", MB_OK);
				//Finish
				return;
			}
			in[curbyte++] ^= xor[k];
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage : %s <infile>\n", argv[0]);
		return  -1;
	}
	FILE* file = nullptr;
	fopen_s(&file, argv[1], "rb");
	if (file == nullptr)
	{
		return -1;
	}
	rewind(file);
	fseek(file, 0, SEEK_END);
	size_t szFileSize = ftell(file);
	rewind(file);
	unsigned char* Buff = nullptr;
	try
	{
		Buff = new unsigned char[szFileSize];
	}
	catch (std::bad_alloc&)
	{
		printf("Failed to allocate!\n");
		return -1;
	}
	catch (...)
	{
		printf("Unknown error\n");
		return -1;
	}

	fread(Buff, 1, szFileSize, file);
	fclose(file);

	static byte Sign[16] = { 0x74, 0x32, 0x25, 0x71, 0x79, 0x25, 0x62, 0x7E, 0x77, 0x18, 0x77, 0x79, 0x78, 0x7C, 0x19, 0x19 };

	if (!memcmp(Buff, Sign, 16))
	{
		//byte* start = Buff + 16;
		byte* start = Buff;
		//size_t size = szFileSize - 16;
		size_t size = szFileSize;
		Decode(start, size);

		FILE* out = fopen((string(argv[1]) + ".out").c_str(), "wb");
		fwrite(start, 1, size, out);
		fclose(out);
	}
	else
	{
		printf("Invalid file\n");
	}
	delete[] Buff;
	return 0;
}



/*
CPU Disasm
Address   Hex dump          Command                                                 Comments
0043E5E0  |> /8B15 A4B85A00 /mov edx,dword ptr [5AB8A4]                             ; ASCII " £G"
0043E5E6  |. |53            |push ebx                                               ; /<%d>
0043E5E7  |. |52            |push edx                                               ; |<%s> => [5AB8A4] //Key
0043E5E8  |. |8D8424 840000 |lea eax,[esp+84]                                       ; |
0043E5EF  |. |68 FCA44700   |push offset 0047A4FC                                   ; |Format = "%s%d"
0043E5F4  |. |50            |push eax                                               ; |Buf => offset LOCAL.67
0043E5F5  |. |FF15 E8824700 |call dword ptr [<&USER32.wsprintfA>]                   ; \USER32.wsprintfA
0043E5FB  |. |83C4 10       |add esp,10
0043E5FE  |. |8D4C24 7C     |lea ecx,[esp+7C]
0043E602  |. |51            |push ecx                                               ; /Arg1 => offset LOCAL.67
0043E603  |. |8D4C24 44     |lea ecx,[esp+44]                                       ; |
0043E607  |. |E8 14480000   |call 00442E20                                          ; \HANABIRA.00442E20 //Md5Init
0043E60C  |. |33D2          |xor edx,edx
0043E60E  |. |895424 1C     |mov dword ptr [esp+1C],edx
0043E612  |. |895424 20     |mov dword ptr [esp+20],edx
0043E616  |. |895424 24     |mov dword ptr [esp+24],edx
0043E61A  |. |895424 28     |mov dword ptr [esp+28],edx
0043E61E  |. |895424 2C     |mov dword ptr [esp+2C],edx
0043E622  |. |895424 30     |mov dword ptr [esp+30],edx
0043E626  |. |895424 34     |mov dword ptr [esp+34],edx
0043E62A  |. |895424 38     |mov dword ptr [esp+38],edx
0043E62E  |. |6A 20         |push 20                                                ; /Arg3 = 20 strlen = 20
0043E630  |. |8D4C24 44     |lea ecx,[esp+44]                                       ; |
0043E634  |. |885424 40     |mov byte ptr [esp+40],dl                               ; |
0043E638  |. |E8 03470000   |call 00442D40                                          ; |
0043E63D  |. |50            |push eax                                               ; |Arg2  buffer
0043E63E  |. |8D4424 24     |lea eax,[esp+24]                                       ; |
0043E642  |. |50            |push eax                                               ; |Arg1 => offset LOCAL.91 Md5-ctx
0043E643  |. |E8 68770000   |call 00445DB0                                          ; \HANABIRA.00445DB0 UpdateMd5
0043E648  |. |83C4 0C       |add esp,0C
0043E64B  |. |33C0          |xor eax,eax
0043E64D  |. |8D49 00       |lea ecx,[ecx]
0043E650  |> |3BF7          |/cmp esi,edi
0043E652  |. |73 40         ||jae short 0043E694 //End
0043E654  |. |8A16          ||mov dl,byte ptr [esi]
0043E656  |. |8A4C04 1C     ||mov cl,byte ptr [eax+esp+1C]
0043E65A  |. |32D1          ||xor dl,cl
0043E65C  |. |8816          ||mov byte ptr [esi],dl
0043E65E  |. |46            ||inc esi
0043E65F  |. |3BF7          ||cmp esi,edi
0043E661  |. |73 31         ||jae short 0043E694
0043E663  |. |8A0E          ||mov cl,byte ptr [esi]
0043E665  |. |8A5404 1D     ||mov dl,byte ptr [eax+esp+1D]
0043E669  |. |32CA          ||xor cl,dl      //Decoding by xor key
0043E66B  |. |880E          ||mov byte ptr [esi],cl
0043E66D  |. |46            ||inc esi
0043E66E  |. |3BF7          ||cmp esi,edi
0043E670  |. |73 22         ||jae short 0043E694 //End
0043E672  |. |8A16          ||mov dl,byte ptr [esi]
0043E674  |. |8A4C04 1E     ||mov cl,byte ptr [eax+esp+1E]
0043E678  |. |32D1          ||xor dl,cl
0043E67A  |. |8816          ||mov byte ptr [esi],dl
0043E67C  |. |46            ||inc esi
0043E67D  |. |3BF7          ||cmp esi,edi
0043E67F  |. |73 13         ||jae short 0043E694
0043E681  |. |8A0E          ||mov cl,byte ptr [esi]
0043E683  |. |8A5404 1F     ||mov dl,byte ptr [eax+esp+1F]
0043E687  |. |32CA          ||xor cl,dl
0043E689  |. |880E          ||mov byte ptr [esi],cl
0043E68B  |. |83C0 04       ||add eax,4
0043E68E  |. |46            ||inc esi
0043E68F  |. |83F8 20       ||cmp eax,20
0043E692  |.^|7C BC         |\jl short 0043E650
0043E694  |> |8B4424 10     |mov eax,dword ptr [esp+10]
0043E698  |. |43            |inc ebx
0043E699  |. |3BD8          |cmp ebx,eax
0043E69B  |.^\0F8C 3FFFFFFF \jl 0043E5E0
0043E6A1  |>  8B75 5C       mov esi,dword ptr [ebp+5C]
0043E6A4  |.  B9 04000000   mov ecx,4
0043E6A9  |.  BF E4015B00   mov edi,offset 005B01E4                                 ; ASCII "MSCENARIO FILE  " //Real Signature
0043E6AE  |.  33C0          xor eax,eax
0043E6B0  |.  F3:A7         repe cmps dword ptr [esi],dword ptr [edi]
0043E6B2  |.  8D4C24 40     lea ecx,[esp+40]
0043E6B6  |.  C78424 880100 mov dword ptr [esp+188],-1
0043E6C1  |.  74 0C         je short 0043E6CF

*/
