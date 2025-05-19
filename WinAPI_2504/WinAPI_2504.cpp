// WinAPI_2504.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinAPI_2504.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND hWnd;                                      // 현재 창입니다.
Vector2 mousePos;

WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

struct Vertex//정점 : 3차원 공간에서의 한 점
{
    float x, y, z;

    Vertex(float x = 0, float y = 0)
        : x(x), y(y), z(0)
    {
    }
};

vector<Vertex> vertices;

ID3D11Device* device;//CPU - 직렬, 로드, 연산
ID3D11DeviceContext* deviceContext;//GPU - 병렬, 출력

IDXGISwapChain* swapChain;//후면 버퍼 관리
ID3D11RenderTargetView* renderTargetView;//VRAM 후면버퍼 메모리 관리

ID3D11VertexShader* vertexShader;
ID3D11PixelShader* pixelShader;
ID3D11InputLayout* inputLayout;
ID3D11Buffer* vertexBuffer;//VRAM 메모리

void Init();
void Render();
void Release();


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI2504, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI2504));

    MSG msg = {};

    //GameManager* gameManager = new GameManager();
    Init();
    
    while (msg.message != WM_QUIT)
    {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//gameManager->Update();
			//gameManager->Render();
            Render();
		}
    }

    Release();

    return (int) msg.wParam;
}



void Init()
{
    UINT width = SCREEN_WIDTH;
    UINT height = SCREEN_HEIGHT;

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.Windowed = true;

    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );
    
    ID3D11Texture2D* backBuffer;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

    /////////////////////////////////////////////////////////////////////////////////

    //Shader Load
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    ID3DBlob* vertexBlob;
    D3DCompileFromFile(L"Resources/Shaders/Tutorial.hlsl", nullptr, nullptr,
        "VS", "vs_5_0", flags, 0, &vertexBlob, nullptr);

    device->CreateVertexShader(vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), nullptr, &vertexShader);

    ID3DBlob* pixelBlob;
    D3DCompileFromFile(L"Resources/Shaders/Tutorial.hlsl", nullptr, nullptr,
        "PS", "ps_5_0", flags, 0, &pixelBlob, nullptr);

    device->CreatePixelShader(pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(), nullptr, &pixelShader);

    /////////////////////////////////////////////////////////////////////////
    //InputLayout
    D3D11_INPUT_ELEMENT_DESC elementDesc = {};
    elementDesc.SemanticName = "POSITION";
    elementDesc.SemanticIndex = 0;
    elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    elementDesc.InputSlot = 0;
    elementDesc.AlignedByteOffset = 0;
    elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    elementDesc.InstanceDataStepRate = 0;

    vector<D3D11_INPUT_ELEMENT_DESC> elementDescs;
    elementDescs.push_back(elementDesc);

    device->CreateInputLayout(elementDescs.data(), elementDescs.size(),
        vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(),
        &inputLayout);

    vertexBlob->Release();
    pixelBlob->Release();
    /////////////////////////////////////////////////////////////////
    //Vieport 변환
    D3D11_VIEWPORT viewport;
    viewport.Width = SCREEN_WIDTH;
    viewport.Height = SCREEN_HEIGHT;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;

    deviceContext->RSSetViewports(1, &viewport);
    ///////////////////////////////////////////////////////////////////
    //Vertex 설정
    //Vertex vertex = { 0, 0, 0 };

    //Polygon : 정점 3개가 합쳐져서 이루는 삼각형
    //정점의 순서에 따라서 시계방향이 앞면을 가진다.

    vertices.emplace_back(+0.5f, +0.5f);    
    vertices.emplace_back(+0.5f, -0.5f);
    vertices.emplace_back(-0.5f, +0.5f);
    vertices.emplace_back(-0.5f, -0.5f);


    //vertices.emplace_back(-0.5f, +0.5f);
    //vertices.emplace_back(+0.5f, -0.5f);
    //vertices.emplace_back(-0.5f, -0.5f);
    
    //vertices.emplace_back(-0.5f, -0.5f);

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(Vertex) * vertices.size();
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    //initData.pSysMem = &vertices[0];
    initData.pSysMem = vertices.data();

    device->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);
}

void Render()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView, clearColor);

    //Render();
    UINT offset = 0;
    UINT stride = sizeof(Vertex);//정점 하나의 크기

    deviceContext->IASetInputLayout(inputLayout);
    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    //deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    //deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    //deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    deviceContext->VSSetShader(vertexShader, nullptr, 0);
    deviceContext->PSSetShader(pixelShader, nullptr, 0);

    deviceContext->Draw(vertices.size(), 0);

    swapChain->Present(0, 0);
}

void Release()
{
    device->Release();
    deviceContext->Release();

    swapChain->Release();
    renderTargetView->Release();
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI2504));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPI2504);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   WCHAR title[] = L"내 게임";

   RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
   AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

   hWnd = CreateWindowW(szWindowClass, title, WS_OVERLAPPEDWINDOW,
       100, 100,//시작 위치
       rect.right - rect.left,
       rect.bottom - rect.top,//창 크기
       nullptr, nullptr, hInstance, nullptr);

   SetMenu(hWnd, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_MOUSEMOVE:
	{
		mousePos.x = (float)LOWORD(lParam);
		mousePos.y = (float)HIWORD(lParam);
	}
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);            

            EndPaint(hWnd, &ps);
        }
        break;	
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
