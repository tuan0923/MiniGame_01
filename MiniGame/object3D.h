//===================================================================
//
//		�|���S�������̃w�b�_�[[polygon.h]
//		Author:SHUGO KURODA
//
//===================================================================
#ifndef _POLYGON_H_			//���̃}�N����`������Ȃ�������
#define _POLYGON_H_			//2�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"

//======================================================
//	�}�N����`
//======================================================
#define POLYGON_SIZE	(2000.0f)	//�|���S���̃T�C�Y

//======================================================
//	�N���X�錾
//======================================================
class CObject3D : public CObject
{
public:
	// ���_�t�H�[�}�b�g
	static const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);	//���W�E�@���E�J���[�E�e�N�X�`��;
	// ���_�̐�
	static const int MAX_VERTEX = 4;

	// ���_�f�[�^
	struct VERTEX_3D
	{
		D3DXVECTOR3 pos;		//���_���W
		D3DXVECTOR3 nor;		//�@���x�N�g��
		D3DCOLOR col;			//���_�J���[
		D3DXVECTOR2 tex;		//�e�N�X�`�����W
	};

	CObject3D();
	~CObject3D() override;

	static CObject3D *Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);

	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	D3DXVECTOR3 GetPosition() { return m_pos; }
	D3DXVECTOR3 GetRotation() { return m_rot; }
	D3DXVECTOR2 GetSize() { return m_size; }

	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetSize(const D3DXVECTOR2& size) { m_size = size; }
	void SetStop(const bool& bStop) { m_bStop = bStop; }

	// �e�N�X�`���̐ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 Texture) { m_pTexture = Texture; }

private:
	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = nullptr;
	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;
	// �ʒu
	D3DXVECTOR3 m_pos;
	// ����
	D3DXVECTOR3 m_rot;
	// �T�C�Y
	D3DXVECTOR2 m_size;
	// ���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxWorld;

	// �j���J�E���^�[
	int m_nDel;
	bool m_bStop;
};

#endif