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

const int max = 101;
const int mod = 1000000007;
int c[max][max], solved[max][max]; // init solved false
int C(int n, int m) {
	if(solved[n][m] == true) return c[n][m];

	if(m >= 0 && n >= 0) {
		solved[n][m] = true;
		if(n == m || m == 0)
			return c[n][m] = 1;
		else
			return c[n][m] = (C(n - 1, m) + C(n - 1, m - 1)) % mod;
	}
}

bool checkBox(const int & Row1, const int & Col1, const int & Row2, const int & Col2, const char S[][10]) {
	for(int i = Row1; i <= Row2; i++) {
		for(int j = Col1; j <= Col2; j++) {
			if(S[i - 1][j - 1] == 'X') return false;
		}
	}
	return true;
}

long long hash_state(const int & Row1, const int & Col1, const int & Row2, const int & Col2, const int & K) {
	long long state = 0;
	long long tmp;
	state = (state & 8388608);
	tmp = K;
	state = (state | tmp);
	tmp = Col1;
	state = (state | (tmp << 7));
	tmp = Col2;
	state = (state | (tmp << 11));
	tmp = Row1;
	state = (state | (tmp << 15));
	tmp = Row2;
	state = (state | (tmp << 19));
	return state % 8388608;
}

std::unordered_map <long long, int> hashTable;

long long teerPaper(const int & Row1, const int & Col1, const int & Row2, const int & Col2, const int & K, const char S[][10]) {

	if((Row2 - Row1 + 1) * (Col2 - Col1 + 1) <= K && K > 0) { return 0; }
	else if(((Row2 - Row1 < 0) || (Col2 - Col1 < 0)) && K > 0) { return 0; }
	else if(K == 0) { return 1; }

	auto state = hash_state(Row1, Col1, Row2, Col2, K);
	if(hashTable.find(state) != hashTable.end()) { return hashTable[state]; }

	long long sum = 0;
	for(int K_A = 0; K_A <= K - 1; K_A++) {
		for(int X = Row1; X <= Row2; X++) {
			if(checkBox(X, Col1, X, Col2, S) && (((X - 1 >= Row1) && (X - 1 <= Row2)) || ((X + 1 >= Row1) && (X + 1 <= Row2)))) {
				long long V_A = teerPaper(Row1, Col1, X - 1, Col2, K_A, S);
				auto stateA = hash_state(Row1, Col1, X - 1, Col2, K_A);
				hashTable[stateA] = V_A;
				if(V_A == 0) sum += 0;
				else {
					long long V_B = teerPaper(X + 1, Col1, Row2, Col2, K - 1 - K_A, S);
					sum += (((C(K - 1, K_A) * V_A) % mod)  * V_B) % mod;
					sum %= mod;
					auto stateB = hash_state(X + 1, Col1, Row2, Col2, K - 1 - K_A);
					hashTable[stateB] = V_B;
				}
			}
		}
		for(int Y = Col1; Y <= Col2; Y++) {
			if(checkBox(Row1, Y, Row2, Y, S) && (((Y - 1 >= Col1) && (Y - 1 <= Col2)) || ((Y + 1 >= Col1) && (Y + 1 <= Col2)))) {
				long long V_A = teerPaper(Row1, Col1, Row2, Y - 1, K_A, S);
				auto stateA = hash_state(Row1, Col1, Row2, Y - 1, K_A);
				hashTable[stateA] = V_A;
				if(V_A == 0) sum += 0;
				else {
					long long V_B = teerPaper(Row1, Y + 1, Row2, Col2, K - 1 - K_A, S);
                    sum += (((C(K - 1, K_A) * V_A) % mod)  * V_B) % mod;
					sum %= mod;
					auto stateB = hash_state(Row1, Y + 1, Row2, Col2, K - 1 - K_A);
					hashTable[stateB] = V_B;
				}
			}
		}
	}
	return sum;
}



int main() {
	/*****************/
	clock_t begin = clock();
	/*****************/
	int N = 0, M = 0;
	scanf("%d %d", &N, &M);
	char SMat[10][10];
	char tmp;
	int numX = 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			std::cin >> tmp;
			SMat[i][j] = tmp;
			if(tmp == 'X') numX++;
		}
	}
    
	long long num = 0;
	for(int K = M * N - numX; K >= 0; K--) {
		num += teerPaper(1, 1, N, M, K, SMat);
        num %= mod;
	}
    

	std::cout << num << std::endl;
}
