//===================================================================
// 
//	�G�̐������[enemy_data.h]
//	Author : SHUGO KURODA
//
//===================================================================
#ifndef _ENEMY_DATA_H_
#define _ENEMY_DATA_H_

#include "renderer.h"

//===================================================================
// �}�N����`
//===================================================================
#define MAX_MOVE		(30)		//�ő�ړ���
#define MAX_WAVE		(50)		//�ő�E�F�[�u��(�����l)

//*******************************************************************
//	�G�̃��[�h���̒�`
//*******************************************************************
// �G�̈ړ����
typedef struct
{
	D3DXVECTOR3 posEnd;		//�ڕW�̈ʒu
	int nFrameMove;			//�ړ�����(�t���[��)
}EnemyMove;

//�G�̐������
typedef struct
{
	EnemyMove move[MAX_MOVE];	//�ړ����
	D3DXVECTOR3 pos;	//�o������ʒu
	int nMaxMove;		//�ő�ړ���
	int nFrame;			//�o������t���[��(����)
	int nType;			//�G�̎��
	int nLife;			//�G�̃��C�t
	int nColor;			//�Ō���̓G�̐F(���Ƃ��A�C�e���̎��)
	int nNum;			//�o������G�̐�
	int nInterval;		//�A���œG���o���Ԋu
}EnemyInfo;

//�{�X�����ݏo���G�̐������
typedef struct
{
	EnemyMove move[MAX_MOVE];	//�ړ����
	int nType;			//�G�̎��
	int nLife;			//�G�̃��C�t
	int nNum;			//�o������G�̐�
	int nInterval;		//�A���œG���o���Ԋu
}ParentEnemyInfo;

//�G�̐����J�E���^�[���
typedef struct
{
	// �G���A���Ő��������܂ł̎���
	int nCreate;
	// �G���������ꂽ��
	int nNum;
	//�G�𐶐����Ȃ����ǂ���
	bool bCreate;
}EnemyCount;

typedef struct
{
	// �G�����������܂ł̎���
	int nCreatenCount;
	//�G�̐����J�E���^�[���
	EnemyCount count[MAX_WAVE];
	// �G�̐������
	EnemyInfo *pCreate;
	// �ő�E�F�[�u��
	int nWave;
}EnemySetInfo;

#endif
