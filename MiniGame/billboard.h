//========================================================
//
// �r���{�[�h���� [billboard.cpp]
// Author : SHUGO KURODA
//
//========================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "object.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CBillboard : public CObject
{
public:
	//�����o�֐�
	CBillboard();						//�R���X�g���N�^
	virtual ~CBillboard() override;		//�f�X�g���N�^

	// ����
	static CBillboard* Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const D3DXVECTOR3& rot, const char* name);

	// ������
	virtual HRESULT Init() override;
	// �I��
	virtual void Uninit() override;
	// �X�V
	virtual void Update() override;
	// �`��
	virtual void Draw() override;

	// �ʒu�ݒ�
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	// �p�x�ݒ�
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	// �T�C�Y�ݒ�
	void SetSize(D3DXVECTOR2 size);
	// �ʒu�擾
	D3DXVECTOR3 GetPosition() { return m_pos; }
	// �p�x�擾
	D3DXVECTOR3 GetRotation() { return m_rot; }
	// ���f���̐ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 texture) { m_pTexture = texture; }

private:
	//�e�N�X�`���ւ̃|�C���^�[
	LPDIRECT3DTEXTURE9 m_pTexture;
	//�r���{�[�h�̒��_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	//�ʒu
	D3DXVECTOR3 m_pos;
	//��]
	D3DXVECTOR3 m_rot;
	//�T�C�Y
	D3DXVECTOR2 m_size;
	//�Ίp���̒���
	float m_fLength;
	//�Ίp���̊p�x
	float m_fAngle;
	//���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxWorld;
};

#endif 
