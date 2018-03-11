// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.
//Templated functions must remain in the header file

#include <string>


template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
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

	double m_maxLF; //The speed/size performance of the hash
	double m_currLF; 
	double m_size; //Number of buckets in the hash, default to 100 on construction
	double m_totElements;
	Node* m_hashTable; //Dynamically sized array
};

template<typename KeyType, typename ValueType>
inline
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor = .5)
	: m_maxLF(maxLoadFactor),
	m_currLF(0), //no initial filled buckets
	m_size(100), //start at 100 buckets
	m_totElements(0)
{
	if (maxLoadFactor <= 0) {
		m_maxLF = .5;
	}
	if (maxLoadFactor > 2) {
		m_maxLF = 2.0;
	}
	
	m_hashTable = new Node*[m_size];
	
	//Initialize hash table to be empty buckets
	for (int i = 0; i < m_size; i++) { //O(B)
	m_hashTable[i] = nullptr;
	}	
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
				del = del->next
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