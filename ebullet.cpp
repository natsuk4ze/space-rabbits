//=============================================================================
//
// �o���b�g���� [ebullet.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "ebullet.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEBullet(int no);
void SetTextureEBullet(int no, int cntPattern);
void SetVertexEBullet(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEBullet = NULL;		// �e�N�X�`���ւ̃|���S��

EBULLET					ebulletWk[EBULLET_MAX];			// �o���b�g�\����

//LPDIRECTSOUNDBUFFER8	g_pSE;						// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEBullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET *ebullet = &ebulletWk[0];		// �G�l�~�[�̃|�C���^�[��������

										// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EBULLET,			// �t�@�C���̖��O
			&g_pD3DTextureEBullet);			// �ǂݍ��ރ������̃|�C���^

		//g_pSE = LoadSound(SE_00);

	}

	// �o���b�g�̏���������
	for (int i = 0; i < EBULLET_MAX; i++, ebullet++)
	{
		ebullet->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		ebullet->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		ebullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		ebullet->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		ebullet->CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_EBULLET_SIZE_X, TEXTURE_EBULLET_SIZE_Y);
		ebullet->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		ebullet->BaseAngle = atan2f(TEXTURE_EBULLET_SIZE_Y, TEXTURE_EBULLET_SIZE_X);	// �G�l�~�[�̊p�x��������

		ebullet->Texture = g_pD3DTextureEBullet;					// �e�N�X�`�����
		MakeVertexEBullet(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEBullet(void)
{
	if (g_pD3DTextureEBullet != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEBullet->Release();
		g_pD3DTextureEBullet = NULL;
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
void UpdateEBullet(void)
{
	EBULLET *ebullet = ebulletWk;				// �o���b�g�̃|�C���^�[��������

	for (int i = 0; i < EBULLET_MAX; i++, ebullet++)
	{
		if (ebullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �o���b�g�̈ړ�����
			ebullet->pos.y += EBULLET_SPEED;

			// ��ʊO�܂Ői�񂾁H
			if (ebullet->pos.y > SCREEN_HEIGHT)	// �����̑傫�����l�����ĉ�ʊO�����肵�Ă���
			{
				ebullet->use = false;
				ebullet->pos.x = -100.0f;
			}


			SetVertexEBullet(i);				// �ړ���̍��W�Œ��_��ݒ�
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET *ebullet = ebulletWk;				// �o���b�g�̃|�C���^�[��������

											// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EBULLET_MAX; i++, ebullet++)
	{
		if (ebullet->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, ebullet->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EBULLET, ebullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEBullet(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EBULLET *ebullet = &ebulletWk[no];			// �o���b�g�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	SetVertexEBullet(no);

	// rhw�̐ݒ�
	ebullet->vertexWk[0].rhw =
		ebullet->vertexWk[1].rhw =
		ebullet->vertexWk[2].rhw =
		ebullet->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	ebullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	ebullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	ebullet->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	ebullet->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET, 0.0f);
	ebullet->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET);
	ebullet->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEBullet(int no, int cntPattern)
{
	EBULLET *ebullet = &ebulletWk[no];			// �o���b�g�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EBULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EBULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EBULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EBULLET;

	ebullet->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	ebullet->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	ebullet->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	ebullet->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEBullet(int no)
{
	EBULLET *ebullet = &ebulletWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	ebullet->vertexWk[0].vtx.x = ebullet->pos.x - cosf(ebullet->BaseAngle + ebullet->rot.z) * ebullet->Radius;
	ebullet->vertexWk[0].vtx.y = ebullet->pos.y - sinf(ebullet->BaseAngle + ebullet->rot.z) * ebullet->Radius;
	ebullet->vertexWk[0].vtx.z = 0.0f;

	ebullet->vertexWk[1].vtx.x = ebullet->pos.x + cosf(ebullet->BaseAngle - ebullet->rot.z) * ebullet->Radius;
	ebullet->vertexWk[1].vtx.y = ebullet->pos.y - sinf(ebullet->BaseAngle - ebullet->rot.z) * ebullet->Radius;
	ebullet->vertexWk[1].vtx.z = 0.0f;

	ebullet->vertexWk[2].vtx.x = ebullet->pos.x - cosf(ebullet->BaseAngle - ebullet->rot.z) * ebullet->Radius;
	ebullet->vertexWk[2].vtx.y = ebullet->pos.y + sinf(ebullet->BaseAngle - ebullet->rot.z) * ebullet->Radius;
	ebullet->vertexWk[2].vtx.z = 0.0f;

	ebullet->vertexWk[3].vtx.x = ebullet->pos.x + cosf(ebullet->BaseAngle + ebullet->rot.z) * ebullet->Radius;
	ebullet->vertexWk[3].vtx.y = ebullet->pos.y + sinf(ebullet->BaseAngle + ebullet->rot.z) * ebullet->Radius;
	ebullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetEBullet(D3DXVECTOR3 pos)
{
	EBULLET *ebullet = &ebulletWk[0];			// �o���b�g�̃|�C���^�[��������

											// �������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < EBULLET_MAX; i++, ebullet++)
	{
		if (ebullet->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			ebullet->use = true;				// �g�p��Ԃ֕ύX����
			ebullet->pos = pos;				// ���W���Z�b�g

											// ���ˉ��Đ�
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �o���b�g�̎擾�֐�
//=============================================================================
EBULLET *GetEBullet(int no)
{
	return(&ebulletWk[no]);
}

