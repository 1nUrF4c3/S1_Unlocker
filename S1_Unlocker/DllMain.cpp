#include <Windows.h>
#include <MinHook.h>

int is_item_locked()
{
	return 0;
}

void init()
{
	MH_Initialize();

	MH_CreateHook(reinterpret_cast<void*>(0x1403BD790), is_item_locked, NULL);
	MH_CreateHook(reinterpret_cast<void*>(0x1403BD290), is_item_locked, NULL);
	MH_CreateHook(reinterpret_cast<void*>(0x1403BAF60), is_item_locked, NULL);

	MH_EnableHook(MH_ALL_HOOKS);
}

void free()
{
	MH_DisableHook(MH_ALL_HOOKS);

	MH_RemoveHook(reinterpret_cast<void*>(0x1403BD790));
	MH_RemoveHook(reinterpret_cast<void*>(0x1403BD290));
	MH_RemoveHook(reinterpret_cast<void*>(0x1403BAF60));

	MH_Uninitialize();
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hinstDLL);

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		init();
		return TRUE;

	case DLL_PROCESS_DETACH:
		free();
		return TRUE;

	default:
		return FALSE;
	}
}