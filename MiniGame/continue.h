//=============================================================================
//
// �R���e�B�j���[���[continue.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _CONTINUE_H_
#define _CONTINUE_H_

#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;
class CUi;

//*****************************************************************************
// �w�i�N���X��`
//*****************************************************************************
class CContinue : public CObject
{
	// �萔��`
	static const int LIFE_SIZE = 30;
	static const int MAX_CONTINUE = 2;
	static const int MAX_UI = 2;

	// �����o�֐�
public:
	CContinue();									//�R���X�g���N�^
	~CContinue() override;							//�f�X�g���N�^

	static CContinue *Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);		//����
	HRESULT Init() override;						//������
	void Uninit() override;							//�I��
	void Update() override;							//�X�V
	void Draw() override;							//�`��
	void Add(const int& nScore);					//�J�E���g�_�E���̉��Z

	// ���C�t�̎擾
	int GetLife() { return m_nContinue; }
	// �R���e�B�j���[���o��Ԃ̐ݒ�
	static void SetContinue(bool bContinue) { m_bContinue = bContinue; }
	// �R���e�B�j���[���o��Ԃ̎擾
	static bool GetContinue() { return m_bContinue; }

private:
	void Set();										//���l�̐ݒ�

	// �����o�ϐ� //
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�̃|�C���^
	CNumber *m_apNumber[MAX_CONTINUE];		//���C�t�Ɏg�p���鐔��
	CUi *m_pUi[MAX_UI];						//UI���̊i�[�p
	CObject2D *m_pFade;						//�t�F�[�h�p
	int m_nContinue;						//���C�t���i�[
	int m_nCountDown;						//�R���e�B�j���[�̃J�E���g�_�E��
	static bool m_bContinue;				//�R���e�B�j���[�����ǂ���
};

#endif // _LIFE_H_
