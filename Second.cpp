#include "Second.h"


Second::Second(std::string s, bool t) : Base(s, t) {};

Second::Second(const Base * b) : Base(b){};

std::string Second::sortCMYK()
{
	if (shelf.length() < 6)
		return lessThanSixSort();

	std::string text(shelf);
	int quads = make_quads(text);
	if (quads == 0)
		return text;
	if (text.length() == 6)
		return sortLastSix(text, "CMYK");
	for (int i = 0; i < quads; ++i)
	{
		move(text, 0);
		std::string prefix = text.substr(text.length() - 6, 2) + "CMYK";
		text = sortLastSix(text, prefix);
	}
	while (text.substr(0, 4) != "CMYK")
		move(text, 0);
	if(trace)
		moves_history.push_back(text);
	return text;
}

int Second::make_quads(std::string &text)
{
	std::vector<int> counter(4, 0);
	for (unsigned i = 0; i < text.size(); ++i)
		++counter[ORDER.find(text[i])];
	int quads = *std::min_element(counter.begin(), counter.end());
	if (text.length() == 6)
		return quads;
	
	std::set<char> prev(ORDER.begin(), ORDER.end());
	prev.erase(text[0]);
	bool rearranged = false;
	int pos = 1;
	while(pos < quads*4)
	{
		if (pos == int(text.length()) - 6)
		{
			arrangeTip(text, prev, pos, quads);
			break;
		}
		if (prev.find(text[pos]) == prev.end())
		{
			if ((text.length() - pos) % 2 == 0 && !rearranged)
			{
				arrangeNextFours(text, pos, prev);
				rearranged = true;
			}
			else
				move(text, pos);
			continue;
		}
		prev.erase(text[pos]);
		pos += 1;
		rearranged = false;
		if (pos % 4 == 0)
			prev = std::set<char>(ORDER.begin(), ORDER.end());
	}
	return quads;
}

void Second::arrangeTip(std::string &text, std::set<char> &prev, int pos, int quads)
{
	std::string prefix;
	for (unsigned i = 0; i < ORDER.length(); ++i)
		if (prev.find(ORDER[i]) != prev.end())
			prefix += ORDER[i];
	if (quads * 4 > pos + int(prefix.length()))
		prefix += "CMYK";
	text = sortLastSix(text, prefix);
}

bool Second::findOneElement(std::set<char> &prev, std::vector<char> &list)
{
	for (auto it = list.begin(); it != list.end(); ++it)
		if (prev.find(*it) != prev.end())
			return true;
	return false;
}

void Second::arrangeNextFours(std::string &text, int pos, std::set<char> prev)
{
	std::vector<char> every_next_4;
	for (unsigned i = 1; i < (text.length() - pos) / 4; ++i)
		every_next_4.push_back(text[pos + i * 4]);
	while (!findOneElement(prev, every_next_4))
	{
		move(text, pos + 1);
		every_next_4.clear();
		for (unsigned i = 1; i < (text.length() - pos) / 4; ++i)
			every_next_4.push_back(text[pos + i * 4]);
	}
}