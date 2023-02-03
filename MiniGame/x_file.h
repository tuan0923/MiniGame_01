//=============================================================================
//
// X�t�@�C������ [x_file.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _X_FILE_H_
#define _X_FILE_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "x_file_data.h"
#include <vector>
#include <string>
#include <map>

//using namespace std;

//=============================================================================
// �N���X��`
//=============================================================================
class CXFile
{
public:
	//�����o�֐�
	CXFile();					//�R���X�g���N�^
	~CXFile();					//�f�X�g���N�^

	// ������
	void Init();
	// �I��
	void Uninit();
	// X�t�@�C���̃e�N�X�`���ǂݍ���
	void LoadXFileTexture(SModelInfo *XFile);

	// X�t�@�C�����̎擾(���O�w��)
	SModelInfo GetXFile(std::string texType) { return m_aXFile[m_texType[texType]]; }
	// X�t�@�C�����̎擾(�ԍ��w��)
	SModelInfo GetXFile(int nCnt) { return m_aXFile[nCnt]; }
	// X�t�@�C���̃p�X�擾����
	std::string GetPas(int nCntTex) { return m_aPas[nCntTex]; }
	// X�t�@�C���̑����擾����
	int GetNum() { return m_nNumXFile; }

private:
	std::vector<SModelInfo> m_aXFile;		// X�t�@�C�����
	std::vector<std::string> m_aPas;		// X�t�@�C���̃p�X
	std::map<std::string, int> m_texType;	// X�t�@�C���̎��
	int m_nNumXFile;						// X�t�@�C���̑���
};

#endif		// _X_FILE_H_
