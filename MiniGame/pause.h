//=============================================================================
//
// �|�[�Y��ʏ�� [pause.h]
// Author:SHUGO KURODA
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include <stdio.h>

#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;			// �I�u�W�F�N�g�N���X

//*****************************************************************************
// �|�[�Y��ʃN���X(�h���N���X)
//*****************************************************************************
class CPause : public CObject
{
public:
	enum TYPE
	{//�|�[�Y�̎��
		TYPE_FRAME = 0,		// �|�[�Y��ʘg
		//TYPE_RESUME,		// �ĊJ
		TYPE_RESTART,		// ��蒼��
		TYPE_EXIT,			// �^�C�g���ɖ߂�
		TYPE_SELECTOR,		// �I���J�[�\��
		TYPE_MAX			// �|�[�Y�̍ő吔
	};

	CPause();
	~CPause();

	static CPause *Create(int nNumPlayer);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetPause();

private:
	bool m_bPause;
	int m_nPauseSelect;					// �|�[�Y���j���[����J�ڂ���ꏊ��ۑ�
	int m_nNumPlayer;					// �|�[�Y���j���[���J�����v���C���[

	static CObject2D *m_apObject2D[TYPE_MAX];			//2D�|���S���ւ̃|�C���^
	bool m_bWait;		//�A���{�^�������h�~�p
};

#endif
