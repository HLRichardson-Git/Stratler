
#include "engine/state/state.h"
#include "engine/pokemon/pokemon.h"
#include "util/table/table.h"

#include <iostream>

#include <string>

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>

// Data
static ID3D11Device*            g_pd3dDevice = nullptr;
static ID3D11DeviceContext*     g_pd3dDeviceContext = nullptr;
static IDXGISwapChain*          g_pSwapChain = nullptr;
static bool                     g_SwapChainOccluded = false;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView*  g_mainRenderTargetView = nullptr;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Stratler", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    int inputValues1[6] = { 100, 100, 100, 100, 100, 100 };
    int inputValues2[6] = { 100, 100, 100, 100, 100, 100 };
    int updatedValues[6] = { 0, 0, 0, 0, 0, 0 };
    int updatedValues2[6] = { 0, 0, 0, 0, 0, 0 };

    const std::string playerTeamPath = "../../data/player_teams/playerTeam.txt";
    const std::string opponentTeamPath = "../../data/player_teams/opponentTeam.txt";
    Team player(playerTeamPath);
    player.displayTeamInfo();
    Team opponent(opponentTeamPath);
    //opponent.displayTeamInfo();
    Game game(player, opponent);
    int selectedPlayerPokemonIndex = -1;
    int selectedOpponentPokemonIndex = -1;

     // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle window being minimized or screen locked
        if (g_SwapChainOccluded && g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
        {
            ::Sleep(10);
            continue;
        }
        g_SwapChainOccluded = false;

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Welcome to Stratler!"); // Create a window

            ImVec2 availableSize = ImGui::GetContentRegionAvail();
            float columnWidthFourth = availableSize.x / 4;
            float columnWidthHalf = availableSize.x / 2;

            // Set up two columns
            ImGui::Columns(3);

            ImGui::SetColumnWidth(0, columnWidthFourth);
            ImGui::SetColumnWidth(1, columnWidthFourth);
            ImGui::SetColumnWidth(2, columnWidthHalf);
            
            // First column: Text and Input
            for (int i = 0; i < TEAM_SIZE; i++) {
                std::string pokemonName = game.getPlayer().getPokemon(i).getName();
                ImGui::RadioButton(pokemonName.c_str(), &selectedPlayerPokemonIndex, i); // Set the radio button value based on index
                ImGui::SameLine();

                ImGui::Text("Health: %d", game.getPlayer().getPokemon(i).getStats().getHP());
                // Input box for integers (ImGui::InputInt expects integers)
                ImGui::SetNextItemWidth(columnWidthFourth - 15.0f);
                ImGui::InputInt(("##input1_" + std::to_string(i)).c_str(), &inputValues1[i]);
                if (inputValues1[i] < 0) inputValues1[i] = 0;
                else if (inputValues1[i] > 100) inputValues1[i] = 100;

                game.getPlayer().getPokemon(i).setPercentageHP(inputValues1[i]);
            }
            ImGui::NextColumn(); // Move to the second column

            // Second column: Text and Input
            for (int i = 0; i < TEAM_SIZE; i++) {
                std::string pokemonName = game.getOpponent().getPokemon(i).getName();
                ImGui::RadioButton(("Opponent " + pokemonName).c_str(), &selectedOpponentPokemonIndex, i); // Set the radio button value based on index
                ImGui::SameLine();  // Puts input box on the same line as the text
                ImGui::Text("Health: %d", game.getOpponent().getPokemon(i).getStats().getHP());
                // Input box for integers (ImGui::InputInt expects integers)
                ImGui::SetNextItemWidth(columnWidthFourth - 15.0f);
                ImGui::InputInt(("##input2_" + std::to_string(i)).c_str(), &inputValues2[i]);
                if (inputValues2[i] < 0) inputValues2[i] = 0;
                else if (inputValues2[i] > 100) inputValues2[i] = 100;

                //updatedValues2[i] = (inputValues2[i] * opponent.getPokemon(i).getMaxHP()) / 100;
                //opponent.getPokemon(i).setPercentageHP(inputValues2[i]);
                game.getOpponent().getPokemon(i).setPercentageHP(inputValues2[i]);
            }

            // End the columns
            ImGui::NextColumn();

            if (selectedPlayerPokemonIndex != -1 && selectedOpponentPokemonIndex != -1) {
                std::string playerPokemonName = player.getPokemon(selectedPlayerPokemonIndex).getName();
                std::string opponentPokemonName = opponent.getPokemon(selectedOpponentPokemonIndex).getName();
                ImGui::Text("%s vs. %s", playerPokemonName.c_str(), opponentPokemonName.c_str());

                game.setPlayerCurrentPokemonIndex(selectedPlayerPokemonIndex);
                game.setOpponentCurrentPokemonIndex(selectedOpponentPokemonIndex);
                std::vector<PokemonMoveRanking> rankings = game.evaluateBestMoves(true);
                for (size_t i = 0; i < TEAM_SIZE; i++) {
                    std::string movePokemonName = rankings[i].pokemon.getName();
                    std::string moveName = rankings[i].bestMove.move.getName();
                    int moveDamage = rankings[i].bestMove.damage;
                    int moveScore = rankings[i].score;
                    ImGui::Text("%s - Best Move: %s - Damage: %d - Score: %d", movePokemonName.c_str(), moveName.c_str(), moveDamage, moveScore);
                }
            }

            ImGui::End(); // End the window
        }

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // Present
        HRESULT hr = g_pSwapChain->Present(1, 0);   // Present with vsync
        //HRESULT hr = g_pSwapChain->Present(0, 0); // Present without vsync
        g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}