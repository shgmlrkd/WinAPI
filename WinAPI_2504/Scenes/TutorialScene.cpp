#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    vertexShader = Shader::AddVS(L"Tutorial.hlsl");
    pixelShader = Shader::AddPS(L"Tutorial.hlsl");    

    int n = 100;

    float stepAngle = PI * 2 / n;
    float radius = 100.0f;

    vertices.emplace_back(0, 0);

    for (int i = 0; i < n; i++)
    {
        float x = cos(stepAngle * i) * radius;
        float y = sin(stepAngle * i) * radius;

        vertices.emplace_back(x, y);
    }

    for (int i = 0; i < n; i++)
    {
        indices.push_back(0);

        int index = i + 2;
        if (index > n)
            index -= n;

        indices.push_back(index);
        indices.push_back(i + 1);
    }


    //VertexBuffer
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());
    //IndexBuffer
    indexBuffer = new IndexBuffer(indices.data(), indices.size());

    worldBuffer = new MatrixBuffer();
    viewBuffer = new MatrixBuffer();
    projectionBuffer = new MatrixBuffer();

    //Orthographic : 원근감이 없는 직육면체의 절두체를 형성하는 투영변환
    Matrix projection = XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, -1.0f, 1.0f);

    viewBuffer->SetVS(1);

    projectionBuffer->Set(projection);
    projectionBuffer->SetVS(2);

    matWorld._11 = 1;
    matWorld._22 = 1;
    matWorld._33 = 1;
    matWorld._44 = 1;
}

TutorialScene::~TutorialScene()
{
    delete vertexBuffer;
    delete indexBuffer;
}

void TutorialScene::Update()
{
    if (Input::Get()->IsKeyPress('D'))
    {
        //matWorld._41 += 100.0f * DELTA;
        pos.x += 100.0f * DELTA;
    }
    
    if (Input::Get()->IsKeyPress('W'))
    {
        //matWorld._42 += 100.0f * DELTA;
        pos.y += 100.0f * DELTA;
    }    

    //world = XMLoadFloat4x4(&matWorld);
    world = XMMatrixTranslation(pos.x, pos.y, 0.0f);
}

void TutorialScene::Render()
{   
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);    

    vertexBuffer->Set();
    indexBuffer->Set();

    vertexShader->Set();
    pixelShader->Set();

    //DC->Draw(vertices.size(), 0);
    DC->DrawIndexed(indices.size(), 0, 0);
}
