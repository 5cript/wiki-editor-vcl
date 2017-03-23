//---------------------------------------------------------------------------

#pragma hdrstop

#include "mini_timer.h"
#include "finally.h"
#include "debug.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
const std::chrono::high_resolution_clock::duration Timer::sleepTime = std::chrono::milliseconds{100};
//---------------------------------------------------------------------------
Timer::Timer(std::function <bool()> func)
	: func_{std::move(func)}
	, active_{false}
	, interval_{}
	, timerThread_{}
{
}
//---------------------------------------------------------------------------
Timer::~Timer()
{
	stop();
}
//---------------------------------------------------------------------------
void Timer::start(std::chrono::high_resolution_clock::duration const& interval, bool immediate)
{
    stop();

	interval_ = interval;
	active_.store(true);

	timerThread_ = std::thread([this, immediate]() {
		ON_SCOPE_EXIT(
			[this]() {
				active_.store(false);
			}
		);

		if (immediate)
			if (!func_())
				return;

		auto last = std::chrono::high_resolution_clock::now();
		while (active_.load())
		{
			auto now = std::chrono::high_resolution_clock::now();
			if (now - last >= interval_)
			{
				last = now;
				if (active_.load())
					if (!func_())
						break;
			}
			std::this_thread::sleep_for(sleepTime);
		}
		return;
	});
}
//---------------------------------------------------------------------------
void Timer::stop()
{
	active_.store(false);
	if (timerThread_.joinable())
		timerThread_.join();
}
//---------------------------------------------------------------------------
