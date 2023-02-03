//===================================================================
//
//	���C�g����[light.cpp]
//	Author:SHUGO KURODA
//
//===================================================================
#include "manager.h"
#include "renderer.h"

#include "light.h"

//======================================================
//	�ÓI�����o�ϐ�
//======================================================
int CLight::m_nNumLight = 0;		//���C�g�̐�

//======================================================
//	�R���X�g���N�^
//======================================================
CLight::CLight() :m_vecDir(0.0f, 0.0f, 0.0f), m_Diffuse(0.0f, 0.0f, 0.0f, 0.0f)
{
}

//======================================================
//	�f�X�g���N�^
//======================================================
CLight::~CLight()
{
}

//======================================================
//	��������
//======================================================
CLight *CLight::Create(const D3DXVECTOR3& vecDir, const D3DXCOLOR& diffuse)
{
	//�C���X�^���X����
	CLight *pLight = new CLight;

	// ���C�g�̕����x�N�g����ݒ�
	pLight->m_vecDir = vecDir;

	// ���C�g�̊g�U����ݒ�
	pLight->m_Diffuse = diffuse;

	// ������
	pLight->Init();

	return pLight;
}

//======================================================
//	����������
//======================================================
HRESULT CLight::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//���C�g���̏�����
	ZeroMemory(&m_aLight, sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	m_aLight.Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�
	m_aLight.Diffuse = m_Diffuse;

	//���K������(�傫���P�̃x�N�g���ɂ���)
	D3DXVec3Normalize(&m_vecDir, &m_vecDir);
	m_aLight.Direction = m_vecDir;

	//���C�g��ݒ� 
	pDevice->SetLight(m_nNumLight, &m_aLight);

	//���C�g��L���ɂ���
	pDevice->LightEnable(m_nNumLight, TRUE);

	//���C�g�̑��������Z
	m_nNumLight++;

	return S_OK;
}

//======================================================
//	�I������
//======================================================
void CLight::Uninit()
{
	// ���C�g�̑�����������
	m_nNumLight = 0;
}

//======================================================
//	�X�V����
//======================================================
void CLight::Update()
{
}

//======================================================
//	�`�揈��
//======================================================
void CLight::Draw()
{
}
