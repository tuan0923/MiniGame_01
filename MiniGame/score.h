//=============================================================================
//
// �X�R�A���
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// �w�i�N���X��`
//*****************************************************************************
class CScore : public CObject
{
// �萔��`
	static const int SCORE_SIZE = 30;
	static const int MAX_SCORE = 8;

// �����o�֐�
public:
	CScore();										//�R���X�g���N�^
	~CScore() override;								//�f�X�g���N�^

	static CScore *Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const int& nNumSpace);		//����
	HRESULT Init() override;						//������
	void Uninit() override;							//�I��
	void Update() override;							//�X�V
	void Draw() override;							//�`��
	void Add(const int& nScore);					//�X�R�A�̉��Z
	void Set(const int& nScore);					//�X�R�A�̉��Z

	int GetScore() { return m_nScore; }				// �X�R�A�̎擾
	void SetColor(D3DXCOLOR col);					// �F�̐ݒ�
	D3DXCOLOR GetColor();							// �F�̎擾

private:
	void Set();										//�X�R�A�̐ݒ�

// �����o�ϐ� //
private:
	CNumber *m_apNumber[MAX_SCORE];					//�X�R�A�Ɏg�p���鐔��
	int m_nScore;									//�X�R�A���i�[
};

#endif // _SCORE_H_