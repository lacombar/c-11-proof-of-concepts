#include <chrono>
#include <memory>
#include <list>
#include <tuple>
#include <vector>
#include <iostream>

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
class Foo {
};

#define NTEST	20
#define NITER	10000000

int main(int argc, char *argv[])
{
	SplitLapTimer s;

	s.start("Direct std::unique_ptr");
	for (auto i = 0; i < NTEST; i++) {
		for (auto j = 0; j < NITER; j++) {
			std::unique_ptr<Foo> f(new Foo);
		}
		s.split();
	}

	std::cout << s << std::endl;
	s.reset();

	s.start("Indirect std::make_unique");
	for (auto i = 0; i < NTEST; i++) {
		for (auto j = 0; j < NITER; j++) {
			std::unique_ptr<Foo> f = std::make_unique<Foo>();
		}
		s.split();
	}

	std::cout << s << std::endl;
	s.reset();

	s.start("Direct std::shared_ptr");
	for (auto i = 0; i < NTEST; i++) {
		for (auto j = 0; j < NITER; j++) {
			std::shared_ptr<Foo> f(new Foo);
		}
		s.split();
	}

	std::cout << s << std::endl;
	s.reset();

	s.start("Indirect std::make_shared");
	for (auto i = 0; i < NTEST; i++) {
		for (auto j = 0; j < NITER; j++) {
			std::shared_ptr<Foo> f = std::make_shared<Foo>();
		}
		s.split();
	}

	std::cout << s << std::endl;

	return 0;
}
