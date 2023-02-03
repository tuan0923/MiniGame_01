//===================================================================
//
//	���b�V���t�B�[���h�����̃w�b�_�[[mesh_field.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _MESH_FIELD_H_
#define _MESH_FIELD_H_

#include "object.h"

//-------------------------------------------
//	�}�N����`
//-------------------------------------------
#define MESHFIELD_X_BLOCK			(1)			//X�����̃u���b�N��
#define MESHFIELD_Y_BLOCK			(20)		//Y�����̃u���b�N��

//-------------------------------------------
// ���S�N���X
//-------------------------------------------
class CMeshField : public CObject
{
public:
	// �R���X�g���N�^
	CMeshField();
	// �f�X�g���N�^
	~CMeshField() override;

	// ����
	static CMeshField *Create();
	// �e�N�X�`���̓ǂݍ���
	static HRESULT Load();
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
	// �ړ��ʂ̐ݒ�
	void SetMove(const D3DXVECTOR3& move) { m_move = move; }
	// �I���t���O�̐ݒ�
	void SetUninit(bool bUninit) { m_bUninit = bUninit; }

private:
	// �e�N�X�`���̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���(��ʃV�F�C�N�p)
	D3DXCOLOR m_col;		//�F
	int m_nCounterAnim;
	int m_nPatternAnim;
	bool m_bCol;			//�F�ύX�t���O
	bool m_bUninit;	//�I�����邩�ǂ���
};

#endif		// _MESH_FIELD_H_
