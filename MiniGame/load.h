//===================================================================
//
//	���[�h�����̃w�b�_�[[load.h]
//	Author:���c ����
//
//===================================================================
#ifndef _LOAD_H_			//���̃}�N����`������Ȃ�������
#define _LOAD_H_			//2�d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "enemy_data.h"

//======================================================
//	���[�h�����̃l�[���X�y�[�X
//======================================================
namespace LoadSpace
{
	HRESULT LoadEnemy(HWND hWnd);
	EnemyInfo *GetEnemy();
	ParentEnemyInfo *GetParentEnemy();
	int GetWave();
	int LoadScore();
	void SaveScore(int nScore);
}

#endif