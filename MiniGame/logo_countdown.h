//-------------------------------------------
//
// �J�E���g�_�E�����S�̏��[logo_countdown.h]
// Author : SHUGO KURODA
//
//-------------------------------------------
#ifndef _LOGO_COUNTDOWN_H_
#define _LOGO_COUNTDOWN_H_

//-------------------------------------------
// �C���N���[�h
//-------------------------------------------
#include "logo.h"

//-------------------------------------------
// �O���錾
//-------------------------------------------
class CNumber;

//-------------------------------------------
// �J�E���g�_�E�����S�N���X
//-------------------------------------------
class CLogoCountDown : public CLogo
{
public:
	// �R���X�g���N�^
	CLogoCountDown();
	// �f�X�g���N�^
	~CLogoCountDown() override;

	// ����
	static CLogoCountDown* Create(const int& nNum);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	void Set();							// �X�R�A�̐ݒ�

private:
	CNumber *m_apNumber;				// �����̃|�C���^
	int m_nNum;							// �����̊i�[���
};

#endif		// _LOGO_COUNTDOWN_H_
