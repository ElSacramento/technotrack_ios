#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <iterator>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/foreach.hpp>
#include <typeinfo>
using namespace std;

template <typename T> 
class mySet {
	set<T> someSet;
public:
	mySet(){};
	mySet(const mySet& copySet) {
		someSet = copySet.someSet;
		//mySet<T> temp = (copySet);
		//this->someSet = const_cast< mySet<T>& >(copySet.getSet());
	}
	mySet(set<T> copySet) {
		this->addSet(copySet);
	}

	void add(T element) {
		(this->someSet).insert(element);
	}
	void addSet(set<T> copySet) {
		auto it = copySet.begin();
		while (it != copySet.end()) {
			this->someSet.insert(*it);
			it++;
		}
	}

	set <T> getSet () {
		return this->someSet;
	}
	
	mySet operator = (mySet& setSecond) {
		this->someSet.clear();
		set<T> temp = setSecond.getSet();
		this->addSet(temp);
		return this->someSet;
	}
	mySet operator - (mySet& setSecond){ 
		set<T> temp = setSecond.getSet();
		for (auto it = temp.begin(); it != temp.end(); ++it) {
			auto it2 = (this->someSet).find(*it);
			if (it2 != this->someSet.end())
				this->someSet.erase(it2);
		}
		return this->someSet;
	}
	mySet operator + (mySet& setSecond){
		set<T> temp = setSecond.getSet();
		this->addSet(temp);
		return this->someSet;
	}
	mySet setsIntersection(mySet& setSecond){
		set<T> result;
		set<T> temp = setSecond.getSet();
		auto it = temp.begin();
		while (it != temp.end()) {
			auto it2 = (this->someSet).find(*it);
			if (it2 != (this->someSet).end())
				result.insert(*it2);
			it++;
		}
		mySet res(result);
		return res;
	}
	void showSet() {
		for (auto it = this->someSet.begin(); it != this->someSet.end(); it++)
			cout << *it << " ";
		cout << endl;
	}

	~mySet(){};
};

int main() {
	string st;
	getline(cin,st);
	auto it = st.begin();
	int i = 0;
	while (it != st.end() && *it != '+' && *it != '-' && *it != '&') {
		it++;
		i++;
	}
	string firstSet = st.substr(1, i - 2);
	string secondSet = st.substr(i + 2, st.length() - i - 3);
	vector<string> v1;
	vector<string> v2;	
	boost::split(v1, firstSet, boost::is_any_of(" "));
	boost::split(v2, secondSet, boost::is_any_of(" "));
	set<string> set1 (v1.begin(), v1.end());
	set<string> set2 (v2.begin(), v2.end());
	mySet<string> setFirst (set1);
	mySet<string> setSecond(set2);
	mySet<string> setResult = setFirst;
	if (*it == '+')
		setResult = setFirst + setSecond;
	if (*it == '-')
		setResult = setFirst - setSecond;
	if (*it == '&')
		setResult = setFirst.setsIntersection(setSecond);
	return 0;
}