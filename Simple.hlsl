//������������������������������������������������������������������������������
// �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������

//  Sample3D.hlsl
Texture2D g_texture : register(t0); //�e�N�X�`���[
SamplerState g_sampler : register(s0); //�T���v���[

//������������������������������������������������������������������������������
// �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
    float4x4 matWVP; // ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
    float4x4 matNomal;
    float4   diffuseColor;
    bool     useTexture; //�e�N�X�`�����g�����ǂ���
    
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
                 //�Z�}���e�B�N�X
    float4 pos : SV_POSITION; //�ʒu
    float2 uv : TEXCOORD; //UV���W
    float4 color : COLOR; //�F(���邳)
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
    VS_OUT outData;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
    //�@������]
    //nomal = matW;
    outData.pos = mul(pos, matWVP);
    uv.w = 1;
    outData.uv = uv.xy;
    
    normal = mul(normal, matNomal); //�@���x�N�g�������[���h�r���[�v���W�F�N�V�����s��ŕϊ�
    normal = normalize(normal); //�@���x�N�g���̒����𐳋K��->1�ɂ���
    normal.w = 0;
    float4 light = float4(-1, 0.5, -0.7, 0);
    light = normalize(light);
    light.w = 0;
    outData.color = clamp(dot(normal, light), 0, 1);
    
    return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
    float4 color;
    if(useTexture == 1)
    {
        color = g_texture.Sample(g_sampler, inData.uv);
    }
    else
    {
        color = diffuseColor;
    }
    return color * inData.color;
}