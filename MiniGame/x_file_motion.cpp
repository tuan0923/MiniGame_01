//=============================================================================
//
// X�t�@�C�����[�V���� [x_file_motion.cpp]
// Author : SHUGO KURODA
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <stdio.h>
#include "x_file_motion.h"

#include "renderer.h"
#include "manager.h"

// �ǉ�
//#include "motion_parts.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_CHAR (256)			//��s�̍ő�ǂݎ�蕶����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CXFileMotion::CXFileMotion()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CXFileMotion::~CXFileMotion()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CXFileMotion::Init(HWND hWnd)
{
	// �t�@�C���|�C���^�[�錾
	FILE *pFile = NULL;

	char cBff[MAX_CHAR];			// ��s���ǂݎ�邽�߂̕ϐ�
	char cBffHead[MAX_CHAR];		// ���̕�����ǂݎ�邽�߂̕ϐ�
	int nNum = 0;

	// �t�@�C�����J��
	pFile = fopen("data/TEXT/motion_pas.ini", "r");

	if (pFile == NULL)
	{// �J���Ȃ��������p
		MessageBox(hWnd, "INI�t�@�C�����J���܂���ł���", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// ������̓ǂݎ�胋�[�v����
	while (fgets(cBff, MAX_CHAR, pFile) != NULL)
	{
		// ������̕���
		sscanf(cBff, "%s", &cBffHead);

		// ������̒���TEX_NUM����������
		if (strcmp(&cBffHead[0], "MODEL_MOTION_NUM") == 0)
		{
			// ���f�����[�V�����ő吔�ǂݍ���
			sscanf(cBff, "%s = %d", &cBffHead, &m_nNumMotion);
		}
		if (strcmp(&cBffHead[0], "MODEL_MOTIONSET") == 0)
		{// ���f�����[�V�����ǂݍ��݂��J�n

			// ��s���ۑ�
			while (fgets(cBff, MAX_CHAR, pFile) != NULL)
			{
				// ������̕���
				sscanf(cBff, "%s", &cBffHead);

				if (strcmp(&cBffHead[0], "SCRIPT_FILENAME") == 0)
				{// ���[�V�����e�L�X�g�̑��΃p�X�p

					// ���΃p�X�ۑ��p
					char sPath[MAX_CHAR];

					// ��s�̕����񂩂瑊�΃p�X�̓ǂݎ��
					sscanf(cBff, "%s = %s", &cBffHead, &sPath[0]);

					// X�t�@�C���̓ǂݍ���
					if (LoadMotion(&sPath[0]) == false)
					{// �ǂݍ��ݎ��s
						MessageBox(hWnd, "���[�V�����e�L�X�g���J���܂���ł���", "�x���I", MB_ICONWARNING);
						return E_FAIL;
					}
				}
				else if (strcmp(&cBffHead[0], "NAME") == 0)
				{// ���O�̎擾
					sscanf(cBff, "%s = %s", &cBffHead, &cBff[0]);
					// ���O�Ɛ��̊��蓖��
					m_texType[cBff] = nNum;
					nNum++;
				}
				else if (strcmp(&cBffHead[0], "END_MODEL_MOTIONSET") == 0)
				{// ���f�����[�V�����ǂݍ��ݏI��
					break;
				}
			}
		}
		else if (strcmp(&cBffHead[0], "END_SCRIPT") == 0)
		{// �ǂݍ��ݏI��
			break;
		}
	}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CXFileMotion::Uninit()
{
	for (int nCntMotion = 0; nCntMotion < m_nNumMotion; nCntMotion++)
	{
		for (int nCntParts = 0; nCntParts < m_aMotion[nCntMotion].nNumParts; nCntParts++)
		{
			// ���b�V���̔j��
			if (m_aMotion[nCntMotion].aParts[nCntParts].xFile.pMesh != NULL)
			{
				m_aMotion[nCntMotion].aParts[nCntParts].xFile.pMesh->Release();
				m_aMotion[nCntMotion].aParts[nCntParts].xFile.pMesh = NULL;
			}
			// �}�e���A���̔j��
			if (m_aMotion[nCntMotion].aParts[nCntParts].xFile.pBuffMat != NULL)
			{
				m_aMotion[nCntMotion].aParts[nCntParts].xFile.pBuffMat->Release();
				m_aMotion[nCntMotion].aParts[nCntParts].xFile.pBuffMat = NULL;
			}
		}
	}
}

//-----------------------------------------------------------------------------
// ���[�V�������̓ǂݍ���
//-----------------------------------------------------------------------------
bool CXFileMotion::LoadMotion(char* pas)
{
	// �t�@�C���|�C���^�[�錾
	FILE *pFile = NULL;

	// �t�@�C�����J��
	pFile = fopen(pas, "r");

	if (pFile == NULL)
	{// �t�@�C�����J���Ȃ������ꍇ
		return false;
	}

	// ���[�V�������ۑ��p
	ModelMotion motion;
	// ��s���ǂݎ�邽�߂̕ϐ�
	char cBff[MAX_CHAR];
	// ���̕�����ǂݎ�邽�߂̕ϐ�
	char cBffHead[MAX_CHAR];
	// �p�[�c�̓ǂݍ���
	std::vector<SModelInfo> partsXFile;
	//�X�N���v�g��ǂݍ��ނ��ǂ���
	bool bReadScript = false;

	//������̓ǂݎ�胋�[�v����
	while (fgets(cBff, MAX_CHAR, pFile) != NULL)
	{
		// �����ǂݍ��ݗp�ϐ��̏�����
		memset(&cBffHead, 0, sizeof(cBffHead));
		// ������̕���
		sscanf(cBff, "%s", &cBffHead);

		if (!bReadScript && strcmp(&cBffHead[0], "SCRIPT") == 0)
		{// �X�N���v�g�̓ǂݍ��݂��J�n
			bReadScript = true;
		}
		else if (bReadScript)
		{// SCRIPT�ǂݍ��݂��J�n������

			if (strcmp(&cBffHead[0], "MODEL_FILENAME") == 0)
			{//X�t�@�C���̑��΃p�X�p

				// ���΃p�X�ۑ��p
				char sPath[MAX_CHAR];

				// ��s�̕����񂩂瑊�΃p�X�̓ǂݎ��
				sscanf(cBff, "%s = %s", &cBffHead, &sPath[0]);

				// �p�[�c�̓ǂݍ���
				SModelInfo xFile = LoadParts(&sPath[0]);

				// �p�[�c���̊i�[
				partsXFile.push_back(xFile);
			}
			else if (strcmp(&cBffHead[0], "CHARACTERSET") == 0)
			{//�v���C���[�̔z�u�p

				//�v���C���[���̓ǂݎ�胋�[�v����
				while (fgets(cBff, MAX_CHAR, pFile) != NULL)
				{
					//������̕���
					sscanf(cBff, "%s", &cBffHead);

					if (strcmp(&cBffHead[0], "NUM_PARTS") == 0)
					{//�p�[�c��
						//������̕���
						sscanf(cBff, "%s = %d", &cBffHead, &motion.nNumParts);
					}
					else if (strcmp(&cBffHead[0], "MOVE") == 0)
					{//�ړ���
						//������̕���
						sscanf(cBff, "%s = %f", &cBffHead, &motion.fMove);
					}
					else if (strcmp(&cBffHead[0], "JUMP") == 0)
					{//�W�����v��
						//������̕���
						sscanf(cBff, "%s = %f", &cBffHead, &motion.fJump);
					}
					else if (strcmp(&cBffHead[0], "PARTSSET") == 0)
					{
						// �p�[�c���ۑ��p	
						Parts parts;

						//�v���C���[�p�[�c���̓ǂݎ�胋�[�v����
						while (fgets(cBff, MAX_CHAR, pFile) != NULL)
						{
							//������̕���
							sscanf(cBff, "%s", &cBffHead);

							if (strcmp(&cBffHead[0], "INDEX") == 0)
							{//�p�[�c�ԍ�
								// ������̕���
								sscanf(cBff, "%s = %d", &cBffHead, &parts.nIndex);
							}
							else if (strcmp(&cBffHead[0], "PARENT") == 0)
							{//���݂̃p�[�c�̐e
								// ������̕���
								sscanf(cBff, "%s = %d", &cBffHead, &parts.nParent);
							}
							else if (strcmp(&cBffHead[0], "POS") == 0)
							{//�ʒu
								// ������̕���
								sscanf(cBff, "%s = %f%f%f", &cBffHead, &parts.pos.x, &parts.pos.y, &parts.pos.z);

								// �p�[�c�̐e�����Ȃ��Ȃ�
								if (parts.nParent == -1)
								{// �p�[�c���_�̕ۑ�
									motion.posParent = parts.pos;
								}
							}
							else if (strcmp(&cBffHead[0], "ROT") == 0)
							{//��](�p�x)
								// ������̕���
								sscanf(cBff, "%s = %f%f%f", &cBffHead, &parts.rot.x, &parts.rot.y, &parts.rot.z);
								parts.baseRot = parts.rot;
							}
							else if (strcmp(&cBffHead[0], "END_PARTSSET") == 0)
							{// �p�[�c�ǂݍ��ݏI��
								parts.xFile = partsXFile[parts.nIndex];
								// �p�[�c���̕ۑ�
								motion.aParts.push_back(parts);
								break;
							}
						}
					}
					else if (strcmp(&cBffHead[0], "END_CHARACTERSET") == 0)
					{//�v���C���[�ǂݍ��ݏI��
						break;
					}
				}
			}
			else if (strcmp(&cBffHead[0], "MOTIONSET") == 0)
			{//���[�V�����ݒ�p

				// ���[�V�������ۑ��p
				MotionSet motionInfo;

				//���[�V�������̓ǂݎ�胋�[�v����
				while (fgets(cBff, MAX_CHAR, pFile) != NULL)
				{
					//������̕���
					sscanf(cBff, "%s", &cBffHead);

					if (strcmp(&cBffHead[0], "LOOP") == 0)
					{//���[�v�ݒ�
						//������̕���
						sscanf(cBff, "%s = %d", &cBffHead, &motionInfo.nLoop);
					}
					else if (strcmp(&cBffHead[0], "NUM_KEY") == 0)
					{//�L�[�̐�
						//������̕���
						sscanf(cBff, "%s = %d", &cBffHead, &motionInfo.nNumKey);
					}
					else if (strcmp(&cBffHead[0], "KEYSET") == 0)
					{
						// �L�[���ۑ��p
						KeySet keyInfo;

						//�L�[�Z�b�g���̓ǂݎ�胋�[�v����
						while (fgets(cBff, MAX_CHAR, pFile) != NULL)
						{
							//������̕���
							sscanf(cBff, "%s", &cBffHead);

							if (strcmp(&cBffHead[0], "FRAME") == 0)
							{//���[�v�ݒ�
								//������̕���
								sscanf(cBff, "%s = %d", &cBffHead, &keyInfo.nFrame);

								if (keyInfo.nFrame == 0)
								{//�Đ��t���[������0�̏ꍇ1�ɂ���
									keyInfo.nFrame = 1;
								}
							}
							if (strcmp(&cBffHead[0], "KEY") == 0)
							{// ���[�v�ݒ�

								// �L�[���ۑ��p
								Key key;

								// �L�[���̓ǂݎ�胋�[�v����
								while (fgets(cBff, MAX_CHAR, pFile) != NULL)
								{
									//������̕���
									sscanf(cBff, "%s", &cBffHead);

									if (strcmp(&cBffHead[0], "POS") == 0)
									{//���[�V�����Đ����̈ʒu���ǂݍ���
									 //������̕���
										sscanf(cBff, "%s = %f%f%f", &cBffHead, &key.pos.x, &key.pos.y, &key.pos.z);
									}
									else if (strcmp(&cBffHead[0], "ROT") == 0)
									{//���[�V�����Đ����̉�]���ǂݍ���
									 //������̕���
										sscanf(cBff, "%s = %f%f%f", &cBffHead, &key.rot.x, &key.rot.y, &key.rot.z);
									}
									else if (strcmp(&cBffHead[0], "END_KEY") == 0)
									{
										keyInfo.aKey.push_back(key);
										break;
									}
								}
							}
							else if (strcmp(&cBffHead[0], "END_KEYSET") == 0)
							{
								motionInfo.aKeyInfo.push_back(keyInfo);
								break;
							}
						}
					}
					else if (strcmp(&cBffHead[0], "END_MOTIONSET") == 0)
					{
						// ���[�V�����̑��������Z
						motion.nNumMotion++;
						motion.aMotion.push_back(motionInfo);
						break;
					}
				}
			}
			// �e�L�X�g�t�@�C����ǂݐ؂�����
			else if (strcmp(&cBffHead[0], "END_SCRIPT") == 0)
			{
				// ���[�V�������̊i�[
				m_aMotion.push_back(motion);
				break;
			}
		}
	}

	//�t�@�C�������
	fclose(pFile);

	return true;
}

//-----------------------------------------------------------------------------
// X�t�@�C���̓ǂݍ���
//-----------------------------------------------------------------------------
SModelInfo CXFileMotion::LoadParts(const char* pas)
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	// ���f�����ۑ��p
	SModelInfo xFile;

	//X�t�@�C���̓ǂݍ���
	HRESULT hr = D3DXLoadMeshFromX(pas,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&xFile.pBuffMat,
		NULL,
		&xFile.nNumMat,
		&xFile.pMesh);

	if (hr != S_OK)
	{//X�t�@�C���ǂݍ��ݎ��s
		//return nullptr;
	}

	// �e�N�X�`���̓ǂݍ��ݏ���
	LoadXFileTexture(&xFile);

	return xFile;
}

//-----------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-----------------------------------------------------------------------------
void CXFileMotion::LoadXFileTexture(SModelInfo* pXFile)
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
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &pXFile->pTexture[nCntMat]);
		}
	}
}
