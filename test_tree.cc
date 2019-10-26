// Liulan Zheng
// CSCI 335 Homework 2
// Main file for Part2(b) of Homework 2.

#include "avl_tree_modified.h"
#include "sequence_map.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

namespace {
	
/**
 * Helper function for TestTree to store nodes in tree
 * @db_line: lines from db_filename file,
 *          which has a format of "enzyme_acronym/recognition_sequence/…/recognition_sequence//"
 * @enzyme_acronyme: a string that is found right before the first '/' in db_line
 * Return enzyme_acronyme found in db_line; Else return an empty string
 */
string getEnzymeAcronym(string & db_line)
{
	string enzyme_acronyme;
	for(size_t i = 0; i < db_line.length(); i++)
	{
		if(db_line[i] == '/')
		{
			enzyme_acronyme = db_line.substr(0, i);
			db_line = db_line.substr(i+1);
			return enzyme_acronyme;
		}
	}
	return "";
}

/**
 * Helper function for TestTree to store nodes in tree
 * @db_line: a string that has a format of "recognition_sequence/…/recognition_sequence//"
 * @a_reco_seq (pass by reference): a string that right before the first '/' in db_line
 * Return false db_line doesn't contain recognition_sequence; Else return true
 */
bool getNextRecognitionSequence(string & db_line, string & a_reco_seq)
{
	if(db_line[0] == '/')
		return false;
	for(size_t i = 0; i < db_line.length(); i++)
	{
		if(db_line[i] == '/')
		{
			a_reco_seq = db_line.substr(0, i);
			db_line = db_line.substr(i+1);
			return true;
		}
	}
	return false;
}

/**
 * @sequence_filename: name of the file that contains one recognition sequence on each line
 * @a_tree: a TreeType tree created in TestTree
 * @total_calls: total number of recursions called by a_tree.find()
 * @success: total number of sequences from seq_filename are found in a_tree
 * @average_recursion: average number of recursion calls for Find i.e. total number of recursion called by find / success
 */
template<typename TreeType>
void Find(const string &seq_filename, TreeType &a_tree, int& success, float& average_recursion)
{
	ifstream newFile;
	newFile.open(seq_filename);
	int total_calls = 0;
	string sequence;
	while(getline(newFile, sequence))
	{
		SequenceMap map(sequence , "");
		if(a_tree.find(map,total_calls ))
			success++;
	}
	newFile.close();
	average_recursion = (float)total_calls/success;
}

/**
 * @sequence_filename: name of the file that contains one recognition sequence on each line
 * @a_tree: a TreeType tree created in TestTree
 * @total: total number of time remove is called
 * @total_calls: total number of recursions called by a_tree.remove()
 * @success: total number of successful remove in removing every other sequence in seq_filename
 * @average_recursion: average number of recursion calls for Find i.e. total number of recursion called by find / success
 */
template<typename TreeType>
void Remove(const string & seq_filename, TreeType & a_tree, int& success, float& average_recursion)
{
	ifstream newFile;
	newFile.open(seq_filename);
	int total_calls = 0;
	string sequence;
	int total= 0;
   	while(getline(newFile, sequence))
	{
		SequenceMap map(sequence , "");
		a_tree.remove(map, total_calls, success);		
		getline(newFile, sequence);
		total++;
		
	}
	newFile.close();
	average_recursion = (float)total_calls/total;
}

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) 
{
  	string db_line;
  //Read the file line-by-line
	ifstream inFile;
	inFile.open(db_filename);
	while(getline(inFile, db_line))
	{        
		if(db_line[db_line.length()-1] == '/')
		{
			string an_enz_acro = getEnzymeAcronym(db_line);
			string a_reco_seq;
			while(getNextRecognitionSequence(db_line, a_reco_seq)){
				SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
				a_tree.insert(new_sequence_map);
			}
		}
	}
	inFile.close();
}

}  // namespace


int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);
  
  // print the total number of nodes on a_tree
  cout << "2: " << a_tree.NumberOfNode() << endl; 
  // print the average depth (i.e., internal path length / total number of nodes)
  cout << "3a: " << a_tree.AverageDepth() << endl;
  // print the ratio of the average depth to (log2 n), where n is total number of nodes
  cout << "3b: " << a_tree.RatioOfAverageDepthToLog2N() << endl;
  
  int successful_finds = 0;
  float average_find = 0;
  Find(seq_filename, a_tree, successful_finds, average_find);
  // print the total number of successful finds
  cout << "4a: " << successful_finds << endl;
  // print the average number of recursion calls for find
  cout << "4b: " << average_find << endl;
  
  int successful_remove = 0;
  float average_remove = 0;
  Remove(seq_filename, a_tree, successful_remove, average_remove);
  // print the total number of successful removes
  cout << "5a: " << successful_remove << endl;
  // print the average number of recursion calls for remove
  cout << "5b: " << average_remove << endl;
  
  
  /**********AFTER REMOVE CERTAIN NODES FROM THE TREE************/
  // print the total number of nodes on a_tree
  cout << "6a: " << a_tree.NumberOfNode() << endl; 
  // print the average depth (i.e., internal path length / total number of nodes)
  cout << "6b: " << a_tree.AverageDepth() << endl;
  // print the ratio of the average depth to (log2 n), where n is total number of nodes
  cout << "6c: " << a_tree.RatioOfAverageDepthToLog2N() << endl;
  
 

  return 0;
}
