//=============================================================================
//
// X�t�@�C�����[�V���� [x_file_motion.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _X_FILE_MOTION_H_
#define _X_FILE_MOTION_H_

#include "motion_data.h"
#include <vector>
#include <string>
#include <map>

//using namespace std;

//=============================================================================
// �N���X��`
//=============================================================================
class CXFileMotion
{
	// �����o�֐�
public:
	CXFileMotion();					//�R���X�g���N�^
	~CXFileMotion();				//�f�X�g���N�^

	// ������
	HRESULT Init(HWND hWnd);
	// �I��
	void Uninit();
	// ���[�V�������̓ǂݍ���
	bool LoadMotion(char *pas);
	// X�t�@�C�����̎擾(���O�w��)
	ModelMotion GetMotion(std::string texType) { return m_aMotion[m_texType[texType]]; }
	// X�t�@�C�����̎擾(�ԍ��w��)
	ModelMotion GetMotion(int nCnt) { return m_aMotion[nCnt]; }

private:
	// �p�[�c�̓ǂݍ���
	SModelInfo LoadParts(const char* pas);
	// �e�N�X�`���̓ǂݍ���
	void LoadXFileTexture(SModelInfo* pXFile);

	// �����o�ϐ�
private:
	std::vector<ModelMotion> m_aMotion;		// ���[�V�������
	std::vector<std::string> m_aPas;		// X�t�@�C���̃p�X
	std::map<std::string, int> m_texType;	// X�t�@�C���̎��
	int m_nNumMotion;						// X�t�@�C���̑���
};

#endif	//_X_FILE_MOTION_H_
