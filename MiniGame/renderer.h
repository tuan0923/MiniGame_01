//=============================================================================
//
// �����_���[����[renderer.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _RENDERER_
#define _RENDERER_

//*****************************************************************************
//	�w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <d3dx9.h>		// �`�揈���ɕK�v

//*****************************************************************************
//	���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")   // �`�揈���ɕK�v   

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRenderer
{
public:	//�萔
	// �X�N���[���̕�
	static const int SCREEN_WIDTH = 1280;
	// �X�N���[���̍���
	static const int SCREEN_HEIGHT = 720;

public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }

#ifdef _DEBUG
	void DrawFPS();
#endif // _DEBUG

private:	//�����o�ϐ�
	// Direct3D�I�u�W�F�N�g
	LPDIRECT3D9 m_pD3D = nullptr;
	// Device�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice = nullptr;

#ifdef _DEBUG
	// �t�H���g
	LPD3DXFONT m_pFont = nullptr;
#endif // _DEBUG

};

#endif // _RENDERER_
