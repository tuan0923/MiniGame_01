//=============================================================================
//
// �X�R�A���
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// �w�i�N���X��`
//*****************************************************************************
class CLife : public CObject
{
	// �萔��`
	static const int LIFE_SIZE = 30;
	static const int MAX_LIFE = 1;

	// �����o�֐�
public:
	CLife();										//�R���X�g���N�^
	~CLife() override;								//�f�X�g���N�^

	static CLife *Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);		//����
	HRESULT Init() override;						//������
	void Uninit() override;							//�I��
	void Update() override;							//�X�V
	void Draw() override;							//�`��
	void Add(const int& nScore);					//���C�t�̉��Z

	// ���C�t�̎擾
	int GetLife() { return m_nLife; }

private:
	void Set();										//���C�t�̐ݒ�

	// �����o�ϐ� //
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//���_�o�b�t�@�̃|�C���^
	CNumber *m_apNumber[MAX_LIFE];					//���C�t�Ɏg�p���鐔��
	int m_nLife;									//���C�t���i�[
};

#endif // _LIFE_H_
