//=============================================================================
//
// �I�u�W�F�N�g����[object.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _OBJECT_2D_
#define _OBJECT_2D_

#include "object.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject2D : public CObject
{
public:
	// ���_�t�H�[�}�b�g
	static const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	// ���_�̐�
	static const int MAX_VERTEX = 4;

	// ���_�f�[�^
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;
		float rhw;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	};

public:
	CObject2D();
	CObject2D(EObject type);
	virtual ~CObject2D() override;

	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR2 size);
	void SetRot(float fRot) { m_fRot = fRot; }
	void SetMove(const D3DXVECTOR3& move){ m_move = move; }

	void SetVertex();
	void SetColor(D3DXCOLOR col);
	void SetAnimation(int nAnimU, int nAnimV, int nPartU, int nPartV);
	void SetAnimation(int nAnimU, int nAnimV, float fPartU, float fPartV);
	void SetAnimBg(int nSpeed, int nPattern, bool bRightToLeft);
	void SetAnimBgLeftUp(int nSpeed, int nPattern, bool bRightToLeft);

	void SetTextureRange(int nRange, int nPattern);
	// �e�N�X�`���̐ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 Texture) { m_pTexture = Texture; }

	// �ʒu�̎擾
	const D3DXVECTOR3& GetPosition() const { return m_pos; }
	// �����̎擾
	const float& GetRot() const { return m_fRot; }
	// �T�C�Y�̎擾
	const D3DXVECTOR2& GetSize() const { return m_size; }
	// �Ίp���̒����擾
	const float& GetLength() const { return m_fLength; }
	// �F�̎擾
	const D3DXCOLOR& GetColor() const { return m_col; }

private:	//�����o�ϐ�
	//���_�o�b�t�@�ւ̃|�C���^�[
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	//�e�N�X�`���ւ̃|�C���^�[
	LPDIRECT3DTEXTURE9 m_pTexture;
	//�ʒu
	D3DXVECTOR3 m_pos;
	//�T�C�Y
	D3DXVECTOR2 m_size;
	//����
	float m_fRot;
	//�Ίp���̒���
	float m_fLength;
	//�Ίp���̊p�x
	float m_fAngle;
	//���_�J���[
	D3DXCOLOR m_col;
	//�A�j���[�V�����J�E���^�[
	int m_nCounterAnim;
	//�A�j���[�V�����p�^�[��
	int m_nPatternAnim;

	// �ړ���(��ʃV�F�C�N�p)
	D3DXVECTOR3 m_move;
};

#endif // _OBJECT_2D_
