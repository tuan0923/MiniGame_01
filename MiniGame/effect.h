//====================================================================
//
// �G�t�F�N�g�̏��� (effect.h)
// Author : SHUGO KURODA
//
//====================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//================================================
// �C���N���[�h�t�@�C��
//================================================
#include "object2D.h"

//================================================
// �N���X�錾
//================================================
// �G�t�F�N�g�N���X
class CEffect : public CObject2D
{
private:
	int MAX_LIFE = 30;	//�@�G�t�F�N�g�̎���

public:
	// �G�t�F�N�g�̎��
	enum TYPE
	{
		TYPE_SPHERE = 0,		// ����
		TYPE_AFTERIMAGE,		// �c��
		TYPE_MAX				// �ő吔
	};

	// �e�N�X�`���̎��
	enum TEX
	{
		TEX_NONE = 0,
		TEX_SPHERE,				// ����
		TEX_BOSS,				// �{�X
		TEX_MAX
	};

	CEffect();
	~CEffect() override;

	static CEffect *Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const TYPE& type, const TEX& tex);
	static HRESULT Load();		//�e�N�X�`���̓ǂݍ���
	static void Unload();		//�e�N�X�`���̍폜

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEX_MAX];   //�e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_move;		// �ړ���
	int m_nLife;			// ����
	TYPE m_type;			// �G�t�F�N�g�̎��
};

#endif