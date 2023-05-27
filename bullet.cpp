//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBullet(int no);
void SetTextureBullet(int no, int cntPattern);
void SetVertexBullet(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBullet = NULL;		// �e�N�X�`���ւ̃|���S��

BULLET					bulletWk[BULLET_MAX];			// �o���b�g�\����

LPDIRECTSOUNDBUFFER8	g_pSE;						// SE�p�o�b�t�@

													//=============================================================================
													// ����������
													//=============================================================================
HRESULT InitBullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = &bulletWk[0];		// �G�l�~�[�̃|�C���^�[��������

										// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BULLET,			// �t�@�C���̖��O
			&g_pD3DTextureBullet);			// �ǂݍ��ރ������̃|�C���^

		g_pSE = LoadSound(SE_00);

	}

	// �o���b�g�̏���������
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		bullet->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		bullet->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		bullet->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		bullet->CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BULLET_SIZE_X, TEXTURE_BULLET_SIZE_Y);
		bullet->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		bullet->BaseAngle = atan2f(TEXTURE_BULLET_SIZE_Y, TEXTURE_BULLET_SIZE_X);	// �G�l�~�[�̊p�x��������

		bullet->Texture = g_pD3DTextureBullet;					// �e�N�X�`�����
		MakeVertexBullet(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	if (g_pD3DTextureBullet != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBullet->Release();
		g_pD3DTextureBullet = NULL;
	}

	if (g_pSE != NULL)
	{	// �e�N�X�`���̊J��
		g_pSE->Release();
		g_pSE = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	BULLET *bullet = bulletWk;				// �o���b�g�̃|�C���^�[��������

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �o���b�g�̈ړ�����
			bullet->pos.y -= BULLET_SPEED;

			// ��ʊO�܂Ői�񂾁H
			if (bullet->pos.y < -TEXTURE_BULLET_SIZE_Y)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				bullet->use = false;
				bullet->pos.x = -100.0f;
			}

			if (i & 1)
			{
				bullet->rot.z += 0.1f;
			}
			else
			{
				bullet->rot.z -= 0.1f;
			}

			SetVertexBullet(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = bulletWk;				// �o���b�g�̃|�C���^�[��������

											// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, bullet->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BULLET, bullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBullet(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = &bulletWk[no];			// �o���b�g�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	SetVertexBullet(no);

	// rhw�̐ݒ�
	bullet->vertexWk[0].rhw =
		bullet->vertexWk[1].rhw =
		bullet->vertexWk[2].rhw =
		bullet->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLET, 0.0f);
	bullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLET);
	bullet->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLET, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLET);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBullet(int no, int cntPattern)
{
	BULLET *bullet = &bulletWk[no];			// �o���b�g�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLET;

	bullet->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	bullet->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	bullet->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	bullet->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBullet(int no)
{
	BULLET *bullet = &bulletWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	bullet->vertexWk[0].vtx.x = bullet->pos.x - cosf(bullet->BaseAngle + bullet->rot.z) * bullet->Radius;
	bullet->vertexWk[0].vtx.y = bullet->pos.y - sinf(bullet->BaseAngle + bullet->rot.z) * bullet->Radius;
	bullet->vertexWk[0].vtx.z = 0.0f;

	bullet->vertexWk[1].vtx.x = bullet->pos.x + cosf(bullet->BaseAngle - bullet->rot.z) * bullet->Radius;
	bullet->vertexWk[1].vtx.y = bullet->pos.y - sinf(bullet->BaseAngle - bullet->rot.z) * bullet->Radius;
	bullet->vertexWk[1].vtx.z = 0.0f;

	bullet->vertexWk[2].vtx.x = bullet->pos.x - cosf(bullet->BaseAngle - bullet->rot.z) * bullet->Radius;
	bullet->vertexWk[2].vtx.y = bullet->pos.y + sinf(bullet->BaseAngle - bullet->rot.z) * bullet->Radius;
	bullet->vertexWk[2].vtx.z = 0.0f;

	bullet->vertexWk[3].vtx.x = bullet->pos.x + cosf(bullet->BaseAngle + bullet->rot.z) * bullet->Radius;
	bullet->vertexWk[3].vtx.y = bullet->pos.y + sinf(bullet->BaseAngle + bullet->rot.z) * bullet->Radius;
	bullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetBullet(D3DXVECTOR3 pos)
{
	BULLET *bullet = &bulletWk[0];			// �o���b�g�̃|�C���^�[��������

											// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			bullet->use = true;				// �g�p��Ԃ֕ύX����
			bullet->pos = pos;				// ���W���Z�b�g

											// ���ˉ��Đ�
			PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �o���b�g�̎擾�֐�
//=============================================================================
BULLET *GetBullet(int no)
{
	return(&bulletWk[no]);
}

