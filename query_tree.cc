// Liulan Zheng
// Main file for Part2(a) of Homework 2.

#include "avl_tree.h"
#include "sequence_map.h"
#include <iostream>
#include <string>
#include <fstream>
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

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) 
{
  // You can use public functions of TreeType. For example:
  //a_tree.insert(10);
  //a_tree.printTree();

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
			while(getNextRecognitionSequence(db_line, a_reco_seq))
			{
				SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
				a_tree.insert(new_sequence_map);
			}
		}
	}
	inFile.close();
	//a_tree.printTree();
}
	
}  // namespace

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  cout << "Input filename is " << db_filename << endl;
 
  AvlTree<SequenceMap> a_tree;
  
  QueryTree(db_filename, a_tree);
  string rec_seq;
  string enzyme_acr = "";
  while(cin >> rec_seq)            // Read from the input file that contains a recognition sequence on each line
  {
	  SequenceMap a_seq_map(rec_seq, enzyme_acr);
	  a_tree.findInTree(a_seq_map);  // If sequence is found in a_tree, print out all the enzyme acronyms in this sequence; Else print "Not Found"
  }

  return 0;
}
