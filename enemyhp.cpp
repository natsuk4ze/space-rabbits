//=============================================================================
//
// �G���� [enemyhp.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "enemyhp.h"
#include "input.h"
#include "enemy.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemyhp(int no);
void SetTextureEnemyhp(int no, int cntPattern);
void SetVertexEnemyhp(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyhp = NULL;		// �e�N�X�`���ւ̃|���S��

ENEMYHP					enemyhpWk[ENEMYHP_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyhp(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYHP *enemyhp = &enemyhpWk[0];				// �G�l�~�[�̃|�C���^�[��������

														// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMYHP,				// �t�@�C���̖��O
			&g_pD3DTextureEnemyhp);			// �ǂݍ��ރ������̃|�C���^
	}

	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMYHP_MAX; i++, enemyhp++)
	{
		enemyhp->use = true;										// �g�p
		enemyhp->pos = D3DXVECTOR3(-300 + i * 30.0f, 50.0f, 0.0f);	// ���W�f�[�^��������
																	//enemyhp->pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);	// ���W�f�[�^��������

		enemyhp->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		enemyhp->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		enemyhp->CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMYHP_SIZE_X, TEXTURE_ENEMYHP_SIZE_Y);
		enemyhp->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		enemyhp->BaseAngle = atan2f(TEXTURE_ENEMYHP_SIZE_Y, TEXTURE_ENEMYHP_SIZE_X);	// �G�l�~�[�̊p�x��������

		enemyhp->Texture = g_pD3DTextureEnemyhp;					// �e�N�X�`�����
		MakeVertexEnemyhp(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyhp(void)
{
	if (g_pD3DTextureEnemyhp != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEnemyhp->Release();
		g_pD3DTextureEnemyhp = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyhp(void)
{
	ENEMYHP *enemyhp = &enemyhpWk[0];				// �G�l�~�[�̃|�C���^�[��������
	ENEMY*enemy = GetEnemy(0);				// �G�l�~�[�̃|�C���^�[��������


	for (int i = 0; i < ENEMYHP_MAX; i++, enemyhp++)
	{
		if (enemyhp->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{

			// �A�j���[�V����
			enemyhp->CountAnim++;
			if ((enemyhp->CountAnim % TIME_ANIMATION_ENEMYHP) == 0)
			{
				// �p�^�[���̐؂�ւ�
				enemyhp->PatternAnim = (enemyhp->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMYHP;

				// �e�N�X�`�����W��ݒ�
				SetTextureEnemyhp(i, enemyhp->PatternAnim);
			}

			if (i >= enemy->HP)
			{
				enemyhp->use = false;
			}

			else
			{
				enemyhp->use = true;
			}

		}

		SetVertexEnemyhp(i);	// �ړ���̍��W�Œ��_��ݒ�

	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyhp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYHP *enemyhp = &enemyhpWk[0];				// �G�l�~�[�̃|�C���^�[��������

														// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMYHP_MAX; i++, enemyhp++)
	{
		if (enemyhp->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, enemyhp->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMYHP, enemyhp->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemyhp(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYHP *enemyhp = &enemyhpWk[no];			// �G�l�~�[�̃|�C���^�[��������

													// ���_���W�̐ݒ�
	SetVertexEnemyhp(no);

	// rhw�̐ݒ�
	enemyhp->vertexWk[0].rhw =
		enemyhp->vertexWk[1].rhw =
		enemyhp->vertexWk[2].rhw =
		enemyhp->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemyhp->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyhp->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyhp->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemyhp->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemyhp->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemyhp->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYHP, 0.0f);
	enemyhp->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYHP);
	enemyhp->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYHP, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYHP);

	enemyhp->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemyhp->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	enemyhp->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	enemyhp->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemyhp(int no, int cntPattern)
{
	ENEMYHP *enemyhp = &enemyhpWk[no];			// �G�l�~�[�̃|�C���^�[��������

													// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMYHP;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMYHP;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYHP;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYHP;

	enemyhp->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	enemyhp->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	enemyhp->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	enemyhp->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemyhp(int no)
{
	ENEMYHP *enemyhp = &enemyhpWk[no];			// �G�l�~�[�̃|�C���^�[��������

													// ���_���W�̐ݒ�
	enemyhp->vertexWk[0].vtx.x = enemyhp->pos.x - cosf(enemyhp->BaseAngle + enemyhp->rot.z) * enemyhp->Radius;
	enemyhp->vertexWk[0].vtx.y = enemyhp->pos.y - sinf(enemyhp->BaseAngle + enemyhp->rot.z) * enemyhp->Radius;
	enemyhp->vertexWk[0].vtx.z = 0.0f;

	enemyhp->vertexWk[1].vtx.x = enemyhp->pos.x + cosf(enemyhp->BaseAngle - enemyhp->rot.z) * enemyhp->Radius;
	enemyhp->vertexWk[1].vtx.y = enemyhp->pos.y - sinf(enemyhp->BaseAngle - enemyhp->rot.z) * enemyhp->Radius;
	enemyhp->vertexWk[1].vtx.z = 0.0f;

	enemyhp->vertexWk[2].vtx.x = enemyhp->pos.x - cosf(enemyhp->BaseAngle - enemyhp->rot.z) * enemyhp->Radius;
	enemyhp->vertexWk[2].vtx.y = enemyhp->pos.y + sinf(enemyhp->BaseAngle - enemyhp->rot.z) * enemyhp->Radius;
	enemyhp->vertexWk[2].vtx.z = 0.0f;

	enemyhp->vertexWk[3].vtx.x = enemyhp->pos.x + cosf(enemyhp->BaseAngle + enemyhp->rot.z) * enemyhp->Radius;
	enemyhp->vertexWk[3].vtx.y = enemyhp->pos.y + sinf(enemyhp->BaseAngle + enemyhp->rot.z) * enemyhp->Radius;
	enemyhp->vertexWk[3].vtx.z = 0.0f;
}
//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetEnemyhp(D3DXVECTOR3 pos)
{
	ENEMYHP *enemyhp = &enemyhpWk[0];			// �o���b�g�̃|�C���^�[��������

											//�������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < ENEMYHP_MAX; i++, enemyhp++)
	{
		if (enemyhp->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			enemyhp->use = true;				// �g�p��Ԃ֕ύX����
			enemyhp->pos = pos;				// ���W���Z�b�g

											//								// ���ˉ��Đ�
											//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}


//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMYHP *GetEnemyhp(int no)
{
	return(&enemyhpWk[no]);
}
