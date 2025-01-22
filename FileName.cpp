#include <Windows.h>
#include <iostream>
#include <string>

// 获取窗口句柄
HWND GetWindowByTitle(const std::string& title) {
    return FindWindowA(nullptr, title.c_str());
}

// 获取窗口大小
bool GetWindowSize(HWND hwnd, int& width, int& height) {
    if (!hwnd) {
        return false;
    }

    RECT rect;
    if (GetWindowRect(hwnd, &rect)) {
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;
        return true;
    }
    return false;
}

// 模拟鼠标点击
void SimulateMouseClick(int x, int y) {
    // 移动鼠标到指定位置
    SetCursorPos(x, y);

    // 模拟鼠标左键按下
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

    // 模拟鼠标左键释放
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

// 切换到目标窗口
bool SwitchToWindow(HWND hwnd) {
    if (!hwnd) {
        return false;
    }

    // 激活窗口
    return SetForegroundWindow(hwnd);
}

int main() {
    std::string targetWindowTitle = "向日葵简约版";

    // 获取窗口句柄
    HWND hwnd = GetWindowByTitle(targetWindowTitle);
    if (!hwnd) {
        std::cout << "未找到窗口: " << targetWindowTitle << "\n";
        return 1;
    }

    // 切换到目标窗口
    if (!SwitchToWindow(hwnd)) {
        std::cout << "无法切换到窗口: " << targetWindowTitle << "\n";
        return 1;
    }

    // 获取窗口大小
    int width, height;
    if (!GetWindowSize(hwnd, width, height)) {
        std::cout << "无法获取窗口大小\n";
        return 1;
    }

    std::cout << "窗口大小: 宽度=" << width << ", 高度=" << height << "\n";

    //在这里修改点击的位置，按照比例修改
    // 计算目标点击位置
    int targetX = width / 5;
    int targetY = height / 2.05;

    // 将坐标转换为屏幕坐标
    RECT rect;
    if (GetWindowRect(hwnd, &rect)) {
        targetX += rect.left;
        targetY += rect.top;

        // 模拟鼠标点击
        SimulateMouseClick(targetX, targetY);

        std::cout << "已点击窗口的目标位置: (" << targetX << ", " << targetY << ")\n";
    }
    else {
        std::cout << "无法获取窗口的屏幕坐标\n";
    }

    return 0;
}
