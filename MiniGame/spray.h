//-------------------------------------------
//
// �򖗂̏��[spray.h]
// Author : SHUGO KURODA
//
//-------------------------------------------
#ifndef _SPRAY_H_
#define _SPRAY_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object2D.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �����N���X
//-------------------------------------------
class CSpray : public CObject2D
{
private:		// �萔
	// ��
	static const float SIZE_WIDTH;
	// ����
	static const float SIZE_HEIGHT;
	// �A�j���[�V�����Ԋu
	static const int ANIM_INTERVAL;
	// �A�j���[�V�����ő吔
	static const int MAX_ANIM;
	// U���W�̍ő啪����
	static const int DIVISION_U;
	// V���W�̍ő啪����
	static const int DIVISION_V;

public:
	// �R���X�g���N�^
	CSpray();
	// �f�X�g���N�^
	~CSpray() override;

	// ����
	static CSpray* Create(const D3DXVECTOR3& pos);
	// �e�N�X�`���̓ǂݍ���
	static HRESULT Load();
	// �e�N�X�`���̍폜
	static void Unload();
	//�ړ�����
	static void Move(float fMove);

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
	// ���݂̃A�j���[�V����V�ԍ�
	int m_nPatterAnimV;
};

#endif		// _EXPLOSION_H_
