//=============================================================================
//
// �}�l�[�W���[����[manager.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "player.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;

class CTitle;
class CGame;
class CResult;

class CSound;				// �T�E���h�N���X
class CFade;				// �t�F�[�h�N���X
class CInputKeyboard;		// �L�[�{�[�h�N���X
class CInputJoypad;			// �W���C�p�b�h�N���X
class CInputMouse;			// �}�E�X�N���X

// �ǉ�
class CTexture;				// �e�N�X�`���N���X
class CXFile;				// X�t�@�C���N���X
class CXFileMotion;			// ���f�����[�V�����N���X
class CSetModel;			// ���f���z�u�N���X
class CDebugProc;			// �f�o�b�N�\���N���X

//*****************************************************************************
// �N���X��`(��{�N���X)
//*****************************************************************************
class CManager
{
public:
	// ���[�h�̎��
	enum MODE
	{
		MODE_TITLE = 0,		// �^�C�g��
		MODE_TUTORIAL,		// �`���[�g���A��
		MODE_GAME,			// �Q�[��
		MODE_RESULT,		// ���U���g
		MODE_MAX,
	};

	// �v���C���[�̎Q�����
	struct SEntryInfo
	{
		// �G���g���[���Ă��邩�ǂ���
		bool bEntry;
		// �Q�[���p�b�h�̔ԍ�
		int nGamePadNum;
		// �L�[�{�[�h�ŎQ�����Ă��邩�ǂ���
		bool bEntryKeyboard;
	};

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	// �S�ẴV�[����j��
	void UninitSceneAll();
	
	void SetMode(MODE mode);
	MODE GetMode() { return m_mode; }
	
	CRenderer *GetRenderer() { return m_pRenderer; }

	CTitle *GetTitle() { return m_pTitle; }
	CGame *GetGame() { return m_pGame; }
	CResult *GetResult() { return m_pResult; }

	CFade *GetFade() { return m_pFade; }
	CSound *GetSound() { return m_pSound; }
	CInputKeyboard *GetInputKeyboard() { return m_pInputKeyboard; }
	CInputJoypad *GetInputJoypad() { return m_pInputJoypad; }
	CInputMouse *GetInputMouse() { return m_pInputMouse; }

	// �ǉ�
	CTexture *GetTexture() { return m_pTexture; }
	CXFile *GetXFile() { return m_pXFile; }
	CXFileMotion *GetMotion() { return m_pMotion; }
	CSetModel *GetModelSet() { return m_pSetModel; }
	CDebugProc *GetDebugProc() { return m_pDebugProc; }
	/**/
	
	bool GetPause() { return m_bPause; }
	void SetPause(bool bPause) { m_bPause = bPause; }

	static CManager *GetManager() { return m_pManager; }
	static void SetManager(CManager *pManager) { m_pManager = pManager; }

	// �S�Ẵv���C���[���Q�����Ă��邩�ǂ���
	bool GetEntryAll();
	// �v���C���[�Q�����̐ݒ�
	void SetEntryAll(SEntryInfo *pEntry);

	void ResetEntry();

	// �v���C���[�Q�����̎擾
	SEntryInfo *GetEntry() { return &m_EntryInfo[0]; }

private:
	static CManager *m_pManager;		// �}�l�[�W���[�̃|�C���^

	CTitle *m_pTitle;					// �^�C�g�����̃|�C���^
	CGame *m_pGame;						// �Q�[�����̃|�C���^
	CResult *m_pResult;					// ���U���g���̃|�C���^

	CRenderer *m_pRenderer;				// �����_���[���̃|�C���^
	CInputKeyboard *m_pInputKeyboard;	// �L�[�{�[�h���̃|�C���^
	CInputJoypad *m_pInputJoypad;		// �W���C�p�b�h���̃|�C���^
	CInputMouse *m_pInputMouse;			// �}�E�X���̃|�C���^
	CSound *m_pSound;					// �T�E���h���̃|�C���^
	CFade *m_pFade;						// ��ʃt�F�[�h���̃|�C���^

	// �ǉ�
	CTexture *m_pTexture;				// �e�N�X�`�����̃|�C���^
	CXFile *m_pXFile;					// X�t�@�C�����̃|�C���^
	CXFileMotion *m_pMotion;			// ���f�����[�V�������̃|�C���^
	CSetModel *m_pSetModel;				// ���f���z�u���̃|�C���^
	CDebugProc *m_pDebugProc;			// �f�o�b�N�\�����̃|�C���^
	/**/

	MODE m_mode;						// ���[�h���
	bool m_bPause;						// �|�[�Y���邩�ǂ���

	int8_t m_nCounter;

	// �Q�����Ă��邩�ǂ���
	SEntryInfo m_EntryInfo[CPlayer::PLAYER_MAX];
};

#endif // _MANAGER_
