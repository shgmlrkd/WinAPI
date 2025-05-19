//Shader : GPU를 다루는 프로그래밍 언어
//시멘틱(Sementic) : 반환자료형이나 매개변수의 사용용도를 표기하는 역할
//SV : System Value
float4 VS( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}

float4 PS() : SV_TARGET
{
    return float4(1, 1, 0, 1);
}