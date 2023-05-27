//=============================================================================
//
// �G���� [playerhp.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "playerhp.h"
#include "input.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayerhp(int no);
void SetTexturePlayerhp(int no, int cntPattern);
void SetVertexPlayerhp(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayerhp = NULL;		// �e�N�X�`���ւ̃|���S��

PLAYERHP					playerhpWk[PLAYERHP_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerhp(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERHP *playerhp = &playerhpWk[0];				// �G�l�~�[�̃|�C���^�[��������

											// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_PLAYERHP,				// �t�@�C���̖��O
			&g_pD3DTexturePlayerhp);			// �ǂݍ��ރ������̃|�C���^
	}

	// �G�l�~�[�̏���������
	for (int i = 0; i < PLAYERHP_MAX; i++, playerhp++)
	{
		playerhp->use = true;										// �g�p
		playerhp->pos = D3DXVECTOR3(30+i*30.0f, 50.0f, 0.0f);	// ���W�f�[�^��������
		//playerhp->pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);	// ���W�f�[�^��������

		playerhp->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		playerhp->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		playerhp->CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYERHP_SIZE_X, TEXTURE_PLAYERHP_SIZE_Y);
		playerhp->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		playerhp->BaseAngle = atan2f(TEXTURE_PLAYERHP_SIZE_Y, TEXTURE_PLAYERHP_SIZE_X);	// �G�l�~�[�̊p�x��������

		playerhp->Texture = g_pD3DTexturePlayerhp;					// �e�N�X�`�����
		MakeVertexPlayerhp(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerhp(void)
{
	if (g_pD3DTexturePlayerhp != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexturePlayerhp->Release();
		g_pD3DTexturePlayerhp = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerhp(void)
{
	PLAYERHP *playerhp = &playerhpWk[0];				// �G�l�~�[�̃|�C���^�[��������
	PLAYER*player = GetPlayer(0);				// �G�l�~�[�̃|�C���^�[��������


	for (int i = 0; i < PLAYERHP_MAX; i++, playerhp++)
	{
		if (playerhp->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{

			// �A�j���[�V����
			playerhp->CountAnim++;
			if ((playerhp->CountAnim % TIME_ANIMATION_PLAYERHP) == 0)
			{
				// �p�^�[���̐؂�ւ�
				playerhp->PatternAnim = (playerhp->PatternAnim + 1) % ANIM_PATTERN_NUM_PLAYERHP;

				// �e�N�X�`�����W��ݒ�
				SetTexturePlayerhp(i, playerhp->PatternAnim);
			}

			if (i >= player->HP)
			{
				playerhp->use = false;
			}

			else
			{
				playerhp->use = true;
			}

		}

		SetVertexPlayerhp(i);	// �ړ���̍��W�Œ��_��ݒ�
		
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerhp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERHP *playerhp = &playerhpWk[0];				// �G�l�~�[�̃|�C���^�[��������

											// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PLAYERHP_MAX; i++, playerhp++)
	{
		if (playerhp->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, playerhp->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYERHP, playerhp->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayerhp(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYERHP *playerhp = &playerhpWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	SetVertexPlayerhp(no);

	// rhw�̐ݒ�
	playerhp->vertexWk[0].rhw =
		playerhp->vertexWk[1].rhw =
		playerhp->vertexWk[2].rhw =
		playerhp->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	playerhp->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	playerhp->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	playerhp->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	playerhp->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	playerhp->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	playerhp->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYERHP, 0.0f);
	playerhp->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYERHP);
	playerhp->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYERHP, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYERHP);

	playerhp->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	playerhp->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	playerhp->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	playerhp->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayerhp(int no, int cntPattern)
{
	PLAYERHP *playerhp = &playerhpWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_PLAYERHP;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_PLAYERHP;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_PLAYERHP;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PLAYERHP;

	playerhp->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	playerhp->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	playerhp->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	playerhp->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayerhp(int no)
{
	PLAYERHP *playerhp = &playerhpWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	playerhp->vertexWk[0].vtx.x = playerhp->pos.x - cosf(playerhp->BaseAngle + playerhp->rot.z) * playerhp->Radius;
	playerhp->vertexWk[0].vtx.y = playerhp->pos.y - sinf(playerhp->BaseAngle + playerhp->rot.z) * playerhp->Radius;
	playerhp->vertexWk[0].vtx.z = 0.0f;

	playerhp->vertexWk[1].vtx.x = playerhp->pos.x + cosf(playerhp->BaseAngle - playerhp->rot.z) * playerhp->Radius;
	playerhp->vertexWk[1].vtx.y = playerhp->pos.y - sinf(playerhp->BaseAngle - playerhp->rot.z) * playerhp->Radius;
	playerhp->vertexWk[1].vtx.z = 0.0f;

	playerhp->vertexWk[2].vtx.x = playerhp->pos.x - cosf(playerhp->BaseAngle - playerhp->rot.z) * playerhp->Radius;
	playerhp->vertexWk[2].vtx.y = playerhp->pos.y + sinf(playerhp->BaseAngle - playerhp->rot.z) * playerhp->Radius;
	playerhp->vertexWk[2].vtx.z = 0.0f;

	playerhp->vertexWk[3].vtx.x = playerhp->pos.x + cosf(playerhp->BaseAngle + playerhp->rot.z) * playerhp->Radius;
	playerhp->vertexWk[3].vtx.y = playerhp->pos.y + sinf(playerhp->BaseAngle + playerhp->rot.z) * playerhp->Radius;
	playerhp->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
PLAYERHP *GetPlayerhp(int no)
{
	return(&playerhpWk[no]);
}


