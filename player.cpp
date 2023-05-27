//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "playerhp.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer( int no );
void SetTexturePlayer( int no, int cntPattern );
void SetVertexPlayer( int no );

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePlayer = NULL;		// �e�N�X�`���ւ̃|���S��

PLAYER					playerWk[PLAYER_MAX];			// �v���C���[�\����


//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_PLAYER,				// �t�@�C���̖��O
			&g_pD3DTexturePlayer);				// �ǂݍ��ރ������̃|�C���^
	}

	// �v���C���[�̏���������
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		player->use = true;									// �g�p
		//player->pos = D3DXVECTOR3(i*200.0f+200.0f, 300.0f, 0.0f);	// ���W�f�[�^��������
		player->pos = D3DXVECTOR3(100.0f + 200.0f, 350.0f, 0.0f);	// ���W�f�[�^��������

		player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]�f�[�^��������
		player->PatternAnim = rand() % ANIM_PATTERN_NUM;	// �A�j���p�^�[���ԍ��������_���ŏ�����
		player->CountAnim = 0;								// �A�j���J�E���g��������

		player->HP = PLAYERHP_MAX;
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y);
		player->Radius = D3DXVec2Length(&temp);				// �v���C���[�̔��a��������
		player->BaseAngle = atan2f(TEXTURE_PLAYER_SIZE_Y, TEXTURE_PLAYER_SIZE_X);	// �v���C���[�̊p�x��������

		player->Texture = g_pD3DTexturePlayer;				// �e�N�X�`�����
		MakeVertexPlayer(i);								// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if (g_pD3DTexturePlayer != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *player = &playerWk[0];

	if (player->HP <= 0)
	{
		player->use = false;
	}

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			player->CountAnim++;
			if ((player->CountAnim % TIME_ANIMATION) == 0)
			{
				// �p�^�[���̐؂�ւ�
				player->PatternAnim = (player->PatternAnim + 1) % ANIM_PATTERN_NUM;

				// �e�N�X�`�����W��ݒ�
				SetTexturePlayer(i, player->PatternAnim);
			}

			// �L�[�{�[�h���͂ňړ�(�ЂƂ܂��S�v���C���[�𓯂��L�[�œ��������Ⴄ)
			if (GetKeyboardPress(DIK_DOWN)|| GetKeyboardPress(DIK_S))
			{
				player->pos.y += 4.0f;
			}
			else if (GetKeyboardPress(DIK_UP)|| GetKeyboardPress(DIK_W))
			{
				player->pos.y -= 4.0f;
			}

			if (GetKeyboardPress(DIK_RIGHT)|| GetKeyboardPress(DIK_D))
			{
				player->pos.x += 4.0f;
			}
			else if (GetKeyboardPress(DIK_LEFT)|| GetKeyboardPress(DIK_A))
			{
				player->pos.x -= 4.0f;
			}

			// ��]
			if (GetKeyboardPress(DIK_R))
			{
				player->rot.z += 0.1f;
			}

			// �g��k��
			if (GetKeyboardPress(DIK_F))
			{
				player->Radius -= 1.0f;
			}
			else if (GetKeyboardPress(DIK_T))
			{
				player->Radius += 1.0f;
			}


			// �Q�[���p�b�h�łňړ�����
			if (IsButtonPressed(0, BUTTON_DOWN))
			{
				player->pos.y += 3.0f;
			}
			else if (IsButtonPressed(0, BUTTON_UP))
			{
				player->pos.y -= 3.0f;
			}

			if (IsButtonPressed(0, BUTTON_RIGHT))
			{
				player->pos.x += 3.0f;
			}
			else if (IsButtonPressed(0, BUTTON_LEFT))
			{
				player->pos.x -= 3.0f;
			}


			// �e����
			if (GetKeyboardTrigger(DIK_SPACE))
			{
				D3DXVECTOR3 pos = player->pos;
				pos.y -= TEXTURE_PLAYER_SIZE_Y;
				SetBullet(pos);
			}
			else if(IsButtonTriggered(0, BUTTON_B))
			{
				D3DXVECTOR3 pos = player->pos;
				pos.y -= TEXTURE_PLAYER_SIZE_Y;
				SetBullet(pos);
			}

			if (player->pos.x <= 0.0f)
			{
				player->pos.x = 0.0f;
			}

			if (player->pos.x >= 640.0f)
			{
				player->pos.x = 640.0f;
			}

			if (player->pos.y >= 450.0f)
			{
				player->pos.y = 450.0f;
			}

			if (player->pos.y <= 310.0f)
			{
				player->pos.y = 310.0f;
			}

			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexPlayer(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)			// �g�p���Ă����ԂȂ�`�悷��
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, player->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, player->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[no];

	// ���_���W�̐ݒ�
	SetVertexPlayer(no);

	// rhw�̐ݒ�
	player->vertexWk[0].rhw =
	player->vertexWk[1].rhw =
	player->vertexWk[2].rhw =
	player->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	player->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	player->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	player->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 0.0f );
	player->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );
	player->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );

	//player->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//player->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//player->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//player->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer( int no, int cntPattern )
{
	PLAYER *player = &playerWk[no];
	
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;
	
	player->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	player->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	player->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	player->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer(int no)
{
	PLAYER *player = &playerWk[no];
	
	// ���_���W�̐ݒ�
	player->vertexWk[0].vtx.x = player->pos.x - cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.y = player->pos.y - sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[0].vtx.z = 0.0f;

	player->vertexWk[1].vtx.x = player->pos.x + cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.y = player->pos.y - sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[1].vtx.z = 0.0f;

	player->vertexWk[2].vtx.x = player->pos.x - cosf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.y = player->pos.y + sinf(player->BaseAngle - player->rot.z) * player->Radius;
	player->vertexWk[2].vtx.z = 0.0f;

	player->vertexWk[3].vtx.x = player->pos.x + cosf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.y = player->pos.y + sinf(player->BaseAngle + player->rot.z) * player->Radius;
	player->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
PLAYER *GetPlayer(int no)
{
	return(&playerWk[no]);
}

