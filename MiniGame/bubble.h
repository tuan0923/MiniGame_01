//====================================================================
//
// �A�G�t�F�N�g���� (bubble.h)
// Author : SHUGO KURODA
//
//====================================================================
#ifndef _BUBBLE_H_
#define _BUBBLE_H_

#include "object2D.h"

//================================================
// �N���X�錾
//================================================
// �A�N���X
class CBubble : public CObject2D
{
public:	//�萔
	// �A�T�C�Y�̍ŏ��l
	static const int MIN_SIZE = 10;

public:
	CBubble();
	~CBubble() override;

	//�����o�֐�
	static CBubble *Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);
	static HRESULT Load();
	static void Unload();
	
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;   // �ǂݍ��񂾃e�N�X�`����ۑ�����
	static int m_nReverseCount;				// �A�̗h��𔽓]������p
	int m_nReverse;
	D3DXVECTOR3 m_move;     // �ړ���
};

#endif	//_BUBBLE_H_
