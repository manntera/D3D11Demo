
//==========================
//===�yD3D11Device.h�z
//==========================
//    DirectX11�ɂ�����A
//    �f�o�C�X/�f�o�C�X�R���e�L�X�g��
//    �Ǘ��E�ێ����s���܂��B
//==========================
#pragma	once
#pragma warning(disable: 4005)
#define SAFE_RELEASE(x) if(x){x->Release(); x=NULL;}
#define SAFE_DELETE_ARRAY(p) { if (p){ delete []p; } p = NULL; }
#define SAFE_DELETE(p) { if (p){ delete p; } p = NULL; }

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//

#ifdef _DEBUG
#include<initguid.h>
#include<DXGIDebug.h>
#endif

#include<wrl.h>

#include	<d3dx9.h>
#include <d3dx11.h>
#include<DxErr.h>

#ifdef _DEBUG
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")

using namespace Microsoft;
namespace	OGL
{
	class	D3D11Device
	{
	public:
		void	Create(HWND*	hWnd, int width, int height);
		bool	OutputDebugLog(void);

		static ID3D11Device*				GetDevice(void){ return GetInstance()->mp_device.Get(); }
		static ID3D11DeviceContext*		GetDeviceConText(void){ return GetInstance()->mp_deviceContext.Get(); }
		static IDXGISwapChain*			GetSwapChain(void){ return GetInstance()->mp_swapChain.Get(); }

	private:
		WRL::ComPtr<ID3D11Device>				mp_device;
		WRL::ComPtr<ID3D11DeviceContext>	mp_deviceContext;
		WRL::ComPtr<IDXGISwapChain>			mp_swapChain;
#ifdef _DEBUG
		WRL::ComPtr<ID3D11Debug>				m_pD3dDebug;
#endif

	private:
		void	CreateDevice(HWND*	hWnd, int width, int height);

	public:	//�V���O���g��
		static	D3D11Device *GetInstance()
		{
			static	D3D11Device	obj;
			return &obj;
		}
		virtual ~D3D11Device();

	private:	//�V���O���g��
		D3D11Device();
		D3D11Device(const D3D11Device &x){};
		D3D11Device &operator=(const D3D11Device &){ return *this; }

	};	//EndOf__class_D3D11Device
}	//EndOf__namespace_OGL

void ErrorMessage(char* str);