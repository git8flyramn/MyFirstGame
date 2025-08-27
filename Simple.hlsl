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
    //float4x4 matW; //���[���h�s��
    float4x4 matNomal;
    float4x4 matWorld;
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
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NOMAL)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
    VS_OUT outData;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
    //�@������]
    //nomal = matW;
    outData.pos = mul(pos, matWVP);
    outData.uv = uv.xy;//UV���W�͂��̂܂�
    
    normal = mul(normal, matNomal);//�@���x�N�g�������[���h�r���[�E�v���W�F�N�V�����s��ŕϊ�
   
    normal = normalize(normal);//�@���x�N�g���𐳋K��=����1��
    normal.w = 0;//w������0�ɂ���
    
    float light = float4(-1, 0.5, -0.7, 0);
    light = normalize(light);
    
    outData.color = dot(normal, light);
    
    return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
    float4 color = g_texture.Sample(g_sampler, inData.uv) * inData.color;
    //float4 ret = float(inData.uv.x,inData.uv.y,0,1;
    return color;
}