//=============================================================================
//
// �f�o�b�N�\������ [debugproc.cpp]
// Author : 
//
//=============================================================================
//#define _CRT_SECURE_NO_WARNINGS

#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "stdio.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
//LPD3DXFONT CDebugProc::m_pFont = NULL;
//char CDebugProc::m_aStr[1024] = {};

//=============================================================================
// CDebugProc�̃R���X�g���N�^
//=============================================================================
CDebugProc::CDebugProc() :m_pFont(), m_aStr{}
{
}

//=============================================================================
// CDebugProc�̃f�X�g���N�^
//=============================================================================
CDebugProc::~CDebugProc()
{
}

//=============================================================================
// ����������
//=============================================================================
void CDebugProc::Init()
{
	// �t�H���g�̐���
	D3DXCreateFont(CManager::GetManager()->GetRenderer()->GetDevice(), 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	// �o�b�t�@�̃N���A
	memset(&m_aStr[0], 0, 1024);
}

//=============================================================================
// �I������
//=============================================================================
void CDebugProc::Uninit()
{
	// �t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CDebugProc::Draw()
{
	RECT rect = { 0, 0, CRenderer::SCREEN_WIDTH, CRenderer::SCREEN_HEIGHT };

	// �t�H���g�̕\��
	m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// �o�b�t�@�̃N���A
	memset(&m_aStr[0], 0, 1024);
}

//=============================================================================
// �f�o�b�N�\���p�̕����ǉ�����
//=============================================================================
void CDebugProc::Print(const char *fmt, ...)
{
	// �ϐ��錾
	va_list arg;
	char aStr[256];
	char aWard[64];

	// ������
	memset(aStr, 0, 256);
	memset(aWard, 0, 64);

	// ������̎��ʂ��J�n
	va_start(arg, fmt);

	// �����񂪍Ō�ɂȂ�܂ő�����
	for (int nCnt = 0; *fmt != '\0'; fmt++)
	{
		if (*fmt != '%')
		{
			wsprintf(&aWard[0], "%c", *fmt);
		}
		else
		{
			fmt++;

			switch (*fmt)
			{
			case 'd':
				wsprintf(&aWard[0], "%d", va_arg(arg, int));
				break;

			case 'f':
				sprintf(&aWard[0], "%.2f", va_arg(arg, double));
				break;

			case 's':
				wsprintf(&aWard[0], "%s", va_arg(arg, const char*));
				break;

			case 'c':
				wsprintf(&aWard[0], "%c", va_arg(arg, char));
				break;
			}
		}

		nCnt += wsprintf(&aStr[nCnt], "%s", &aWard[0]);
	}

	// ���ʂ��I����
	va_end(arg);

	// �������A��������
	strcat(m_aStr, aStr);
}
