//=============================================================================
//
//	�L�[�{�[�h���� [input_keyboard.cpp]
//	Author : ITSUKI TAKAIWA, SHUGO KURODA
//
//=============================================================================
#include "input_keyboard.h"

//--------------------------------------------------------------------------------------------------------------
//	CInputKeyboard�̃R���X�g���N�^
//--------------------------------------------------------------------------------------------------------------
CInputKeyboard::CInputKeyboard()
{
	// �����o�ϐ��̏�����
	memset(&m_aKeyState[0], 0, MAX_KEY);
	memset(&m_aKeyStateReleace[0], 0, MAX_KEY);
	memset(&m_aKeyStateTrigger[0], 0, MAX_KEY);
}

//--------------------------------------------------------------------------------------------------------------
//	CInputKeyboard�̃f�X�g���N�^
//--------------------------------------------------------------------------------------------------------------
CInputKeyboard::~CInputKeyboard()
{

}

//--------------------------------------------------------------------------------------------------------------
//	����������
//--------------------------------------------------------------------------------------------------------------
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ���ʂ������͏����̏���������
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(
		GUID_SysKeyboard,
		&m_pDevice,
		NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h�̐ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(
		hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �A�N�Z�X���̎擾
	m_pDevice->Acquire();

	return S_OK;
}

//--------------------------------------------------------------------------------------------------------------
//	�I������
//--------------------------------------------------------------------------------------------------------------
void CInputKeyboard::Uninit()
{
	// �I������
	CInput::Uninit();
}

//--------------------------------------------------------------------------------------------------------------
//	�X�V����
//--------------------------------------------------------------------------------------------------------------
void CInputKeyboard::Update()
{
	// �ϐ��錾
	BYTE aKeyState[MAX_KEY];

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < MAX_KEY; nKey++)
		{
			m_aKeyStateTrigger[nKey] = (m_aKeyState[nKey] & aKeyState[nKey]) ^ aKeyState[nKey];

			m_aKeyStateReleace[nKey] = (m_aKeyState[nKey] | aKeyState[nKey]) ^ aKeyState[nKey];

			m_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else
	{// �A�N�Z�X���̎擾
		m_pDevice->Acquire();
	}
}
