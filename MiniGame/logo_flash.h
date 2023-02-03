//-------------------------------------------
//
// ���S�̏��[logo_flash.h]
// Author : SHUGO KURODA
//
//-------------------------------------------
#ifndef _LOGO_FLASH_H_
#define _LOGO_FLASH_H_

//-------------------------------------------
// �C���N���[�h
//-------------------------------------------
#include "logo.h"

//-------------------------------------------
// ���S�N���X
//-------------------------------------------
class CLogoFlash : public CLogo
{
private:
	// �������̎��
	enum EAnim
	{
		ANIM_NONE = 0,
		ANIM_ADD,
		ANIM_SUB,
	};

public:
	// �R���X�g���N�^
	CLogoFlash();
	// �f�X�g���N�^
	~CLogoFlash() override;

	// ����
	static CLogoFlash* Create(const D3DXVECTOR2& size, const char* name, const int& nCount);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �j�����̉�ʑJ�ڔ���̐ݒ�
	void SetSceneChange(bool bScene) { m_bSceneChange = bScene; }

	// �������̐ݒ�
	void Pattern();

	// �����o�ϐ�
private:
	// �������̎��
	EAnim m_anim;
	// �j�����ɉ�ʑJ�ڂ��邩�ǂ���
	bool m_bSceneChange;
};

#endif		// _LOGO_FLASH_H_
