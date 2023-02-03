//===================================================================
//
//	���f���̃}�l�[�W���[����[model_manager.h]
//	Author : �e���A��
//
//===================================================================
#ifndef _MODEL_MANAGER_H_
#define _MODEL_MANAGER_H_

#include "object.h"

//*******************************************************************
//	���f���̃}�l�[�W���[�N���X�̒�`
//*******************************************************************
class CModelManager :public CObject
{
public:
	//�����o�֐�
	CModelManager();
	~CModelManager();

	static CModelManager *Create();		//�C���X�^���X��������

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	int m_nCounter;			// �J�E���^�[
	int m_nCounterCreate;	// �I�u�W�F�N�g�����܂ł̐��l
	int m_nNumCreate;		// 1��ɐ�������I�u�W�F�N�g��
	int m_nCreateInterval;	// �I�u�W�F�N�g�𐶐�����Ԋu
	int m_nNumModel;
	int m_nNumCreateModel;
};

#endif	// _MODEL_MANAGER_H_
