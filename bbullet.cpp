//=============================================================================
//
// �o���b�g���� [bbullet.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "bbullet.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBBullet(int no);
void SetTextureBBullet(int no, int cntPattern);
void SetVertexBBullet(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBBullet = NULL;		// �e�N�X�`���ւ̃|���S��

BBULLET					bbulletWk[BBULLET_MAX];			// �o���b�g�\����

														//LPDIRECTSOUNDBUFFER8	g_pSE;						// SE�p�o�b�t�@

														//=============================================================================
														// ����������
														//=============================================================================
HRESULT InitBBullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BBULLET *bbullet = &bbulletWk[0];		// �G�l�~�[�̃|�C���^�[��������

											// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BBULLET,			// �t�@�C���̖��O
			&g_pD3DTextureBBullet);			// �ǂݍ��ރ������̃|�C���^

											//g_pSE = LoadSound(SE_00);

	}

	// �o���b�g�̏���������
	for (int i = 0; i < BBULLET_MAX; i++, bbullet++)
	{
		bbullet->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		bbullet->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		bbullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		bbullet->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		bbullet->CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BBULLET_SIZE_X, TEXTURE_BBULLET_SIZE_Y);
		bbullet->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		bbullet->BaseAngle = atan2f(TEXTURE_BBULLET_SIZE_Y, TEXTURE_BBULLET_SIZE_X);	// �G�l�~�[�̊p�x��������

		bbullet->Texture = g_pD3DTextureBBullet;					// �e�N�X�`�����
		MakeVertexBBullet(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBBullet(void)
{
	if (g_pD3DTextureBBullet != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBBullet->Release();
		g_pD3DTextureBBullet = NULL;
	}

	//if (g_pSE != NULL)
	//{	// �e�N�X�`���̊J��
	//	g_pSE->Release();
	//	g_pSE = NULL;
	//}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBBullet(void)
{
	BBULLET *bbullet = bbulletWk;				// �o���b�g�̃|�C���^�[��������
	int data;
	int sayuu;

	srand((unsigned)time(NULL));

	for (int i = 0; i < BBULLET_MAX; i++, bbullet++)
	{
		if (bbullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			sayuu = rand() % (2);
			data = 2 + rand() % (10);

			// �o���b�g�̈ړ�����
			bbullet->pos.y += BBULLET_SPEED;

			if (sayuu == 0)
			{
				bbullet->pos.x += data;

			}

			if (sayuu == 1)
			{
				bbullet->pos.x -= data;

			}

			// ��ʊO�܂Ői�񂾁H
			if (bbullet->pos.y > SCREEN_HEIGHT)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				bbullet->use = false;
				bbullet->pos.x = -100.0f;
			}

			if (i & 1)
			{
				bbullet->rot.z += 0.1f;
			}
			else
			{
				bbullet->rot.z -= 0.1f;
			}

			SetVertexBBullet(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BBULLET *bbullet = bbulletWk;				// �o���b�g�̃|�C���^�[��������

												// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BBULLET_MAX; i++, bbullet++)
	{
		if (bbullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, bbullet->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BBULLET, bbullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBBullet(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BBULLET *bbullet = &bbulletWk[no];			// �o���b�g�̃|�C���^�[��������

												// ���_���W�̐ݒ�
	SetVertexBBullet(no);

	// rhw�̐ݒ�
	bbullet->vertexWk[0].rhw =
		bbullet->vertexWk[1].rhw =
		bbullet->vertexWk[2].rhw =
		bbullet->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bbullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bbullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bbullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	bbullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	bbullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bbullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BBULLET, 0.0f);
	bbullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BBULLET);
	bbullet->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BBULLET, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BBULLET);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBBullet(int no, int cntPattern)
{
	BBULLET *bbullet = &bbulletWk[no];			// �o���b�g�̃|�C���^�[��������

												// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BBULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BBULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BBULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BBULLET;

	bbullet->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	bbullet->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	bbullet->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	bbullet->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBBullet(int no)
{
	BBULLET *bbullet = &bbulletWk[no];			// �G�l�~�[�̃|�C���^�[��������

												// ���_���W�̐ݒ�
	bbullet->vertexWk[0].vtx.x = bbullet->pos.x - cosf(bbullet->BaseAngle + bbullet->rot.z) * bbullet->Radius;
	bbullet->vertexWk[0].vtx.y = bbullet->pos.y - sinf(bbullet->BaseAngle + bbullet->rot.z) * bbullet->Radius;
	bbullet->vertexWk[0].vtx.z = 0.0f;

	bbullet->vertexWk[1].vtx.x = bbullet->pos.x + cosf(bbullet->BaseAngle - bbullet->rot.z) * bbullet->Radius;
	bbullet->vertexWk[1].vtx.y = bbullet->pos.y - sinf(bbullet->BaseAngle - bbullet->rot.z) * bbullet->Radius;
	bbullet->vertexWk[1].vtx.z = 0.0f;

	bbullet->vertexWk[2].vtx.x = bbullet->pos.x - cosf(bbullet->BaseAngle - bbullet->rot.z) * bbullet->Radius;
	bbullet->vertexWk[2].vtx.y = bbullet->pos.y + sinf(bbullet->BaseAngle - bbullet->rot.z) * bbullet->Radius;
	bbullet->vertexWk[2].vtx.z = 0.0f;

	bbullet->vertexWk[3].vtx.x = bbullet->pos.x + cosf(bbullet->BaseAngle + bbullet->rot.z) * bbullet->Radius;
	bbullet->vertexWk[3].vtx.y = bbullet->pos.y + sinf(bbullet->BaseAngle + bbullet->rot.z) * bbullet->Radius;
	bbullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetBBullet(D3DXVECTOR3 pos)
{
	BBULLET *bbullet = &bbulletWk[0];			// �o���b�g�̃|�C���^�[��������

												// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < BBULLET_MAX; i++, bbullet++)
	{
		if (bbullet->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			bbullet->use = true;				// �g�p��Ԃ֕ύX����
			bbullet->pos = pos;				// ���W���Z�b�g

											// ���ˉ��Đ�
											//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �o���b�g�̎擾�֐�
//=============================================================================
BBULLET *GetBBullet(int no)
{
	return(&bbulletWk[no]);
}
