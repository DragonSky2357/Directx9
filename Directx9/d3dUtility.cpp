#include "d3dUtility.h"

bool d3d::InitD3D(
	HINSTANCE hInstance,
	int width, int height,
	bool windowed,
	D3DDEVTYPE deviceType,
	IDirect3DDevice9** device)
{
	//
	// Create the main application window.
	//

	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW; // �����찡 ��µǴ� ����
	wc.lpfnWndProc = (WNDPROC)d3d::WndProc; // �޽��� ó���� ���� �Լ����
	wc.cbClsExtra = 0; // Ŭ������ ���� ������ �޸� ũ��
	wc.cbWndExtra = 0; // �����츦 ���� ������ �޸� ũ��
	wc.hInstance = hInstance; // WinMain() �Լ����� �Ѿ�� ���� ���α׷� �ν��Ͻ���
	wc.hIcon = LoadIcon(0, IDI_APPLICATION); // �⺻ ������ 
	wc.hCursor = LoadCursor(0, IDC_ARROW); // �⺻ Ŀ��
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ���ȭ��(white)
	wc.lpszMenuName = 0; // �޴��̸�
	wc.lpszClassName = "Direct3D9App"; // ������ Ŭ���� �̸� ������ ���鶧 �̸��� �̿�

	// ������ Ŭ������ ����Ѵ�.
	// CreateWindow �Լ��� �����츦 �����ϱ� ���� ������ Ŭ������ �ݵ�� ��ϵǾ� �־�� �Ѵ�
	if (!RegisterClass(&wc))
	{
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}

	HWND hwnd = 0; // ������ �ڵ�

	// ������ Ŭ������ �� �Լ��� �μ� ������ �������� �Ͽ� �����츦 �����Ѵ�
	hwnd = ::CreateWindow("Direct3D9App", "Direct3D9App",
		WS_EX_TOPMOST, // ��� �����캸�� ���������� ���� ���� �ִ� �����츦 �����.
		0, 0, width, height,
		0 /*parent hwnd*/, 0 /* menu */, hInstance, 0 /*extra*/);

	if (!hwnd)
	{
		::MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}

	// ������ �� ��Ʈ���� ǥ�� �� ���� ���θ� ����
	// �ִ�ȭ, �ּ�ȭ�� ���θ� �����ϴ� �Լ�
	::ShowWindow(hwnd, SW_SHOW);

	// �������� �Ϻΰ� �ٸ� ������ � �������ų� �������� �Ǿ��� ���,
	// ��ȿȭ ����(Invalid Region)�� ���� WM_PAINT �޽����� �ش� �����쿡 �������ν�
	// ��ȿȭ ������ ���Ž����ִ� �Լ�
	::UpdateWindow(hwnd);

	//
	// Init D3D: 
	//

	// Step 1: Create the IDirect3D9 object.

	// IDirect3D9 Interface
	// ��ü�� ȯ���� �¾� �Ϸ��� IDirect3D9 Interface �޼��带 ���
	IDirect3D9* d3d9 = 0;

	// IDirect3D9 ��ü�� �ν��Ͻ��� ����
	// ���ø����̼��� ����ε� ��� ���Ϸ� ������� ������ Ȯ��
	// �Ķ���Ͱ����� �ݵ�� D3D_SDK_VERSION
	// SUCCESS : IDirect3D9 Interface
	// FAIL : NULL
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d9)
	{
		::MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}

	// Step 2: Check for hardware vp.

	// Direct3D�� �����ϴ� �ϵ������ �ɷ��� ��Ÿ���� ����ü
	D3DCAPS9 caps;

	// �׷��� ī���� �ϵ���� Ư���� �ľ��ϱ� ���� �Լ�
	// �ϵ��� Vertex ���μ��� ��带 �����ϴ��� Ȯ��
	// �����Ǵ� ����� �ִ��� �츮�� ���� �̸� �ľ��ϱ� ����
	// Adapter : �⺻ ���÷��� ���(D3DADAPTER_DEFAULT : �⺻ ���÷���)
	// DeviceType : ����� ��ġ Ÿ�� ������ �ϵ���� ����
	// pCaps : �ʱ�ȭ�� D3DCAPS9 ����
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) // �ϵ������ Vertex ���μ��� ��� ����� �����Ѱ�?
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING; // �ϵ���� ó��(���)
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; // ����Ʈ���� ó��(����)

	// Step 3: Fill out the D3DPRESENT_PARAMETERS structure.

	// �ϵ���� ����� ���� ����ü
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth = width; // �ȼ����� �ĸ���� �� ũ��(������ �� ũ��)
	d3dpp.BackBufferHeight = height; // �ȼ����� �ĸ���� ���� ũ��(������ ���� ũ��)
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // �ĸ���� �ȼ� Į���(32 ��Ʈ�� ARGB �ȼ� ����)
	d3dpp.BackBufferCount = 1; // �ĸ���� ����(default 1)
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE; // ��Ƽ ���ø��� ��Ƽ �ٸ�����̶�� ��� ������ ���Ž��� ������ ���� ���ϰ� ����
	d3dpp.MultiSampleQuality = 0; // ��Ƽ ���ø� ����
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // �ø��� ü���� ���۰� ��ȯ�Ǵ� ��� D3DSWAPEFFECT_DISCARD�� �����ϴ� ���� ���� ȿ����
	d3dpp.hDeviceWindow = hwnd; // ȭ���� �׷��� ���ø����̼� �����츦 ����
	d3dpp.Windowed = windowed; // �������� true, ��ü ȭ�� false
	d3dpp.EnableAutoDepthStencil = true; // Direct3D�� �ڵ����� ����/���ٽ� ���۸� ����� �����ϱ� ���Ѵٸ� true
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; // ����/���ٽ� ������ ����(24��Ʈ ���� ���ۿ� 8��Ʈ ���ٽ� ����)
	d3dpp.Flags = 0; // �ΰ��� Ư��
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // ȭ�� ����� ���� �⺻ ����� ���
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // �ÿ� ���� ����(���� ����ȭ)

	// Step 4: Create the device.

	HRESULT hr = 0;

	// IDirect3DDevice9 ��ü ���� �Լ�
	// Adapter : ���� ���÷��� ����� ����
	// DeviceType : ��ġ Ÿ�� ����(D3DDEVTYPE_HAL(�ϵ����) or D3DDEVTYPE_REF(����Ʈ����))
	// hFocusWindow : ��ġ�� ȭ���� �׸� ������
	// BehaviorFlags : Vertex ���μ��� ����
	// pPresentationParameters : ��ġ Ư���� �Ϻθ� �����ϴ� �ʱ�ȭ�� D3DPRESENT_PARAMETERS �ν��Ͻ��� ����
	// ppReturnedDeviceInterface : ������ ��ġ�� ����
	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		deviceType,         // device type
		hwnd,               // window associated with device
		vp,                 // vertex processing
		&d3dpp,             // present parameters
		device);            // return created device

	if (FAILED(hr))
	{
		// try again using a 16-bit depth buffer
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			deviceType,
			hwnd,
			vp,
			&d3dpp,
			device);

		if (FAILED(hr))
		{
			d3d9->Release(); // done with d3d9 object
			::MessageBox(0, "CreateDevice() - FAILED", 0, 0);
			return false;
		}
	}

	d3d9->Release(); // done with d3d9 object

	return true;
}


int d3d::EnterMsgLoop(bool (*ptr_display)(float timeDelta))
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	static float lastTime = (float)timeGetTime();

	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			float currTime = (float)timeGetTime();
			float timeDelta = (currTime - lastTime) * 0.001f;

			ptr_display(timeDelta);

			lastTime = currTime;
		}
	}
	return msg.wParam;
}

D3DMATERIAL9 d3d::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p) {
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = a;	
	mtrl.Diffuse = d;	
	mtrl.Specular = s;	
	mtrl.Emissive = e;	
	mtrl.Power = p;		
	return mtrl;
}

D3DLIGHT9 d3d::InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color){
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_DIRECTIONAL;	
	light.Ambient = *color * 0.4f;		
	light.Diffuse = *color;				
	light.Specular = *color * 0.6f;		
	light.Direction = *direction;		

	return light;
}

D3DLIGHT9 d3d::InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color){
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_POINT;
	light.Ambient = *color * 0.6f;
	light.Diffuse = *color;
	light.Specular = *color * 0.6f;
	light.Position = *position;
	light.Range = 1000.0f;
	light.Falloff = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	return light;
}


D3DLIGHT9 d3d::InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_SPOT;
	light.Ambient = *color * 0.0f;
	light.Diffuse = *color;
	light.Specular = *color * 0.6f;
	light.Position = *position;
	light.Direction = *direction;
	light.Range = 1000.0f;
	light.Falloff = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Theta = 0.4f;
	light.Phi = 0.9f;

	return light;
}
