//=============================================================================
//
// X�t�@�C�����[�V���� [set_model.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _SET_MODEL_
#define _SET_MODEL_

#include "motion_data.h"
#include <vector>
#include <string>
#include <map>

//using namespace std;

//=============================================================================
// �N���X��`
//=============================================================================
class CSetModel
{
	// �����o�֐�
public:
	CSetModel();				//�R���X�g���N�^
	~CSetModel();				//�f�X�g���N�^

	// ������
	HRESULT Init(HWND hWnd);
	// �I��
	void Uninit();
	// ���[�V�������̓ǂݍ���
	bool LoadModel(std::string name);
	// X�t�@�C�����̎擾(���O�w��)
	std::string GetPas(std::string texType) { return m_aPas[m_texType[texType]]; }
	// X�t�@�C�����̎擾(�ԍ��w��)
	std::string GetPas(int nCnt) { return m_aPas[nCnt]; }

	// �����o�ϐ�
private:
	std::vector<std::string> m_aPas;		// X�t�@�C���̃p�X
	std::map<std::string, int> m_texType;	// X�t�@�C���̎��
	int m_nNumMotion;						// X�t�@�C���̑���
};

#endif	//_SET_MODEL_
