//=============================================================================
//
// �t�F�[�h��� [fade.h]
// Author:SHUGO KURODA
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "manager.h"
#include "renderer.h"
#include "object2D.h"

//*****************************************************************************
// �t�F�[�h�N���X(��{�N���X)
//*****************************************************************************
class CFade
{
public:
	// �t�F�[�h�R�}���h
	typedef enum
	{
		FADE_NONE = 0,	// �������Ă��Ȃ�
		FADE_IN,		// �t�F�[�h�C��
		FADE_OUT,		// �t�F�[�h�A�E�g
		FADE_MAX,
	}FADE;

	CFade();
	~CFade();

	// �t�F�[�h����
	static CFade* Create(CManager::MODE modeNext);
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static void SetFade(FADE fade, CManager::MODE modeNext);
	static FADE GetFade() { return m_fade; }

private:
	//���_�o�b�t�@�ւ̃|�C���^�[
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	// �t�F�[�h�̏��
	static FADE m_fade;
	// ���̉��(���[�h)
	static CManager::MODE m_modeNext;
	// �t�F�[�h�F
	D3DXCOLOR m_colorFade;
};

#endif
