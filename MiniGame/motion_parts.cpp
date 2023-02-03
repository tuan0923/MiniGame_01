////===================================================================
////
////	���f������[model.cpp]
////	Author:SHUGO KURODA
////
////===================================================================
//
////======================================================
////	�C���N���[�h
////======================================================
//#include "manager.h"
//#include "renderer.h"
//#include "model.h"
//
//#include "input.h"
//#include "camera.h"
////#include "shadow.h"
//#include "bullet.h"
//#include "load.h"
//#include "enemy.h"
//
//// �ǉ�
//#include "motion_parts.h"
//
////-----------------------------------------------------------------------------
//// �R���X�g���N�^
////-----------------------------------------------------------------------------
//CParts::CParts() :m_pos(0.0f, 0.0f, 0.0f), m_baseRot(0.0f, 0.0f, 0.0f), m_rot(0.0f, 0.0f, 0.0f),
//				m_nIndex(0), m_nParent(0)
//{
//}
//
////-----------------------------------------------------------------------------
//// �f�X�g���N�^
////-----------------------------------------------------------------------------
//CParts::~CParts()
//{
//}
//
////-----------------------------------------------------------------------------
//// ����
//// const char* pas �� ��������p�[�c(���)
////-----------------------------------------------------------------------------
//CParts* CParts::Create(const char* pas)
//{
//	//�C���X�^���X����
//	CParts *pModel = new CParts;
//
//	//�f�o�C�X���擾����
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();
//
//	//X�t�@�C���̓ǂݍ���
//	HRESULT hr = D3DXLoadMeshFromX(pas,
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&pModel->m_aXFile.pBuffMat,
//		NULL,
//		&pModel->m_aXFile.nNumMat,
//		&pModel->m_aXFile.pMesh);
//
//	if (hr != S_OK)
//	{//X�t�@�C���ǂݍ��ݎ��s
//		return nullptr;
//	}
//
//	// �e�N�X�`���̓ǂݍ��ݏ���
//	pModel->LoadXFileTexture();
//
//	// ������
//	pModel->Init();
//
//	return pModel;
//}
//
////-----------------------------------------------------------------------------
//// ������
////-----------------------------------------------------------------------------
//HRESULT CParts::Init()
//{
//	//int nNumVix;		//���_��
//	//DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
//	//BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
//
//	////���_���̎擾
//	//nNumVix = m_aXFile.pMesh->GetNumVertices();
//
//	////���_�t�H�[�}�b�g�擾
//	//sizeFVF = D3DXGetFVFVertexSize(m_aXFile.pMesh->GetFVF());
//
//	////���_���b�N
//	//m_aXFile.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
//
//	////���ׂĂ̒��_POS�̎擾
//	//for (int nCntVtx = 0; nCntVtx < nNumVix; nCntVtx++)
//	//{
//	//	//���_���W�̑��
//	//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
//
//	//	if (m_vtxMax.x < vtx.x)
//	//	{//X
//	//		m_vtxMax.x = vtx.x;
//	//	}
//	//	else if (m_vtxMin.x > vtx.x)
//	//	{
//	//		m_vtxMin.x = vtx.x;
//	//	}
//
//	//	if (m_vtxMax.y < vtx.y)
//	//	{//Y
//	//		m_vtxMax.y = vtx.y;
//	//	}
//	//	else if (m_vtxMin.y > vtx.y)
//	//	{
//	//		m_vtxMin.y = vtx.y;
//	//	}
//
//	//	if (m_vtxMax.z < vtx.z)
//	//	{//Z
//	//		m_vtxMax.z = vtx.z;
//	//	}
//	//	else if (m_vtxMin.z > vtx.z)
//	//	{
//	//		m_vtxMin.z = vtx.z;
//	//	}
//
//	//	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
//	//	pVtxBuff += sizeFVF;
//	//}
//
//	////���C����z�u
//	////SetLine(g_Model[nCnt].pos, g_Model[nCnt].vtxMax, g_Model[nCnt].vtxMin, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
//
//	////���_�A�����b�N
//	//m_aXFile.pMesh->UnlockVertexBuffer();
//
//	return S_OK;
//}
//
////-----------------------------------------------------------------------------
//// �I��
////-----------------------------------------------------------------------------
//void CParts::Uninit()
//{
//	Release();
//}
//
////-----------------------------------------------------------------------------
//// �X�V
////-----------------------------------------------------------------------------
//void CParts::Update()
//{
//	//for (int nCntVtx = 0; nCntVtx < MAX_MODEL_TYPE; nCntVtx++)
//	//{
//	//	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
//	//	{
//	//		//�O��̈ʒu��ۑ�
//	//		g_aModel[nCnt].posOld = g_aModel[nCnt].pos;
//
//	//		//�����蔻��
//	//		//CollisionPlayer(&g_aModel[nCnt].pos, &g_aModel[nCnt].posOld, &g_aModel[nCnt].Airmove, g_aModel[nCnt].fWidth, g_aModel[nCnt].fHeight);
//	//	}
//	//}
//}
//
////-----------------------------------------------------------------------------
//// �`��
////-----------------------------------------------------------------------------
//void CParts::Draw()
//{
//	////�f�o�C�X�̎擾
//	//LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();
//
//	//D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
//	//D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
//	//D3DXMATERIAL *pMat;			// �}�e���A���f�[�^�ւ̃|�C���^
//
//	////���[���h�}�g���b�N�X�̏�����
//	//D3DXMatrixIdentity(&m_mtxWorld);
//
//	////�����𔽉f
//	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
//
//	//// ���[���h�}�g���b�N�X�̌v�Z
//	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
//
//	////�ʒu�𔽉f
//	//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
//
//	//// ���[���h�}�g���b�N�X�̌v�Z
//	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
//
//	////���[���h�}�g���b�N�X�̐ݒ�
//	//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
//
//	////���݂̃}�e���A����ێ�
//	//pDevice->GetMaterial(&matDef);
//
//	////�}�e���A���f�[�^�ւ̃|�C���^���擾
//	//pMat = (D3DXMATERIAL*)m_aXFile.pBuffMat->GetBufferPointer();
//
//	//for (int nCntMat = 0; nCntMat < (int)m_aXFile.nNumMat; nCntMat++)
//	//{
//	//	//�}�e���A���̐ݒ�
//	//	pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//	//	//�e�N�X�`���̐ݒ�
//	//	pDevice->SetTexture(0, m_aXFile.pTexture[nCntMat]);
//
//	//	//���f���p�[�c�̕`��
//	//	m_aXFile.pMesh->DrawSubset(nCntMat);
//
//	//	//�e�N�X�`���̐ݒ�����ɖ߂�
//	//	pDevice->SetTexture(0, NULL);
//	//}
//
//	////�ێ����Ă����}�e���A����߂�
//	//pDevice->SetMaterial(&matDef);
//}
//
////-----------------------------------------------------------------------------
//// �e�N�X�`���̓ǂݍ���
////-----------------------------------------------------------------------------
//void CParts::LoadXFileTexture()
//{
//	//�}�e���A���f�[�^�ւ̃|�C���^
//	D3DXMATERIAL *pMat;
//
//	//�}�e���A���f�[�^�ւ̃|�C���^���擾
//	pMat = (D3DXMATERIAL*)m_aXFile.pBuffMat->GetBufferPointer();
//
//	for (int nCntMat = 0; nCntMat < (int)m_aXFile.nNumMat; nCntMat++)
//	{
//		//�}�e���A���̐ݒ�
//		//pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//		//�e�N�X�`�����������ꍇ
//		if ((pMat[nCntMat].pTextureFilename != NULL) && (strcmp(pMat[nCntMat].pTextureFilename, "") != 0))
//		{
//			//�f�o�C�X���擾����
//			LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();
//			//�e�N�X�`���̓ǂݍ���
//			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_aXFile.pTexture[nCntMat]);
//		}
//	}
//}
