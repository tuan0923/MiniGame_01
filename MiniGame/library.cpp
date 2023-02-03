//===================================================================
//
// �l�X�ȏ������܂Ƃ߂��t�@�C�� (library.cpp)
// Author : SHUGO KURODA
//
//===================================================================
#include "library.h"

//*******************************************************************
// �}�N����`
//*******************************************************************
// �X�N���[���T�C�Y
#define SCREEN_WIDTH		(CRenderer::SCREEN_WIDTH)
#define SCREEN_HEIGHT		(CRenderer::SCREEN_HEIGHT)

//-----------------------------------------------------------------------------------------------
// ��ʊO����
//-----------------------------------------------------------------------------------------------
bool LibrarySpace::OutScreen2D(const D3DXVECTOR3 *pPos, const D3DXVECTOR2 size)
{
	// ��ʂ̒[����o�Ă��邩�ǂ���
	if (pPos->x < -(size.x / 2) ||
		pPos->x > SCREEN_WIDTH + size.x / 2 ||
		pPos->y < -(size.y / 2) ||
		pPos->y > SCREEN_HEIGHT + size.y / 2)
	{
		//��ʊO�ɏo��
		return true;
	}

	//�܂���ʓ�
	return false;
}

//-----------------------------------------------------------------------------------------------
// ��ʓ��͈̔͐���
//-----------------------------------------------------------------------------------------------
bool LibrarySpace::SteyInScreen2D(D3DXVECTOR3 *pPos, D3DXVECTOR2 size)
{
	// ��ʒ[���ǂ���
    bool bScreenIn = false;    

    // ��ʂ̍�
    if (pPos->x < size.x / 2)
    {
        // �����o��
        pPos->x = size.x / 2;
        // �����o���t���O��true��
        bScreenIn = true;
    }
    // ��ʂ̉E
    if (pPos->x > SCREEN_WIDTH - size.x / 2)
    {
		// �����o��
        pPos->x = SCREEN_WIDTH - size.x / 2;
        // �����o���t���O��true��
        bScreenIn = true;
    }

    // ��ʂ̏�
	if (pPos->y < 100.0f + size.y / 2)
	{
		// �����o��
		pPos->y = 100.0f + size.y / 2;
		// �����o���t���O��true��
		bScreenIn = true;
	}

    // ��ʂ̉�
    if (pPos->y > SCREEN_HEIGHT - size.y / 2)
    {
		// �����o��
        pPos->y = SCREEN_HEIGHT - size.y / 2;
        // �����o���t���O��true��
        bScreenIn = true;
    }

    return bScreenIn;
}

//-----------------------------------------------------------------------------------------------
// ��`�̓����蔻��2D
//-----------------------------------------------------------------------------------------------
bool LibrarySpace::BoxCollision2D(const D3DXVECTOR3 *pPos1, const D3DXVECTOR3*pPos2, const D3DXVECTOR3*pSize1, const D3DXVECTOR3*pSize2)
{
	// �l�ʂ̓����蔻��
	if (pPos1->x - pSize1->x / 2 <= pPos2->x + pSize2->x / 2 &&
		pPos1->x + pSize1->x / 2 >= pPos2->x - pSize2->x / 2 &&
		pPos1->y - pSize1->y / 2 <= pPos2->y + pSize2->y / 2 &&
		pPos1->y + pSize1->y / 2 >= pPos2->y - pSize2->y / 2)
	{
		// ��������
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------------------
// ��`�̓����蔻��3D(pPosIn�̒��S�_���^��)
//-----------------------------------------------------------------------------------------------
bool LibrarySpace::BoxCollision3D(D3DXVECTOR3* pPosIn, const D3DXVECTOR3* pPosInOld, const D3DXVECTOR3* pPosOut, const D3DXVECTOR3* pSizeIn, const D3DXVECTOR3* pSizeOut)
{
	//�Փ˃t���O
	bool bIsPush = false;

	if (pPosInOld->x + pSizeIn->x <= pPosOut->x - pSizeOut->x		//�O��̈ʒu(X��)��X���̍ŏ��l�ȉ�
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//���݂̈ʒu(X��)��X���̍ŏ��l�ȏ�
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z���̍ő�l������
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z		//Z���̍ŏ��l������
		&& pPosIn->y - pSizeIn->y <= pPosOut->y + pSizeOut->y		//Y���̍ő�l������
		&& pPosIn->y + pSizeIn->y >= pPosOut->y - pSizeOut->y)		//Y���̍ŏ��l������
	{//�����̓����蔻��(-X)
		pPosIn->x = (pPosOut->x - pSizeOut->x) - pSizeIn->x;
		bIsPush = true;
	}
	else if (pPosInOld->x - pSizeIn->x >= pPosOut->x + pSizeOut->x	//�O��̈ʒu(X��)��X���̍ŏ��l�ȏ�
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//���݂̈ʒu(X��)��X���̍ŏ��l�ȉ�
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z���̍ő�l������
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z		//Z���̍ŏ��l������
		&& pPosIn->y - pSizeIn->y <= pPosOut->y + pSizeOut->y		//Y���̍ő�l������
		&& pPosIn->y + pSizeIn->y >= pPosOut->y - pSizeOut->y)		//Y���̍ŏ��l������
	{//�E���̓����蔻��(+X)
		pPosIn->x = (pPosOut->x + pSizeOut->x) + pSizeIn->x;
		bIsPush = true;
	}

	if (pPosInOld->z + pSizeIn->z <= pPosOut->z - pSizeOut->z		//�O��̈ʒu(Z��)��Z���̍ŏ��l�ȉ�
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z		//���݂̈ʒu(Z��)��Z���̍ŏ��l�ȏ�
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X���̍ő�l������
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X���̍ŏ��l������
		&& pPosIn->y - pSizeIn->y <= pPosOut->y + pSizeOut->y		//Y���̍ő�l������
		&& pPosIn->y + pSizeIn->y >= pPosOut->y - pSizeOut->y)		//Y���̍ŏ��l������
	{//��O���̓����蔻��(-Z)
		pPosIn->z = (pPosOut->z - pSizeOut->z) - pSizeIn->z;
		bIsPush = true;
	}
	else if (pPosInOld->z - pSizeIn->z >= pPosOut->z + pSizeOut->z	//�O��̈ʒu(Z��)��Z���̍ŏ��l�ȏ�
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//���݂̈ʒu(Z��)��Z���̍ŏ��l�ȉ�
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X���̍ő�l������
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X���̍ŏ��l������
		&& pPosIn->y - pSizeIn->y <= pPosOut->y + pSizeOut->y		//Y���̍ő�l������
		&& pPosIn->y + pSizeIn->y >= pPosOut->y - pSizeOut->y)		//Y���̍ŏ��l������
	{//�����̓����蔻��(+Z)
		pPosIn->z = (pPosOut->z + pSizeOut->z) + pSizeIn->z;
		bIsPush = true;
	}

	if (pPosInOld->y - pSizeIn->y >= pPosOut->y + pSizeOut->y		//�O��̈ʒu(Y��)��Y���̍ŏ��l�ȏ�
		&& pPosIn->y - pSizeIn->y <= pPosOut->y + pSizeOut->y		//���݂̈ʒu(Y��)��Y���̍ŏ��l�ȉ�
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X���̍ő�l������
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X���̍ŏ��l������
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z���̍ő�l������
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z)		//Z���̍ŏ��l������
	{//�㑤�̓����蔻��(+Y)
		pPosIn->y = (pPosOut->y + pSizeOut->y) + pSizeIn->y;
	}
	else if (pPosInOld->y + pSizeIn->y <= pPosOut->y - pSizeOut->y	//�O��̈ʒu(Y��)��Y���̍ŏ��l�ȉ�
		&& pPosIn->y + pSizeIn->y >= pPosOut->y - pSizeOut->y		//���݂̈ʒu(Y��)��Y���̍ŏ��l�ȏ�
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X���̍ő�l������
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X���̍ŏ��l������
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z���̍ő�l������
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z)		//Z���̍ŏ��l������
	{//�����̓����蔻��(-Y)
		pPosIn->y = (pPosOut->y - pSizeOut->y) - pSizeIn->y;
		bIsPush = true;
	}

	return bIsPush;
}

//-----------------------------------------------------------------------------------------------
// ��`�̓����蔻��3D(pPos�̒��S�_����)
//-----------------------------------------------------------------------------------------------
LibrarySpace::EStatePush LibrarySpace::BoxCollisionUnder3D(D3DXVECTOR3 * pPosIn, const D3DXVECTOR3 * pPosInOld, const D3DXVECTOR3 * pPosOut, const D3DXVECTOR3 * pSizeIn, const D3DXVECTOR3 * pSizeOut)
{
	//�Փˏ��
	EStatePush Push = PUSH_NONE;

	if (pPosInOld->x + pSizeIn->x <= pPosOut->x - pSizeOut->x		//�O��̈ʒu(X��)��X���̍ŏ��l�ȉ�
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//���݂̈ʒu(X��)��X���̍ŏ��l�ȏ�
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z���̍ő�l������
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z		//Z���̍ŏ��l������
		&& pPosIn->y <= pPosOut->y + pSizeOut->y		//Y���̍ő�l������
		&& pPosIn->y >= pPosOut->y - pSizeOut->y)		//Y���̍ŏ��l������
	{//�����̓����蔻��(-X)
		pPosIn->x = (pPosOut->x - pSizeOut->x) - pSizeIn->x;
		Push = PUSH_X;
	}
	else if (pPosInOld->x - pSizeIn->x >= pPosOut->x + pSizeOut->x	//�O��̈ʒu(X��)��X���̍ŏ��l�ȏ�
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//���݂̈ʒu(X��)��X���̍ŏ��l�ȉ�
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z���̍ő�l������
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z		//Z���̍ŏ��l������
		&& pPosIn->y <= pPosOut->y + pSizeOut->y		//Y���̍ő�l������
		&& pPosIn->y >= pPosOut->y - pSizeOut->y)		//Y���̍ŏ��l������
	{//�E���̓����蔻��(+X)
		pPosIn->x = (pPosOut->x + pSizeOut->x) + pSizeIn->x;
		Push = PUSH_X;
	}
	else if (pPosInOld->z + pSizeIn->z <= pPosOut->z - pSizeOut->z		//�O��̈ʒu(Z��)��Z���̍ŏ��l�ȉ�
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z		//���݂̈ʒu(Z��)��Z���̍ŏ��l�ȏ�
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X���̍ő�l������
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X���̍ŏ��l������
		&& pPosIn->y <= pPosOut->y + pSizeOut->y		//Y���̍ő�l������
		&& pPosIn->y >= pPosOut->y - pSizeOut->y)		//Y���̍ŏ��l������
	{//��O���̓����蔻��(-Z)
		pPosIn->z = (pPosOut->z - pSizeOut->z) - pSizeIn->z;
		Push = PUSH_Z;
	}
	else if (pPosInOld->z - pSizeIn->z >= pPosOut->z + pSizeOut->z	//�O��̈ʒu(Z��)��Z���̍ŏ��l�ȏ�
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//���݂̈ʒu(Z��)��Z���̍ŏ��l�ȉ�
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X���̍ő�l������
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X���̍ŏ��l������
		&& pPosIn->y <= pPosOut->y + pSizeOut->y		//Y���̍ő�l������
		&& pPosIn->y >= pPosOut->y - pSizeOut->y)		//Y���̍ŏ��l������
	{//�����̓����蔻��(+Z)
		pPosIn->z = (pPosOut->z + pSizeOut->z) + pSizeIn->z;
		Push = PUSH_Z;
	}
	else if (pPosInOld->y >= pPosOut->y + pSizeOut->y		//�O��̈ʒu(Y��)��Y���̍ŏ��l�ȏ�
		&& pPosIn->y <= pPosOut->y + pSizeOut->y		//���݂̈ʒu(Y��)��Y���̍ŏ��l�ȉ�
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X���̍ő�l������
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X���̍ŏ��l������
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z���̍ő�l������
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z)		//Z���̍ŏ��l������
	{//�㑤�̓����蔻��(+Y)
		pPosIn->y = (pPosOut->y + pSizeOut->y);
		Push = PUSH_JUMP;
	}
	else if (pPosInOld->y + pSizeIn->y <= pPosOut->y	//�O��̈ʒu(Y��)��Y���̍ŏ��l�ȉ�
		&& pPosIn->y + pSizeIn->y >= pPosOut->y			//���݂̈ʒu(Y��)��Y���̍ŏ��l�ȏ�
		&& pPosIn->x - pSizeIn->x <= pPosOut->x + pSizeOut->x		//X���̍ő�l������
		&& pPosIn->x + pSizeIn->x >= pPosOut->x - pSizeOut->x		//X���̍ŏ��l������
		&& pPosIn->z - pSizeIn->z <= pPosOut->z + pSizeOut->z		//Z���̍ő�l������
		&& pPosIn->z + pSizeIn->z >= pPosOut->z - pSizeOut->z)		//Z���̍ŏ��l������
	{//�����̓����蔻��(-Y)
		pPosIn->y = (pPosOut->y - pSizeOut->y) - pSizeIn->y;
		Push = PUSH_Y;
	}

	return Push;
}

//-----------------------------------------------------------------------------------------------
// ���̂̓����蔻��
//-----------------------------------------------------------------------------------------------
bool LibrarySpace::SphereCollision(const D3DXVECTOR3& posIn, const D3DXVECTOR3& posOut, const float& fsizeIn, const float& fsizeOut)
{
	//2�̍��W���������߂�
	D3DXVECTOR3 Length = posIn - posOut;

	//���W�������狗�������߂�
	float fLength = D3DXVec3Length(&Length);

	if (fsizeIn + fsizeOut > fLength)
	{//���݂��̃T�C�Y�̍��v��苗����������������
		return true;	//��������
	}

	return false;		//�������ĂȂ�
}

//-----------------------------------------------------------------------------------------------
// �~���̓����蔻��
//-----------------------------------------------------------------------------------------------
bool LibrarySpace::CylinderCollision3D(const D3DXVECTOR3 & posIn, const D3DXVECTOR3 & posOut, const float & fsizeIn, const float & fsizeOut)
{
	//2�̍��W���������߂�
	D3DXVECTOR2 Length = D3DXVECTOR2(posIn.x,posIn.z) - D3DXVECTOR2(posOut.x, posOut.z);

	//���W�������狗�������߂�
	float fLength = D3DXVec2Length(&Length);

	if (fsizeIn + fsizeOut > fLength)
	{//���݂��̃T�C�Y�̍��v��苗����������������
		return true;	//��������
	}

	return false;		//�������ĂȂ�
}

//-----------------------------------------------------------------------------------------------
// ���ʂ̓����蔻��
// const float & fsizeIn �� 
// const float & fsizeOut �� 
//-----------------------------------------------------------------------------------------------
bool LibrarySpace::PlaneCollision(const float & fsizeIn, const float & fsizeOut)
{
	if (fsizeIn >= fsizeOut)
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------------------
// �����̎擾
//-----------------------------------------------------------------------------------------------
int LibrarySpace::GetRandNum(int nMax, int nMin)
{
	//�ő�l�`�ŏ��l���痐�����擾
	int nRandNum = rand() % (nMax - nMin + 1) + nMin;

	return nRandNum;
}

//-----------------------------------------------------------------------------------------------
// ����(��������)�̎擾
//-----------------------------------------------------------------------------------------------
float LibrarySpace::GetRandFloat(int nMax, int nMin, int nNumDiv)
{
	int nMaxNum = nMax * nNumDiv;
	int nMinNum = nMin * nNumDiv;
	
	//�ő�l�`�ŏ��l���痐�����擾
	float fRandNum = (float)(rand() % (nMaxNum - nMinNum + 1) + nMinNum);
	fRandNum = fRandNum / nNumDiv;

	return fRandNum;
}

//-----------------------------------------------------------------------------------------------
// �T�C���l�̎擾
//-----------------------------------------------------------------------------------------------
float LibrarySpace::GetSinVec(float fRot, float fNumMul)
{
	return sinf(D3DX_PI * fRot) * fNumMul;
}

//-----------------------------------------------------------------------------------------------
// �R�T�C���l�̎擾
//-----------------------------------------------------------------------------------------------
float LibrarySpace::GetCosVec(float fRot, float fNumMul)
{
	return cosf(D3DX_PI * fRot) * fNumMul;
}

//-----------------------------------------------------------------------------------------------
// �T�C���l�̎擾(�J�����̌���)
//-----------------------------------------------------------------------------------------------
float LibrarySpace::GetSinVec(float fRot, float fRotCamera, float fNumMul)
{
	return sinf(fRotCamera - (D3DX_PI / fRot)) * fNumMul;
}

//-----------------------------------------------------------------------------------------------
// �R�T�C���l�̎擾(�J�����̌���)
//-----------------------------------------------------------------------------------------------
float LibrarySpace::GetCosVec(float fRot, float fRotCamera, float fNumMul)
{
	return cosf(fRotCamera - (D3DX_PI / fRot)) * fNumMul;
}

//-----------------------------------------------------------------------------------------------
// ���W�Ԃ̋����v�Z
//-----------------------------------------------------------------------------------------------
float LibrarySpace::SphereRange(D3DXVECTOR3 posStart, D3DXVECTOR3 posEnd)
{
	//2�̍��W���������߂�
	D3DXVECTOR3 Length = posStart - posEnd;

	//���W�������狗�������߂�
	float fLength = D3DXVec3Length(&Length);

	return fLength;
}
