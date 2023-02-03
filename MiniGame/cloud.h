//===================================================================
//
//	�e�̏���[bullet.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _CLOUD_H_
#define _CLOUD_H_

#include "object2D.h"

//*******************************************************************
//	�e�N���X�̒�`
//*******************************************************************
class CCloud : public CObject2D
{
private:	//�萔��`
	//�ő�e�N�X�`����
	static const int MAX_TEX = 2;
	//��T�C�Y(X)
	static const int DEFAULT_WIDTH = 200;
	//�ō��T�C�Y(X)
	static const int MAX_WIDTH = 400;
	//��T�C�Y(Y)
	static const int DEFAULT_HEIGHT = 100;
	//�ō��T�C�Y(Y)
	static const int MAX_HEIGHT = 200;
	//��ړ���
	static const int DEFAULT_MOVE = 1;
	//�ō��ړ���
	static const int MAX_MOVEING = 2;

public:
	CCloud();
	~CCloud() override;

	//�����o�֐�
	static CCloud *Create();	//�C���X�^���X��������
	static CCloud *Create(D3DXVECTOR3 pos);	//�C���X�^���X��������

	static D3DXVECTOR2 SetRandSize();	//�T�C�Y�������_���Ɍ��߂�
	static HRESULT Load();		//�e�N�X�`���̓ǂݍ���
	static void Unload();		//�e�N�X�`���̍폜
	static void AddPos(float fMul) { m_fCreatePos += 0.5f * fMul; }		//�ʒu�̉��Z
	static void Move(float fMove);		//�_�̈ړ�����

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEX];	//�e�N�X�`���̃|�C���^
	static float m_fCreatePos;		// �_�̐����ʒu
	D3DXVECTOR3 m_move;				// �ړ���
};

#endif		// _BULLET_H_
