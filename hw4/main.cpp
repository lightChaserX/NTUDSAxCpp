#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <deque>
#include <deque>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <ctime>

#define str2num(c) (int(c - 'a') + 1)

using namespace std;
typedef unsigned long long hashType;

const hashType patternNum = 1000000007;
const hashType primeNum = 97;

vector<hashType> rollHashFunc(const string & strX) {
	vector<hashType> HH;
	HH.push_back(0);
	hashType H = str2num(strX[0]);
	HH.push_back(H);
	for(int i = 1; i < strX.length(); i++) {
		H = H * primeNum + str2num(strX[i]);
		//H %= patternNum;
		HH.push_back(H);
	}
	return HH;
}

hashType getHash(const vector<hashType> & HH, const int & left, const int & length, const hashType & pow) {
	hashType va;
	//va = HH[left - 1 + length] - ((hashType)(HH[left - 1] * pow)) % patternNum;
	va = HH[left - 1 + length] - ((hashType)(HH[left - 1] * pow));
	return va;
}

void problem1Solution(const vector<hashType> & HH, const int & mValue, const vector<hashType> & powStore) {
/***********************************************************/
//1 Binary search, find potential length $l$
//2 Given the length $l$*/
/***********************************************************/
	// clock_t begin3 = clock();
	int strN = HH.size() - 1;
	int left = 0,
		mid = 0,
		right = strN;
	int pos = 0, vLength = 0;
	hashType thisKey = 0;
	bool vflag = false;

	while(right - left >= 0) {
		mid = (left + right) / 2;
		int length = mid + 1;
		hashType anchor = 0;
		unordered_map<hashType, int> mapStore;
		bool insideFlag = false;

		for(int j = 0; j < strN - mid; j++) {
			int avalue = 0;
			anchor = getHash(HH, j + 1, length, powStore[length]);

			if(mapStore.find(anchor) == mapStore.end()) { avalue = 1; }
			else { avalue = mapStore[anchor] + 1; }
			mapStore[anchor] = avalue;
			if(avalue >= mValue) {
				vLength = length;
				insideFlag = true;
				vflag = true;
				pos = j;
				break;
			}
		}
		if(insideFlag) left = mid + 1;
		else right = mid - 1;
	}
	unordered_map<hashType, int> mapStore;
	bool insideFlag = false;
	for(int j = 0; j < strN - vLength + 1; j++) {
		int avalue = 0;
		auto anchor = getHash(HH, j + 1, vLength, powStore[vLength]);

		if(mapStore.find(anchor) == mapStore.end()) { avalue = 1; }
		else { avalue = mapStore[anchor] + 1; }
		mapStore[anchor] = avalue;
		if(avalue >= mValue) {
			pos = j;
		}
	}
	if(vflag) {
		cout << vLength << " " << pos << endl;
	}
	else
		cout << "none" << endl;
}

void problem2Solution(const vector<hashType> & HH, const int & mValue, const string & inputStr, const vector<hashType> & powStore) {
	/***********************************************************/
	//1 Binary search, find potential length $l$
	//2 Given the length $l$*/
	/***********************************************************/
	// clock_t begin2 = clock();
	int strN = inputStr.length();
	vector<int> potentialLength;
	vector<hashType> potentialHash;
	int left = 0,
		mid = 0,
		right = strN;
	if(strN > 2) {
		for(int i = 0; i < strN - 2; i++) {
			if((inputStr[0] == inputStr[strN - i - 1]) && (inputStr[strN - 1] == inputStr[i])) {
				hashType prefixHash = getHash(HH, 0 + 1, i + 1, powStore[i + 1]);
				hashType suffixHash = getHash(HH, strN - i, i + 1, powStore[i + 1]);

				if(prefixHash == suffixHash) {
					potentialLength.push_back(i + 1);
					potentialHash.push_back(prefixHash);
				}
			}
		}
	}
	else {
		cout << "Just a legend" << endl;
		return;
	}

	bool flagX2 = false;
	left = 0;
	right = potentialLength.size() - 1;
	int Vlength;
	if(potentialLength.size() == 1) {
		mid = 0;
		int length = potentialLength[mid];
		for(int i = 1; i < strN - length; i++) {
			auto anchorTemp = getHash(HH, i + 1, length, powStore[length]);
			if(potentialHash[mid] == anchorTemp) {
				flagX2 = true;
				Vlength = length;
				break;
			}
		}
	}
	else {
		while(right - left >= 0) {
			bool insideFlag = false;
			mid = ((left + right) / 2);
			int length = potentialLength[mid];
			for(int i = 1; i < strN - length; i++) {
				auto anchorTemp = getHash(HH, i + 1, length, powStore[length]);
				if(potentialHash[mid] == anchorTemp) {
					Vlength = length;
					insideFlag = true;
					flagX2 = true;
					break;
				}
				else insideFlag = false;
			}
			if(insideFlag) left = mid + 1;
			else right = mid - 1;
		}
	}
	if(flagX2) {
		cout << inputStr.substr(0, Vlength) << endl;
	}
	else cout << "Just a legend" << endl;
}

int main() {
	/*precalculate the power*/
	vector<unsigned long long> powStore(100050 + 1, 0);
	unsigned long long tmp = 1;
	powStore[0] = 1;
	for(int i = 1; i <= 100050; i++) {
		//tmp = (tmp * primeNum) % patternNum;
		tmp = (tmp * primeNum);
		powStore[i] = tmp;
	}

	string inputStr;
	int mValue;
	while((cin >> mValue) && (mValue > 0)) {
		cin >> inputStr;
		//getline(cin, inputStr);
		vector<hashType> HH = rollHashFunc(inputStr);

		
		problem1Solution(HH, mValue, powStore);
		
		problem2Solution(HH, mValue, inputStr, powStore);
	}
}
