/** ***************************************************************************
 * @assignment: Project 2
 * @file:   main.cpp
 * @author: Zach Gassner & Justin Blechel
 * @date:   Revised: 28 February 2023
 * @desc: Given a positive integer k > 0, and a subset S of {0,1,2,...,9} of digits,
 * the goal is to find the smallest positive integer N > 0
 * such that N % k = 0 and N uses only the digits from the set S.
 * As an example, if k = 26147 and S = {1, 3}, the value of N = 1113313113.
 *
 * @remark: A DFA (deterministic finite automaton) 'M' is defined by a 5-tuple:
 *     M = <Q, Σ, δ, q₀, F>
 *      - Q: finite set of states
 *      – Σ: finite alphabet
 *      – δ: transition function δ:QxΣ->Q
 *      – q₀∈Q: start state
 *      – F⊆Q: set of accepting states
 *
 * Create a DFA M = <Q, Σ, δ, 0, F> where Q = {0,1,2,...,9}, F = {0},
 * and δ(j, a) = (10 * j + a) % k
 *
 *****************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

//
int delta(int, int, int);
std::string findString(int, const std::vector<int>&);
bool isValidSet(const std::vector<int>&);

/** ***************************************************************************
 * delta function δ(j, a) = (10 ∗ j + a) % k
 * @param   q state of DFA M
 * @param   r digit of subset S
 * @param   k integer to divide
 * @pre     q >= 0,
 *          r ∈ S,
 *          k > 0,
 * @post    int >= 0
 *
 *****************************************************************************/
int delta(int q, int r, int k) {
    if (r == 0 && (q == 0 || q == k)) return k;
    else return (10 * q + r) % k;
}

/** ***************************************************************************
 * check if vector is a valid set, valid digits = {0, 1, 2,..., 9}
 * @param   v vector to check
 * @pre
 * @post
 *
 *****************************************************************************/
bool isValidSet(const std::vector<int>& v) {
    return std::all_of(v.cbegin(),v.cend(),[](int i){return i >= 0 && i < 10;});
}


/** ***************************************************************************
 * The algorithm FindString takes as input a positive integer k, and
 * a subset S of {0, 1, 2, · · · , 9} and outputs
 * the smallest positive integer y > 0 that is an integer multiple of k,
 * and has only the digits (in decimal) from the set S.
 * @param   k positive integer
 * @param   D alphabet
 * @pre     k > 0,
 * @post
 *
 *****************************************************************************/
std::string findString(int k, const std::vector<int>& S) {

    if (!isValidSet(S)) return "no solution";



    std::queue<int> Q;
    std::vector<bool> visited(k, false);
    std::vector<int> parent(k, -1), label(k);

    Q.push(0);
    visited[0] = true;

    int next = 0;
    int tail;

    for (int s : S) {
        next = delta(0, s, k);
        visited[next] = true;
        Q.push(next);
        parent[next] = 0;
        label[next] = s;
    }
    int curr;
    bool flag = false;
    while (!Q.empty()) {
        curr = Q.front();
        Q.pop();
        for (int s : S) {
            next = delta(curr, s, k); // delta(q, r, k) = (10 * q + r) % k
            if (next == 0) { // accepting state is reached
                parent[next] = curr;
                label[next] = s;
                tail = s;
                flag = true;
                break; // out of the while loop
            } else if (!visited[next]) {
                visited[next] = true;
                parent[next] = curr;
                label[next] = s;
                Q.push(next);
            }
        }
        if (flag) break;
    }

    if (next != 0) return "no solution"; // output no solution
    else {



        std::string N;
        // trace the string using parent pointers and
        // concatenate the corresponding labels and
        while (curr != 0) {
            N += char(label[curr]);
            curr = parent[curr];
        }
        // output the reverse of the string.
        std::reverse(N.begin(), N.end());
        N+=char(tail);
        return N;
    }
}

int main() {
    int k = 92917;
    std::vector<int> S = {0, 1};

    std::string result = findString(k, S);

    if (result == "no solution") std::cout << "no solution";
    else {
        for (auto &c: result)
            std::cout << int(c);
    }

    return 0;
}
