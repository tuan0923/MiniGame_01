//=============================================================================
//
// X�t�@�C�����[�V���� [set_model.cpp]
// Author : SHUGO KURODA
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <stdio.h>
#include "set_model.h"

#include "renderer.h"
#include "manager.h"

// �ǉ�
#include "model.h"
#include "model_obstacle.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_CHAR (256)			//��s�̍ő�ǂݎ�蕶����

//=============================================================================
// �\����
//=============================================================================
struct Model
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 rot;			// ��]
	char cName[MAX_CHAR];		// ���
	int8_t nCollision;			// �����蔻��̗L��
	D3DXVECTOR2 shadowSize;		// �e�̃T�C�Y
	int8_t nShadow;				// �e��z�u
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSetModel::CSetModel()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSetModel::~CSetModel()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CSetModel::Init(HWND hWnd)
{
	// �t�@�C�����J��
	FILE *pFile = fopen("data/TEXT/model_pas.ini", "r");

	if (pFile == NULL)
	{//�J���Ȃ��������p
		MessageBox(hWnd, "���f���z�uINI�t�@�C�����J���܂���ł���", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	char cBff[MAX_CHAR];			// ��s���ǂݎ�邽�߂̕ϐ�
	char cBffHead[MAX_CHAR];		// ���̕�����ǂݎ�邽�߂̕ϐ�
	int nNum = 0;

	//������̓ǂݎ�胋�[�v����
	while (fgets(cBff, MAX_CHAR, pFile) != NULL)
	{
		//������̕���
		sscanf(cBff, "%s", &cBffHead);

		// ������̒���TEX_NUM����������
		if (strcmp(&cBffHead[0], "MODEL_NUM") == 0)
		{
			// ���f�����[�V�����ő吔�ǂݍ���
			sscanf(cBff, "%s = %d", &cBffHead, &m_nNumMotion);
		}
		if (strcmp(&cBffHead[0], "MODELSET") == 0)
		{// ���f�����[�V�����ǂݍ��݂��J�n

			// ��s���ۑ�
			while (fgets(cBff, MAX_CHAR, pFile) != NULL)
			{
				//������̕���
				sscanf(cBff, "%s", &cBffHead);

				if (strcmp(&cBffHead[0], "SCRIPT_FILENAME") == 0)
				{//���[�V�����e�L�X�g�̑��΃p�X�p

					//���΃p�X�ۑ��p
					char sPath[MAX_CHAR];

					//��s�̕����񂩂瑊�΃p�X�̓ǂݎ��
					sscanf(cBff, "%s = %s", &cBffHead, &sPath[0]);
					m_aPas.push_back(&sPath[0]);
				}
				else if (strcmp(&cBffHead[0], "NAME") == 0)
				{// ���O�̎擾
					sscanf(cBff, "%s = %s", &cBffHead, &cBff[0]);
					// ���O�Ɛ��̊��蓖��
					m_texType[cBff] = nNum;
					nNum++;
				}
				else if (strcmp(&cBffHead[0], "END_MODELSET") == 0)
				{// ���f�����[�V�����ǂݍ��ݏI��
					break;
				}
			}
		}
		else if (strcmp(&cBffHead[0], "END_SCRIPT") == 0)
		{//�ǂݍ��ݏI��
			break;
		}
	}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CSetModel::Uninit()
{
}

//-----------------------------------------------------------------------------
// ���[�V�������̓ǂݍ���
//-----------------------------------------------------------------------------
bool CSetModel::LoadModel(std::string name)
{
	// �t�@�C�����J��
	FILE *pFile = fopen(m_aPas[m_texType[name]].c_str(), "r");
	
	if (pFile == NULL)
	{// �t�@�C�����J���Ȃ������ꍇ
		return false;
	}

	char cBff[MAX_CHAR];			// ��s���ǂݎ��ϐ�
	char cBffHead[MAX_CHAR];		// ���̕�����ǂݎ��ϐ�
	bool bReadScript = false;		// �X�N���v�g��ǂݍ��ނ��ǂ���

	// ������̓ǂݎ�胋�[�v����
	while (fgets(cBff, MAX_CHAR, pFile) != NULL)
	{
		// ������̕���
		sscanf(cBff, "%s", &cBffHead);

		if (!bReadScript && strcmp(&cBffHead[0], "SCRIPT") == 0)
		{// �X�N���v�g�̓ǂݍ��݂��J�n
			bReadScript = true;
		}
		else if (bReadScript)
		{// SCRIPT�ǂݍ��݂��J�n������

			if (strcmp(&cBffHead[0], "MODELSET") == 0)
			{//���f���̔z�u�p

				// ���f���z�u���̕ۑ��p
				Model model;
				// �����ǂݍ��ݗp�ϐ��̏�����
				memset(&model, 0, sizeof(Model));

				// ���f���z�u�ɕK�v�ȏ��ǂݎ�胋�[�v����
				while (fgets(cBff, MAX_CHAR, pFile) != NULL)
				{
					// ������̕���
					sscanf(cBff, "%s", &cBffHead);

					if (strcmp(&cBffHead[0], "TYPE") == 0)
					{// ���f���̎�ޗp
						sscanf(cBff, "%s = %s", &cBffHead, &model.cName[0]);
					}
					else if (strcmp(&cBffHead[0], "POS") == 0)
					{// �ʒu
						sscanf(cBff, "%s = %f%f%f", &cBffHead, &model.pos.x, &model.pos.y, &model.pos.z);
					}
					else if (strcmp(&cBffHead[0], "ROT") == 0)
					{// �p�x
						sscanf(cBff, "%s = %f%f%f", &cBffHead, &model.rot.x, &model.rot.y, &model.rot.z);
					}
					else if (strcmp(&cBffHead[0], "COLLISION") == 0)
					{// �����蔻��
						sscanf(cBff, "%s = %hhd", &cBffHead, &model.nCollision);
					}
					else if (strcmp(&cBffHead[0], "SHADOW") == 0)
					{// �e�̃Z�b�g
						sscanf(cBff, "%s = %hhd%f%f", &cBffHead, &model.nShadow, &model.shadowSize.x, &model.shadowSize.y);
					}
					else if (strcmp(&cBffHead[0], "END_MODELSET") == 0)
					{// ���f���̃Z�b�g�ɕK�v�ȏ���ǂݐ؂�����

						//if (Model.bShadow == true)
						//{//nCheck��1�ȏ�̏ꍇ�A�e��ݒ肷��
						//	Model.nIdxShadow = SetShadow(D3DXVECTOR3(Model.pos.x, 0.1f, Model.pos.z), Model.rot, fShadowX, fShadowZ);

						// ���f���z�u
						CObstacle::Create(model.pos, model.rot, &model.cName[0])->SetCont(-1);

						break;
					}
				}
			}
			else if (strcmp(&cBffHead[0], "END_SCRIPT") == 0)
			{//�e�L�X�g�t�@�C����ǂݐ؂�����
				break;
			}
		}
	}

	//�t�@�C�������
	fclose(pFile);

	return true;
}
