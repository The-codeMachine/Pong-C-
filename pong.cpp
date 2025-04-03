#include <windows.h>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

struct Ball {
    int x, y, dx, dy;
};

struct Paddle {
    int x, y, width, height;
};

// Global variables for paddle and ball
Ball ball = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 3, 3 };
Paddle playerPaddle = { 30, WINDOW_HEIGHT / 2 - 50, 10, 100 };
Paddle aiPaddle = { WINDOW_WIDTH - 40, WINDOW_HEIGHT / 2 - 50, 10, 100 };

bool upArrow = false, downArrow = false;

void Update() {
    // Move the ball
    ball.x += ball.dx;
    ball.y += ball.dy;

    // Ball collision with top and bottom
    if (ball.y <= 0 || ball.y >= WINDOW_HEIGHT) {
        ball.dy = -ball.dy;
    }

    // Ball collision with paddles
    if ((ball.x <= playerPaddle.x + playerPaddle.width && ball.y >= playerPaddle.y && ball.y <= playerPaddle.y + playerPaddle.height) ||
        (ball.x >= aiPaddle.x - aiPaddle.width && ball.y >= aiPaddle.y && ball.y <= aiPaddle.y + aiPaddle.height)) {
        ball.dx = -ball.dx;
    }

    // Ball out of bounds (AI scores a point)
    if (ball.x <= 0 || ball.x >= WINDOW_WIDTH) {
        ball.x = WINDOW_WIDTH / 2;
        ball.y = WINDOW_HEIGHT / 2;
        ball.dx = -ball.dx;
    }

    // Move player paddle
    if (upArrow && playerPaddle.y > 0) {
        playerPaddle.y -= 6;
    }
    if (downArrow && playerPaddle.y < WINDOW_HEIGHT - playerPaddle.height) {
        playerPaddle.y += 6;
    }

    // Simple AI for the opposing paddle
    if (ball.y < aiPaddle.y) {
        aiPaddle.y -= 4;
    }
    if (ball.y > aiPaddle.y + aiPaddle.height) {
        aiPaddle.y += 4;
    }
}

void Draw(HWND hwnd, HDC hdc) {
    // Clear the screen
    RECT rect;
    GetClientRect(hwnd, &rect);
    FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

    // Draw paddles and ball
    Rectangle(hdc, playerPaddle.x, playerPaddle.y, playerPaddle.x + playerPaddle.width, playerPaddle.y + playerPaddle.height);
    Rectangle(hdc, aiPaddle.x, aiPaddle.y, aiPaddle.x + aiPaddle.width, aiPaddle.y + aiPaddle.height);
    Ellipse(hdc, ball.x - 10, ball.y - 10, ball.x + 10, ball.y + 10);
}

int main() {
    // Create window class
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"PongClass";
    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(0, L"PongClass", L"Pong Game", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL, NULL, wc.hInstance, NULL);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // Set a timer to call WM_TIMER every 16ms (about 60 FPS)
    SetTimer(hwnd, 1, 16, NULL);

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    switch (msg) {
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        Draw(hwnd, hdc);
        EndPaint(hwnd, &ps);
        break;
    case WM_KEYDOWN:
        if (wParam == VK_UP) upArrow = true;
        if (wParam == VK_DOWN) downArrow = true;
        break;
    case WM_KEYUP:
        if (wParam == VK_UP) upArrow = false;
        if (wParam == VK_DOWN) downArrow = false;
        break;
    case WM_TIMER:
        // Update game state and invalidate window to trigger repaint
        Update();
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case WM_DESTROY:
        KillTimer(hwnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
