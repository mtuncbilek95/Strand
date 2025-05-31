#include "DXDebug.h"

namespace Flax
{
    static WString GetErrorMessage(HRESULT hr)
    {
        LPWSTR errorText = nullptr;

        DWORD result = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPWSTR)&errorText, 0, nullptr);

        WString message = (result && errorText) ? errorText : L"Unknown error";
        if (errorText)
            LocalFree(errorText);

        return message;
    }

	void DXDebug::DXAssert(HRESULT hr, const String& target)
	{
        if (SUCCEEDED(hr))
            return;

        String msg = StringHelpers::WStringToString(GetErrorMessage(hr));

		Log::Error(LogType::GraphicsAPI, "DirectX error in {}: {}", target, msg);
	}
}
