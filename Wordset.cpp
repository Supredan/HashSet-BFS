#include "Wordset.hpp"
#include <string>
#include <cmath>
#include <deque>
#include <sstream>
#include <vector>

const int BASE_TO_USE = 41;
const double LOAD_LIMIT = 0.27;

void bigAdd(std::string num1,std::string num2,std::string &res){
    int carry=0;
    int len1=num1.length()-1;
    int len2=num2.length()-1;
    res="";
    while(len1>=0 || len2>=0){
        int a=len1>=0 ? num1[len1--]-'0' : 0;
        int b=len2>=0 ? num2[len2--]-'0' : 0;
        int tmp=a+b+carry;
        carry=tmp/10;
        res=std::to_string(tmp%10)+res;
    }
    if(carry){
        res=std::to_string(carry)+res;
    }
}

int bigMod(std::string bigNumber,int divisor)
{
    int i,len,ans=0;
    len = bigNumber.size();
    for(i=0;i<len;i++)
    {
        ans = ans*10 + bigNumber[i]-'0';
        ans = ans % divisor;
    }
    return ans;
}

// Multiplies str1 and str2, and prints result. 
std::string bigMultiply(std::string num1, std::string num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
        return "0";

    // will keep the result number in vector 
    // in reverse order
    std::vector<int> result(len1 + len2, 0);

    // Below two indexes are used to find positions
    // in result.  
    int i_n1 = 0;
    int i_n2 = 0;

    // Go from right to left in num1 
    for (int i=len1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';

        // To shift position to left after every 
        // multiplication of a digit in num2 
        i_n2 = 0;

        // Go from right to left in num2              
        for (int j=len2-1; j>=0; j--)
        {
            // Take current digit of second number 
            int n2 = num2[j] - '0';

            // Multiply with current digit of first number 
            // and add result to previously stored result 
            // at current position.  
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;

            // Carry for next iteration 
            carry = sum/10;

            // Store result 
            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        // store carry in next cell 
        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        // To shift position to left after every 
        // multiplication of a digit in num1. 
        i_n1++;
    }

    // ignore '0's from the right 
    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
        i--;

    // If all were '0's - means either both or 
    // one of num1 or num2 were '0' 
    if (i == -1)
        return "0";

    // generate the result std::string 
    std::string s = "";

    while (i >= 0)
        s += std::to_string(result[i--]);

    return s;
}

// returns s, as a number in the given base, mod the given modulus
int hashFunction(std::string s, int base, int mod)
{
    int sz = s.size();
    std::string result = "0";
    for (int i = sz - 1; i >=0 ; --i) {
        int value = s[i] - 'a';
        std::string mut = std::to_string(value);
        for (int j = 0; j < sz - i -1; ++j) {
            mut = bigMultiply(mut, std::to_string(base));
        }
        bigAdd(mut, result, result);
    }
	return bigMod(result, mod);
}


WordSet::WordSet()
{
    size = 0;
    mod = 0;
    capacity = SIZES[mod];
    array = new std::string*[capacity]();
}

WordSet::~WordSet()
{
    delete [] array;
    array = nullptr;
}

void WordSet::insert(std::string s)
{
    int hash = hashFunction(s, BASE_TO_USE, capacity);
    int count = 0;
    while (array[hash] != nullptr) {
        hash += pow(++count, 2);
        hash = hash % capacity;
    }
    array[hash] = new std::string(s);
    size++;

    //rehash
    if (size > floor(capacity * LOAD_LIMIT)) {
        int old_capacity = capacity;
        capacity = SIZES[++mod];

        auto **new_array = new std::string*[capacity]();

        for (int i = 0; i < old_capacity; ++i) {
            if (array[i] != nullptr)
            {
                int hash_new = hashFunction(*array[i], BASE_TO_USE, capacity);
                int count_new = 0;
                while (new_array[hash_new] != nullptr) {
                    hash_new += pow(++count_new, 2);
                    hash_new = hash_new % capacity;
                }
                new_array[hash_new] = array[i];
            }
        }

        delete [] array;
        array = new_array;
    }
}


bool WordSet::contains(std::string s) const
{
    int hash = hashFunction(s, BASE_TO_USE, capacity);
    int count = 0;
    while (array[hash] != nullptr) {
        std::string t = *array[hash];
        if (t == s)
            return true;
        hash += pow(++count, 2);
        hash = hash % capacity;
    }
	return false;
}

int WordSet::getCount() const {
    return size;
}

int WordSet::getCapacity() const {
    return capacity;
}

