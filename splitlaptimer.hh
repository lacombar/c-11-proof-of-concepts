#pragma once

#include <chrono>
#include <vector>
#include <tuple>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> split_point_t;

enum stopwatch_mark {
	STOPWATCH_START,
	STOPWATCH_SPLIT,
	STOPWATCH_STOP
};

typedef enum stopwatch_mark stopwatch_mark_t;

typedef std::tuple<stopwatch_mark_t, split_point_t> split_t;

typedef std::chrono::microseconds lap_t;

typedef std::vector<lap_t> laps_t;

class SplitLapTimer
{
	public:
		SplitLapTimer()
		{
		}

		void start(std::string s);
		void stop();
		void split();
		void reset();

		lap_t get_average_lap_time(const laps_t &) const;
		lap_t get_average_lap_time() const;
		laps_t get_laps_time() const;

		friend std::ostream& operator<<(std::ostream& os, const SplitLapTimer&);
	protected:
		std::string		name_;
	private:
		split_point_t get_split_point();
		void insert_split(stopwatch_mark_t);

		std::vector<split_t>	splits_;
};

std::ostream& operator<<(std::ostream& os, const SplitLapTimer& t);
