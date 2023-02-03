//=============================================================================
//
// ���[�h���� [load.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include <stdio.h>
#include "load.h"
#include "enemy_data.h"
#include "game.h"
#include "rank.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_CHAR	(256)			//��s�̍ő�ǂݎ�蕶����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
EnemyInfo g_aEnemyInfo[MAX_WAVE];	//�G���̎擾
ParentEnemyInfo g_aParentEnemyInfo[MAX_WAVE];	//�{�X����������G���̎擾
int g_nMaxWave;

//-----------------------------------------------------------------------------
//	�G�̃Z�b�g���[�h
//-----------------------------------------------------------------------------
HRESULT LoadSpace::LoadEnemy(HWND hWnd)
{
	//�t�@�C���|�C���^�[�錾
	FILE *pFile = NULL;

	//������
	ZeroMemory(&g_aEnemyInfo, sizeof(g_aEnemyInfo));
	ZeroMemory(&g_aParentEnemyInfo, sizeof(g_aParentEnemyInfo));
	int nIdxEnemy = 0;			//�G���̔z��ԍ��̕ۑ��p
	int nIdxParentEnemy = 0;	//�{�X���̔z��ԍ��̕ۑ��p

	//�ϐ��錾
	char cScanf[MAX_CHAR];		//��s���ǂݎ�邽�߂̕ϐ�
	char cScanfHead[MAX_CHAR];	//���̕�����ǂݎ�邽�߂̕ϐ�
	bool bReadScript = false;	//�X�N���v�g��ǂݍ��ނ��ǂ���

	//�t�@�C�����J��
	pFile = fopen("data/TEXT/set_enemy.txt", "r");

	if (pFile == NULL)
	{//�t�@�C�����J���Ȃ������ꍇ
		MessageBox(hWnd, "�G�z�u�e�L�X�g���J���܂���ł���", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	//������̓ǂݎ�胋�[�v����
	while (fgets(cScanf, MAX_CHAR, pFile) != NULL)
	{
		//������̕���
		sscanf(cScanf, "%s", &cScanfHead);

		if (!bReadScript && strcmp(&cScanfHead[0], "SCRIPT") == 0)
		{//�X�N���v�g�̓ǂݍ��݂��J�n
			bReadScript = true;
		}
		else if (strcmp(&cScanfHead[0], "MAX_WAVE") == 0)
		{//�ő�E�F�[�u��
			sscanf(cScanf, "%s = %d", &cScanfHead, &g_nMaxWave);
		}
		else if (bReadScript)
		{//SCRIPT�ǂݍ��݂��J�n������

			//=================================
			// �G���
			//=================================
			if (strcmp(&cScanfHead[0], "ENEMYSET") == 0)
			{//�G�̔z�u���J�n

				//�v���C���[���̓ǂݎ�胋�[�v����
				while (fgets(cScanf, MAX_CHAR, pFile) != NULL)
				{
					//������̕���
					sscanf(cScanf, "%s", &cScanfHead);

					if (strcmp(&cScanfHead[0], "MAXMOVE") == 0)
					{//�ő�ړ���
						sscanf(cScanf, "%s = %d", &cScanfHead, &g_aEnemyInfo[nIdxEnemy].nMaxMove);
					}
					else if (strcmp(&cScanfHead[0], "FRAME") == 0)
					{//�o���t���[��
						sscanf(cScanf, "%s = %d", &cScanfHead, &g_aEnemyInfo[nIdxEnemy].nFrame);
					}
					else if (strcmp(&cScanfHead[0], "POS") == 0)
					{//�o���ʒu
						sscanf(cScanf, "%s = %f%f%f", &cScanfHead, &g_aEnemyInfo[nIdxEnemy].pos.x, &g_aEnemyInfo[nIdxEnemy].pos.y, &g_aEnemyInfo[nIdxEnemy].pos.z);
					}
					else if (strcmp(&cScanfHead[0], "TYPE") == 0)
					{//�G�̎��
						sscanf(cScanf, "%s = %d", &cScanfHead, &g_aEnemyInfo[nIdxEnemy].nType);
					}
					else if (strcmp(&cScanfHead[0], "LIFE") == 0)
					{//�G�̃��C�t
						sscanf(cScanf, "%s = %d", &cScanfHead, &g_aEnemyInfo[nIdxEnemy].nLife);
					}
					else if (strcmp(&cScanfHead[0], "NUM") == 0)
					{//�G�̐�
						sscanf(cScanf, "%s = %d", &cScanfHead, &g_aEnemyInfo[nIdxEnemy].nNum);
					}
					else if (strcmp(&cScanfHead[0], "INTERVAL") == 0)
					{//�G�̐�
						sscanf(cScanf, "%s = %d", &cScanfHead, &g_aEnemyInfo[nIdxEnemy].nInterval);
					}
					else if (strcmp(&cScanfHead[0], "COLOR") == 0)
					{//�Ō���̓G�̐F(���Ƃ��A�C�e��)
						sscanf(cScanf, "%s = %d", &cScanfHead, &g_aEnemyInfo[nIdxEnemy].nColor);
					}
					else if (strcmp(&cScanfHead[0], "MOVESET") == 0)
					{//�G�̈ړ����
						int nIdxMove = 0;
						//�v���C���[�p�[�c���̓ǂݎ�胋�[�v����
						while (fgets(cScanf, MAX_CHAR, pFile) != NULL)
						{
							//������̕���
							sscanf(cScanf, "%s", &cScanfHead);

							if (strcmp(&cScanfHead[0], "MOVE") == 0)
							{//�ړ��ʒu�̐ݒ�
								sscanf(cScanf, "%s = %f%f%d", &cScanfHead,
									&g_aEnemyInfo[nIdxEnemy].move[nIdxMove].posEnd.x,
									&g_aEnemyInfo[nIdxEnemy].move[nIdxMove].posEnd.y,
									&g_aEnemyInfo[nIdxEnemy].move[nIdxMove].nFrameMove);
								//�z��ԍ��̉��Z
								nIdxMove++;
							}
							else if (strcmp(&cScanfHead[0], "END_MOVESET") == 0)
							{//�p�[�c�ǂݍ��ݏI��
								break;
							}
						}
					}
					else if (strcmp(&cScanfHead[0], "END_ENEMYSET") == 0)
					{//�v���C���[�ǂݍ��ݏI��
						nIdxEnemy++;
						break;
					}
				}
			}
			//=================================
			// �{�X����������G���
			//=================================
			else if (strcmp(&cScanfHead[0], "BOSSSET") == 0)
			{//�G�̔z�u���J�n

			 //�v���C���[���̓ǂݎ�胋�[�v����
				while (fgets(cScanf, MAX_CHAR, pFile) != NULL)
				{
					//������̕���
					sscanf(cScanf, "%s", &cScanfHead);

					if (strcmp(&cScanfHead[0], "TYPE") == 0)
					{//�G�̎��
						sscanf(cScanf, "%s = %d", &cScanfHead, &g_aParentEnemyInfo[nIdxParentEnemy].nType);
					}
					else if (strcmp(&cScanfHead[0], "LIFE") == 0)
					{//�G�̃��C�t
						sscanf(cScanf, "%s = %d", &cScanfHead, &g_aParentEnemyInfo[nIdxParentEnemy].nLife);
					}
					else if (strcmp(&cScanfHead[0], "NUM") == 0)
					{//�G�̐�
						sscanf(cScanf, "%s = %d", &cScanfHead, &g_aParentEnemyInfo[nIdxParentEnemy].nNum);
					}
					else if (strcmp(&cScanfHead[0], "INTERVAL") == 0)
					{//�G�̐�
						sscanf(cScanf, "%s = %d", &cScanfHead, &g_aParentEnemyInfo[nIdxParentEnemy].nInterval);
					}
					else if (strcmp(&cScanfHead[0], "MOVESET") == 0)
					{
						int nIdxParentMove = 0;
						//�v���C���[�p�[�c���̓ǂݎ�胋�[�v����
						while (fgets(cScanf, MAX_CHAR, pFile) != NULL)
						{
							//������̕���
							sscanf(cScanf, "%s", &cScanfHead);

							if (strcmp(&cScanfHead[0], "MOVE") == 0)
							{//�ړ��ʒu�̐ݒ�
								sscanf(cScanf, "%s = %f%f%d", &cScanfHead,
									&g_aParentEnemyInfo[nIdxParentEnemy].move[nIdxParentMove].posEnd.x,
									&g_aParentEnemyInfo[nIdxParentEnemy].move[nIdxParentMove].posEnd.y,
									&g_aParentEnemyInfo[nIdxParentEnemy].move[nIdxParentMove].nFrameMove);
								//�z��ԍ��̉��Z
								nIdxParentMove++;
							}
							else if (strcmp(&cScanfHead[0], "END_MOVESET") == 0)
							{//�p�[�c�ǂݍ��ݏI��
								break;
							}
						}
					}
					else if (strcmp(&cScanfHead[0], "END_BOSSSET") == 0)
					{//�v���C���[�ǂݍ��ݏI��
						nIdxParentEnemy++;
						break;
					}
				}
			}
		}
		else if (strcmp(&cScanfHead[0], "END_SCRIPT") == 0)
		{//�e�L�X�g�t�@�C����ǂݐ؂�����
			break;
		}
	}

	//�t�@�C�������
	fclose(pFile);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	�G�̔z�u���̎擾
//-----------------------------------------------------------------------------
EnemyInfo *LoadSpace::GetEnemy()
{
	return &g_aEnemyInfo[0];
}

//-----------------------------------------------------------------------------
//	�{�X�̕����z�u���̎擾
//-----------------------------------------------------------------------------
ParentEnemyInfo *LoadSpace::GetParentEnemy()
{
	return &g_aParentEnemyInfo[0];
}

//-----------------------------------------------------------------------------
//	�ő�E�F�[�u���̎擾
//-----------------------------------------------------------------------------
int LoadSpace::GetWave()
{
	return g_nMaxWave;
}

//-----------------------------------------------------------------------------
//	�����L���O�X�R�A�̃��[�h
//-----------------------------------------------------------------------------
int LoadSpace::LoadScore()
{
	int nScore = 0;

	//�t�@�C�����J��
	FILE *pFile = fopen("data/TEXT/Rank.txt", "r");			//�t�@�C���|�C���^�[�錾

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &nScore);
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}

	//�t�@�C�������
	fclose(pFile);

	return nScore;
}

//-----------------------------------------------------------------------------
//	�����L���O�X�R�A�̃Z�[�u
//-----------------------------------------------------------------------------
void LoadSpace::SaveScore(int nScore)
{
	//�t�@�C�����J��
	FILE *pFile = fopen("data/TEXT/Rank.txt", "w");			//�t�@�C���|�C���^�[�錾

	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", nScore);
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}

	//�t�@�C�������
	fclose(pFile);
}
