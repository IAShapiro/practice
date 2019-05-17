#pragma once
#include <string>
#include <vector>
#include <algorithm>

struct Event
{
	std::string name;
	int residue;
	int capacity;
	std::string data_time;
	int n_of_booking;
};

class concert {
	std::vector<Event> array_;

public:
	concert() = default;

	concert(const int l);

	virtual ~concert() = default;

	concert(concert const& source);

	concert(concert&& source);

	Event& operator[] (const int l);

	void book(const int l);

	friend std::ostream& operator<< (std::ostream &out, const concert &obj);

	friend std::istream& operator>> (std::istream & in, concert &obj);

	static bool cmp_data(Event &a, Event &b);

	static bool cmp_name(Event &a, Event &b);

	void sort_data();

	void sort_name();

	int get_size() const;

	std::vector<Event>::iterator begin();

	std::vector<Event>::iterator end();
};