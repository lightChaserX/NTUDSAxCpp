
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
 
#define numDecode(c) ((c - 1) % 13 + 1)
#define patDecode(c) ((c - 1) / 13)
 
using namespace std;
const int MAX = 216;
const int MIN = -216;
const int lower = 216;
 
typedef std::bitset<59> stateContrainer;
 
unordered_map<char, int> maps_num, maps_pattern;
unordered_map<unsigned long long, int> state_hash;
unordered_map<int, int> AliceInverse, BobInverse;
 
void build_maps(void) {
    maps_num['A'] = 1;
    maps_num['T'] = 10;
    maps_num['J'] = 11;
    maps_num['Q'] = 12;
    maps_num['K'] = 13;
    for (int i = 2; i < 10; i++) maps_num[char(i) + '0'] = i;
    maps_pattern['C'] = 0;
    maps_pattern['D'] = 1;
    maps_pattern['H'] = 2;
    maps_pattern['S'] = 3;
}
 
unsigned long long hash_state(const int &alpha, const int &beta,
    const int &num, const int &pattern,
    const int &Amove, const int &Bmove,
    const int &who, unsigned long long state) {
    state = (state & 576460752269869056);
    unsigned long long tmp;
    // |n|n|who x|beta xxxxxxxxx|alpha xxxxxxxxx|pattern xx|num xxxx|
    tmp = num;
    state = (state | tmp);
    tmp = pattern;
    state = (state | (tmp << 4));
    tmp = alpha + lower;
    state = (state | (tmp << 6));
    tmp = beta + lower;
    state = (state | (tmp << 15));
    tmp = who;
    state = (state | (tmp << 24));
    if ((Amove > 0) && (Bmove == 0)) {
        tmp = 1;
        state = (state | (tmp << (25 + Amove - 1)));
    }
    if ((Bmove > 0) && (Amove == 0)) {
        tmp = 1;
        state = (state | (tmp << (42 + Bmove - 1)));
    }
    return state;
}
 
int vectorSum(vector<int> vector) {
    int sum_of_elems = 0;
    /*for (int i = 0; i < vector.size(); i++) {
        if (vector[i] == 1) {
            sum_of_elems += ((i - 1) % 13) + 1;
        }
    }*/
    for (auto v : vector) sum_of_elems += (v - 1) % 13 + 1;
    return sum_of_elems;
}
 
int constructTree(const vector<int>& Alice, const vector<int>& Bob,
    int lastPockerNum, int lastPockerPattern,
    int Amove, int Bmove, int depth,
    int alpha, int beta, unsigned long long state) {
    int aliceSize = Alice.size(),
        bobSize = Bob.size();
 
    if ((aliceSize > 0) && (bobSize > 0)) {
        bool aliceTrue;
        vector<int> indix;
        int pass = 0, value = 0, best = 0;
 
        aliceTrue = ((depth % 2 == 0) ? true : false);
 
        unsigned long long currentState;
        if ((lastPockerNum == -1) && (lastPockerPattern == -1)) {
            currentState = hash_state(alpha, beta, 15, 3,
                Amove, Bmove, aliceTrue, state);
        }
        else {
            currentState = hash_state(alpha, beta, lastPockerNum, lastPockerPattern,
                Amove, Bmove, aliceTrue, state);
        }
        if (state_hash.find(currentState) == state_hash.end()) {
            if (aliceTrue) {
                best = MIN;
                for (int i = 0; i < aliceSize; i++) {
                    int currentNum = numDecode(Alice[i]);
                    int currentPattern = patDecode(Alice[i]);
                    if ((lastPockerNum == -1) && (lastPockerPattern == -1)) {
                        auto cloned = std::vector<int>(Alice.begin(), Alice.end());
                        cloned.erase(cloned.begin() + i);
                        pass = 1;
                        value = constructTree(cloned, Bob, currentNum, currentPattern,
                            AliceInverse[Alice[i]], 0, depth + 1, alpha, beta, currentState);
                        //check
                        best = ((best > value) ? best : value);
                        alpha = ((best > alpha) ? best : alpha);
                        if (beta <= alpha) break;
                    }
                    else if ((currentNum == lastPockerNum) ||
                        (currentPattern == lastPockerPattern)) {
                        auto cloned = std::vector<int>(Alice.begin(), Alice.end());
                        cloned.erase(cloned.begin() + i);
                        pass = 1;
                        value = constructTree(cloned, Bob, currentNum, currentPattern,
                            AliceInverse[Alice[i]], 0, depth + 1, alpha, beta, currentState);
                        best = ((best > value) ? best : value);
                        alpha = ((best > alpha) ? best : alpha);
                        if (beta <= alpha) break;
                    }
                }
                if (pass == 0) {
                    value = constructTree(Alice, Bob, -1, -1,
                        0, 0, depth + 1, alpha, beta, currentState);
                    best = ((best > value) ? best : value);
                    alpha = ((best > alpha) ? best : alpha);
                }
                state_hash[currentState] = best;
                return best;
            }
            else {
                best = MAX;
                for (int i = 0; i < bobSize; i++) {
                    int currentNum = numDecode(Bob[i]);
                    int currentPattern = patDecode(Bob[i]);
                    if ((lastPockerNum == -1) && (lastPockerPattern == -1)) {
                        auto cloned = std::vector<int>(Bob.begin(), Bob.end());
                        cloned.erase(cloned.begin() + i);
                        pass = 1;
                        value = constructTree(Alice, cloned, currentNum, currentPattern,
                            0, BobInverse[Bob[i]], depth + 1, alpha, beta, currentState);
                        best = ((best < value) ? best : value);
                        beta = ((best < beta) ? best : beta);
                        if (beta <= alpha) break;
                    }
                    else if ((currentNum == lastPockerNum) || (currentPattern == lastPockerPattern)) {
                        auto cloned = std::vector<int>(Bob.begin(), Bob.end());
                        cloned.erase(cloned.begin() + i);
                        pass = 1;
                        value = constructTree(Alice, cloned, currentNum, currentPattern,
                            0, BobInverse[Bob[i]], depth + 1, alpha, beta, currentState);
                        best = ((best < value) ? best : value);
                        beta = ((best < beta) ? best : beta);
                        if (beta <= alpha) break;
                    }
                }
                if (pass == 0) {
                    value = constructTree(Alice, Bob, -1, -1,
                        0, 0, depth + 1, alpha, beta, currentState);
                    best = ((best < value) ? best : value);
                    beta = ((best < beta) ? best : beta);
                }
                state_hash[currentState] = best;
                return best;
            }
        }
        else {
            //printf("%d ", best);            
            return state_hash[currentState];
        }
    }
    if (aliceSize == 0) {
        return vectorSum(Bob);
    }
    else if (bobSize == 0) {
        return -vectorSum(Alice);
    }
    else return MIN;
}
 
int main() {
    build_maps();
    int n = 0;
 
    vector<string> A, B;
    cin >> n;
    string tem_str;
    for (int j = 0; j < n; j++)
    {
        cin >> tem_str;
        A.push_back(tem_str);
    }
    for (int j = 0; j < n; j++)
    {
        cin >> tem_str;
        B.push_back(tem_str);
    }
 
    vector<int> Alice, Bob;
    for (int i = 0; i < A.size(); i++) {
        Alice.push_back(maps_pattern[A[i][0]] * 13 + maps_num[A[i][1]]);
        Bob.push_back(maps_pattern[B[i][0]] * 13 + maps_num[B[i][1]]);
        AliceInverse[maps_pattern[A[i][0]] * 13 + maps_num[A[i][1]]] = i + 1;
        BobInverse[maps_pattern[B[i][0]] * 13 + maps_num[B[i][1]]] = i + 1;
    }
    auto state = hash_state(MIN, MAX, 0, 0, 0, 0, false, 0);
    auto best = constructTree(Alice, Bob, -1, -1, 0, 0, 0, MIN, MAX, state);
    if (best >= 0) { printf("Alice\n%d", best); }
    if (best < 0) { printf("Bob\n%d", -best); }
}
