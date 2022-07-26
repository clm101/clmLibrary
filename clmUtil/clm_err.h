#ifndef CLM_ERR_H
#define CLM_ERR_H

#include <exception>
#include <string>
#include <source_location>
#include <vector>
#include <format>

#include <clmUtil/clm_system.h>
#include <clmUtil/clm_util.h>

#ifdef GFX_REFAC
#include <vulkan/vulkan.hpp>
#undef assert
#else
#include <vulkan/vulkan.h>
#endif

namespace clm::err {
	template<typename T>
	concept Exception = requires(T t, std::string msg) { t = T{msg}; }&& std::derived_from<T, std::exception>;
	template<Exception E>
	void assert(bool condition, 
				std::string msg, 
				std::source_location location = std::source_location::current())
	{
#ifdef _DEBUG
		if (!condition)
		{
			throw E{std::format("{}\nFile: {}\nFunction: {}\nLine: {}",
								msg,
								location.file_name(),
								location.function_name(),
								location.line())};
		}
#endif
	}

	class WindowsExceptionBase : public std::exception {
	public:
		WindowsExceptionBase() = default;
		WindowsExceptionBase(HRESULT, const std::source_location&) noexcept;
		~WindowsExceptionBase() = default;

		const char* what() const noexcept override
		{
			return strErrorMsg.c_str();
		}
		const std::string& get_error_msg() const noexcept { return strErrorMsg; }
		const std::source_location& get_error_loc() const noexcept { return slErrorLoc; }
	private:
		std::string strErrorMsg;
		const std::source_location slErrorLoc;
	};

	class WindowsException : public WindowsExceptionBase {
	public:
		WindowsException(const std::source_location&) noexcept;
		~WindowsException() noexcept = default;
	};

	class VulkanException : public std::exception {
	public:
		VulkanException(std::string, std::source_location = std::source_location::current());

		const char* what() const noexcept override;
	private:
		std::string m_msg;
	};

	template<class T>
	concept ValidWindowsException = requires{
		T{std::source_location::current()};
	};
	template<class T>
	concept ValidGraphicsException = requires{
		T{HRESULT{}, std::vector<std::string>{}, std::source_location::current()};
	};

	template<ValidWindowsException T>
	void check_nullptr(void* ptr, const std::source_location& loc = std::source_location::current())
	{
		if (ptr == nullptr)
		{
			throw T{loc};
		}
	}

	template<ValidWindowsException T>
	void check_hmodule(HMODULE hmod, const std::source_location& loc = std::source_location::current())
	{
		if (hmod == NULL)
		{
			throw T{loc};
		}
	}

	template<ValidWindowsException T>
	void check_ret_val(ATOM ret, const std::source_location& loc = std::source_location::current())
	{
		if (ret == static_cast<ATOM>(0))
		{
			throw T{loc};
		}
	}

	template<ValidWindowsException T>
	void check_ret_val(HRESULT hr, const std::source_location& loc = std::source_location::current())
	{
		if (hr != S_OK)
		{
			throw T{loc};
		}
	}

	template<ValidGraphicsException T>
	void check_ret_val(HRESULT hr, const std::vector<std::string>& vstrMsgs, const std::source_location& loc = std::source_location::current())
	{
		if (hr != S_OK)
		{
			throw T{hr, vstrMsgs, loc};
		}
	}

	void inline check_ret_val(VkResult result, std::string errorMsg = "no message", std::source_location loc = std::source_location::current() )
	{
		if (result != VK_SUCCESS)
		{
			//std::string errorMsg = std::format("Exception thrown\nFile: {}\nFunction: {}\nLine: {}", loc.file_name(), loc.function_name(), loc.line());
			throw VulkanException{errorMsg, loc};
		}
	}

	class EmptyQueueException : public std::exception {
	public:
		EmptyQueueException(const std::source_location& loc) noexcept;
		const char* what() const noexcept override;
	private:
		std::source_location exceptionLoc;
		std::string strMsg;
	};
}

#endif