////===================================================================
////
////	���f���p�[�c[motion_parts.h]
////	Author:SHUGO KURODA
////
////===================================================================
//#ifndef _PARTS_H_			//���̃}�N����`������Ȃ�������
//#define _PARTS_H_			//2�d�C���N���[�h�h�~�̃}�N����`
//
//#include "object.h"
//#include "x_file_data.h"
//
////=============================================================================
//// �N���X��`
////=============================================================================
//class CParts : public CObject
//{
//public:
//	//�����o�֐�
//	CParts();					//�R���X�g���N�^
//	~CParts();					//�f�X�g���N�^
//
//	// ����
//	static CParts* Create(const char* pas);
//
//	// ������
//	HRESULT Init() override;
//	// �I��
//	void Uninit() override;
//	// �X�V
//	void Update() override;
//	// �`��
//	void Draw() override;
//
//	// �ʒu�ݒ�
//	void SetPosition(const D3DXVECTOR3& pos) { m_pos = pos; }
//	// �p�x�ݒ�
//	void SetRotation(const D3DXVECTOR3& rot) { m_rot = rot; }
//	// ���f���̐ݒ�
//	void BindXFile(const SModelInfo& XFile) { m_aXFile = XFile; }
//	// �ʒu�擾
//	D3DXVECTOR3 GetPosition() { return m_pos; }
//	// �p�x�擾
//	D3DXVECTOR3 GetRotation() { return m_rot; }
//	// ��{�̊p�x�擾
//	D3DXVECTOR3 GetRotationBase() { return m_baseRot; }
//
//private:
//	// �e�N�X�`���̓ǂݍ���
//	void LoadXFileTexture();
//
//	// �����o�ϐ�
//private:
//	// X�t�@�C�����
//	SModelInfo m_aXFile;
//	// �ʒu
//	D3DXVECTOR3 m_pos;
//	// ��{�̊p�x
//	D3DXVECTOR3 m_baseRot;
//	// ��]
//	D3DXVECTOR3 m_rot;
//	// ���[���h�}�g���b�N�X
//	D3DXMATRIX m_mtxWorld;
//	// ���̃p�[�c�̔ԍ�
//	int m_nIndex;
//	// �e�p�[�c�̔ԍ�
//	int m_nParent;
//};
//
//#endif
