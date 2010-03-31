/*****************************************************************************
    MQ2Main.dll: MacroQuest2's extension DLL for EverQuest
    Copyright (C) 2002-2003 Plazmic, 2003-2005 Lax

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
******************************************************************************/

#pragma once
#include <isxdk.h>

class EQProtected
{
public:
   EQProtected(unsigned long p_Address, unsigned long p_Size)
   {
      Address=p_Address;
      Size=p_Size;
      Array=(unsigned char*)malloc(p_Size);
      memcpy(Array,(char *)p_Address, p_Size);
   }

   ~EQProtected()
   {
      free(Array);
   }

   inline bool Contains(unsigned long TestAddress)
   {
      return (TestAddress>=Address && TestAddress<Address+Size);
   }
   
   unsigned long Address;
   unsigned long Size;
   unsigned char *Array;
}; 

class CISXEQ :
	public ISXInterface
{
public:
	CISXEQ(void);
	~CISXEQ(void);

	virtual bool Initialize(ISInterface *p_ISInterface);
	virtual void Shutdown();

	void ConnectServices();
	void RegisterCommands();
	void RegisterAliases();
	void RegisterDataTypes();
	void RegisterTopLevelObjects();
	void RegisterServices();

	void DisconnectServices();
	void UnRegisterCommands();
	void UnRegisterAliases();
	void UnRegisterDataTypes();
	void UnRegisterTopLevelObjects();
	void UnRegisterServices();

   inline unsigned char FindByte(unsigned long Address, unsigned char Default)
   {
      for (unsigned long i = 0 ; i < ProtectedList.Size ; i++)
      if (EQProtected *pProtected=ProtectedList[i])
      {
         if (pProtected->Contains(Address))
         {
            return pProtected->Array[Address-pProtected->Address];
         }
      }
      return Default;
   } 
	 VOID HookMemChecker(BOOL Patch); 
	bool Protect(unsigned long Address, unsigned long Size); 
	 bool UnProtect(unsigned long Address); 
	CIndex<EQProtected*> ProtectedList; 
};

extern ISInterface *pISInterface;
extern HISXSERVICE hPulseService;
extern HISXSERVICE hMemoryService;
extern HISXSERVICE hHTTPService;
extern CISXEQ *pExtension;
#define printf pISInterface->Printf

#define EzDetour(Address, Detour, Trampoline) IS_Detour(pExtension,pISInterface,hMemoryService,(unsigned long)Address,Detour,Trampoline)
#define EzUnDetour(Address) IS_UnDetour(pExtension,pISInterface,hMemoryService,(unsigned long)Address)

#define EzModify(Address,NewData,Length) Memory_Modify(pExtension,pISInterface,hMemoryService,(unsigned long)Address,NewData,Length,false)
#define EzUnModify(Address) Memory_UnModify(pExtension,pISInterface,hMemoryService,(unsigned long)Address)

#define EzHttpRequest(_URL_,_pData_) IS_HttpRequest(pExtension,pISInterface,hHTTPService,_URL_,_pData_)

extern ISType *pStringType;
extern ISType *pIntType;
extern ISType *pBoolType;
extern ISType *pFloatType;
extern ISType *pTimeType;
extern ISType *pByteType;
