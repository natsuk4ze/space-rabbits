//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "bg.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBG(void);
void SetTextureBG(float no);
void SetVertexBG(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBG = NULL;		// �e�N�X�`���ւ̃|�C���^
VERTEX_2D				g_vertexWkBG[NUM_VERTEX];	// ���_���i�[���[�N

D3DXVECTOR3				g_posBG;					// �w�i�̈ʒu
BG					BGWk[BG_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBG(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG *BG = &BGWk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_GAME_BG00,		// �t�@�C���̖��O
			&g_pD3DTextureBG);		// �ǂݍ��ރ������[
	}

	g_posBG = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �G�l�~�[�̏���������
	for (int i = 0; i < BG_MAX; i++, BG++)
	{
		BG->use = true;										// �g�p
		BG->pos = D3DXVECTOR3(50 + i * 150.0f, 100.0f, 0.0f);	// ���W�f�[�^��������
		BG->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		BG->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		BG->CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(BG00_SIZE_X, BG00_SIZE_Y);
		BG->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		BG->BaseAngle = atan2f(BG00_SIZE_Y, BG00_SIZE_X);	// �G�l�~�[�̊p�x��������

		BG->Texture = g_pD3DTextureBG;					// �e�N�X�`�����
		//MakeVertexEnemy(i);										// ���_���̍쐬
	}

	// ���_���̍쐬
	MakeVertexBG();

	g_posBG.x = -GetPlayer(0)->pos.x / 4.0f;

	SetVertexBG();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBG(void)
{
	if(g_pD3DTextureBG != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureBG->Release();
		g_pD3DTextureBG = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBG(void)
{
	//BG *BG = &BGWk[0];

	//for (int i = 0; i < BG_MAX; i++, BG++)
	//{


	//	// ���t���[�����s���鏈��

	//	// �A�j���[�V����
	//	BG->CountAnim++;
	//	if ((BG->CountAnim % TIME_ANIMATION) == 0)
	//	{
	//		// �p�^�[���̐؂�ւ�
	//		BG->PatternAnim = (BG->PatternAnim + 1) % ANIM_PATTERN_NUM;

	//		// �e�N�X�`�����W��ݒ�
	//		SetTextureBG(i, BG->PatternAnim);
	//	}
	//}

	//// �X�N���[������
	//g_posBG.x = -GetPlayer(0)->pos.x / 4.0f;
	//g_posBG.y = -GetPlayer(0)->pos.y / 4.0f;


	//SetVertexBG();
	g_posBG.y += 0.010f;
	SetTextureBG(g_posBG.y);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureBG);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBG, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBG(void)
{
	// ���_���W�̐ݒ�
	g_vertexWkBG[0].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y, 0.0f);
	g_vertexWkBG[1].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f);
	g_vertexWkBG[2].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f);
	g_vertexWkBG[3].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	g_vertexWkBG[0].rhw =
	g_vertexWkBG[1].rhw =
	g_vertexWkBG[2].rhw =
	g_vertexWkBG[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
////=============================================================================
//// �e�N�X�`�����W�̐ݒ�
////=============================================================================
//void SetTextureBG(int no, int cntPattern)
//{
//	BG *BG = &BGWk[no];
//
//	// �e�N�X�`�����W�̐ݒ�
//	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
//	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
//	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
//	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;
//
//	BG->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
//	BG->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
//	BG->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
//	BG->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
//}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBG(float yyy)
{
	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkBG[0].tex = D3DXVECTOR2(0.0f, 0.0f - yyy);
	g_vertexWkBG[1].tex = D3DXVECTOR2(1.0f, 0.0f - yyy);
	g_vertexWkBG[2].tex = D3DXVECTOR2(0.0f, 1.0f - yyy);
	g_vertexWkBG[3].tex = D3DXVECTOR2(1.0f, 1.0f - yyy);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBG(void)
{
	// ���_���W�̐ݒ�
	g_vertexWkBG[0].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y, 0.0f) + g_posBG;
	g_vertexWkBG[1].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y, 0.0f) + g_posBG;
	g_vertexWkBG[2].vtx = D3DXVECTOR3(BG00_POS_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + g_posBG;
	g_vertexWkBG[3].vtx = D3DXVECTOR3(BG00_POS_X + BG00_SIZE_X, BG00_POS_Y + BG00_SIZE_Y, 0.0f) + g_posBG;
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
BG *GetBG(int no)
{
	return(&BGWk[no]);
}

