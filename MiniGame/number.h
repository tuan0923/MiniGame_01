//=============================================================================
//
// �����|���S��[number.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "object2D.h"

//*****************************************************************************
// �w�i�N���X��`
//*****************************************************************************
class CNumber : public CObject2D
{
// �萔��` //
public:
	// U���W�̍ő啪����
	static const int DIVISION_U = 16;
	// V���W�̍ő啪����
	static const int DIVISION_V = 1;

// �����o�֐� //
public:
	CNumber(char *cName);					//�R���X�g���N�^
	~CNumber() override;					//�f�X�g���N�^

	static HRESULT Load();					//�e�N�X�`���ǂݍ���
	static void Unload();					//�e�N�X�`���j��
	HRESULT Init() override;				//������
	void Uninit() override;					//�I��
	void Update() override;					//�X�V
	void Draw() override;					//�`��
};

#endif // _NUMBER_H_
