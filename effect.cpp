//=============================================================================
//
// �������� [effect.cpp]
// Author : natsuk4ze
//
//=============================================================================
#include "main.h"
#include "effect.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffect(int no);
void SetTextureEffect(int no, int cntPattern);
void SetVertexEffect(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect = NULL;		// �e�N�X�`���ւ̃|���S��

EFFECT					effectWk[EFFECT_MAX];			// �o���b�g�\����

//LPDIRECTSOUNDBUFFER8	g_pSE;						// SE�p�o�b�t�@

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT *effect = &effectWk[0];		// �G�l�~�[�̃|�C���^�[��������

										// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EFFECT,			// �t�@�C���̖��O
			&g_pD3DTextureEffect);			// �ǂݍ��ރ������̃|�C���^

		//g_pSE = LoadSound(SE_00);

	}

	// �o���b�g�̏���������
	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		effect->use = false;									// ���g�p�i���˂���Ă��Ȃ��e�j
		effect->pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);			// ���W�f�[�^��������
		effect->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�f�[�^��������
		effect->PatternAnim = 0;								// �A�j���p�^�[���ԍ��������_���ŏ�����
		effect->CountAnim = 0;									// �A�j���J�E���g��������

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_EFFECT_SIZE_X, TEXTURE_EFFECT_SIZE_Y);
		effect->Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
		effect->BaseAngle = atan2f(TEXTURE_EFFECT_SIZE_Y, TEXTURE_EFFECT_SIZE_X);	// �G�l�~�[�̊p�x��������

		effect->Texture = g_pD3DTextureEffect;					// �e�N�X�`�����
		MakeVertexEffect(i);									// ���_���̍쐬
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	if (g_pD3DTextureEffect != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureEffect->Release();
		g_pD3DTextureEffect = NULL;
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
void UpdateEffect(void)
{
	EFFECT *effect = effectWk;				// �o���b�g�̃|�C���^�[��������

	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		if (effect->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �A�j���[�V����
			effect->CountAnim++;
			if ((effect->CountAnim % TIME_ANIMATION_EFFECT) == 0)
			{
				// �p�^�[���̐؂�ւ�
				effect->PatternAnim = (effect->PatternAnim + 1);

				// �e�N�X�`�����W��ݒ�
				SetTextureEffect(i, effect->PatternAnim);

				if (effect->PatternAnim >= ANIM_PATTERN_NUM_EFFECT)
				{
					effect->use= false;
					effect->PatternAnim = 0;
				}

			}


			SetVertexEffect(i);				// �ړ���̍��W�Œ��_��ݒ�
		}

	}
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT *effect = effectWk;				// �o���b�g�̃|�C���^�[��������

											// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		if (effect->use == true)			// �g�p���Ă����ԂȂ�X�V����
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, effect->Texture);

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT, effect->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT *effect = &effectWk[no];			// �o���b�g�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	SetVertexEffect(no);

	// rhw�̐ݒ�
	effect->vertexWk[0].rhw =
		effect->vertexWk[1].rhw =
		effect->vertexWk[2].rhw =
		effect->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	effect->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	effect->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	effect->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT, 0.0f);
	effect->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT);
	effect->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT);


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEffect(int no, int cntPattern)
{
	EFFECT *effect = &effectWk[no];			// �o���b�g�̃|�C���^�[��������

											// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT;

	effect->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	effect->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	effect->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	effect->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEffect(int no)
{
	EFFECT *effect = &effectWk[no];			// �G�l�~�[�̃|�C���^�[��������

											// ���_���W�̐ݒ�
	effect->vertexWk[0].vtx.x = effect->pos.x - cosf(effect->BaseAngle + effect->rot.z) * effect->Radius;
	effect->vertexWk[0].vtx.y = effect->pos.y - sinf(effect->BaseAngle + effect->rot.z) * effect->Radius;
	effect->vertexWk[0].vtx.z = 0.0f;

	effect->vertexWk[1].vtx.x = effect->pos.x + cosf(effect->BaseAngle - effect->rot.z) * effect->Radius;
	effect->vertexWk[1].vtx.y = effect->pos.y - sinf(effect->BaseAngle - effect->rot.z) * effect->Radius;
	effect->vertexWk[1].vtx.z = 0.0f;

	effect->vertexWk[2].vtx.x = effect->pos.x - cosf(effect->BaseAngle - effect->rot.z) * effect->Radius;
	effect->vertexWk[2].vtx.y = effect->pos.y + sinf(effect->BaseAngle - effect->rot.z) * effect->Radius;
	effect->vertexWk[2].vtx.z = 0.0f;

	effect->vertexWk[3].vtx.x = effect->pos.x + cosf(effect->BaseAngle + effect->rot.z) * effect->Radius;
	effect->vertexWk[3].vtx.y = effect->pos.y + sinf(effect->BaseAngle + effect->rot.z) * effect->Radius;
	effect->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g�̔��ːݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos)
{
	EFFECT *effect = &effectWk[0];			// �o���b�g�̃|�C���^�[��������

											 //�������g�p�̒e�����������甭�˂��Ȃ�( =����ȏ㌂�ĂȂ����Ď� )
	for (int i = 0; i < EFFECT_MAX; i++, effect++)
	{
		if (effect->use == false)			// ���g�p��Ԃ̃o���b�g��������
		{
			effect->use = true;				// �g�p��Ԃ֕ύX����
			effect->pos = pos;				// ���W���Z�b�g

			//								// ���ˉ��Đ�
			//PlaySound(g_pSE, E_DS8_FLAG_NONE);

			return;							// 1���Z�b�g�����̂ŏI������
		}
	}
}

//=============================================================================
// �o���b�g�̎擾�֐�
//=============================================================================
EFFECT *GetEffect(int no)
{
	return(&effectWk[no]);
}

