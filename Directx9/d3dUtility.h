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
	// Ambient : ���ݻ籤�� ��
	// Diffuse : ȯ����� ��
	// Specular : ���ݻ籤�� ��
	// Emissive : ���� ���� ��ü ȿ��
	// Power : ���ݻ籤�� ��ī�ο� ���� ���� �������� ���̶���Ʈ ����
	///</summary>
	
	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);
	const D3DMATERIAL9 WHITE_MTRL = InitMtrl(WHITE, WHITE, WHITE, BLACK, 8.0f);
	const D3DMATERIAL9 RED_MTRL = InitMtrl(RED, RED, RED,BLACK, 8.0f);
	const D3DMATERIAL9 GREEN_MTRL = InitMtrl(GREEN, GREEN, GREEN, BLACK, 8.0f);
	const D3DMATERIAL9 BLUE_MTRL = InitMtrl(BLUE, BLUE, BLUE, BLACK, 8.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 8.0f);

	///<summary>
	// Type			: ������� �ϴ� ������ Ÿ�� D3DLIGHT_POINT, D3DLIGHT_SPOT, D3DLIGHT_DIRECTIONAL
	// Diffuse		: ������ �߻��ϴ� ȯ�汤�� �÷�
	// Specular		: ������ �߻��ϴ� ���ݻ籤�� �÷�
	// Ambient		: ������ �߻��ϴ� ���ݻ籤�� �÷�
	// Position		: ���� ���ϴ� ������ �����ϴ� ����, ���⼺ ������ ��� �̰��� �ǹ� ����
	// Direction	: ���� ���ϴ� ������ �����ϴ� ����, �� ���������� �̰��� ������� ����
	// Range		: ���� ������ �Ҹ��� ������ ������ �� �ִ� �ִ� �Ÿ� �� ���� ��FLT_MAX���� Ŭ �� ����
	// Falloff		: ����Ʈ ���������� ��� ������ ���԰� �ٱ����� ���� �� ���� ���� ���̸� ���� ������ 1.0f
	// Attenuation0, 
	// Attenuation1,
	// Attenuation2	: �Ÿ��� ���� ���� ���Ⱑ �������� ���� �� ������ ����Ʈ �������� ���
	// Theta		: ����Ʈ �������� ��� ���� ������ �������� ����
	// Phi			: ����Ʈ �������� �ƿ� 
	///</summary>
	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
	D3DLIGHT9 InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);
	D3DLIGHT9 InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color);
}

