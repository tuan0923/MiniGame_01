//========================================================
//
// �r���{�[�h���� [billboard_player.cpp]
// Author : SHUGO KURODA
//
//========================================================
#ifndef _BILLBOARD_PLAYER_H_
#define _BILLBOARD_PLAYER_H_

#include "billboard.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CBillboardPlayer : public CBillboard
{
public:
	//�����o�֐�
	CBillboardPlayer();						//�R���X�g���N�^
	virtual ~CBillboardPlayer() override;	//�f�X�g���N�^

	// ����
	static CBillboardPlayer* Create(D3DXVECTOR3* ParentPos, const char* name);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �Ǐ]�Ώۂ̈ʒu
	D3DXVECTOR3 *m_pPosParent;
};

#endif 
