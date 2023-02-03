//=============================================================================
//
//	�W���C�p�b�h���͏��� [inputJoypad.cpp]
//	Author : SHUGO KURODA
//
//=============================================================================

//======================================================
//	�C���N���[�h
//======================================================
#include "input_joypad.h"

//======================================================
//	�R���X�g���N�^
//======================================================
CInputJoypad::CInputJoypad()
{
}

//======================================================
//	�f�X�g���N�^
//======================================================
CInputJoypad::~CInputJoypad()
{
}

//======================================================
//	�W���C�p�b�h�̏���������
//======================================================
HRESULT CInputJoypad::Init()
{
	//XInput�̃X�e�[�g��ݒ�i�L���ɂ���j
	XInputEnable(true);

	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		//�������[�̃N���A
		memset(&m_JoyKeyState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_JoyKeyStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));

		//�W���C�p�b�h�̐U������̂O�N���A
		ZeroMemory(&m_JoyMoter[nCnt], sizeof(XINPUT_VIBRATION));

		//�U������p�̏�����
		m_nStrength[nCnt] = 0;
		m_nTime[nCnt] = 0;
	}

	return S_OK;
}

//======================================================
//	�W���C�p�b�h�̏I������
//======================================================
void CInputJoypad::Uninit()
{
	//XInput�̃X�e�[�g�𖳌��ɂ���
	XInputEnable(false);
}

//======================================================
//	�W���C�p�b�h�̍X�V����
//======================================================
void CInputJoypad::Update()
{
	XINPUT_STATE JoyKeyState[MAX_CONTROLLER];		//�W���C�p�b�h���͏��

	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		//�W���C�p�b�h�̏�Ԃ��擾
		if (XInputGetState(nCnt, &JoyKeyState[nCnt]) == ERROR_SUCCESS)
		{
			m_JoyKeyStateTrigger[nCnt].Gamepad.wButtons
				= ~m_JoyKeyState[nCnt].Gamepad.wButtons
				& JoyKeyState[nCnt].Gamepad.wButtons;		//�g���K�[����ۑ�
			m_JoyKeyState[nCnt] = JoyKeyState[nCnt];		//�v���X����
		}

		//�W���C�p�b�h�̐U��
		m_JoyMoter[nCnt].wLeftMotorSpeed = (WORD)m_nStrength[nCnt];
		m_JoyMoter[nCnt].wRightMotorSpeed = (WORD)m_nStrength[nCnt];
		XInputSetState(nCnt, &m_JoyMoter[nCnt]);

		if (m_nTime[nCnt] > 0)
		{
			m_nTime[nCnt]--;
		}
		else
		{
			m_nStrength[nCnt] = 0;
			m_nTime[nCnt] = 0;
		}
	}
}

//======================================================
//	�W���C�p�b�h�̃v���X����
//======================================================
bool CInputJoypad::GetPress(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyState[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//======================================================
//	�W���C�p�b�h�̃g���K�[����
//======================================================
bool CInputJoypad::GetTrigger(JOYKEY Key, int nPlayer)
{
	return (m_JoyKeyStateTrigger[nPlayer].Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//======================================================
//	�W���C�p�b�g�i�X�e�B�b�N�v���X�j����
//======================================================
D3DXVECTOR3 CInputJoypad::GetStick(JOYKEY Key, int nPlayer)
{
	switch (Key)
	{
	case JOYKEY_LEFT_STICK:
		m_JoyStickPos[nPlayer] = D3DXVECTOR3(m_JoyKeyState[nPlayer].Gamepad.sThumbLX / 32767.0f, -m_JoyKeyState[nPlayer].Gamepad.sThumbLY / 32767.0f, 0.0f);
		break;
	case JOYKEY_RIGHT_STICK:
		m_JoyStickPos[nPlayer] = D3DXVECTOR3(m_JoyKeyState[nPlayer].Gamepad.sThumbRX / 32767.0f, -m_JoyKeyState[nPlayer].Gamepad.sThumbRY / 32767.0f, 0.0f);
		break;
	}

	return m_JoyStickPos[nPlayer];
}

//======================================================
//	�W���C�p�b�g�i�g���K�[�y�_���j����
//======================================================
int CInputJoypad::GetTriggerPedal(JOYKEY Key, int nPlayer)
{
	int nJoypadTriggerPedal = 0;
	switch (Key)
	{
	case JOYKEY_LEFT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState[nPlayer].Gamepad.bLeftTrigger;
		break;

	case JOYKEY_RIGHT_TRIGGER:
		nJoypadTriggerPedal = m_JoyKeyState[nPlayer].Gamepad.bRightTrigger;
		break;
	}

	return nJoypadTriggerPedal;
}

//======================================================
//	�R���g���[���[�̐U������
//======================================================
void CInputJoypad::Vibration(int nTime, WORD nStrength, int nPlayer)
{
	m_nTime[nPlayer] = nTime;			//�U����������
	m_nStrength[nPlayer] = nStrength;	//�U���̋���
}
