#include <memory>
#include <iostream>

#include "splitlaptimer.hh"

std::ostream& operator<<(std::ostream& os, const SplitLapTimer& t)
{
	const laps_t laps = t.get_laps_time();

	os << t.name_ << ":";

	for (auto lap: laps) {
		os << " ";
		os << lap.count();
	}

	lap_t average = t.get_average_lap_time(laps);

	os << " <" << average.count() << ">";

	return os;
}

void
SplitLapTimer::start(std::string name)
{

	name_ = std::move(name);

	insert_split(STOPWATCH_START);
}

void
SplitLapTimer::stop()
{

	insert_split(STOPWATCH_STOP);
}

void
SplitLapTimer::split()
{

	insert_split(STOPWATCH_SPLIT);
}

void
SplitLapTimer::reset()
{
	splits_.clear();
	name_.clear();
}

split_point_t
SplitLapTimer::get_split_point()
{

	return std::chrono::high_resolution_clock::now();
}

void
SplitLapTimer::insert_split(stopwatch_mark_t m)
{
	bool cond;

#if 0
	switch (m) {
	case STOPWATCH_START:
		cond = !splits_.empty();
		break;
	case STOPWATCH_STOP:
	case STOPWATCH_SPLIT:
		cond = splits_.empty();
		break;
	}

	if (cond)
		throw std::runtime_error("assertion failure on insert");
#endif

	splits_.push_back(make_tuple(m, get_split_point()));
}

laps_t
SplitLapTimer::get_laps_time() const
{
	laps_t laps;
	split_point_t p;

	for (auto &split : splits_) {
		stopwatch_mark_t mark;
		split_point_t point;

		std::tie(mark, point) = split;

		switch (mark) {
		case STOPWATCH_START:
			break;
		case STOPWATCH_SPLIT:
		case STOPWATCH_STOP:
			laps.push_back(std::chrono::duration_cast<std::chrono::microseconds>(point - p));
			break;
		}

		p = std::move(point);
	}

	return laps;
}

lap_t
SplitLapTimer::get_average_lap_time(const laps_t &laps) const
{
	lap_t ret(0);

	for (auto lap : laps)
		ret += lap;

	ret /= laps.size();

	return ret;
}

lap_t
SplitLapTimer::get_average_lap_time() const
{
	const laps_t laps = get_laps_time();

	return get_average_lap_time(laps);
}
