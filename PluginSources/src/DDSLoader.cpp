#include "Microsoft/DirectX/include/D3D11.h"
#include "Microsoft/DirectXTK-master/Inc/DDSTextureLoader.h"
#include "Unity/UnityPluginInterface.h"

static ID3D11Device* D3D11Device = nullptr;
static ID3D11DeviceContext* D3D11DeviceContext = nullptr;

extern "C"
{
	struct TextureDesc
	{
		ID3D11Texture2D *Texture;
		int Width;
		int Height;
		int MipLevels;
		int Format;
	};

	void EXPORT_API Initialize() {}

	void EXPORT_API UnitySetGraphicsDevice(void* device, int deviceType, int eventType)
	{
		if (deviceType == kGfxRendererD3D11)
		{
			if (eventType == kGfxDeviceEventInitialize)
			{
				D3D11Device = (ID3D11Device*)device;
				D3D11Device->GetImmediateContext(&D3D11DeviceContext);
			}
			else if (eventType == kGfxDeviceEventShutdown)
			{
			}
		}
	}

	TextureDesc EXPORT_API LoadDDS(LPWSTR path)
	{
		ID3D11Resource* texture;
		auto result = DirectX::CreateDDSTextureFromFile(D3D11Device, D3D11DeviceContext, path, &texture, nullptr);

		if(result != S_OK)
			return TextureDesc{ nullptr, 0, 0, 0, 0 };

		ID3D11Texture2D *pTextureInterface;
		texture->QueryInterface<ID3D11Texture2D>(&pTextureInterface);
		D3D11_TEXTURE2D_DESC desc;
		pTextureInterface->GetDesc(&desc);
		return TextureDesc{ pTextureInterface, (int)desc.Width, (int)desc.Height, (int)desc.MipLevels, (int)desc.Format };
	}

	void EXPORT_API FreeTexture(void* texturePtr)
	{
		ID3D11Texture2D* textureView = (ID3D11Texture2D*)texturePtr;
		textureView->Release();
	}
}