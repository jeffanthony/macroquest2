#pragma once

struct _EQChat
{
	PCHAR Line;
	DWORD Color;
	BOOL Filtered;
};

#define CHATSERVICE_INCOMING						((ISXSERVICE_MSG)+1)
#define CHATSERVICE_OUTGOING						((ISXSERVICE_MSG)+2)

#define UISERVICE_CLEANUP							((ISXSERVICE_MSG)+1)
#define UISERVICE_RELOAD							((ISXSERVICE_MSG)+2)

#define GAMESTATESERVICE_CHANGED					((ISXSERVICE_MSG)+1)

#define SPAWNSERVICE_ADDSPAWN						((ISXSERVICE_MSG)+1)
#define SPAWNSERVICE_REMOVESPAWN					((ISXSERVICE_MSG)+2)
#define SPAWNSERVICE_ADDITEM						((ISXSERVICE_MSG)+3)
#define SPAWNSERVICE_REMOVEITEM						((ISXSERVICE_MSG)+4)
#define SPAWNSERVICE_ADDGM							((ISXSERVICE_MSG)+5)
#define SPAWNSERVICE_REMOVEGM						((ISXSERVICE_MSG)+6)

#define ZONESERVICE_BEGINZONE						((ISXSERVICE_MSG)+1)
#define ZONESERVICE_ENDZONE							((ISXSERVICE_MSG)+2)
#define ZONESERVICE_ZONED							((ISXSERVICE_MSG)+3)
