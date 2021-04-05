//#include "main.h"

#pragma once


class CSecure
{
public:
	void Add(DWORD dwAddress, BYTE byteSize);
	int isAddressSecured(DWORD dwAddress);
	//void SDetourAttach(PVOID* ppPointer, PVOID pDetour);
	void memcpy_safe(void* _dest, const void* _src, uint32_t len);
	/*void HookInstallCall(DWORD dwInstallAddress, DWORD dwHookFunction);
	void CreateJump(BYTE* pAddress, DWORD dwJumpTo, DWORD dwLen);*/

	template<class T>
	void Write(DWORD dwAddress, T Value)
	{
		Add(dwAddress, sizeof(Value));
		*(T*)dwAddress = (T)Value;
	}

	struct stMemory
	{
		DWORD dwAddress;
		BYTE origByte;
	} g_Memory;

	std::vector<stMemory> vecMemory;
};
//void RegisterRPCIndex(int rpcID, void(*functionPointer) (RPCParameters* rpcParms));
//void CAC_Checksum(RPCParameters* rpcParms, BYTE* pOutput);
//void CAC_Challenge(RPCParameters* rpcParms);
//void CAC_ReadMemory(RPCParameters* rpcParms);
//std::string RandomString();


extern CSecure* pSecure;
