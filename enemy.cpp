//=============================================================================
//
// �G���� [enemy.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "input.h"
#include "ebullet.h"
#include "enemyhp.h"
#include "score.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy( int no );
void SetTextureEnemy( int no, int cntPattern );
void SetVertexEnemy( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemy = NULL;		// �e�N�X�`���ւ̃|���S��

ENEMY					enemyWk[ENEMY_MAX];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[0];				// �G�l�~�[�̃|�C���^�[��������
	
	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMY,				// �t�@�C���̖��O
			&g_pD3DTextureEnemy);			// �ǂݍ��ރ������̃|�C���^
	}

	// �G�l�~�[�̏���������
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		enemy->use = true;										// �g�p
		enemy->pos = D3DXVECTOR3(50+i*300.0f, -200.0f, 0.0f);	// ���W�f�[�^��������
		//enemy->pos = D3DXVECTOR3(310.0f, 100.0f, 0.0f);	// ���W�f�[�^��������

		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
		enemy->PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
		enemy->CountAnim = 0;									// �A�j���J�E���g��������
		enemy->HP = ENEMYHP_MAX;

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y);
		enemy->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		enemy->BaseAngle = atan2f(TEXTURE_ENEMY_SIZE_Y, TEXTURE_ENEMY_SIZE_X);	// �G�l�~�[�̊p�x��������

		enemy->Texture = g_pD3DTextureEnemy;					// �e�N�X�`�����
		MakeVertexEnemy(i);										// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	if (g_pD3DTextureEnemy != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEnemy->Release();
		g_pD3DTextureEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	ENEMY *enemy = &enemyWk[0];				// �G�l�~�[�̃|�C���^�[��������
	SCORE *score = GetScore(0);			// �o���b�g�̃|�C���^�[��������

	int data;
											// �e����
	srand((unsigned)time(NULL));

	if (enemy->HP <= 0)
	{
		enemy->use = false;
	}

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			enemy->CountAnim++;
			if ((enemy->CountAnim % TIME_ANIMATION_ENEMY) == 0)
			{
				// �p�^�[���̐؂�ւ�
				enemy->PatternAnim = (enemy->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY;

				// �e�N�X�`�����W��ݒ�
				SetTextureEnemy(i, enemy->PatternAnim);
			}

			data = rand() % (9);

			if (score->g_nScore >= 180)
			{
				if (enemy->pos.y < 100.0f)
				{
					enemy->pos.y += 1.50f;
				}

				else
				{
					enemy->pos.y = 100.0f;
				}

			}

			if (enemy->pos.y == 100)
			{

				if ((data == 1) || (data == 2))
				{
					enemy->pos.x += 2.0f;
				}
				else if ((data == 3) || (data == 4))
				{
					enemy->pos.x -= 2.0f;
				}

				if (enemy->pos.x <= 150.0f)
				{
					enemy->pos.x = 150.0f;
				}

				if (enemy->pos.x >= 500.0f)
				{
					enemy->pos.x = 500.0f;
				}

				// �e����
				if ((data == 5) || (data == 6) || (data == 7) || (data == 8))
				{
					D3DXVECTOR3 pos = enemy->pos;
					pos.y -= (TEXTURE_ENEMY_SIZE_Y)-130;
					SetEBullet(pos);
				}

			}



			SetVertexEnemy(i);	// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[0];				// �G�l�~�[�̃|�C���^�[��������

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, enemy->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, enemy->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy( int no )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[no];			// �G�l�~�[�̃|�C���^�[��������

	// ���_���W�̐ݒ�
	SetVertexEnemy( no );

	// rhw�̐ݒ�
	enemy->vertexWk[0].rhw =
	enemy->vertexWk[1].rhw =
	enemy->vertexWk[2].rhw =
	enemy->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemy->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY, 0.0f);
	enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY);
	enemy->vertexWk[3].tex = D3DXVECTOR2( 1.0f/ TEXTURE_PATTERN_DIVIDE_X_ENEMY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY);

	enemy->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	enemy->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	enemy->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	enemy->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy( int no, int cntPattern )
{
	ENEMY *enemy = &enemyWk[no];			// �G�l�~�[�̃|�C���^�[��������

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY;
	
	enemy->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy( int no )
{
	ENEMY *enemy = &enemyWk[no];			// �G�l�~�[�̃|�C���^�[��������
	
	// ���_���W�̐ݒ�
	enemy->vertexWk[0].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[0].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[0].vtx.z = 0.0f;

	enemy->vertexWk[1].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[1].vtx.y = enemy->pos.y - sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[1].vtx.z = 0.0f;

	enemy->vertexWk[2].vtx.x = enemy->pos.x - cosf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[2].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle - enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[2].vtx.z = 0.0f;

	enemy->vertexWk[3].vtx.x = enemy->pos.x + cosf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[3].vtx.y = enemy->pos.y + sinf(enemy->BaseAngle + enemy->rot.z) * enemy->Radius;
	enemy->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY *GetEnemy(int no)
{
	return(&enemyWk[no]);
}


