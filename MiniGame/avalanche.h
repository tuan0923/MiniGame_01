//===================================================================
//
//	����������̏���[avalanche.h]
//	Author:Koshimoto Manato
//
//===================================================================
#ifndef _AVALANCHE_H_
#define _AVALANCHE_H_

#include "object.h"

//*******************************************************************
//	�O���錾
//*******************************************************************
class CEffect;

//*******************************************************************
//	����N���X�̒�`
//*******************************************************************
class CAvalanche : public CObject
{
private:
	static const int MAX_AVALANCHE = 256;	//����Ɏg�p����G�t�F�N�g�̍ő吔
public:
	CAvalanche();					//�R���X�g���N�^
	~CAvalanche() override;			//�f�X�g���N�^

	//�����o�֐�
	static CAvalanche *Create();	//��������
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��

private:
	static CEffect *m_pEffect[MAX_AVALANCHE];	//����̃G�t�F�N�g���
	int m_nDuration;				//����̌p������
	int m_nEffectIdx;				//����̃G�t�F�N�g�̃C���f�b�N�X
	bool m_bEnd;					//������I��������ǂ���
};

#endif		// _AVALANCHE_H_
