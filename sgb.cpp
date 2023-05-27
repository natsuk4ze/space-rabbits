//=============================================================================
//
// �G���� [SGB.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "SGB.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexSGB(int no);
void SetTextureSGB(int no, int cntPattern);
//void SetTextureSGB(float no);
void SetVertexSGB(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureSGB = NULL;		// �e�N�X�`���ւ̃|���S��

SGB					SGBWk[SGB_MAX];		// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSGB(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SGB *SGB = SGBWk;// �G�l�~�[�̃|�C���^�[��������
	int xdata;
	int ydata;

	srand((unsigned)time(NULL));

								// �e�N�X�`���[�̏��������s���H

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_SGB,				// �t�@�C���̖��O
			&g_pD3DTextureSGB);			// �ǂݍ��ރ������̃|�C���^
	}

	// �G�l�~�[�̏���������
	for (int i = 0; i < SGB_MAX; i++, SGB++)
	{
		xdata = rand() % (500);
		ydata = -1*(rand() % (300));

		SGB->use = true;										// �g�p
		SGB->pos = D3DXVECTOR3((float)(50+i*xdata), (float)(ydata), 0.0f);	// ���W�f�[�^��������
		//SGB->pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);	// ���W�f�[�^��������

		SGB->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		SGB->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		SGB->CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_SGB_SIZE_X, TEXTURE_SGB_SIZE_Y);
		SGB->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		SGB->BaseAngle = atan2f(TEXTURE_SGB_SIZE_Y, TEXTURE_SGB_SIZE_X);	// �G�l�~�[�̊p�x��������

		SGB->Texture = g_pD3DTextureSGB;					// �e�N�X�`�����
		MakeVertexSGB(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSGB(void)
{
	if (g_pD3DTextureSGB != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureSGB->Release();
		g_pD3DTextureSGB = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSGB(void)
{
	SGB *SGB = SGBWk;				// �G�l�~�[�̃|�C���^�[��������
	int xdata;
	int ydata;

	// �e����
	srand((unsigned)time(NULL));

	// �e�N�X�`���[�̏��������s���H
	for (int i = 0; i < SGB_MAX; i++, SGB++)
	{
		if (SGB->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			 //�A�j���[�V����
			   SGB->CountAnim++;
			if ((SGB->CountAnim % TIME_ANIMATION_SGB) == 0)
			{
				 //�p�^�[���̐؂�ւ�
				SGB->PatternAnim = (SGB->PatternAnim + 1) % ANIM_PATTERN_NUM_SGB;

				 //�e�N�X�`�����W��ݒ�
				SetTextureSGB(i, SGB->PatternAnim);
				
			}

			xdata = rand() % (500);
			ydata = -1*(rand() % (300));


			SGB->pos.y += 2.0f;


			if (SGB->pos.y >= 450.0f)
			{
				//SGB->use = false;
				SGB->pos.x = (float)(xdata);
				SGB->pos.y = (float)(ydata);

			}

			if (i & 1)
			{
				SGB->rot.z += 0.005f;
			}

			else
			{
				SGB->rot.z -= 0.005f;
			}


			

			SetVertexSGB(i);	// �ړ���̍��W�Œ��_��ݒ�
		}

	}

	

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSGB(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SGB *SGB = SGBWk;				// �G�l�~�[�̃|�C���^�[��������

										// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < SGB_MAX; i++, SGB++)
	{
		if (SGB->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, SGB->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_SGB, SGB->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexSGB(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SGB *SGB = &SGBWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	SetVertexSGB(no);

	// rhw�̐ݒ�
	SGB->vertexWk[0].rhw =
	SGB->vertexWk[1].rhw =
	SGB->vertexWk[2].rhw =
	SGB->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	SGB->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	SGB->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	SGB->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	SGB->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	SGB->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	SGB->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_SGB, 0.0f);
	SGB->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_SGB);
	SGB->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_SGB, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_SGB);

	//SGB->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//SGB->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//SGB->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//SGB->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
//
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureSGB(int no, int cntPattern)
{
	SGB *SGB = &SGBWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_SGB;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_Y_SGB;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_SGB;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_SGB;

	SGB->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	SGB->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	SGB->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	SGB->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}
////=============================================================================
//// �e�N�X�`�����W�̐ݒ�
////=============================================================================
//void SetTextureSGB(float yyy)
//{
//	// �e�N�X�`�����W�̐ݒ�
//	g_vertexWkSGB[0].tex = D3DXVECTOR2(0.0f, 0.0f - yyy);
//	g_vertexWkSGB[1].tex = D3DXVECTOR2(1.0f, 0.0f - yyy);
//	g_vertexWkSGB[2].tex = D3DXVECTOR2(0.0f, 1.0f - yyy);
//	g_vertexWkSGB[3].tex = D3DXVECTOR2(1.0f, 1.0f - yyy);
//}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexSGB(int no)
{
	SGB *SGB = &SGBWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	SGB->vertexWk[0].vtx.x = SGB->pos.x - cosf(SGB->BaseAngle + SGB->rot.z) * SGB->Radius;
	SGB->vertexWk[0].vtx.y = SGB->pos.y - sinf(SGB->BaseAngle + SGB->rot.z) * SGB->Radius;
	SGB->vertexWk[0].vtx.z = 0.0f;

	SGB->vertexWk[1].vtx.x = SGB->pos.x + cosf(SGB->BaseAngle - SGB->rot.z) * SGB->Radius;
	SGB->vertexWk[1].vtx.y = SGB->pos.y - sinf(SGB->BaseAngle - SGB->rot.z) * SGB->Radius;
	SGB->vertexWk[1].vtx.z = 0.0f;

	SGB->vertexWk[2].vtx.x = SGB->pos.x - cosf(SGB->BaseAngle - SGB->rot.z) * SGB->Radius;
	SGB->vertexWk[2].vtx.y = SGB->pos.y + sinf(SGB->BaseAngle - SGB->rot.z) * SGB->Radius;
	SGB->vertexWk[2].vtx.z = 0.0f;

	SGB->vertexWk[3].vtx.x = SGB->pos.x + cosf(SGB->BaseAngle + SGB->rot.z) * SGB->Radius;
	SGB->vertexWk[3].vtx.y = SGB->pos.y + sinf(SGB->BaseAngle + SGB->rot.z) * SGB->Radius;
	SGB->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
SGB *GetSGB(int no)
{
	return(&SGBWk[no]);
}

