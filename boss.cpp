//=============================================================================
//
// �G���� [boss.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "boss.h"
#include "input.h"
#include "bbullet.h"
#include "bosshp.h"
#include "score.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBoss(int no);
void SetTextureBoss(int no, int cntPattern);
void SetVertexBoss(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBoss = NULL;		// �e�N�X�`���ւ̃|���S��

BOSS					bossWk[BOSS_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBoss(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS *boss = &bossWk[0];				// �G�l�~�[�̃|�C���^�[��������

											// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOSS,				// �t�@�C���̖��O
			&g_pD3DTextureBoss);			// �ǂݍ��ރ������̃|�C���^
	}
	  

		// �G�l�~�[�̏���������
	for (int i = 0; i < BOSS_MAX; i++, boss++)
	{
		boss->use = true;										// �g�p

		//boss->pos = D3DXVECTOR3(50+i*150.0f, 100.0f, 0.0f);	// ���W�f�[�^��������
		boss->pos = D3DXVECTOR3(310.0f, -150.0f, 0.0f);	// ���W�f�[�^��������
		boss->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		boss->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		boss->CountAnim = 0;									// �A�j���J�E���g��������
		boss->HP = BOSSHP_MAX;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BOSS_SIZE_X, TEXTURE_BOSS_SIZE_Y);
		boss->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		boss->BaseAngle = atan2f(TEXTURE_BOSS_SIZE_Y, TEXTURE_BOSS_SIZE_X);	// �G�l�~�[�̊p�x��������
		boss->Texture = g_pD3DTextureBoss;					// �e�N�X�`�����

		MakeVertexBoss(i);										// ���_���̍쐬
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBoss(void)
{
	if (g_pD3DTextureBoss != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBoss->Release();
		g_pD3DTextureBoss = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoss(void)
{
	BOSS *boss = &bossWk[0];				// �G�l�~�[�̃|�C���^�[��������
	SCORE *score = GetScore(0);			// �o���b�g�̃|�C���^�[��������

	int data;
	// �e����
	srand((unsigned)time(NULL));


	for (int i = 0; i < BOSS_MAX; i++, boss++)
	{
		if (boss->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			boss->CountAnim++;

			if ((boss->CountAnim % TIME_ANIMATION_BOSS) == 0)
			{
				// �p�^�[���̐؂�ւ�
				boss->PatternAnim = (boss->PatternAnim + 1) % ANIM_PATTERN_NUM_BOSS;

				// �e�N�X�`�����W��ݒ�
				SetTextureBoss(i, boss->PatternAnim);
			}

			data = rand() % (9);

			if ((boss->HP > 0)&&(score->g_nScore >= 4000))
			{

				if (boss->pos.y < 100.0f)
				{
					boss->pos.y += 0.75f;
				}

				else
				{
					boss->pos.y = 100.0f;
				}

			}

			if (boss->pos.y == 100.0f)
			{

				if ((data == 1) || (data == 2))
				{
					boss->pos.x += 2.0f;
				}
				else if ((data == 3) || (data == 4))
				{
					boss->pos.x -= 2.0f;
				}

				if ((boss->HP > 0)&&(boss->pos.x <= 200.0f))
				{
					boss->pos.x = 200.0f;
				}

				if ((boss->HP > 0)&&(boss->pos.x >= 400.0f))
				{
					boss->pos.x = 400.0f;
				}

				// �e����
				if ((data == 5) || (data == 6) || (data == 7) || (data == 8))
				{
					D3DXVECTOR3 pos = boss->pos;
					pos.y -= (TEXTURE_BOSS_SIZE_Y)-130;
					SetBBullet(pos);
				}




			}

			if (boss->HP <= 0)
			{
				boss->pos.x += 2.50f;
				boss->pos.y -= 2.50f;

				boss->rot.z += 0.010f;

				if (boss->pos.y == -150)

				{
					boss->use = false;
				}


			}

			SetVertexBoss(i);	// �ړ���̍��W�Œ��_��ݒ�

		}
	}



}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS *boss = &bossWk[0];				// �G�l�~�[�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BOSS_MAX; i++, boss++)
	{

		if (boss->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, boss->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BOSS, boss->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBoss(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOSS *boss = &bossWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	SetVertexBoss(no);

	// rhw�̐ݒ�
	boss->vertexWk[0].rhw =
		boss->vertexWk[1].rhw =
		boss->vertexWk[2].rhw =
		boss->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	boss->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	boss->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	boss->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS, 0.0f);
	boss->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS);
	boss->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS);

	boss->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	boss->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	boss->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	boss->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBoss(int no, int cntPattern)
{
	BOSS *boss = &bossWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BOSS;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BOSS;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BOSS;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BOSS;

	boss->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	boss->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	boss->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	boss->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBoss(int no)
{
	BOSS *boss = &bossWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	boss->vertexWk[0].vtx.x = boss->pos.x - cosf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk[0].vtx.y = boss->pos.y - sinf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk[0].vtx.z = 0.0f;

	boss->vertexWk[1].vtx.x = boss->pos.x + cosf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk[1].vtx.y = boss->pos.y - sinf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk[1].vtx.z = 0.0f;

	boss->vertexWk[2].vtx.x = boss->pos.x - cosf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk[2].vtx.y = boss->pos.y + sinf(boss->BaseAngle - boss->rot.z) * boss->Radius;
	boss->vertexWk[2].vtx.z = 0.0f;

	boss->vertexWk[3].vtx.x = boss->pos.x + cosf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk[3].vtx.y = boss->pos.y + sinf(boss->BaseAngle + boss->rot.z) * boss->Radius;
	boss->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
BOSS *GetBoss(int no)
{
	return(&bossWk[no]);
}

