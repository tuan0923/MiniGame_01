//=============================================================================
//
// �W���C�p�b�h���� (input_joypad.cpp)
// Author:Itsuki Takaiwa
//
//=============================================================================
#include "input_mouse.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DEADZONE        (2500)      // �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX       (10000)     // �L���͈͂̍ő�l
#define RANGE_MIN       (-10000)    // �L���͈͂̍ŏ��l

#define MAX_DIRECTION	(4)			// �L�[�����̍ő吔

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************	

//=============================================================================	
// CInputMouse�̃R���X�g���N�^
//=============================================================================	
CInputMouse::CInputMouse()
{
	memset(&m_CurrentMouseState, 0, sizeof(DIMOUSESTATE));
	memset(&m_PrevMouseState, 0, sizeof(DIMOUSESTATE));
}

//=============================================================================	
// CInputMouse�̃f�X�g���N�^
//=============================================================================	
CInputMouse::~CInputMouse()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �C���v�b�g�����̋��ʏ���������
	CInput::Init(hInstance, hWnd);

	// �}�E�X�f�o�C�X�̎擾
	if (FAILED(m_pInput->CreateDevice(
		GUID_SysMouse,
		&m_pDevice,
		NULL)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃t�H�[�}�b�g�ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// �������[�h�̐ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(
		hWnd,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CInputMouse::Uninit()
{
	// CInput�̏I������
	CInput::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CInputMouse::Update()
{
	HRESULT hr;

	if (m_pDevice != NULL)
	{
		hr = m_pDevice->Poll();

		// ���݂̏���O��̏��ɕۑ�
		m_PrevMouseState = m_CurrentMouseState;
		m_posOld = m_pos;
		// ���݂̃}�E�X�̏�Ԃ��擾
		if (SUCCEEDED(hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState)))
		{
			GetCursorPos(&m_pos);
			//ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &m_pos);
		}
		else
		{
			m_pDevice->Acquire();
		}
	}
}

bool CInputMouse::GetPress(int nButton)
{
	return (m_CurrentMouseState.rgbButtons[nButton] & 0x80) ? true : false;
}

bool CInputMouse::GetTrigger(int nButton)
{
	if (!(m_PrevMouseState.rgbButtons[nButton] & 0x80) && (m_CurrentMouseState.rgbButtons[nButton] & 0x80))
	{
		return true;
	}
	return false;
}

bool CInputMouse::GetRelese(int nButton)
{
	if ((m_PrevMouseState.rgbButtons[nButton] & 0x80) && !(m_CurrentMouseState.rgbButtons[nButton] & 0x80))
	{
		return true;
	}
	return false;
}

D3DXVECTOR2 CInputMouse::GetMouseMove()
{
	return D3DXVECTOR2((float)m_CurrentMouseState.lX, (float)m_CurrentMouseState.lY);
}

float CInputMouse::GetMouseWheel()
{
	return (float)m_CurrentMouseState.lZ;
}