#pragma once

#include <d3dx9.h>
#include <string>

namespace d3d
{
	bool InitD3D(
		HINSTANCE hInstance,       // [in] Application instance.
		int width, int height,     // [in] Backbuffer dimensions.
		bool windowed,             // [in] Windowed (true)or full screen (false).
		D3DDEVTYPE deviceType,     // [in] HAL or REF
		IDirect3DDevice9** device);// [out]The created device.

	int EnterMsgLoop(
		bool (*ptr_display)(float timeDelta));

	LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam);

	template<class T> void Release(T t)
	{
		if (t)
		{
			t->Release();
			t = 0;
		}
	}

	template<class T> void Delete(T t)
	{
		if (t)
		{
			delete t;
			t = 0;
		}
	}

	const D3DXCOLOR WHITE(D3DCOLOR_XRGB(255, 255, 255));
	const D3DXCOLOR BLACK(D3DCOLOR_XRGB(0, 0, 0));
	const D3DXCOLOR RED(D3DCOLOR_XRGB(255, 0, 0));
	const D3DXCOLOR GREEN(D3DCOLOR_XRGB(0, 255, 0));
	const D3DXCOLOR BLUE(D3DCOLOR_XRGB(0, 0, 255));
	const D3DXCOLOR YELLOW(D3DCOLOR_XRGB(255, 255, 0));
	const D3DXCOLOR CYAN(D3DCOLOR_XRGB(0, 255, 255));
	const D3DXCOLOR MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

	///<summary>
	// Ambient : 난반사광의 양
	// Diffuse : 환경관의 양
	// Specular : 정반사광의 양
	// Emissive : 좀더 밝은 물체 효과
	// Power : 정반사광의 날카로운 정도 값이 높을수록 하이라이트 강조
	///</summary>
	
	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);
	const D3DMATERIAL9 WHITE_MTRL = InitMtrl(WHITE, WHITE, WHITE, BLACK, 8.0f);
	const D3DMATERIAL9 RED_MTRL = InitMtrl(RED, RED, RED,BLACK, 8.0f);
	const D3DMATERIAL9 GREEN_MTRL = InitMtrl(GREEN, GREEN, GREEN, BLACK, 8.0f);
	const D3DMATERIAL9 BLUE_MTRL = InitMtrl(BLUE, BLUE, BLUE, BLACK, 8.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 8.0f);

	///<summary>
	// Type			: 만들고자 하는 광원의 타입 D3DLIGHT_POINT, D3DLIGHT_SPOT, D3DLIGHT_DIRECTIONAL
	// Diffuse		: 광원이 발산하는 환경광의 컬러
	// Specular		: 광원이 발산하는 난반사광의 컬러
	// Ambient		: 광원이 발산하는 정반사광의 컬러
	// Position		: 빛이 향하는 방향을 정의하는 벡터, 방향성 광원의 경우 이값은 의미 없음
	// Direction	: 빛이 향하는 방향을 정의하는 벡터, 점 광원에서는 이값을 사용하지 않음
	// Range		: 빛이 완전히 소멸할 때까지 진행할 수 있는 최대 거리 이 값은 √FLT_MAX보다 클 수 없음
	// Falloff		: 스포트 광원에서만 사용 안쪽의 원뿔과 바깥쪽의 원뿔 간 빛의 세기 차이를 정의 보통은 1.0f
	// Attenuation0, 
	// Attenuation1,
	// Attenuation2	: 거리에 따라 빛의 세기가 약해지는 정도 점 광원과 스포트 광원에서 사용
	// Theta		: 스포트 광원에서 사용 안쪽 원뿔의 라디안으로 지정
	// Phi			: 스포트 광원에서 아용 
	///</summary>
	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
	D3DLIGHT9 InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);
	D3DLIGHT9 InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color);
}

