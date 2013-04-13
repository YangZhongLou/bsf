#include "CmD3D11RenderWindowManager.h"
#include "CmD3D11RenderSystem.h"
#include "CmD3D11RenderWindow.h"
#include "CmAsyncOp.h"

namespace CamelotEngine
{
	D3D11RenderWindowManager::D3D11RenderWindowManager(D3D11RenderSystem* renderSystem)
		:mRenderSystem(renderSystem)
	{
		assert(mRenderSystem != nullptr);
	}

	RenderWindowPtr D3D11RenderWindowManager::createImpl(RENDER_WINDOW_DESC& desc, RenderWindowPtr parentWindow)
	{
		RenderSystem* rs = RenderSystem::instancePtr();
		D3D11RenderSystem* d3d11rs = static_cast<D3D11RenderSystem*>(rs);

		if(parentWindow != nullptr)
		{
			HWND hWnd;
			parentWindow->getCustomAttribute("WINDOW", &hWnd);
			desc.platformSpecific["parentWindowHandle"] = toString((unsigned long)hWnd);
		}

		// Create the window
		D3D11RenderWindow* renderWindow = CM_NEW(D3D11RenderWindow, PoolAlloc) D3D11RenderWindow(desc, d3d11rs->getPrimaryDevice(), d3d11rs->getDXGIFactory());
		return RenderWindowPtr(renderWindow, &CoreObject::_deleteDelayed<D3D11RenderWindow, PoolAlloc>);
	}
}