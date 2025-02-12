#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <stdlib.h>
#include <cmath>
#include <sstream>
using namespace std;
#define WORD 32								// for 32 bits in a uint32_t type
#define PRIME 32494189635056477				// long prime number required for hash functions
typedef unsigned long long int ullong_t;	// alias for type



/*
[Class Methods]
Class bit_vector:
	default constructor: initialises empty array of 0s of given size;
	parameterized constructor: initialises empty array of 0s of size _bit_size;
	copy constructor: Makes a deep copy of a previous bit_vector of same size;
	set(bit_pos, bit_val): sets bit to bit_val at position bit_pos;
	reset(): resets all bits to 0;
	flip(): flips all bits;
	test(i): returns value at index i;
	operator[i]: returns value at index i (works only for rvalue);
	size(): returns length of bit vector;
	count(): returns number of 1s in the vector;
	any(): checks if atleast 1 bit is set to 1;
	none(): checks if none of the bits are set to 1;
	all(): checks if all of the bits are set to 1;
	friend ostream operator<<: displays bit vector;
*/

template<ullong_t bit_size>
class bit_vector;

template<ullong_t bit_size>
ostream& operator<<(ostream &output, bit_vector<bit_size>& b);

template<typename T>
class bloom_filter;

template<typename T>
ostream& operator<<(ostream& output, bloom_filter<T>& bf);

template<ullong_t bit_size = 0>
class bit_vector{
	private:
	ullong_t _bit_size;			// Total number of bits in the array
	ullong_t _array_size;		// Number of 32 bit WORDS in the array [ONLY FOR INTERNAL USE]
	uint32_t* _bit_array;		// The actual array of 32 bit words

	// Internal helper functions
	ullong_t array_index(ullong_t bit_pos){
		return bit_pos / WORD;
	}

	ullong_t array_offset(ullong_t bit_pos){
		return bit_pos % WORD;
	}

	public:
	// Constructors and destructors
	bit_vector() : _bit_size(bit_size) {
		_array_size = _bit_size / WORD + 1;
		_bit_array = new uint32_t[_array_size];
		for(int i = 0; i < _array_size; ++i){
			_bit_array[i] = 0;
		}
	}

	bit_vector(ullong_t _bit_size) : _bit_size(_bit_size){
		_array_size = _bit_size / WORD + 1;
		_bit_array = new uint32_t[_array_size];
		for(int i = 0; i < _array_size; ++i){
			_bit_array[i] = 0;
		}
	}

	bit_vector(bit_vector<bit_size>& b){
		this -> _bit_size = b._bit_size;
		this -> _array_size = b._array_size;
		this -> _bit_array = new uint32_t[this -> _array_size];
		for(int i = 0; i < this -> _bit_size; ++i){
			this -> set(i, b.test(i));
		}
	}

	~bit_vector(){
		delete[] _bit_array;
	}

	// Bit operation functions
	bool set(ullong_t bit_pos, bool bit_val){
		if(bit_pos >= _bit_size){
			return false;
		}

		ullong_t bit_index = array_index(bit_pos);
		ullong_t bit_offset = array_offset(bit_pos);
		if(bit_val){
			_bit_array[bit_index] |= (1 << (WORD - bit_offset - 1));
		}
		else{
			_bit_array[bit_index] &= ~(1 << (WORD - bit_offset - 1));
		}
		return true;
	}

	void reset(){
		for(ullong_t i = 0; i < this -> _bit_size; ++i){
			this -> set(i, 0);
		}
	}

	void flip(){
		for(ullong_t i = 0; i < this -> _bit_size; ++i){
			if(this -> test(i) == true){
				this -> set(i, false);
			}
			else{
				this -> set(i, true);
			}
		}
	}

	// Bit access functions
	bool test(ullong_t bit_pos){
		if(bit_pos >= _bit_size){
			return false;
		}
		ullong_t bit_index = array_index(bit_pos);
		ullong_t bit_offset = array_offset(bit_pos);
		return _bit_array[bit_index] & (1 << (WORD - bit_offset - 1));
	}

	bool operator[] (ullong_t bit_pos){
		return this -> test(bit_pos);
	}

	ullong_t size(){
		return this -> _bit_size;
	}

	ullong_t count(){
		ullong_t _count = 0;
		for(ullong_t i = 0; i < this -> _bit_size; ++i){
			if(this -> test(i) == true){
				++_count;
			}
		}
		return _count;
	}

	bool any(){
		for(ullong_t i = 0; i < this -> _bit_size; ++i){
			if(this -> test(i) == true){
				return true;
			}
		}
		return false;
	}

	bool none(){
		if(this -> any() == false){
			return true;
		}
		else{
			return false;
		}
	}

	bool all(){
		for(ullong_t i = 0; i < this -> _bit_size; ++i){
			if(this -> test(i) == false){
				return false;
			}
		}
		return true;
	}

	// friend functions
	friend ostream& operator<<<bit_size>(ostream &output, bit_vector<bit_size>& b);
};

// operator overloaded friend function for bit vector
template<ullong_t bit_size>
ostream& operator<<(ostream &output, bit_vector<bit_size>& b){
	uint32_t compare = (1 << (WORD - 1));
	// printing all but last element of bit array
	ullong_t i = 0;
	for(i = 0; i < b._array_size - 1; ++i){
		uint32_t temp = b._bit_array[i];
		for(int j = 0; j < WORD; ++j){
			output << ((temp & compare) ? 1 : 0) << " ";
			temp = temp << 1;
		}
	}
	// printing last element of the bit array
	uint32_t temp = b._bit_array[i];
	ullong_t max_offset = b._bit_size % WORD;
	for(int j = 0; j < max_offset; ++j){
		output << ((temp & compare) ? 1 : 0) << " ";
		temp = temp << 1;
	}
	return output;
}


enum Month {
	Jan = 1,
	Feb,
	Mar,
	Apr,
	May,
	Jun,
	Jul,
	Aug,
	Sep,
	Oct,
	Nov,
	Dec
};


class Date{
	private:
		int day_;
		Month month_;
		int year_;
		int hour_;
		int minute_;
		int second_;
		// int num_days_[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	public:
		Date(int day, Month month, int year, int hour = 0, int minute = 0, int second = 0) : day_(day), month_(month), year_(year), hour_(hour), minute_(minute), second_(second) {
		}
		ullong_t timestamp(){
			ullong_t temp = 0;
			temp += ((day_ - 1) * 86400);
			temp += ((month_ - 1) * 86400 * 30);
			temp += ((year_ - 1970) * 86400 * 365);
			temp += ((hour_) * 3600);
			temp += ((minute_) * 60);
			temp += ((second_));
			return temp;
		}
		int get_day(){
			return day_;
		}
		int get_month(){
			return month_;
		}
		int get_year(){
			return year_;
		}
		int get_hour(){
			return hour_;
		}
		int get_minute(){
			return minute_;
		}
		int get_second(){
			return second_;
		}
		void set_day(int day){
			day_ = day;
		}
		void set_month(Month month){
			month_ = month;
		}
		void set_year(int year){
			year_ = year;
		}
		void set_hour(int hour){
			hour_ = hour;
		}
		void set_minute(int minute){
			minute_ = minute;
		}
		void set_second(int second){
			second_ = second;
		}
		friend ostream& operator<<(ostream& output, Date &date);
};


ostream& operator<<(ostream& output, Date &date){
	output << date.day_ << "-" << date.month_ << "-" << date.year_ << ", " << date.hour_ << ":" << date.minute_ << ":" << date.second_;
	return output;
}




/*
[Class Methods]
Class Hasher:
	static methods:
	hash(string value, int seed): hashes a string and returns ullong_t;
	hash(int value, int seed): hashes an int and returns ullong_t;
	hash(ullong_t value, int seed): hashes a ullong_t and returns ullong_t;
	hash(long double value, int seed): hashes a double and returns ullong_t;
*/

class hasher{
	public:
		static ullong_t hash(string value, int seed){
			ullong_t hashed_value = 1;
			long long int temp = 1;
			for(int i = 0; i < value.size(); ++i){
				temp = (temp * 53) % PRIME;
				hashed_value = (hashed_value + (temp * (int)value[i] + 47 * seed)) % PRIME;
			}
			return hashed_value;
		}
		static ullong_t hash(int value, int seed){
			ullong_t hashed_value = 1;
			hashed_value = (53 * value + 47 * seed) % PRIME;
			return hashed_value;
		}
		static ullong_t hash(ullong_t value, int seed){
			ullong_t hashed_value = 1;
			hashed_value = (53 * value + 47 * seed) % PRIME;
			return hashed_value;
		}
		static ullong_t hash(long double value, int seed){
			ostringstream strs;
			strs << value;
			string str = strs.str();
			return hash(str, seed);
		}
		static ullong_t hash(Date date, int seed){
			// cout << date << " " << seed << " " << hash(date.timestamp(), seed) << endl;
			return hash(date.timestamp(), seed);
		}
};




/*
[Class Methods]
Class bloom_filter:
	parameterized constructor 1: simple init method from parameters _false_positive_rate and _expected_num_elements;
	parameterized constructor 2: another init method from _num_hash_fn, _bit_array_size, _expected_num_elements;
	copy constructor: Makes a deep copy of a previous bloom_filter of same size;
	insert(): insert hashed value k number of times after each hash function with seed;
	check(): checks and returns true/false;
	get_false_positive_rate(): returns false probability percentage calculated from the # of inserted elements;
	get_num_hash_fn(): returns number of hash functions used;
	get_bit_array_size(): returns size of bit array;
	get_expected_num_elements(): returns the expected number of elements to be inserted;
*/

template<typename T>
class bloom_filter{
	private:
		long double _false_positive_rate;	// false positivity rate
		int _num_hash_fn;					// number of hash functions (also works as seed)
		ullong_t _bit_array_size;			// size of bit array required
		ullong_t _expected_num_elements;	// expected number of elements to insert
		bit_vector<>* _bit_vector;			// pointer to the bit_vector used internally

		// Internal functions
		inline void update_fpr(int num_hash_fn, ullong_t bit_array_size, ullong_t expected_num_elements){
			_false_positive_rate = pow(( 1.0 - (pow( (1.0-(1.0/bit_array_size)) , (num_hash_fn*expected_num_elements) ) )), (num_hash_fn));
		}

	public:
		// Constructors and destructors
		bloom_filter(long double false_positive_rate, ullong_t expected_num_elements)
		: _false_positive_rate(false_positive_rate), _expected_num_elements(expected_num_elements){
			_bit_array_size = -1 * ((_expected_num_elements * log(_false_positive_rate)) / pow(log(2), 2));
			_num_hash_fn = ceil((1.0 * _bit_array_size / _expected_num_elements) * log(2));
			_bit_vector = new bit_vector<>(_bit_array_size);
		}

		bloom_filter(int num_hash_fn, ullong_t bit_array_size, ullong_t expected_num_elements)
		: _num_hash_fn(num_hash_fn), _bit_array_size(bit_array_size), _expected_num_elements(expected_num_elements){
			update_fpr(_num_hash_fn, _bit_array_size, _expected_num_elements);
			_bit_vector = new bit_vector<>(_bit_array_size);
		}

		bloom_filter(bloom_filter<T> &bf){
			this -> _false_positive_rate = bf._false_positive_rate;
			this -> _num_hash_fn = bf._num_hash_fn;
			this -> _bit_array_size = bf._bit_array_size;
			this -> _expected_num_elements = bf._expected_num_elements;
			this -> _bit_vector = new bit_vector<>(*(bf._bit_vector));
		}

		~bloom_filter(){
			(*(this->_bit_vector)).~bit_vector();
		}

		// main functionalities
		bool insert(T value){
			for(int i = 0; i < _num_hash_fn; ++i){
				int seed = i + 1;
				ullong_t hashed_value = hasher::hash(value, seed);
				ullong_t insert_at_index = hashed_value % _bit_array_size;
				bool is_inserted = _bit_vector -> set(insert_at_index, 1);

				if(!is_inserted){
					return false;
				}
			}
			return true;
		}

		bool check(T value){
			for(int i = 0; i < _num_hash_fn; ++i){
				int seed = i + 1;
				ullong_t hashed_value = hasher::hash(value, seed);
				ullong_t check_at_index = hashed_value % _bit_array_size;
				bool check_index = _bit_vector -> test(check_at_index);

				if(!check_index){
					return false;
				}
			}
			return true;
		}

		// getters of private attributes
		long double get_false_positive_rate(){
			return _false_positive_rate;
		}

		int get_num_hash_fn(){
			return _num_hash_fn;
		}

		ullong_t get_bit_array_size(){
			return _bit_array_size;
		}

		ullong_t get_expected_num_elements(){
			return _expected_num_elements;
		}

		// friend functions
		friend ostream& operator<<<T>(ostream& output, bloom_filter<T>& bf);
};

// operator overloaded friend function for bloom filter
template<typename T>
ostream& operator<<(ostream& output, bloom_filter<T>& bf){
	output << *(bf._bit_vector);
	return output;
}

#endif
