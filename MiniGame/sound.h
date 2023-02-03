//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA, SHUGO KURODA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <xaudio2.h>					// �T�E���h�Đ��ɕK�v

//-----------------------------------------------------------------------------
// �T�E���h�N���X(��{�N���X)
//-----------------------------------------------------------------------------
class CSound
{
public:
	CSound();
	~CSound();

	// �T�E���h�t�@�C��
	typedef enum
	{
		// BGM��
		SOUND_LABEL_TITLE = 0,			// �^�C�g��BGM
		SOUND_LABEL_GAME,				// �Q�[��BGM
		// �Q�[��SE��
		SOUND_LABEL_SE_ATTACK,			// �U��
		SOUND_LABEL_SE_DAMAGE,			// ��e
		SOUND_LABEL_SE_DIE,				// ���S
		SOUND_LABEL_SE_JUMP,			// �W�����v
		SOUND_LABEL_SE_ENTRY,			// �v���C���[�Q��
		SOUND_LABEL_SE_PAUSE,			// �|�[�Y��ʂ��J��
		SOUND_LABEL_SE_BOSS,			// �ҏb�̙��K
		SOUND_LABEL_SE_WIN,				// �����t�@���t�@�[��
		SOUND_LABEL_SE_COUNT,			// �J�E���g�_�E����
		SOUND_LABEL_SE_START,			// �X�^�[�g
		SOUND_LABEL_SE_MENU_OK,			// ����
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit();
	static HRESULT Play(SOUND_LABEL label);
	static void Stop(SOUND_LABEL label);
	static void Stop();

private:
	// �p�����[�^�\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	static IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y

	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};

#endif
