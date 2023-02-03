//-------------------------------------------
//
// �Q�[�W���[gauge.h]
// Author : SHUGO KURODA
//
//-------------------------------------------
#ifndef _GAUGE_H_
#define _GAUGE_H_

//-------------------------------------------
// �C���N���[�h
//-------------------------------------------
#include "object2D.h"

//-------------------------------------------
// ���S�N���X
//-------------------------------------------
class CGauge : public CObject2D
{
private:
	// �ő�Q�[�W��
	static const int MAX_LEVEL = 4;
	// �T�C�YX
	static const float SIZE_X;
	// �T�C�YY
	static const float SIZE_Y;

public:
	// �ǂ̃v���C���[�̃Q�[�W��
	enum PARENT
	{
		PLAYER_1 = 0,	//1P
		PLAYER_2,		//2P
	};

	//�ǂ̎�ނ̃Q�[�W��
	enum TYPE
	{
		TYPE_NONE = 0,			// �����Ȃ�
		TYPE_BULLET,			// ���C���e
		TYPE_BULLET_OPTION,		// �I�v�V�����e
		TYPE_BARRIER,			// �o���A
		TYPE_MAX
	};

	// �R���X�g���N�^
	CGauge();
	// �f�X�g���N�^
	~CGauge() override;

	// ����
	static CGauge* Create(const D3DXVECTOR3& pos, const TYPE& type, const PARENT& parent);
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
	// �Q�[�W�̎�ނ�
	TYPE m_type;
	// �ǂ̃v���C���[��UI��
	PARENT m_parent;
};

#endif		// _GAUGE_H_
