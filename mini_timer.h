//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include <thread>
#include <string>
#include <cstdint>
#include <atomic>
#include <chrono>
#include <functional>
//---------------------------------------------------------------------------
class Timer
{
	public:
		Timer(std::function <bool()> func);
		~Timer();

		void start(std::chrono::high_resolution_clock::duration const& interval, bool immediate = false);
		void stop();

		// Disable all copy operations
		Timer& operator=(Timer const&) = delete;
		Timer(Timer const&) = delete;

	private:
		std::function <bool()> func_;
		std::atomic_bool active_;
		std::chrono::high_resolution_clock::duration interval_;
		std::thread timerThread_;

		const static std::chrono::high_resolution_clock::duration sleepTime;
};
//---------------------------------------------------------------------------

