#include <Windows.h>
#include <iostream>
#include <string>

// ��ȡ���ھ��
HWND GetWindowByTitle(const std::string& title) {
    return FindWindowA(nullptr, title.c_str());
}

// ��ȡ���ڴ�С
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

// ģ�������
void SimulateMouseClick(int x, int y) {
    // �ƶ���굽ָ��λ��
    SetCursorPos(x, y);

    // ģ������������
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

    // ģ���������ͷ�
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

// �л���Ŀ�괰��
bool SwitchToWindow(HWND hwnd) {
    if (!hwnd) {
        return false;
    }

    // �����
    return SetForegroundWindow(hwnd);
}

int main() {
    std::string targetWindowTitle = "���տ���Լ��";

    // ��ȡ���ھ��
    HWND hwnd = GetWindowByTitle(targetWindowTitle);
    if (!hwnd) {
        std::cout << "δ�ҵ�����: " << targetWindowTitle << "\n";
        return 1;
    }

    // �л���Ŀ�괰��
    if (!SwitchToWindow(hwnd)) {
        std::cout << "�޷��л�������: " << targetWindowTitle << "\n";
        return 1;
    }

    // ��ȡ���ڴ�С
    int width, height;
    if (!GetWindowSize(hwnd, width, height)) {
        std::cout << "�޷���ȡ���ڴ�С\n";
        return 1;
    }

    std::cout << "���ڴ�С: ���=" << width << ", �߶�=" << height << "\n";

    //�������޸ĵ����λ�ã����ձ����޸�
    // ����Ŀ����λ��
    int targetX = width / 5;
    int targetY = height / 2.05;

    // ������ת��Ϊ��Ļ����
    RECT rect;
    if (GetWindowRect(hwnd, &rect)) {
        targetX += rect.left;
        targetY += rect.top;

        // ģ�������
        SimulateMouseClick(targetX, targetY);

        std::cout << "�ѵ�����ڵ�Ŀ��λ��: (" << targetX << ", " << targetY << ")\n";
    }
    else {
        std::cout << "�޷���ȡ���ڵ���Ļ����\n";
    }

    return 0;
}
