// Liulan Zheng
// CSCI 335 Homework 2

#ifndef CSCI335_HOMEWORK2_SEQUENCE_MAP
#define CSCI335_HOMEWORK2_SEQUENCE_MAP
#include<vector>
#include <iostream>
#include <cstddef>
#include<string>
using namespace std;

class SequenceMap
{
private: 
	string recognition_sequence_;
	vector<string> enzyme_acronyms_;
public:
/************************Big Five ********************/

	// Destructor
	~SequenceMap() = default;
	// Copy Constructor
	SequenceMap(const SequenceMap & rhs) = default;
	// Copy assignment operator 
	SequenceMap & operator=(const SequenceMap & rhs) = default;
	// Move constructor
	SequenceMap(SequenceMap && rhs) = default;
	// Move assignment operator
	SequenceMap & operator=(SequenceMap && rhs) = default;
	
/********************end of Big Five ****************/
	// Constructor with two parameters
	SequenceMap(const string &a_rec_seq, const string &an_enz_acro)
	{
		recognition_sequence_ = a_rec_seq;
		enzyme_acronyms_.push_back(an_enz_acro);
	}
	
	// overload the operator < to compare two regular strings
	bool operator<(const SequenceMap &rhs) const
	{
		return recognition_sequence_ < rhs.recognition_sequence_;
	}

	
	// Helper function for overloading operator <<
	void Print(std::ostream &out) const 
	{
		for(size_t i = 0; i < enzyme_acronyms_.size(); i++)
		{	
			out << enzyme_acronyms_[i];
			if(i == enzyme_acronyms_.size()-1)
				out<<endl;
			else
				out<<" ";
		}
	}
	
	// Overloading the << operator.
	friend std::ostream &operator<<(std::ostream &out, const SequenceMap &a_sequenceMap) 
	{
		a_sequenceMap.Print(out);
		return out;
	}
	
	/**
	 * @pre: The object's recognition_sequence_ equals to other_sequence.recognition_sequence_
	 * @post: The other_sequence.enzyme_acronyms_ and object's enzyme_acronyms_
 	 *		  The other_sequence object will not be affected
	 */ 
	 void Merge(const SequenceMap &other_sequence){
		vector<string> other_enzyme_acronyms = other_sequence.enzyme_acronyms_;
		for(size_t i = 0; i < other_enzyme_acronyms.size(); i++){
			enzyme_acronyms_.push_back(other_enzyme_acronyms[i]);
		}
	}
};
#endif
	