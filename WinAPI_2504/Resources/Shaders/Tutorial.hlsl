//Shader : GPU�� �ٷ�� ���α׷��� ���
//�ø�ƽ(Sementic) : ��ȯ�ڷ����̳� �Ű������� ���뵵�� ǥ���ϴ� ����
//SV : System Value
<<<<<<< HEAD
float4 VS( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
=======

//Constant Buffer(�������) : CPU���� �����ϴ� ��
cbuffer WorldBuffer : register(b0)
{
    matrix world;
}
cbuffer ViewBuffer : register(b1)
{
    matrix view;
}
cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
}

float4 VS( float4 pos : POSITION ) : SV_POSITION
{
    float4 output = mul(pos, world);
    output = mul(output, view);
    output = mul(output, projection);
    
	return output;
>>>>>>> upstream/main
}

float4 PS() : SV_TARGET
{
    return float4(1, 1, 0, 1);
}