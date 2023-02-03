//-------------------------------------------
//
// ���S�̐���[logo.h]
// Author : Koshimoto�@Manato
//
//-------------------------------------------
#ifndef _LOGO_H_
#define _LOGO_H_

//-------------------------------------------
// �C���N���[�h
//-------------------------------------------
#include "object2D.h"

//-------------------------------------------
// ���S�N���X
//-------------------------------------------
class CLogo : public CObject2D
{
public:
	enum LOGOTYPE
	{//���S�̎��


	};

	// �R���X�g���N�^
	CLogo();
	// �f�X�g���N�^
	~CLogo() override;

	// ����
	static CLogo* Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const D3DXCOLOR& col, const char *aLogoname);
	// �e�N�X�`���̓ǂݍ���
	static HRESULT Load(const char *aLogoname);
	// �e�N�X�`���̍폜
	static void Unload();

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �e�N�X�`���̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LOGOTYPE  m_Logotype;
	// �j������܂ł̃J�E���^�[
	int m_nCountUninit;
	// ���̃T�C�Y�L���p
	D3DXVECTOR2 m_DefaultSize;
};

#endif		// _LOGO_H_
