//===================================================================
//
//	�A�C�e������[item.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "object2D.h"
#include "model.h"
//*******************************************************************
//	�A�C�e���N���X�̒�`
//*******************************************************************
class CItem : public CModel
{
private:
	// �T�C�Y(X)
	static const float SIZE_WIDTH;
	// �T�C�Y(Y)
	static const float SIZE_HEIGHT;
	// ��{�ړ���
	static const float MOVE_DEFAULT;
	// �A�j���[�V�����Ԋu
	static const int ANIM_INTERVAL;
	// �A�j���[�V�����ő吔
	static const int MAX_ANIM;
	// U���W�̍ő啪����
	static const int DIVISION_U;
	// V���W�̍ő啪����
	static const int DIVISION_V;

public:
	enum EType
	{//�A�C�e���̎��
		TYPE_NONE = 0,
		TYPE_RED,
		TYPE_BLUE,
		TYPE_GREEN,
		TYPE_ORANGE,
		TYPE_MAX,
	};

	CItem();
	~CItem() override;

	//�����o�֐�
	static CItem *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const EType type, const char* name);		//�C���X�^���X��������
	//�e�N�X�`���̓ǂݍ���
	static HRESULT Load();
	//�e�N�X�`���̍폜
	static void Unload();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//�����蔻��
	bool Collision(D3DXVECTOR3 posStart);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	//�e�N�X�`���̃|�C���^
	float m_fRot;					//��]�̊p�x
	int m_nCntAnim;					//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;				//�A�j���[�V�����̃p�^�[��No.
	EType m_type;					//�A�C�e���̎��
};

#endif		// _ITEM_H_
