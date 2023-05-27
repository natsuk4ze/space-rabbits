//=============================================================================
//
// �G���� [bosshp.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "bosshp.h"
#include "input.h"
#include "boss.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBosshp(int no);
void SetTextureBosshp(int no, int cntPattern);
void SetVertexBosshp(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBosshp = NULL;		// �e�N�X�`���ւ̃|���S��

BOSSHP					bosshpWk[BOSSHP_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBosshp(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSSHP *bosshp = &bosshpWk[0];				// �G�l�~�[�̃|�C���^�[��������

													// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOSSHP,				// �t�@�C���̖��O
			&g_pD3DTextureBosshp);			// �ǂݍ��ރ������̃|�C���^
	}

	// �G�l�~�[�̏���������
	for (int i = 0; i < BOSSHP_MAX; i++, bosshp++)
	{
		bosshp->use = true;										// �g�p
		bosshp->pos = D3DXVECTOR3(-300.0f, 50.0f, 0.0f);	// ���W�f�[�^��������
																	//bosshp->pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);	// ���W�f�[�^��������

		bosshp->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		bosshp->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		bosshp->CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BOSSHP_SIZE_X, TEXTURE_BOSSHP_SIZE_Y);
		bosshp->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		bosshp->BaseAngle = atan2f(TEXTURE_BOSSHP_SIZE_Y, TEXTURE_BOSSHP_SIZE_X);	// �G�l�~�[�̊p�x��������

		bosshp->Texture = g_pD3DTextureBosshp;					// �e�N�X�`�����
		MakeVertexBosshp(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBosshp(void)
{
	if (g_pD3DTextureBosshp != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBosshp->Release();
		g_pD3DTextureBosshp = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBosshp(void)
{
	BOSSHP *bosshp = &bosshpWk[0];				// �G�l�~�[�̃|�C���^�[��������
	BOSS*boss = GetBoss(0);				// �G�l�~�[�̃|�C���^�[��������


	for (int i = 0; i < BOSSHP_MAX; i++, bosshp++)
	{
		if (bosshp->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{

			//// �A�j���[�V����
			//bosshp->CountAnim++;
			//if ((bosshp->CountAnim % TIME_ANIMATION_BOSSHP) == 0)
			//{
			//	// �p�^�[���̐؂�ւ�
			//	bosshp->PatternAnim = (bosshp->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSSHP;

			//	// �e�N�X�`�����W��ݒ�
			//	SetTextureBosshp(i, bosshp->PatternAnim);
			//}

			if (i >= boss->HP)
			{
				bosshp->use = false;
			}

			else
			{
				bosshp->use = true;
			}

		}

		SetVertexBosshp(i);	// �ړ���̍��W�Œ��_��ݒ�

	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBosshp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSSHP *bosshp = &bosshpWk[0];				// �G�l�~�[�̃|�C���^�[��������

													// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSSHP_MAX; i++, bosshp++)
	{
		if (bosshp->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, bosshp->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSSHP, bosshp->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBosshp(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSSHP *bosshp = &bosshpWk[no];			// �G�l�~�[�̃|�C���^�[��������

												// ���_���W�̐ݒ�
	SetVertexBosshp(no);

	// rhw�̐ݒ�
	bosshp->vertexWk[0].rhw =
		bosshp->vertexWk[1].rhw =
		bosshp->vertexWk[2].rhw =
		bosshp->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bosshp->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bosshp->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bosshp->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bosshp->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bosshp->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bosshp->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSSHP, 0.0f);
	bosshp->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSSHP);
	bosshp->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSSHP, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSSHP);

	bosshp->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bosshp->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	bosshp->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bosshp->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBosshp(int no, int cntPattern)
{
	BOSSHP *bosshp = &bosshpWk[no];			// �G�l�~�[�̃|�C���^�[��������

												// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSSHP;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSSHP;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSSHP;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSSHP;

	bosshp->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	bosshp->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	bosshp->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	bosshp->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBosshp(int no)
{
	BOSSHP *bosshp = &bosshpWk[no];			// �G�l�~�[�̃|�C���^�[��������

												// ���_���W�̐ݒ�
	bosshp->vertexWk[0].vtx.x = bosshp->pos.x - cosf(bosshp->BaseAngle + bosshp->rot.z) * bosshp->Radius;
	bosshp->vertexWk[0].vtx.y = bosshp->pos.y - sinf(bosshp->BaseAngle + bosshp->rot.z) * bosshp->Radius;
	bosshp->vertexWk[0].vtx.z = 0.0f;

	bosshp->vertexWk[1].vtx.x = bosshp->pos.x + cosf(bosshp->BaseAngle - bosshp->rot.z) * bosshp->Radius;
	bosshp->vertexWk[1].vtx.y = bosshp->pos.y - sinf(bosshp->BaseAngle - bosshp->rot.z) * bosshp->Radius;
	bosshp->vertexWk[1].vtx.z = 0.0f;

	bosshp->vertexWk[2].vtx.x = bosshp->pos.x - cosf(bosshp->BaseAngle - bosshp->rot.z) * bosshp->Radius;
	bosshp->vertexWk[2].vtx.y = bosshp->pos.y + sinf(bosshp->BaseAngle - bosshp->rot.z) * bosshp->Radius;
	bosshp->vertexWk[2].vtx.z = 0.0f;

	bosshp->vertexWk[3].vtx.x = bosshp->pos.x + cosf(bosshp->BaseAngle + bosshp->rot.z) * bosshp->Radius;
	bosshp->vertexWk[3].vtx.y = bosshp->pos.y + sinf(bosshp->BaseAngle + bosshp->rot.z) * bosshp->Radius;
	bosshp->vertexWk[3].vtx.z = 0.0f;
}
//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetBosshp(D3DXVECTOR3 pos)
{
	BOSSHP *bosshp = &bosshpWk[0];			// �o���b�g�̃|�C���^�[��������

												//�������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < BOSSHP_MAX; i++, bosshp++)
	{
		if (bosshp->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			bosshp->use = true;				// �g�p��Ԃ֕ύX����
			bosshp->pos = pos;				// ���W���Z�b�g

											//								// ���ˉ��Đ�
											//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}


//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
BOSSHP *GetBosshp(int no)
{
	return(&bosshpWk[no]);
}
