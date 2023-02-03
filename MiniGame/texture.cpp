//=============================================================================
//
// �e�N�X�`���}�l�[�W���[ [texture.cpp]
// Author : SHUGO KURODA
//
//=============================================================================
#include <stdio.h>

#include "texture.h"
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
CTexture::CTexture()
{
	// �ϐ��̏�����
	m_texType.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CTexture::Init()
{
	// �t�@�C���ǂݍ���
	FILE *pFile = fopen("data/TEXT/tex_pas.txt", "r");

	if (pFile == NULL)
	{// �t�@�C�����J���Ȃ������ꍇ
		return;
	}

	char cScanf[MAX_CHAR];		//��s���ǂݎ�邽�߂̕ϐ�
	char cScanfHead[MAX_CHAR];	//���̕�����ǂݎ�邽�߂̕ϐ�
	bool bReadScript = false;	//�X�N���v�g��ǂݍ��ނ��ǂ���
	int nNum = 0;

	// ��s���ۑ�
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

			// ������̒���TEX_NUM����������
			if (strcmp(&cScanfHead[0], "TEX_NUM") == 0)
			{
				// �e�N�X�`���ő吔�ǂݍ���
				sscanf(cScanf, "%s = %d", &cScanfHead, &m_nNumTex);
			}
			if (strcmp(&cScanfHead[0], "TEXSET") == 0)
			{// �e�N�X�`���ǂݍ��݂��J�n

				// ��s���ۑ�
				while (fgets(cScanf, MAX_CHAR, pFile) != NULL)
				{
					// ������̕���
					sscanf(cScanf, "%s", &cScanfHead);

					// ������̒���PAS����������
					if (strcmp(&cScanfHead[0], "PAS") == 0)
					{// �p�X�̎擾
						sscanf(cScanf, "%s = %s", &cScanfHead, &cScanf[0]);
						m_aPas.push_back(&cScanf[0]);
					}
					else if (strcmp(&cScanfHead[0], "NAME") == 0)
					{// ���O�̎擾
						sscanf(cScanf, "%s = %s", &cScanfHead, &cScanf[0]);
						// ���O�Ɛ��̊��蓖��
						m_texType[cScanf] = nNum;
						nNum++;
					}
					else if (strcmp(&cScanfHead[0], "END_TEXSET") == 0)
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

	// �f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	for (int nCntTex = 0; nCntTex < m_nNumTex; nCntTex++)
	{
		// �e�N�X�`���ۑ��p
		LPDIRECT3DTEXTURE9 pTexBuffer = nullptr;

		// �e�N�X�`���̐���
		D3DXCreateTextureFromFile(pDevice, m_aPas[nCntTex].c_str(), &pTexBuffer);

		// �e�N�X�`���̊��蓖��
		m_apTexture.push_back(pTexBuffer);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CTexture::Uninit()
{
	for (int nCntTexture = 0; nCntTexture < m_nNumTex; nCntTexture++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCntTexture] != NULL)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = NULL;
		}
	}
}
