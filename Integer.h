// ------------------
// integer/Integer.h
// Tj Wrenn
// ------------------

#ifndef Integer_h
#define Integer_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument, out_of_range
#include <string>    // string
#include <vector>    // vector

// ----------
// namespaces
// ----------

namespace alg   {
	namespace prog    {
		namespace integer {

			// -------
			// Integer
			// -------

			template < typename T, typename C = std::vector<T> >
			class Integer {
				// -------
				// friends
				// -------

				/**
				* O(n) copy must be made
				* M(n) copy must be made
				* @param x an Integer
				* @return a new Integer by negating x
				*/
				friend Integer operator - (const Integer& x) {
					container_type tmp(x.data);  //invoke container's copy constructor
					Integer r(0);
					r.data.swap(tmp);
					r.sign = !x.sign && (x != ZERO);
					return r;}

				/**
				* O(n)
				* M(m-n) or M(1) depending on lhs < rhs or rhs > lhs respectively
				* @param lhs an Integer
				* @param rhs an Integer
				* @return a new Integer by adding lhs and rhs
				*/
				friend Integer operator + (Integer lhs, const Integer& rhs) {
					return lhs += rhs;}

				/**
				* O(n)
				* M(m-n) or M(1) depending on lhs < rhs or rhs > lhs respectively
				* @param lhs an Integer
				* @param rhs an Integer
				* @return a new Integer by subtracting rhs from lhs
				*/
				friend Integer operator - (Integer lhs, const Integer& rhs) {
					return lhs -= rhs;}

				/**
				* O(n*m) but significantly less if rhs contains many zeros
				* M(n + m) where n is the length of lhs and m is the length of rhs
				* @param lhs an Integer
				* @param rhs an Integer
				* @return a new Integer by multiplying lhs and rhs
				*/
				friend Integer operator * (Integer lhs, const Integer& rhs) {
					return lhs *= rhs;}

				/**
				* O(1) or O(n*m) depending if |rhs| > |lhs| or |rhs| < |lhs| respectively
				* M(1) or M(n) depending if |rhs| > |lhs| or |rhs| < |lhs| respectively
				* @param lhs an Integer
				* @param rhs an Integer
				* @return a new Integer by dividing lhs by rhs
				* @throws std::invalid_argument
				*/
				friend Integer operator / (Integer lhs, const Integer& rhs) throw (std::invalid_argument) {
					return lhs /= rhs;}

				/**
				* O(1) or O((n+1)*m) depending if |rhs| > |lhs| or |rhs| <= |lhs| respectively
				* M(1) or M(n) depending if |rhs| > |lhs| or |rhs| <= |lhs| respectively
				* @param lhs an Integer
				* @param rhs an Integer
				* @return a new Integer by modding lhs by rhs
				* @throws std::invalid_argument
				*/
				friend Integer operator % (Integer lhs, const Integer& rhs) throw (std::invalid_argument) {
					return lhs %= rhs;}

				/**
				* O(1) or O(n) depending on if signs differ or sizes differ, or if sizes are the same respectively
				* M(1)
				* @param lhs an Integer
				* @param rhs an Integer
				* @return true if lhs is equal to rhs
				*/
				friend bool operator == (const Integer& lhs, const Integer& rhs) {
					//handle simple cases without needing to deep compare
					//differing signs
					if(lhs.sign != rhs.sign) return false;
					//differing numbers of digits
					if(lhs.data.size() != rhs.data.size()) return false;

					return lhs.data == rhs.data;  //invoke Container's lexigraphical compare
				}

				/**
				* O(1) or O(n) depending on if signs differ or sizes differ, or if sizes are the same respectively
				* M(1)
				* @param lhs an Integer
				* @param rhs an Integer
				* @return true if lhs is not equal to rhs
				*/
				friend bool operator != (const Integer& lhs, const Integer& rhs) {
					return !(lhs == rhs);}

				/**
				* O(1) or O(n) depending on if signs differ or sizes differ, or if sizes are the same respectively
				* M(1)
				* @param lhs an Integer
				* @param rhs an Integer
				* @return true if lhs is less than rhs
				*/
				friend bool operator < (const Integer& lhs, const Integer& rhs) {
					//handle simple cases without needing to deep compare
					if(lhs.sign && !rhs.sign) return true;
					if(!lhs.sign && rhs.sign) return false;
					if(lhs.sign) {
						assert(rhs.sign);
						if(lhs.data.size() > rhs.data.size()) return true;
						if(lhs.data.size() < rhs.data.size()) return false;

						assert(lhs.data.size() == rhs.data.size());
						return lhs.data > rhs.data;  //invoke Container's lexigraphical compare
					} else {
						assert(!rhs.sign);
						if(lhs.data.size() < rhs.data.size()) return true;
						if(lhs.data.size() > rhs.data.size()) return false;

						assert(lhs.data.size() == rhs.data.size());

						return lhs.data < rhs.data;  //invoke Container's lexigraphical compare
					}
				}

				/**
				* O(1) or O(n) depending on if signs differ or sizes differ, or if sizes are the same respectively
				* M(1)
				* @param lhs an Integer
				* @param rhs an Integer
				* @return true if lhs is less than or equal to rhs
				*/
				friend bool operator <= (const Integer& lhs, const Integer& rhs) {
					return !(rhs < lhs);}

				/**
				* O(1) or O(n) depending on if signs differ or sizes differ, or if sizes are the same respectively
				* M(1)
				* @param lhs an Integer
				* @param rhs an Integer
				* @return true if lhs is greater than rhs
				*/
				friend bool operator > (const Integer& lhs, const Integer& rhs) {
					return (rhs < lhs);}

				/**
				* O(1) or O(n) depending on if signs differ or sizes differ, or if sizes are the same respectively
				* M(1)
				* @param lhs an Integer
				* @param rhs an Integer
				* @return true if lhs is greater than or equal to rhs
				*/
				friend bool operator >= (const Integer& lhs, const Integer& rhs) {
					return !(lhs < rhs);}

				/**
				* O(n)
				* M(1)
				* @param lhs an ostream
				* @param rhs an Integer
				* @return the ostream
				*/
				friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
					if(rhs.sign) lhs << "-";
					for(const_iterator i = rhs.data.begin(); i<rhs.data.end(); ++i)
						lhs << *i;
					return lhs;}

			public:
				// --------
				// typedefs
				// --------

				typedef C                                        container_type;
				typedef typename container_type::value_type      value_type;

				typedef typename container_type::size_type       size_type;
				typedef typename container_type::difference_type difference_type;

				typedef typename container_type::reference       reference;
				typedef typename container_type::const_reference const_reference;

				typedef typename container_type::iterator        iterator;
				typedef typename container_type::const_iterator  const_iterator;

				static const Integer ZERO;
				static const Integer ONE;
			private:
				// ----
				// data
				// ----
				container_type data;
				bool sign;

				// -------
				// isDigit
				// -------

				/**
				* O(1)
				* M(1)
				* @param char c
				* @return true if c is a digit
				*/
				static inline bool isDigit(char c){ c-='0'; return c >= 0 && c <= 9; }

				// -----
				// valid
				// -----

				/**
				* O(1)
				* M(1)
				* @return true if Integer has valid digits
				*/
				bool valid () const {
					return data.size() > 0;}

			public:
				// ------------
				// constructors
				// ------------

				/**
				* O(log i)
				* M(log i)
				* @param i the decimal representation of a positive or negative number in base 10
				*/
				Integer (int i) {
					if(i<0){
						do{
							data.insert(data.begin(), -(i%10));
							i/=10;
						}while(i);
						sign=true;
					} else {
						do{
							data.insert(data.begin(), i%10);
							i/=10;
						}while(i);
						sign=false;
					}

					assert(valid());}

				/**
				* O(n)
				* M(n)
				* @param s the string representation of a positive or negative number in base 10
				* @throws std::invalid_argument
				*/
				explicit Integer (const std::string& s) throw (std::invalid_argument) {
					sign = false;
					std::string::const_iterator i=s.begin();
					//see if first character is - and handle accordingly
					if('-'==*i){
						++i;
						if(s.end() == i) //handles the case if user passes in just a "-"
							throw std::invalid_argument("Integer::Integer()");

						sign = true;
					}

					for(;('0'==*i) && (i < s.end()-1); ++i) {} //scoot past leading zeros if there are any

					if(i == s.end()-1 && *i == '0') sign = false; //eliminate negative zero

					for(;i<s.end(); ++i){
						if(!isDigit(*i)){
							data.clear();   //all data thus far is deemed garbage if a non-digit is encountered
							data.push_back(0);
							throw std::invalid_argument("Integer::Integer()");
						}
						data.push_back(*i-'0');
					}

					if(data.size() == 0) // empty string is NOT valid integer
						throw std::invalid_argument("Integer::Integer()");

					assert(valid());
				}

				// Default copy, destructor, and copy assignment.
				// Integer (const Integer&);
				// ~Integer ();
				// Integer& operator = (const Integer&);

				// -----------
				// operator []
				// -----------

				/**
				* O(1) if underlying container has const time indexing operator
				* M(1)
				* @param index
				* @return value at specified index from right
				*/
				reference operator [] (size_type index) {
					return data[data.size()-index-1];}

				/**
				* O(1) if underlying container has const time indexing operator
				* M(1)
				* @param index
				* @return value at specified index
				*/
				const_reference operator [] (size_type index) const {
					return const_cast<Integer*>(this)->operator[](index);}

				// -----------
				// operator ++
				// -----------

				/**
				* O(1) no copy is made.  assuming minimal carrying occurs.
				* M(1) no copy is made.
				* @return the incremented Integer *this
				*/
				Integer& operator ++ () {
					*this += 1;
					assert(valid());
					return *this;}

				/**
				* O(n) copy is made.
				* M(n) copy is made.
				* @return copy of *this
				*/
				Integer operator ++ (int) {
					Integer x = *this;
					++(*this);
					assert(valid());
					return x;}

				// -----------
				// operator --
				// -----------

				/**
				* O(1) no copy is made.  assuming minimal carrying occurs.
				* M(1) no copy is made
				* @return the decremented Integer *this
				*/
				Integer& operator -- () {
					*this -= 1;
					assert(valid());
					return *this;}

				/**
				* O(n) copy is made
				* M(n) copy is made
				* @return copy of *this
				*/
				Integer operator -- (int) {
					Integer x = *this;
					--(*this);
					assert(valid());
					return x;}

				// -----------
				// operator +=
				// -----------

				/**
				* O(n)
				* M(m-n) or M(1) depending on lhs < rhs or rhs > lhs respectively
				* @param that the rhs addend
				* @return lhs as the sum of lhs and rhs addends
				*/
				Integer& operator += (const Integer& that) {

					bool bottomIsBigger;  //holds true if |y|>|x| in x-y.
					//Only matters when signs differ between the two addends
					if(this->sign != that.sign){
						if(that.sign) {
							this->sign = true;
							bottomIsBigger = (that < *this);
							this->sign = false;
						} else {
							this->sign = false;
							bottomIsBigger = (*this < that);
							this->sign = true;
						}
					}

					//MUST use a signed type.  size_type can not guarantee this.
					int offset = that.data.size()-(this->data.size());

					//make lhs the same size as the rhs if |lhs| < |rhs|
					if(offset < 0) offset = 0;
					this->data.insert(this->data.begin(), offset, 0);

					assert(that.data.size() <= this->data.size());

					iterator top = this->data.end()-1;
					const_iterator bottom = that.data.end()-1;
					value_type carry = 0;

					//handle both cases separately for speed
					//+top +bottom or -top -bottom
					if(this->sign == that.sign){
						while(bottom >= that.data.begin()){
							value_type sum = (*top+*bottom)+carry;
							carry = sum / 10;
							sum %= 10;
							*top = sum;
							--top;
							--bottom;
						}
						while(top >= this->data.begin()){
							value_type sum = *top+carry;
							carry = sum / 10;
							sum %= 10;
							*top = sum;
							--top;
						}
						if(carry) this->data.insert(this->data.begin(), carry);
					} else { //-top +bottom or +top -bottom
						//compute top - bottom in base 10
						carry = 1;
						while(bottom >= that.data.begin()){
							//1. Add top to the 10's complement of bottom.
							value_type sum = (*top+(9-*bottom))+carry;
							carry = sum / 10;
							sum %= 10;
							*top = sum;
							--top;
							--bottom;
						}
						while(top >= this->data.begin()){
							value_type sum = *top+9+carry;
							carry = sum / 10;
							sum %= 10;
							*top = sum;
							--top;
						}
						//2. If there is a carry, discard it. What is left is the result top - bottom.
						//3. If there is no carry, take the 10's complement of the sum
						if(!carry) {
							carry = 1;
							top = this->data.end()-1;
							while(top >= this->data.begin()){
								value_type sum = 9-*top+carry;
								carry = sum / 10;
								sum %= 10;
								*top = sum;
								--top;
							}
						}

						if(bottomIsBigger) this->sign = !this->sign;

						//get rid of leading zeros
						top = this->data.begin();
						if(0==*top){
							while(0==*top && top < this->data.end()-1){
								++top;
							}
							this->data.erase(this->data.begin(), top);

							//turn -0 into 0 if necessary
							if(this->data.size()==1 && this->data[0]==0)
								this->sign = false;
						}
					}

					assert(valid());
					return *this;}

				// -----------
				// operator -=
				// -----------

				/**
				* O(n)
				* M(m-n) or M(1) depending on lhs < rhs or rhs > lhs respectively
				* @param that the subtrahend
				* @return lhs as minuend minus subtrahend
				*/
				Integer& operator -= (const Integer& that) {

					bool bottomIsBigger;  //holds true if |y|>|x| in x-y.
					//Only matters when signs same between the minuend and subtrahend
					if(this->sign == that.sign){
						if(that.sign) {
							bottomIsBigger = (that < *this);
						} else {
							bottomIsBigger = (*this < that);
						}
					}

					//MUST use a signed type.  size_type can not guarantee this.
					int offset = that.data.size()-(this->data.size());

					//make lhs the same size as the rhs if |lhs| < |rhs|
					if(offset < 0) offset = 0;
					this->data.insert(this->data.begin(), offset, 0);

					assert(that.data.size() <= this->data.size());

					iterator top = this->data.end()-1;
					const_iterator bottom = that.data.end()-1;
					value_type carry = 0;

					//handle both cases separately for speed
					//+top +bottom or -top -bottom
					if(this->sign != that.sign){
						while(bottom >= that.data.begin()){
							value_type sum = (*top+*bottom)+carry;
							carry = sum / 10;
							sum %= 10;
							*top = sum;
							--top;
							--bottom;
						}
						while(top >= this->data.begin()){
							value_type sum = *top+carry;
							carry = sum / 10;
							sum %= 10;
							*top = sum;
							--top;
						}
						if(carry) this->data.insert(this->data.begin(), carry);
					} else { //-top +bottom or +top -bottom
						//compute top - bottom in base 10
						carry = 1;
						while(bottom >= that.data.begin()){
							//1. Add top to the 10's complement of bottom.
							value_type sum = (*top+(9-*bottom))+carry;
							carry = sum / 10;
							sum %= 10;
							*top = sum;
							--top;
							--bottom;
						}
						while(top >= this->data.begin()){
							value_type sum = *top+9+carry;
							carry = sum / 10;
							sum %= 10;
							*top = sum;
							--top;
						}
						//2. If there is a carry, discard it. What is left is the result top - bottom.
						//3. If there is no carry, take the 10's complement of the sum
						if(!carry) {
							carry = 1;
							top = this->data.end()-1;
							while(top >= this->data.begin()){
								value_type sum = 9-*top+carry;
								carry = sum / 10;
								sum %= 10;
								*top = sum;
								--top;
							}
						}

						if(bottomIsBigger) this->sign = !this->sign;

						//get rid of leading zeros
						top = this->data.begin();
						if(0==*top){
							while(*top==0 && top < this->data.end()-1){
								++top;
							}
							this->data.erase(this->data.begin(), top);

							//turn -0 into 0 if necessary
							if(this->data.size()==1 && this->data[0]==0)
								this->sign = false;
						}
					}

					assert(valid());
					return *this;}

				// -----------
				// operator *=
				// -----------

				/**
				* O(n*m) but significantly less if rhs contains many zeros
				* M(n + m) where n is the length of lhs and m is the length of rhs
				* @param that the rhs multiplicand
				* @return lhs as the product of lhs and rhs
				*/
				Integer& operator *= (const Integer& that) {
					Integer rval(0); //will hold the result

					//the most digits a product could have is the sum of
					//the numbers of digits of both multiplicands combined
					rval.data.resize(this->size() + that.size(), 0);

					//the sign of the product is the xor of the signs of multiplicands
					this->sign ^= that.sign;

					const_iterator thatBegin = that.data.begin();
					const_iterator thatEnd = that.data.end()-1;
					iterator rvalEnd = rval.data.end()-1;
					for(const_iterator y=that.data.end()-1; y>=thatBegin; --y){
						if(*y){
							const difference_type shift = thatEnd - y;
							//unsigned was experimentally found to be much faster than value_type
							unsigned carry = 0;
							iterator z = rvalEnd-shift;
							const_iterator thisBegin = this->data.begin();
							for(const_iterator x=this->data.end()-1;x>=thisBegin; --x){
								unsigned prod = (*x) * (*y) + (*z) + carry;
								*z-- = (prod%10);
								carry = prod / 10;
							}
							*z = carry;
						}
					}

					this->data.swap(rval.data);

					iterator top = this->data.begin();
					//if there are no leading zeros, return
					if(*top){
						assert(valid());
						return *this;
					}

					//otherwise get rid of leading zeros
					while(*top==0 && top < this->data.end()-1){
						++top;
					}
					this->data.erase(this->data.begin(), top);

					//turn -0 into 0 if necessary
					if(this->data.size()==1 && this->data[0]==0)
						this->sign = false;

					assert(valid());
					return *this;}

				// -----------
				// operator /=
				// -----------

				/**
				* O(1) or O(n*m) depending if |rhs| > |lhs| or |rhs| < |lhs| respectively
				* M(1) or M(n) depending if |rhs| > |lhs| or |rhs| < |lhs| respectively
				* @param that the denominator
				* @return lhs as the quotient of lhs divided by rhs
				* @throws std::invalid_argument
				*/
				Integer& operator /= (const Integer& that) throw (std::invalid_argument) {
					// precondition: that != 0
					if(that == ZERO)
						throw std::invalid_argument("Integer::operator/=()");

					bool thatOldSign = that.sign;
					bool thisOldSign = this->sign;

					((Integer &)that).sign = false;  //we promise we'll set it back :-)
					this->sign = false;

					if(that > *this) {
						this->sign = false;
						this->data.clear();
						this->data.push_back(0);
						((Integer &)that).sign = thatOldSign;
						return *this;  //in int division, xxx/yyyy == 0
					}

					Integer rval(0); //will hold the result
					rval.data.resize(this->size(), 0);

					//      zz
					//   -----
					//yyy|xxxx

					Integer s(0);
					s.data.clear();

					const_iterator x = this->data.begin();
					const_iterator y = that.data.begin();
					iterator z = rval.data.begin();

					do{
						while(s < that && x < this->data.end()){
							s.data.push_back(*x);
							++x;
							++z;
						}
						--z;

						//get rid of leading zeros on s if there are any
						{ iterator sprefix = s.data.begin();
						if(0==*sprefix){
							while(0==*sprefix && sprefix < s.data.end()-1){
								++sprefix;
							}
							s.data.erase(s.data.begin(), sprefix);
						}
						}

						unsigned t = 0;
						while(that*Integer(t+1) <= s){
							++t;
						}

						*z++ = t;
						s -= that*t;
					} while(z < rval.data.end());

					this->data.swap(rval.data);
					this->sign = thisOldSign ^ thatOldSign;
					((Integer &)that).sign = thatOldSign;  //see we changed it back.  :-)

					iterator top = this->data.begin();
					//if there are no leading zeros, return
					if(*top){
						assert(valid());
						return *this;
					}

					//otherwise get rid of leading zeros
					while(*top==0 && top < this->data.end()-1){
						++top;
					}
					this->data.erase(this->data.begin(), top);

					assert(valid());
					return *this;}


				// -----------
				// operator %=
				// -----------

				/**
				* O(1) or O((n+1)*m) depending if |rhs| > |lhs| or |rhs| <= |lhs| respectively
				* M(1) or M(n) depending if |rhs| > |lhs| or |rhs| <= |lhs| respectively
				* @param that the modulus
				* @return lhs as lhs mod rhs
				* @throws std::invalid_argument
				*/
				Integer& operator %= (const Integer& that) throw (std::invalid_argument) {
					if(that <= ZERO) throw std::invalid_argument("Integer::operator%=()");
					if(*this < ZERO) throw std::invalid_argument("Integer::operator%=()");
					//for complexity, this converges to *this -= *this * that
					*this -= (*this / that) * that;
					assert(valid());
					return *this;}


				// --
				// at
				// --

				/**
				* O(1) if underlying container has constant time at
				* M(1)
				* @param index the index to return
				* @return value at specified index starting from right
				* @throws std::out_of_range
				*/
				reference at (size_type index) throw (std::out_of_range) {
					try{
						return data.at(data.size()-index-1);
					}
					catch(std::out_of_range &e){
						throw std::out_of_range("Integer::at()");
					}
				}

				/**
				* O(1) if underlying container has constant time at
				* M(1)
				* @param index the index to return
				* @return value at specified index starting from right
				* @throws std::out_of_range
				*/
				const_reference at (size_type index) const throw (std::out_of_range) {
					return const_cast<Integer*>(this)->at(index);}

				// -----
				// begin
				// -----

				/**
				* O(1)
				* M(1)
				* returns iterator that points to most significant digit (does not point at sign)
				*/
				iterator begin () {
					return this->data.begin();}

				/**
				* O(1)
				* M(1)
				* returns iterator that points to most significant digit (does not point at sign)
				*/
				const_iterator begin () const {
					return this->data.begin();}

				// ---
				// end
				// ---

				/**
				* O(1)
				* M(1)
				* returns iterator that points one past the least significant digit
				*/
				iterator end () {
					return this->data.end();}

				/**
				* O(1)
				* M(1)
				* returns iterator that points one past the least significant digit
				*/
				const_iterator end () const {
					return this->data.end();}

				// ----
				// size
				// ----

				/**
				* O(1)
				* M(1)
				* returns size of container
				*/
				size_type size () const {
					return data.size();}

				// ----
				// swap
				// ----

				/**
				* O(1)
				* M(1)
				* @param that an Integer
				*/
				void swap(Integer &that) {
					this->data.swap(that.data);
					this->sign ^= that.sign;
					that.sign ^= this->sign;
					this->sign ^= that.sign;
				}

			};

			//init the static const ZERO and ONE
			template < typename T, typename C >
				const Integer<T, C> Integer<T, C>::ZERO = Integer<T, C>(0);

			template < typename T, typename C >
				const Integer<T, C> Integer<T, C>::ONE = Integer<T, C>(1);
			// ---
			// abs
			// ---

			/**
			* absolute value
			*/

			/**
			* O(n)  because a copy must be made
			* M(n)  because a copy must be made
			* @param x an Integer
			* @return the absolute value of x
			*/
			template <typename T, typename C>
				Integer<T, C> abs (const Integer<T, C>& x) {
					if(x<Integer<T,C>::ZERO)
						return -x;
					return x;
				}

				// ----
				// fact
				// ----

				/**
				* factorial
				*/

				/**
				* O((n^2)!)
				* M(n-log (n^2)!)
				* @param x an Integer
				* @return the factorial of x
				* @throws std::invalid_argument
				*/
				template <typename T, typename C>
					Integer<T, C> fact (const Integer<T, C>& x) throw (std::invalid_argument) {
						if(x < Integer<T,C>::ZERO) throw std::invalid_argument("fact()");
						if(x == Integer<T,C>::ZERO) return Integer<T,C>::ONE;  //0! == 1
						Integer<T, C> r = Integer<T,C>::ONE;
						for(Integer<T, C> i = x;i > Integer<T,C>::ONE; --i){
							r *= i;
						}
						return r;}

					// ---
					// gcd
					// ---

					/**
					* greatest common divisor
					*/

					/**
					* O(1) O(m) O(n) O(?) depending if m==n, n==1, m==1, or otherwise.  It's very difficult to analyze this.
					* M(n+m) because copies are made of lhs and rhs
					* @param x an Integer
					* @param y an Integer
					* @return the gcd of x and y
					* @throws std::invalid_argument
					*/
					template <typename T, typename C>
						Integer<T, C> gcd (const Integer<T, C>& x, const Integer<T, C>& y) throw (std::invalid_argument) {
							if(x==Integer<T,C>::ZERO && y==Integer<T,C>::ZERO) throw std::invalid_argument("gcd()");
							if(x<Integer<T,C>::ZERO || y<Integer<T,C>::ZERO) throw std::invalid_argument("gcd()");

							//make sure that we don't div by zero
							Integer<T, C> b = (y == Integer<T,C>::ZERO) ? x : y;
							Integer<T, C> a = (y == Integer<T,C>::ZERO) ? y : x;

							while(b!=Integer<T,C>::ZERO){
								Integer<T,C> t = b;
								b = a % b;
								a.swap(t);
							}
							return a;
						}


						// ---
						// pow
						// ---

						/**
						* quick power
						*/

						/**
						* O(log exp)
						* M(log (n^exp))
						* @param x the base
						* @param exp the exponent
						* @return the base raised to the exponent
						* @throws std::invalid_argument
						*/
						template <typename T, typename C>
							Integer<T, C> pow (const Integer<T, C>& x, int exp) throw (std::invalid_argument) {
								if (exp < 0) throw std::invalid_argument("pow()");
								if(!exp) return Integer<T, C>::ONE; //x^0==1
								if(exp & 1){ //if exp is odd
									Integer<T, C> e = pow(x, exp/2);
									return e*e*x;
								}
								Integer<T, C> e = pow(x, exp/2);
								return e*e;
							}

		} // integer
	} // prog
} // alg

#endif // Integer_h

