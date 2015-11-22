#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

template <typename T, typename comparator = less<T> > //+ comparator <less<T>
class interval_set {
public:
	interval_set(){};
	interval_set(const interval_set& copySet) : my_set(copySet.my_set){};
	interval_set(set< pair<T, T> > copySet) {
		this->my_set = copySet;
		if (this->size() > 1)
			this->merge();
	}
	int size(){
		return my_set.size();
	}
	bool empty(){
		return (this->size() == 0) ? true: false;
	}
	void merge(){
		auto s = my_set.begin();
		s++;
		auto f = my_set.end();
		while (s != f) {
			auto s_0 = s;
			s_0--;
			if (s != my_set.begin() && !compare((s_0)->first, s->first) && !compare(s->first, s_0->first)) {
				my_set.erase(s_0);
			}
			if (s != my_set.begin() && !compare((s_0)->second, s->second)) { //s->second <= s_0->second
				auto temp = s_0;
				my_set.erase(s);
				s = temp;
			}
			if (s != my_set.begin() && !compare(s_0->second + 1, s->first)) {
				auto temp = s_0;
				my_set.insert({ (s_0)->first, (s)->second });
				temp++;
				my_set.erase(s);
				my_set.erase(s_0);
				s = temp;
			}

			s++;
		}
	}
	void insert(const pair<T, T>& elem){
		my_set.insert(elem);
		if (this->size() > 1)
			this->merge();
	}
	void insert(const pair<T, T>&& elem){
		my_set.insert(std::move(elem));
		if (this->size() > 1)
			this->merge();
	}
	typename std::set<pair <T,T> >::iterator begin(){
		return my_set.begin();
	}
	typename std::set<pair <T, T> >::iterator end(){
		return my_set.end();
	}
	void erase(pair<T, T> elem){
		auto s = my_set.begin();
		auto f = my_set.end();
		while (s != f) {
			if (s != f && compare(elem.first, s->first) && compare(s->second, elem.second)) {
				T a = s->first;
				T b = s->second;
				my_set.erase(s);
				this->erase(make_pair(elem.first, a - 1));
				this->erase(make_pair(b + 1, elem.second));
				s = f;
				s--;
			}
			if (s != f && !compare(elem.first, s->first) && !compare(s->second, elem.first) && compare(s->second, elem.second)) {
				if (!compare(elem.first - 1, s->first)) my_set.insert({ s->first, elem.first - 1 });
				elem.first = s->second + 1;
				T a = s->first;
				T b = s->second;
				my_set.erase(s);
				this->erase(make_pair(b + 1, elem.second));
				s = f;
				s--;
			}
			if (s != f && compare(elem.first, s->first) && !compare(s->second, elem.second) && !compare(elem.second, s->first)) {
				if (!compare(s->second, elem.second + 1)) my_set.insert({ elem.second + 1, s->second});
				my_set.erase(s);
				s = f;
				s--;
			}
			if (s != f && !compare(elem.first, s->first) && !compare(s->second, elem.second)) {
				if (!compare(elem.first - 1, s->first)) my_set.insert({ s->first, elem.first - 1 });
				my_set.insert({ elem.second + 1, s->second });
				my_set.erase(s);
				s = f;
				s--;
			}

			s++;
		}
	}
	void clear(){
		my_set.clear();
	}
	const set < pair<T, T> > get_interval_set() const {
		return this->my_set;
	}
	interval_set operator = (const interval_set& setSecond) {
		this->clear();
		set< pair <T, T> > temp = setSecond.get_interval_set();
		my_set = temp;
		return this->my_set;
	}
	bool find(pair<T, T> elem){ 
		auto s = my_set.begin();
		auto f = my_set.end();
		while (s != f) {
			if (!compare(elem.first, s->first) && !compare(s->second, elem.second)) {
				return true;
			}
			s++;
		}
		return false;
	}
	
	~interval_set(){};
private:
	set< pair<T, T> > my_set;
	comparator compare; //compare(a,b) return true if a < b
};

pair<int, int> increase(pair<int, int> x) {
	cout << x.first;
	return x;
}

int main() {
	set <pair <int, int> > test{ { 1, 2 }, { 1, 4 } };
	interval_set<int> nes(test);
	nes.insert(make_pair(3, 4));
	nes.insert({ 2, 5 });
	nes.insert({ 3, 3 });
	nes.insert({ 2, 7 });
	nes.insert({ 8, 10 });
	nes.insert({ 11, 12 });
	nes.insert({ 14, 16 });
	nes.insert({ 17, 17 });
	nes.insert({ 20, 21 });
	nes.insert({ 3, 5 });
	//nes.erase({ 1, 4 });
	//nes.erase({ 7, 25 });
	interval_set<int> nes2(test);
	//cout << nes.find({ 5, 6 });
	for_each(nes.begin(), nes.end(), [](pair<int, int> x){cout << x.first << " " << x.second << endl; });
	cout << count_if(nes.begin(), nes.end(), [](pair<int, int> x){return (x.second - x.first <= 3); });
	//transform(nes.begin(), nes.end(), nes2.begin(), increase); //there is no operator = for pair
	return 0;
}