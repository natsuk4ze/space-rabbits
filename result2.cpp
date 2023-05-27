//=============================================================================
//
// ���U���g��ʏ��� [result2.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "result2.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResult2(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResult2 = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureResult2Logo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkResult2[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_vertexWkResult2Logo[NUM_VERTEX];		// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RESULT2,				// �t�@�C���̖��O
		&g_pD3DTextureResult2);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RESULT2_LOGO,		// �t�@�C���̖��O
		&g_pD3DTextureResult2Logo);	// �ǂݍ��ރ������[

									// ���_���̍쐬
	MakeVertexResult2();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult2(void)
{
	if (g_pD3DTextureResult2 != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResult2->Release();
		g_pD3DTextureResult2 = NULL;
	}

	if (g_pD3DTextureResult2Logo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureResult2Logo->Release();
		g_pD3DTextureResult2Logo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult2(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetStage(STAGE_TITLE);
	}
	else if (IsButtonTriggered(0, BUTTON_B))
	{
		SetStage(STAGE_TITLE);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�

	pDevice->SetTexture(0, g_pD3DTextureResult2);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResult2, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureResult2Logo);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResult2Logo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexResult2(void)
{
	// ���_���W�̐ݒ�
	g_vertexWkResult2[0].vtx = D3DXVECTOR3(RESULT2_POS_X, RESULT2_POS_Y, 0.0f);
	g_vertexWkResult2[1].vtx = D3DXVECTOR3(RESULT2_POS_X + RESULT2_SIZE_X, RESULT2_POS_Y, 0.0f);
	g_vertexWkResult2[2].vtx = D3DXVECTOR3(RESULT2_POS_X, RESULT2_POS_Y + RESULT2_SIZE_Y, 0.0f);
	g_vertexWkResult2[3].vtx = D3DXVECTOR3(RESULT2_POS_X + RESULT2_SIZE_X, RESULT2_POS_Y + RESULT2_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkResult2[0].rhw =
		g_vertexWkResult2[1].rhw =
		g_vertexWkResult2[2].rhw =
		g_vertexWkResult2[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkResult2[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult2[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult2[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult2[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkResult2[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkResult2[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkResult2[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkResult2[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkResult2Logo[0].vtx = D3DXVECTOR3(RESULT2LOGO_POS_X, RESULT2LOGO_POS_Y, 0.0f);
	g_vertexWkResult2Logo[1].vtx = D3DXVECTOR3(RESULT2LOGO_POS_X + RESULT2LOGO_SIZE_X, RESULT2LOGO_POS_Y, 0.0f);
	g_vertexWkResult2Logo[2].vtx = D3DXVECTOR3(RESULT2LOGO_POS_X, RESULT2LOGO_POS_Y + RESULT2LOGO_SIZE_Y, 0.0f);
	g_vertexWkResult2Logo[3].vtx = D3DXVECTOR3(RESULT2LOGO_POS_X + RESULT2LOGO_SIZE_X, RESULT2LOGO_POS_Y + RESULT2LOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkResult2Logo[0].rhw =
		g_vertexWkResult2Logo[1].rhw =
		g_vertexWkResult2Logo[2].rhw =
		g_vertexWkResult2Logo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkResult2Logo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult2Logo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult2Logo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkResult2Logo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkResult2Logo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkResult2Logo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkResult2Logo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkResult2Logo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
