#include "Components/PongGame.h"



int main(int argc, char* argv[])
{
    
// #pragma region lab1
//     auto game = Game(L"Framework", 1280, 720);
//     
//     std::vector<DirectX::XMFLOAT4> points = {
//         DirectX::XMFLOAT4(0.5f, 0.5f, 0, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
//         DirectX::XMFLOAT4(-0.5f, -0.5f, 0, 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
//         DirectX::XMFLOAT4(-0.5f, 0.5f, 0, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
//         DirectX::XMFLOAT4(0.5f, -0.5f, 0, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
//     };
//     std::vector<int> indices = {0, 1, 2, 0, 1, 3};
//     
//     game.components_.push_back(new BaseComponent(&game, points, indices));
// #pragma endregion lab1

    
#pragma region lab2
    auto game = PongGame();
#pragma endregion lab2


    game.Run();
    return 0;
}
