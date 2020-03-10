#include "DxLib.h"
#include "Scene.h"

//===============================================================
// ƒƒCƒ“ƒ‹[ƒ`ƒ“
//===============================================================
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	g_cScene = new CScene;
	g_cScene->Update();
	delete g_cScene;
	return 0;
}