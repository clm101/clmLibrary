#include <clmUtil/clm_err.h>

#include <format>

namespace clm::err {
	WindowsExceptionBase::WindowsExceptionBase(HRESULT hr, const std::source_location& loc) noexcept
		:
		slErrorLoc(loc)
	{
		char* ptrFormatMsg = nullptr;
		std::string strFmtMsg{};
		if (FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
						   nullptr, hr, LocaleNameToLCID(LOCALE_NAME_SYSTEM_DEFAULT, LOCALE_ALLOW_NEUTRAL_NAMES),
						   reinterpret_cast<LPSTR>(&ptrFormatMsg), 0, nullptr) == 0)
		{
			strFmtMsg = "Unidentified error code";
		}
		else
		{
			strFmtMsg = std::string{ptrFormatMsg};
			LocalFree(ptrFormatMsg);
		}
		strErrorMsg = std::format("Exception thrown\nIn: {}\nOn line: {}\nError message: {}\n", loc.function_name(), loc.line(), strFmtMsg);
	}

	WindowsException::WindowsException(const std::source_location& loc) noexcept
		:
		WindowsExceptionBase(GetLastError(), loc)
	{}

	VulkanException::VulkanException(std::string msg, std::source_location loc)
	{
		m_msg = std::format("Vulkan Exception:\nMsg: {}\nFile: {}\nFunction: {}\nLine: \n",
							msg,
							loc.file_name(),
							loc.function_name(),
							loc.line());
	}

	const char* VulkanException::what() const noexcept
	{
		return m_msg.c_str();
	}
}