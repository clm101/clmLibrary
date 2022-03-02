#ifndef TIME_BENCH_H
#define TIME_BENCH_H

#include <chrono>

#include "time_log.h"

namespace clm::bench {
	class time_bench {
	public:
		time_bench() = delete;
		time_bench(time_log& log) noexcept
			:
			m_log(log)
		{
			m_start = std::chrono::high_resolution_clock::now();
		}
		~time_bench()
		{
			timestamp_t end = std::chrono::high_resolution_clock::now();
			m_log.insert_delta(end - m_start);
		}
	private:
		timestamp_t m_start;
		time_log& m_log;
	};
}

#endif