#pragma once

#include "Alisa/Core/Window.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Alisa
{
    class Win32Window final : public Window
    {
    public:
        Win32Window(const WindowProps& props);
        virtual ~Win32Window();

        void OnUpdate() override;

        uint32_t GetWidth() const override { return m_Data.Width; }
        uint32_t GetHeight() const override { return m_Data.Height; }

        void* GetNativeWindow() const override { return m_Window; }

        void SetEventCallback(const EventCallbackFn& callback) override;

    private:
        void Init(const WindowProps& props);
        void Shutdown();

    private:
        HWND m_Window = nullptr;
        HINSTANCE m_Instance = nullptr;

        struct WindowData
        {
            std::string     Title;
            uint32_t        Width;
            uint32_t        Height;
            EventCallbackFn EventCallback;
        };
        WindowData m_Data;

    private:
        friend LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    };
} // namespace Alisa
