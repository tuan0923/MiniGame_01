//-----------------------------------------------------------------------------------------------
//
// �N���o�X(�n�ʂ̋T��)����[model_crevasse.cpp]
// Author : SHUGO kURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"

#include "load.h"
#include "sound.h"

#include "game.h"
#include "library.h"
#include "effect.h"
#include "logo.h"
#include "score.h"
#include "fade_scene.h"

#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "logo.h"

// �ǉ�
#include "x_file.h"
#include "title.h"
#include "model_crevasse.h"

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CCrevasse::CCrevasse() :m_PosOld(0.0f, 0.0f, 0.0f)
{
	//�I�u�W�F�N�g�̎�ސݒ�
	SetType(EObject::OBJ_OBSTACLE);
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CCrevasse::~CCrevasse()
{
}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CCrevasse *CCrevasse::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* name)
{
	// �|�C���^�N���X��錾
	CCrevasse* pCrevasse = new CCrevasse;

	if (pCrevasse != nullptr)
	{
		// �ʒu�ݒ�
		pCrevasse->SetPosition(pos);
		// �p�x�ݒ�
		pCrevasse->SetRotation(rot);
		// X�t�@�C���̐ݒ�
		pCrevasse->BindXFile(CManager::GetManager()->GetXFile()->GetXFile(name));
		// ������
		pCrevasse->Init();
	}

	return pCrevasse;
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CCrevasse::Init()
{
	// ������
	CModel::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CCrevasse::Uninit()
{
	CModel::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CCrevasse::Update()
{
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CCrevasse::Draw()
{
	//�`�揈��
	CModel::Draw();
}

//-----------------------------------------------------------------------------------------------
// �S�Ă̏�Q���̓����蔻��
//-----------------------------------------------------------------------------------------------
void CCrevasse::CollisionAll(D3DXVECTOR3* pPosPlayer, D3DXVECTOR3* pPosPlayerOld, D3DXVECTOR3* pSizePlayer)
{
	for (int nCntObject = 0; nCntObject < CObject::MAX_OBJECT; nCntObject++)
	{
		// �I�u�W�F�N�g�̃|�C���^�擾
		CObject *pObject = CObject::GetObject(nCntObject);

		if (pObject != nullptr)
		{
			// �I�u�W�F�N�g�̎�ގ擾
			CObject::EObject objType = pObject->GetObjType();

			//�v���C���[�̒e�ƓG�̔���
			if (objType == OBJ_OBSTACLE)
			{
				//�I�u�W�F�N�g�|�C���^���L���X�g
				CCrevasse *pObstacle = (CCrevasse*)pObject;

				// �����蔻��
				pObstacle->Collision(pPosPlayer, pPosPlayerOld, pSizePlayer);
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
// �����蔻��
//-----------------------------------------------------------------------------------------------
bool CCrevasse::Collision(D3DXVECTOR3* pPosPlayer, D3DXVECTOR3* pPosPlayerOld, D3DXVECTOR3* pSizePlayer)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSizeMax();

	// ��`�̓����蔻��3D
	if (LibrarySpace::BoxCollision3D(pPosPlayer, pPosPlayerOld, &pos, pSizePlayer, &size))
	{//�_���[�W����
		return true;	//��������
	}

	return false;	//�������ĂȂ�
}
