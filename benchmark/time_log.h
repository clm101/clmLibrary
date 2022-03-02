#ifndef TIME_LOG_H
#define TIME_LOG_H

#include <chrono>
#include <iostream>
#include <format>
#include <vector>

namespace clm::bench {
	using timestamp_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

	class time_log {
		using time_delta_t = std::chrono::duration<double>;
	public:
		time_log() noexcept = default;
		~time_log() noexcept = default;

		void insert_delta(time_delta_t delta)
		{
			deltas.push_back(delta);
		}

		void print()
		{
			for (const auto& delta : deltas)
			{
				std::cout << std::format("Time delta:\t{}\n", delta);
			}
		}

		void clear() noexcept
		{
			deltas.clear();
		}
	private:
		std::vector<time_delta_t> deltas;
	};
}

#endif