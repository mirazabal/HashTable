// implementation with a single linked list for collisions, so to insert O(1) and to get O(N)
// https://en.wikipedia.org/wiki/Hash_table#Separate_chaining for collisions
//
//
#include <memory>
#include <stdexcept>
#include <iostream>

namespace mirazabal	{	namespace HashTable	{


template<typename T, typename K>
class HashTable
{

static constexpr unsigned table_size{1000};

class Node
{
	public:
		Node(int value,int key ) : next_(nullptr), value_(value), key_(key)
		{
		};
		int key_;
		int value_;
		std::unique_ptr<Node> next_;
};	

	public:
		void insert(T key, K value )
		{
			auto hash_value = get_hash(key);

			if( table[hash_value] == nullptr ){
				table[hash_value] = std::unique_ptr<Node>(new Node(value, key)); 
			}else{
				Node* temp = table[hash_value].get();
				while( temp->next_ != nullptr ){
					temp = temp->next_.get();
				}
				temp->next_ = std::unique_ptr<Node>(new Node(value, key) );
			}
		};

		bool find_key(T key)
		{
			auto hash_value = get_hash(key);
			if(table[hash_value] == nullptr)
				return false;
			else{
				Node* temp = table[hash_value].get();
				while(temp->key_ != key && temp->next_ != nullptr){
					temp = temp->next_.get();
				}
				if(temp->key_ == key)
					return true;
				else
					return false;
			}
		};

		K get_value(T key){
			auto hash_value = get_hash(key);
			if(table[hash_value] != nullptr ){
				Node* temp = table[hash_value].get();
				while( temp->key_ != key && temp->next_ != nullptr){
					temp = temp->next_.get();
				}
				if(temp->key_ == key){
					return temp->value_;
				}		
			}
			throw std::invalid_argument("Key not found");
		};

	private:	
		int get_hash(T key)
		{
			return key % table_size;
		};
		
		std::array< std::unique_ptr<Node>, table_size > table;
};
}}


int main()
{
	mirazabal::HashTable::HashTable<int, int> has;

	has.insert(0, 52400);
	if (has.find_key(0))
		std::cout<< "Key found" << std::endl;
	else
		std::cout << "Key, not found" << std::endl;


	for(int i = 0; i < 10000; i++){
		has.insert(i, i+ 56789);
	}
	for(int i = 0; i < 10000; i++){
		if(has.find_key(i))
			std::cout << "key found"<< std::endl;
		else
			throw std::runtime_error("Something went wrong");
	}
	return 0;
}

