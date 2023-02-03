//=============================================================================
//
//	���b�V��(��)���� [mesh_sphere.h]
//	Author : SHUGO KURODA
//
//=============================================================================
#ifndef _MESH_SPHERE_H_			//���̃}�N����`������Ȃ�������
#define _MESH_SPHERE_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "object.h"

//-------------------------------------------
// ���S�N���X
//-------------------------------------------
class CMeshSphere : public CObject
{
public:
	// �R���X�g���N�^
	CMeshSphere();
	// �f�X�g���N�^
	~CMeshSphere() override;

	// ����
	static CMeshSphere *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXCOLOR& col, const D3DXVECTOR2& rad, const int& nMeshX, const int& nMeshZ, const char* name);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	void SetPosTracking(D3DXVECTOR3* pPos) { m_pPosTrak = pPos; }
	void SetMove(bool bMove) { m_bMove = bMove; }

private:
	// �e�N�X�`���̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXCOLOR m_col;		// �J���[
	D3DXVECTOR2 m_rad;		// �e���c��
	int m_nMeshX;
	int m_nMeshZ;			// �c���̃��b�V�����̐�
	int m_nPolygon;			// �|���S����
	int m_nTop;				// ���_
	int m_nIdx;				// �C���f�b�N�X��
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X

	bool m_bMove;

	D3DXVECTOR3 *m_pPosTrak;
};

#endif		// _MESH_SPHERE_H_
