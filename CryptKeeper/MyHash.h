// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.
//Templated functions must remain in the header file

#include <string>
#include <vector>


template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
	MyHash(double maxLoadFactor, int size);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const;
    double getLoadFactor() const;

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;

private:

	struct Node {
		KeyType m_key; //Pattern #
		ValueType m_val; //The Word
		Node* next;
	};

	double m_maxLF; //The speed/size performance of the hash in %
	double m_currLF; 
	int m_size; //Number of buckets in the hash, default to 100 on construction
	int m_totElements;
	std::vector<Node*> m_hashTable; //Dynamically sized array
};

template<typename KeyType, typename ValueType>
inline
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
	: m_maxLF(maxLoadFactor),
	m_currLF(0), //no initial filled buckets
	m_size(100), //start at 100 buckets max
	m_totElements(0) //start with 0 filled buckets ->currLF =0
{
	if (maxLoadFactor <= 0) {
		m_maxLF = .5;
	}
	if (maxLoadFactor > 2) {
		m_maxLF = 2.0;
	}
	
	m_hashTable[0] = new Node[m_size];
	
	//Initialize hash table to be empty buckets
	for (int i = 0; i < m_size; i++) { //O(B)
	m_hashTable[i] = nullptr;
	}	
}


template<typename KeyType, typename ValueType>
inline
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor, int size) //Check out this fancy C+11 Syntax
	: MyHash(maxLoadFactor) //Delegate constructor!
{
	m_size = size; //overwrite the default
					//Smells like clean code bby
}


template<typename KeyType, typename ValueType>
inline
MyHash<KeyType, ValueType>::~MyHash() {
	//Need to delete the dynamic memort of the has table 
	Node* del = nullptr;
	Node* delHelper = nullptr;
	for (int i = 0; i < m_size; i++) {
		del = m_hashTable[i];
		while (del != nullptr) { //If theres any memory in this bucket, delete it
			delHelper = del;
			if (del->next != nullptr) { //Advance to next node in open list 
				del = del->next;
			}
			delete delHelper; //Always delete existing node
		}
		del = delHelper = nullptr;
		//Del and DelHelper both deleted, loop back to new assignment
			//Set to nullptr instead of random memory
	}
}

template<typename KeyType, typename ValueType>
inline
int MyHash<KeyType, ValueType>::getNumItems() const {
	return m_totElements;
}


template<typename KeyType, typename ValueType>
inline
double MyHash<KeyType, ValueType>::getLoadFactor() const {
	return m_currLF;
}


template<typename KeyType, typename ValueType>
inline
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value) {

	//Finds if key already exists in table
		//Updates to new value
		//(A key may only map to one value)
	//If adding a new node to the list causes the currLF >= maxLF
		//Dynamically allocate a new hashTable with 2x the amount of memory
			//p = MyHash(m_size *2);
			//d = this;
			// for (this.size)
				// p.associate(this.Node[i]); //Need to dynamically rehash all terms
			//swap(this, p)
			//delete p; //MUST DELETE CONTENTS OF OLD ARRAY

	int index = key % m_size;

	Node* look = m_hashTable[index];

	int i = 0; //Depth of bucket, used to check if new bucket made


	if (look != nullptr) { //Goal to stop before nullptr
		while (look->next != nullptr) {//Loop through bucket chain 

			if (value == look->m_val) {//Key already exists
				look->m_val = value; //update and return
				return; //Dont increase size of list
			}
			look = look->next;
			i++; //Deeper into bucket
		}
	}

	//Now before an empty space in bucket, with unique key
	Node* add = new Node;
	add->m_key = key;
	add->m_val = value;
	add->next = nullptr;

	look->next = add; //Add to list
	m_totElements++; //Increase size of elements

	//Update load factor
	m_currLF = m_totElements / m_size;


	if (m_currLF > m_maxLF ) {
		//Need to create bigger array 2x the size
			//Hashing is unique to MyHash Objects (not a vector prop)
				//Need a a new MyHash
				
		//Re hash all data to new hashTable
		//delete all current data
		//swap tables
		int newSize = m_size * 2;
		MyHash* newHash = new MyHash(m_maxLF, newSize); //keep user input, but update size


	}


}

template<typename KeyType, typename ValueType>
inline
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const {
	//Patternize() key
		//Use hashFunction on pattern to find location
			//Loop through Node list
				//Return the value of the found key
			//If increment to nullptr, return nullptr



}