//=============================================================================
//
// �ėp���w�N���X [UtilityMath.cpp](CUtilityMath)
// Author : Kodama Yuto
//
//=============================================================================
#include "UtilityMath.h"


//=============================================================================
//	���[���h�}�g���b�N�X�v�Z�֐�
//=============================================================================
D3DXMATRIX* CUtilityMath::CalWorldMatrix(D3DXMATRIX* pOut, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,
	const D3DXMATRIX* parent,const D3DXVECTOR3& scale, D3DXMATRIX* pViewMtx)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale,mtxInv, mtxParent;				// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(pOut);

	// ��]�𔽉f
	if (pViewMtx != NULL)	//pViewMtx��NULL���ǂ����Ńr���{�[�h���𔻕ʂ���
	{//	�r���{�[�h�Ȃ�
		D3DXMatrixIdentity(&mtxInv);
		//�t�s���ݒ�
		mtxInv._11 = pViewMtx->_11;
		mtxInv._12 = pViewMtx->_21;
		mtxInv._13 = pViewMtx->_31;
		mtxInv._21 = pViewMtx->_12;
		mtxInv._22 = pViewMtx->_22;
		mtxInv._23 = pViewMtx->_32;
		mtxInv._31 = pViewMtx->_13;
		mtxInv._32 = pViewMtx->_23;
		mtxInv._33 = pViewMtx->_33;

		//�o�����s��ɉ�]�𔽉f���ă��[���h�}�g���b�N�X�ɓ����
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(pOut, &mtxInv, &mtxRot);
	}
	else
	{//�r���{�[�h�łȂ��Ȃ�
		//���ʂɉ�]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(pOut, pOut, &mtxRot);
	}

	//�g��k���̔��f
	D3DXMatrixScaling(&mtxScale, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(pOut, pOut, &mtxScale);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(pOut, pOut, &mtxTrans);


	if (parent != NULL)
	{
		//�e�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(pOut,pOut,parent);
	}

	return pOut;
}

//=============================================================================
//	�p�x�␳�֐�
//=============================================================================
float CUtilityMath::RotateNormarizePI(float* value)
{//float
	if (*value > D3DX_PI)
	{
		*value -= D3DX_PI * 2.0f;
	}
	else if (*value < -D3DX_PI)
	{
		*value += D3DX_PI * 2.0f;
	}

	return *value;
}
D3DXVECTOR3 CUtilityMath::RotateNormarizePI(D3DXVECTOR3* RotateValue)
{//D3DXVECTOR3(float�R��)

	RotateNormarizePI(&RotateValue->x);
	RotateNormarizePI(&RotateValue->y);
	RotateNormarizePI(&RotateValue->z);

	return *RotateValue;
}

//=============================================================================
//	float�^�̐��`�⊮�֐�
//=============================================================================
float CUtilityMath::FloatLeap(const float& fromValue, const float& toValue, const float fTime)
{
	return (1.0f - fTime) * fromValue + fTime * toValue;
}

//=============================================================================
//	���l�̐��`�ʑ��֐�
//=============================================================================
float CUtilityMath::Mapping(const float& value, const float& fromSource, const float& toSource, const float& fromTarget, const float& toTarget,bool bClamp)
{
	float fResult = (value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget;

	if (bClamp == true)
	{//�N�����v
		if (fResult > toTarget) { fResult = toTarget; }
		else if (fResult < fromTarget) { fResult = fromTarget; }
	}
	return fResult;
}

//=============================================================================
//	�ړ��͂ɌW�����|����֐�
//=============================================================================
D3DXVECTOR3 CUtilityMath::MoveCoeffient(D3DXVECTOR3& value, const float& coeffient)
{//D3DXVECTOR3
	value.x += (0.0f - value.x) * coeffient;
	value.y += (0.0f - value.y) * coeffient;
	value.z += (0.0f - value.z) * coeffient;

	return value;
}

//=============================================================================
//	�C�ӂ̌�����float���l�̌ܓ�����֐�
//=============================================================================
float CUtilityMath::RoundF_n(float& fValue, const int nRound)
{
	fValue *= powf(10.0f,(float)(nRound - 1));	//�l�̌ܓ��������l��10��(n-1)��{����B
	fValue = round(fValue);						//�����_�ȉ����l�̌ܓ�����B
	fValue /= pow(10.0f, (float)(nRound - 1));  //10��(n-1)��Ŋ���B

	return fValue;
}

//=============================================================================
//
// �C�[�W���O�N���X [UtilityMath.cpp](CEasingFunc)
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
//	�C�[�W���O�֐�
//=============================================================================
float CEasingFunc::Easing(CEasingFunc::EASE_TYPE type, float& fTime)
{
	float fResult = 0.0f;

	if (fTime > 1.0f)
	{
		fTime = 1.0f;
	}
	else if (fTime < 0.0f)
	{
		fTime = 0.0f;
	}

	float Time = fTime;
	//�^�C�v���Ƃɏ����𕪂���
	switch (type)
	{
	case EASE_LINIAR:
		fResult = Time;
		break;
	case EASE_IN_QUAD:
		fResult = Time * Time;
		break;
	case EASE_OUT_QUAD:
		fResult = -1.0f*Time*(Time - 2.0f);
		break;
	case EASE_INOUT_QUAD:
		Time /= 0.5f;
		if (Time < 1.0f)
		{
			fResult = Time * Time * 0.5f;
		}
		else
		{
			Time = Time - 1.0f;
			fResult = -0.5f * (Time*(Time - 2) - 1);
		}
		break;
	case EASE_IN_CUBIC:
		fResult = Time * Time * Time;
		break;
	case EASE_OUT_CUBIC:
		Time = Time - 1.0f;
		fResult = (Time*Time*Time + 1);
		break;
	case EASE_INOUT_CUBIC:
		Time /= 0.5f;
		if (Time < 1.0f)
		{
			fResult = 0.5f*Time*Time*Time;
		}
		else
		{
			Time = Time - 2;
			fResult = 0.5f * (Time*Time*Time + 2);
		}

		break;
	}

	return fResult;
}

//=============================================================================
//
// �R�����x�N�g���N���X [UtilityMath.cpp](VECTOR_3D)
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
//	�p�x��@���Ƃ��Ďg����悤�ɐ��`�ʑ�����֐�
//=============================================================================
VECTOR_3D VECTOR_3D::RotateNormalize(void)
{
	//�p�x�𐳋K��
	//X
	if (this->X > _PI)
	{
		this->X -= _PI * 2.0f;
	}
	else if (this->X < -_PI)
	{
		this->X += _PI * 2.0f;
	}
	//Y
	if (this->Y > _PI)
	{
		this->Y -= _PI * 2.0f;
	}
	else if (this->Y < -_PI)
	{
		this->Y += _PI * 2.0f;
	}
	//Z
	if (this->Z > _PI)
	{
		this->Z -= _PI * 2.0f;
	}
	else if (this->Z < -_PI)
	{
		this->Z += _PI * 2.0f;
	}

	//-1.0f����1.0f�܂ł̐��l�ɒ���
	this->X = CUtilityMath::Mapping(this->X, -_PI, _PI, -1.0f, 1.0f, true);
	this->Y = CUtilityMath::Mapping(this->Y, -_PI, _PI, -1.0f, 1.0f, true);
	this->Z = CUtilityMath::Mapping(this->Z, -_PI, _PI, -1.0f, 1.0f, true);

	return *this;
}