/*
#include"d3dUtility.h"

// Globals

// DrawPrimitive 베이스의 렌더링의 실행, 리소스의 생성, 시스템 레벨 변수의 처리, 감마 곡선 레벨의 조정
// 팔레트의 처리, 셰이더의 생성을 실시하려면 IDirect3DDevice9 인터페이스의 메서드를 사용
IDirect3DDevice9* Device = 0;

const int Width = 640;
const int Height = 480;

// vertex buffer 리소스를 조작
IDirect3DVertexBuffer9* Triangle = 0;

struct Vertex {
	Vertex() {}

	Vertex(float x, float y, float z) {
		_x = x; _y = y; _z = z;
	}

	float _x, _y, _z;

	// FVF(flexible vertex format) : 프로그램에 알맞게 새로운 정점 포맷을 정할 수 있도록 유연성을 제공
	static const DWORD FVF;
};
// D3DFVF_XYZ : 3D 공간상의 정점변환이전의 좌표
const DWORD Vertex::FVF = D3DFVF_XYZ;

bool Setup() {

	// Create the vertex buffer

	Device->CreateVertexBuffer(
		3 * sizeof(Vertex),		// size in bytes,
		D3DUSAGE_WRITEONLY,		// flag
		Vertex::FVF,			// vertex format
		D3DPOOL_MANAGED,		// managed memory pool
		&Triangle,				// return create vertex buffer
		0);

	// Fill the buffers with the triangle data

	Vertex* vertices;
	Triangle->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = Vertex(-1.0f, 0.0f, 2.0f);
	vertices[1] = Vertex(0.0f, 1.0f, 2.0f);
	vertices[2] = Vertex(1.0f, 0.0f, 2.0f);

	Triangle->Unlock();

	// Set the projection matrix
	// 시야에 근거해, 왼손 좌표계 퍼스펙티브 투영 행렬을 생성

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,							// reult
		D3DX_PI * 0.5f,					// 90 - degrees
		(float)Width / (float)Height,	// aspect ratio
		1.0f,							// near plane
		1000.0f);						// far plane

	// 투영 변환 행렬로서 설정되는 변환 행렬을 식별
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	// Set wireframe mode render state
	Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return true;
}

void Cleanup() {
	d3d::Release<IDirect3DVertexBuffer9*>(Triangle);
}

bool Display(float timeDelta) {
	if (Device) {
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
		Device->BeginScene();

		Device->SetStreamSource(0, Triangle, 0, sizeof(Vertex));
		Device->SetFVF(Vertex::FVF);

		// Draw one triangle
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}

//
// WndProc
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd)
{
	if (!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}

	if (!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop(Display);

	Cleanup();

	Device->Release();

	return 0;
}
*/

