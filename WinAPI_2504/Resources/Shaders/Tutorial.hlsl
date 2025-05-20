//Shader : GPU를 다루는 프로그래밍 언어
//시멘틱(Sementic) : 반환자료형이나 매개변수의 사용용도를 표기하는 역할
//SV : System Value

//Constant Buffer(상수버퍼) : CPU에서 전달하는 값
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
}

float4 PS() : SV_TARGET
{
    return float4(1, 1, 0, 1);
}