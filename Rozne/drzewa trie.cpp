/* Drzewo trie
 */
#include <cstdio>
#include <cmath>
#include <climits>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <stack>
#include <cassert>
#include <string>

#define FOR_EACH( it, container ) for( typeof(container.begin()) it = container.begin(); it != container.end(); it++ )

class trie {
	private:
		struct trie_element : std::map<char, trie_element>{
			int value;
			trie_element() : value(0) {} 
		};
		trie_element root;
	public:
		class iterator {
			private:
				char val[32];
				std::stack< trie_element* > stack;
				std::stack< trie_element::iterator > it_stack;
				std::pair<const char*, int&> *pair;
			public:
				~iterator() {
					if( pair )
						delete pair;
				}
				iterator() : pair(NULL) { val[0] = 0; }
				iterator(trie_element& root) {
					val[0] = 0;
					stack.push(&root);
					pair = new std::pair<const char*, int&>(val, root.value);
				}
				iterator(const iterator& other) : stack(other.stack), it_stack(other.it_stack) {
					strcpy( val, other.val );
					pair = new std::pair<const char*, int&>(*other.pair);
				}
				bool operator==(const iterator& other) const {
					if( stack.empty() or other.stack.empty() )
						return stack.empty() and other.stack.empty();
					return stack.top() == other.stack.top();
				}
				bool operator!=(const iterator& other) const {
					if( stack.empty() or other.stack.empty() )
						return not ( stack.empty() and other.stack.empty() );
					return stack.top() != other.stack.top();
				}
				std::pair<const char*, int&>& operator*() {
					return *pair;
				}
				std::pair<const char*, int&>* operator->() {
					return pair;
				}
				iterator& operator++() {
					if( stack.empty() )
						return *this;
					it_stack.push( stack.top()->begin() );
					while( it_stack.top() == stack.top()->end() ) {
						assert( stack.size() == it_stack.size() );
						stack.pop();
						it_stack.pop();
						if( stack.empty() )
							return *this;
						it_stack.top()++;
					}			
					val[stack.size()-1] = it_stack.top()->first;
					val[stack.size()] = 0;
					stack.push( & it_stack.top()->second );
					pair = new std::pair<const char*, int&>(val, stack.top()->value);
					return *this;
				}
				iterator operator++(int) {
					iterator ret = *this;
					operator++();
					return ret;
				}
		};
		iterator begin() {
			return iterator(root);
		}
		iterator end() {
			return iterator();
		}

		int& operator[](const char* key) {
			trie_element *e = &root;
			for( int i = 0; key[i]; i++ ) {
				e = &((*e)[key[i]]);
			}
			return e->value;
		}
};

char buf[132];
void test() {
	trie T;
	int count=0;
	while( gets(buf) and buf[0] ) {
		++T[buf];
		++count;
	}
	int q = 0;
	FOR_EACH( it, T ) {
		if( it->second )
			printf("%s %.4f\n", it->first, 100.0 * it->second / count );
	}
}

int main() {
	int T;
	scanf("%d", &T );
	gets(buf);
	gets(buf);
	while( T --> 0 ) {
		test();
		if( T )
			printf("\n");
	}
}
