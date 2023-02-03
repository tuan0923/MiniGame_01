//=============================================================================
//
// �����_���[����[renderer.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include <tchar.h> // _T
#include <stdio.h>

#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "object2D.h"
#include "fade.h"
#include "debugproc.h"

#include "game.h"
#include "camera.h"

#include <assert.h>

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRenderer::CRenderer() :m_pD3D(nullptr), m_pD3DDevice(nullptr)
{
#ifdef _DEBUG
	m_pFont = nullptr;
#endif // _DEBUG
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{
	assert(CManager::GetManager()->GetRenderer() != nullptr);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));			// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;					// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;		// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;		// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;					// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��

	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`��ƒ��_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))))
	{
		// �������s
		return E_FAIL;
	}

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// �J�����O
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);					// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// ���f�X�e�B�l�[�V�����J���[

	//�T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);			// �e�N�X�`���g�厞�̕�Ԑݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);			// �e�N�X�`���k�����̕�Ԑݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// �e�N�X�`��U�l�̌J��Ԃ��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// �e�N�X�`��V�l�̌J��Ԃ��ݒ�

	//�e�N�X�`���X�e�[�W�X�e�[�g�p�����[�^�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		// ���u�����f�B���O�����ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// �ŏ��̃�����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);		// �Q�Ԗڂ̃�����

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRenderer::Uninit()
{
#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CRenderer::Update()
{
	//�I�u�W�F�N�g�̍X�V����
	CObject::UpdateAll();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRenderer::Draw()
{
	// �t�F�[�h���̎擾
	CFade *pFade = CManager::GetManager()->GetFade();

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		//�I�u�W�F�N�g�̕`�揈��
		CObject::DrawAll();

		//�t�F�[�h�̕`��
		pFade->Draw();

#ifdef _DEBUG
		// FPS�\��
		//DrawFPS();
#endif // _DEBUG

		// �f�o�b�N�\���̕`��
		CManager::GetManager()->GetDebugProc()->Draw();

		//�`��I��
		m_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifdef _DEBUG
//=============================================================================
// FPS�`�揈��
//=============================================================================
void CRenderer::DrawFPS()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	RECT rectObj[CObject::MAX_OBJECT];
	char str[256];
	char strObj[CObject::MAX_OBJECT][256];

	int nCntFPS = GetCounterFPS();

	wsprintf(str, _T("FPS : %d\n"), nCntFPS);

	// FPS�`��
	m_pFont->DrawTextA(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	if (CManager::GetManager()->GetGame() == nullptr)
	{
		return;
	}

	// �J�������̎擾
	if (CManager::GetManager()->GetGame()->GetCamera() != nullptr)
	{
		D3DXVECTOR3 posCameraR = CManager::GetManager()->GetGame()->GetCamera()->GetPosR();

		D3DXVECTOR3 posCameraV = CManager::GetManager()->GetGame()->GetCamera()->GetPosV();

		D3DXVECTOR3 rotCamera = CManager::GetManager()->GetGame()->GetCamera()->GetRotation();

		char strCamera[3][256];
		RECT rectCamera[3];

		sprintf(strCamera[0], _T("posCameraR : X=%.2f Y=%.2f Z=%.2f"), posCameraR.x, posCameraR.y, posCameraR.z);
		sprintf(strCamera[1], _T("posCameraV : X=%.2f Y=%.2f Z=%.2f"), posCameraV.x, posCameraV.y, posCameraV.z);
		sprintf(strCamera[2], _T("rotCamera : X=%.2f Y=%.2f Z=%.2f"), rotCamera.x, rotCamera.y, rotCamera.z);

		for (int nCntCam = 0; nCntCam < 3; nCntCam++)
		{
			rectCamera[nCntCam] = { 0, 20 * (nCntCam + 2), SCREEN_WIDTH, SCREEN_HEIGHT };

			//�I�u�W�F�N�g�̈ʒu�`��
			m_pFont->DrawTextA(NULL, strCamera[nCntCam], -1, &rectCamera[nCntCam], DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
		}
	}



	////�I�u�W�F�N�g���̎擾
	//for (int nCntObj = 0; nCntObj < CObject::MAX_OBJECT; nCntObj++)
	//{
	//	CObject *pObject = CObject::GetObject(nCntObj);
	//	if (pObject != nullptr && nCntObj != 1)
	//	{
	//		if (nCntObj > 35)
	//		{
	//			rectObj[nCntObj] = { 300, 20 * (nCntObj - 35), SCREEN_WIDTH, SCREEN_HEIGHT };
	//		}
	//		else
	//		{
	//			rectObj[nCntObj] = { 0, 20 * (nCntObj + 1), SCREEN_WIDTH, SCREEN_HEIGHT };
	//		}

	//		D3DXVECTOR3 pos = ((CObject2D*)pObject)->GetPosition();

	//		sprintf(strObj[nCntObj], _T("OBJ[%d] : X=%.2f Y=%.2f Z=%.2f"), nCntObj, pos.x, pos.y, pos.z);

	//		//�I�u�W�F�N�g�̈ʒu�`��
	//		m_pFont->DrawTextA(NULL, strObj[nCntObj], -1, &rectObj[nCntObj], DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	//	}
	//}
}

#endif // _DEBUG
