#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Core/Minigin.h"

int main(int, char*[]) {
	MyEngine::Minigin engine;
	engine.Run();
    return 0;
}