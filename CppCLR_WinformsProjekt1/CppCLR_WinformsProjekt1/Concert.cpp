#include "stdafx.h"
#include "Concert.h"
#include <string>
#include <iomanip>

concert::concert(const int l)
{
	if (l < 0)
	{
		throw std::invalid_argument("Error! Size < 0. Default dimensions(0) are set\n");
	}
	array_.reserve(l);
}

concert::concert(concert const& source) {
	std::vector<Event> array(source.array_.capacity());
	array = source.array_;
}

concert::concert(concert&& source) {
	array_ = source.array_;
	source.array_.clear();
}

Event& concert::operator[] (const int l)
{
	if (l < 0 || static_cast<int>(this->array_.size()) <= l)
	{
		throw std::out_of_range("Error! Invalid index\n");
	}
	return this->array_[l];
}

void concert::book(const int l)
{
	if (l < 1 || l > static_cast<int>(this->array_.size()))
	{
		throw std::out_of_range("Error! Incorrect number of concert\n");
	}

	if (this->array_[l - 1].residue == 0)
	{
		throw std::exception("No tickets avilable\n");
	}
	this->array_[l - 1].n_of_booking++;
	this->array_[l - 1].residue--;
}

std::ostream& operator<< (std::ostream &out, const concert &obj)
{
	for (int i = 0; i < static_cast<int>(obj.array_.size()); i++)
	{
		out << i + 1 << ") " << std::setw(20) << std::left << obj.array_[i].name << " " << std::setw(7) <<
			std::right << obj.array_[i].residue << "/" << std::setw(7) << std::left <<
			obj.array_[i].capacity << " " << obj.array_[i].data_time << std::endl;
	}

	out << std::endl;

	return out;
}

std::istream& operator>> (std::istream & in, concert &obj)
{
	Event temp;
	std::string buffer;

	getline(in, temp.name, ';');
	getline(in, buffer, ';');
	temp.capacity = std::stoi(buffer);
	buffer.clear();
	getline(in, buffer, ';');
	temp.residue = std::stoi(buffer);
	buffer.clear();
	getline(in, buffer, '\n');
	temp.data_time = buffer;
	temp.n_of_booking = 0;
	obj.array_.push_back(temp);

	return in;
}

bool concert::cmp_data(Event &a, Event &b)
{
	return (a.data_time < b.data_time);
}

bool concert::cmp_name(Event &a, Event &b)
{
	return (a.name < b.name);
}

void concert::sort_data()
{
	std::sort(array_.begin(), array_.end(), cmp_data);
}

void concert::sort_name()
{
	std::sort(array_.begin(), array_.end(), cmp_name);
}

int concert::get_size() const
{
	return this->array_.size();
}

std::vector<Event>::iterator concert::begin()
{
	return array_.begin();
}

std::vector<Event>::iterator concert::end()
{
	return array_.end();
}
