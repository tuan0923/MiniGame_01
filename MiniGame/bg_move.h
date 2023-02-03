//-------------------------------------------
//
// ���S�̏��[logo.h]
// Author : SHUGO KURODA
//
//-------------------------------------------
#ifndef _BG_MOVE_H_
#define _BG_MOVE_H_

//-------------------------------------------
// �C���N���[�h
//-------------------------------------------
#include "object2D.h"

//-------------------------------------------
// ���S�N���X
//-------------------------------------------
class CBgMove: public CObject2D
{
public:
	// �R���X�g���N�^
	CBgMove();
	// �f�X�g���N�^
	~CBgMove() override;

	// ����
	static CBgMove* Create();
	// �e�N�X�`���̓ǂݍ���
	static HRESULT Load();
	// �e�N�X�`���̍폜
	static void Unload();

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �e�N�X�`���̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;
	// �A�j���[�V�����p�J�E���^�[
	int m_nCntAnim;
	// ���݂̃A�j���[�V�����ԍ�
	int m_nPatternAnim;
};

#endif		// _BG_MOVE_H_
