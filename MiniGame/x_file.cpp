//=============================================================================
//
// X�t�@�C���}�l�[�W���[ [x_file.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include <stdio.h>

#include "x_file.h"
#include "renderer.h"
#include "manager.h"

//================================================
// �}�N����`
//================================================
#define MAX_CHAR		(128)		// �ő�ǂݎ�蕶����

//================================================
// �ÓI�����o�ϐ��錾
//================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CXFile::CXFile()
{
	// �ϐ��̏�����
	m_texType.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CXFile::~CXFile()
{
}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CXFile::Init()
{
	//�t�@�C���ǂݍ���
	FILE *pFile = fopen("data/TEXT/x_file_pas.txt", "r");

	if (pFile == NULL)
	{// �t�@�C�����J���Ȃ������ꍇ
		return;
	}

	char cScanf[MAX_CHAR];		//��s���ǂݎ�邽�߂̕ϐ�
	char cScanfHead[MAX_CHAR];	//���̕�����ǂݎ�邽�߂̕ϐ�
	bool bReadScript = false;	//�X�N���v�g��ǂݍ��ނ��ǂ���
	int nNum = 0;

	//��s���ۑ�
	while (fgets(cScanf, MAX_CHAR, pFile) != NULL)
	{
		// ������̕���
		sscanf(cScanf, "%s", &cScanfHead);

		if (!bReadScript && strcmp(&cScanfHead[0], "SCRIPT") == 0)
		{// �X�N���v�g�̓ǂݍ��݂��J�n
			bReadScript = true;
		}
		else if (bReadScript)
		{// SCRIPT�ǂݍ��݂��J�n������

			//������̒���TEX_NUM����������
			if (strcmp(&cScanfHead[0], "XFILE_NUM") == 0)
			{
				// �e�N�X�`���ő吔�ǂݍ���
				sscanf(cScanf, "%s = %d", &cScanfHead, &m_nNumXFile);
			}
			if (strcmp(&cScanfHead[0], "XFILESET") == 0)
			{// �e�N�X�`���ǂݍ��݂��J�n

				//��s���ۑ�
				while (fgets(cScanf, MAX_CHAR, pFile) != NULL)
				{
					// ������̕���
					sscanf(cScanf, "%s", &cScanfHead);

					// ������̒���PAS����������
					if (strcmp(&cScanfHead[0], "PAS") == 0)
					{
						// �p�X�̎擾
						sscanf(cScanf, "%s = %s", &cScanfHead, &cScanf[0]);
						m_aPas.push_back(&cScanf[0]);
					}
					else if (strcmp(&cScanfHead[0], "NAME") == 0)
					{// ���O�̎擾
						//���O�̎擾
						sscanf(cScanf, "%s = %s", &cScanfHead, &cScanf[0]);
						// ���O�Ɛ��̊��蓖��
						m_texType[cScanf] = nNum;
						nNum++;
					}
					else if (strcmp(&cScanfHead[0], "END_XFILESET") == 0)
					{// �e�N�X�`���ǂݍ��ݏI��
						break;
					}
				}
			}
			else if (strcmp(&cScanfHead[0], "END_SCRIPT") == 0)
			{// �e�L�X�g�t�@�C����ǂݐ؂�����
				break;
			}
		}
	}

	// �t�@�C�������
	fclose(pFile);

	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	for (int nCntXFile = 0; nCntXFile < m_nNumXFile; nCntXFile++)
	{
		// �e�N�X�`���ۑ��p
		SModelInfo xFile;

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_aPas[nCntXFile].c_str(),
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&xFile.pBuffMat,
			NULL,
			&xFile.nNumMat,
			&xFile.pMesh);

		// �e�N�X�`���̓ǂݍ��ݏ���
		LoadXFileTexture(&xFile);

		// X�t�@�C�����̕ۑ�
		m_aXFile.push_back(xFile);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CXFile::Uninit()
{
	for (int nCnt = 0; nCnt < m_nNumXFile; nCnt++)
	{
		//���b�V���̔j��
		if (m_aXFile[nCnt].pMesh != NULL)
		{
			m_aXFile[nCnt].pMesh->Release();
			m_aXFile[nCnt].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (m_aXFile[nCnt].pBuffMat != NULL)
		{
			m_aXFile[nCnt].pBuffMat->Release();
			m_aXFile[nCnt].pBuffMat = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �e�N�X�`���ǂݍ���
//-----------------------------------------------------------------------------
void CXFile::LoadXFileTexture(SModelInfo* pXFile)
{
	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)pXFile->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pXFile->nNumMat; nCntMat++)
	{
		//�f�o�C�X���擾����
		LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`�����������ꍇ
		if ((pMat[nCntMat].pTextureFilename != NULL) && (strcmp(pMat[nCntMat].pTextureFilename, "") != 0))
		{//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &pXFile->pTexture[nCntMat]);
		}
	}
}
