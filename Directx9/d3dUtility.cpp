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

	wc.style = CS_HREDRAW | CS_VREDRAW; // 윈도우가 출력되는 형태
	wc.lpfnWndProc = (WNDPROC)d3d::WndProc; // 메시지 처리에 사용될 함수등록
	wc.cbClsExtra = 0; // 클래스를 위한 여분의 메모리 크기
	wc.cbWndExtra = 0; // 윈도우를 위한 여분의 메모리 크기
	wc.hInstance = hInstance; // WinMain() 함수에서 넘어온 응용 프로그램 인스턴스값
	wc.hIcon = LoadIcon(0, IDI_APPLICATION); // 기본 아이콘 
	wc.hCursor = LoadCursor(0, IDC_ARROW); // 기본 커서
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 배경화면(white)
	wc.lpszMenuName = 0; // 메뉴이름
	wc.lpszClassName = "Direct3D9App"; // 윈도우 클래스 이름 윈도우 만들때 이름을 이용

	// 윈도우 클래스를 등록한다.
	// CreateWindow 함수로 윈도우를 생성하기 전에 윈도우 클래스가 반드시 등록되어 있어야 한다
	if (!RegisterClass(&wc))
	{
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}

	HWND hwnd = 0; // 윈도우 핸들

	// 윈도우 클래스와 이 함수의 인수 정보를 바탕으로 하여 윈도우를 생성한다
	hwnd = ::CreateWindow("Direct3D9App", "Direct3D9App",
		WS_EX_TOPMOST, // 모든 윈도우보다 수직적으로 가장 위에 있는 윈도우를 만든다.
		0, 0, width, height,
		0 /*parent hwnd*/, 0 /* menu */, hInstance, 0 /*extra*/);

	if (!hwnd)
	{
		::MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}

	// 윈도우 및 컨트롤의 표시 및 숨김 여부를 설정
	// 최대화, 최소화의 여부를 결정하는 함수
	::ShowWindow(hwnd, SW_SHOW);

	// 윈도우의 일부가 다른 윈도우 등에 가려졌거나 리사이즈 되었을 경우,
	// 무효화 영역(Invalid Region)에 대해 WM_PAINT 메시지를 해당 윈도우에 보냄으로써
	// 무효화 영역을 갱신시켜주는 함수
	::UpdateWindow(hwnd);

	//
	// Init D3D: 
	//

	// Step 1: Create the IDirect3D9 object.

	// IDirect3D9 Interface
	// 개체의 환경을 셋업 하려면 IDirect3D9 Interface 메서드를 사용
	IDirect3D9* d3d9 = 0;

	// IDirect3D9 개체의 인스턴스를 생성
	// 어플리케이션이 제대로된 헤더 파일로 만들어진 것인지 확인
	// 파라미터값으로 반드시 D3D_SDK_VERSION
	// SUCCESS : IDirect3D9 Interface
	// FAIL : NULL
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d9)
	{
		::MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
		return false;
	}

	// Step 2: Check for hardware vp.

	// Direct3D가 공개하는 하드웨어의 능력을 나타내는 구조체
	D3DCAPS9 caps;

	// 그래픽 카드의 하드웨어 특성을 파악하기 위한 함수
	// 하드웨어가 Vertex 프로세싱 모드를 지원하는지 확인
	// 지원되는 기능을 최대한 살리기 위해 미리 파악하기 위함
	// Adapter : 기본 디스플레이 어뎁터(D3DADAPTER_DEFAULT : 기본 디스플레이)
	// DeviceType : 사용할 장치 타입 보통은 하드웨어 지정
	// pCaps : 초기화된 D3DCAPS9 리턴
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps);

	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) // 하드웨어의 Vertex 프로세싱 모드 사용이 가능한가?
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING; // 하드웨어 처리(고속)
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; // 소프트웨어 처리(저속)

	// Step 3: Fill out the D3DPRESENT_PARAMETERS structure.

	// 하드웨어 사용을 위한 구조체
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth = width; // 픽셀단위 후면버퍼 폭 크기(윈도우 폭 크기)
	d3dpp.BackBufferHeight = height; // 픽셀단위 후면버퍼 높이 크기(윈도우 높이 크기)
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // 후면버퍼 픽셀 칼라수(32 비트의 ARGB 픽셀 포맷)
	d3dpp.BackBufferCount = 1; // 후면버퍼 갯수(default 1)
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE; // 멀티 샘플링은 안티 앨리어싱이라고 계단 현상을 제거시켜 주지만 성능 저하가 심함
	d3dpp.MultiSampleQuality = 0; // 멀티 샘플링 레벨
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // 플리핑 체인의 버퍼가 교환되는 방법 D3DSWAPEFFECT_DISCARD를 지정하는 것이 가장 효과적
	d3dpp.hDeviceWindow = hwnd; // 화면이 그려질 애플리케이션 윈도우를 지정
	d3dpp.Windowed = windowed; // 윈도우모드 true, 전체 화면 false
	d3dpp.EnableAutoDepthStencil = true; // Direct3D가 자동으로 깊이/스텐실 버퍼를 만들고 관리하길 원한다면 true
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; // 깊이/스텐실 버퍼의 포맷(24비트 깊이 버퍼와 8비트 스텐실 버퍼)
	d3dpp.Flags = 0; // 부가적 특성
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // 화면 재생율 보통 기본 재생율 사용
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // 시연 간격 지정(수직 동기화)

	// Step 4: Create the device.

	HRESULT hr = 0;

	// IDirect3DDevice9 객체 생성 함수
	// Adapter : 물리 디스플레이 어댑터 지정
	// DeviceType : 장치 타입 지정(D3DDEVTYPE_HAL(하드웨어) or D3DDEVTYPE_REF(소프트웨어))
	// hFocusWindow : 장치가 화면을 그릴 윈도우
	// BehaviorFlags : Vertex 프로세싱 지정
	// pPresentationParameters : 장치 특성의 일부를 정의하는 초기화된 D3DPRESENT_PARAMETERS 인스턴스를 지정
	// ppReturnedDeviceInterface : 생성된 장치를 리턴
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
