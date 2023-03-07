/** ***************************************************************************
 * @assignment: Project 2
 * @file:   main.cpp
 * @author: Zach Gassner & Justin Blechel
 * @date:   Revised: 3 March 2023
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
#include <sstream>
#include <iterator>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>

// function declarations
int delta(int, int, int);
std::string findString(int, const std::vector<int>&);
bool valid(int k, const std::vector<int>&);
void check(int, const std::string&);



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
 * validate the preconditions of the findString function
 * check if k >= 0
 * check if the vector is a valid set, valid digits = {0, 1, 2,..., 9}
 * @param   v vector to check
 * @pre     vector
 * @post    true if vector contains only digits 1-9, else false
 *
 *****************************************************************************/
bool valid(int k, const std::vector<int>& v) {
    if (k <= 0) {
        std::cout << "\nError: k cannot be less than or equal to 0" << std::endl;
        return false;
    }
    else if (v.empty()) {
        std::cout << "\nError: set S is empty" << std::endl;
        return false;
    }
    else if (!std::all_of(v.cbegin(),v.cend(),[](int i){return i >= 0 && i <= 9;})) {
        std::cout << "\nError: out of range digit/s in set S" << std::endl;
        return false;
    }
    return true;
}



/** ***************************************************************************
 * The algorithm FindString takes as input a positive integer k, and
 * a subset S of {0, 1, 2, · · · , 9} and outputs
 * the smallest positive integer y > 0 that is an integer multiple of k,
 * and has only the digits (in decimal) from the set S.
 * @param   k positive integer
 * @param   S input alphabet, subset of digits 0-9
 * @pre     k > 0
 *          digit s of subset S: 0 < s <= 9
 * @post
 *
 *****************************************************************************/
std::string findString(int k, const std::vector<int>& S) {

    // validate parameters k and S
    if (!valid(k, S)) return "";

    std::queue<int> Q;
    std::vector<bool> visited(k, false); // for all j in {0, 1, ..., k-1} visited[j] = false;
    std::vector<int> parent(k, -1), label(k);

    // initialize starting state
    Q.push(0);
    visited[0] = true;

    // initialize current, next and last state
    int curr, next, last;

    // for each digit 's' in subset 'S' (input alphabet)
    for (auto & s : S) {
        next = delta(0, s, k);  // next state
        visited[next] = true;         // visited = true
        Q.push(next);
        parent[next] = 0;
        label[next] = s;
    }


    while (!Q.empty()) {
        bool flag = false;
        curr = Q.front();
        Q.pop();
        for (auto & s : S) {
            next = delta(curr, s, k); // delta(q, r, k) = (10 * q + r) % k
            if (next == 0) { // accepting state is reached
                parent[next] = curr;
                label[next] = s;
                last = s;
                flag = true;
                break; // out of the loop - final state
            } else if (!visited[next]) {
                visited[next] = true;
                parent[next] = curr;
                label[next] = s;
                Q.push(next);
            }
        }
        if (flag) break; // out of the loop - final state
    }

    if (next != 0) { // output no solution
        return "";
    }

    else { // trace string using parent pointers and concatenate corresponding labels

        // A string stream associates a string object with a stream
        // allowing us to read from the string as if it were a stream
        std::stringstream stream;

        // trace string using parent pointers
        while (curr != 0) {
            stream << label[curr];
            curr = parent[curr];
        }

        // create a temporary string to store the stream
        const std::string &temp = stream.str();

        stream.seekp(0); // set the position of the next character to be inserted to 0

        stream << last;  // add the last state to the front (will be reversed)

        stream << temp;  // concatenate the strings

        // initialize string 'N' to the concatenated string stream
        std::string N = stream.str();

        // reverse string 'N' to get the correct result
        std::reverse(N.begin(), N.end());

        return N; // return the resulting string 'N'
    }
}



/** ***************************************************************************
 * check if N % k = 0
 * @param   k positive integer
 * @param   N positive integer represented by a string
 * @pre     k > 0
 *          N is not empty, can be stored as unsigned long long
 * @post    output that the solution was validated OR
 *          that an OOR error occurred and it was unable to validate
 *****************************************************************************/
void check(int k, const std::string& N){
    try {
        if (!N.empty() && std::stoull(N) % k == 0) {
            std::cout << "solution is valid: ";
        }
    }
    catch (const std::out_of_range& out_of_range) {
        std::cout << "out of range error, solution too large for simple validation: " << std::endl;
    }
}

/** ***************************************************************************
 * main procedure tests all cases given
 * initialize i test cases (k, S)
 * call findString on test case i
 * output result and repeat for test case i + 1
 *****************************************************************************/
int main() {
    // start a timer for i test cases
    auto totalStart = std::chrono::high_resolution_clock::now();

    // initialize array of positive integers k
    std::vector<int> v = {26147, 92917, 198217, 135, 97911, 97979, 1355};

    // initialize array of subsets S
    std::vector<std::vector<int>> m = {{1, 3}, {0, 1}, {1}, {1, 3, 7}, {1, 3}, {0, 1}, {1, 3, 7}};

    std::cout << std::endl;
    // loop through test cases
    for (int i = 0; i < v.size(); ++i) {
        std::cout << "Test Case " << i+1 << ": \n===========================================\n";
        int k = v[i];
        std::vector<int> S = m[i];
        std::cout << "k = " << k << ", S = {";
        for (int j = 0; j < S.size()-1; ++j) {
            std::cout << S[j] << ", ";
        }
        std::cout << S[S.size()-1] << "}" << std::endl;

        // time the function findString on test case i
        auto start = std::chrono::high_resolution_clock::now();
        std::string N = findString(k, S);
        auto stop = std::chrono::high_resolution_clock::now();

        if (N.empty()) // if N is empty no solution was found
            std::cout << "No solution found." << std::endl;

        check(k, N); // check if N % k = 0

        if (!N.empty()) // if k has a solution N (N is not empty), output it
            std::cout << N << std::endl;

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time taken by findString function: "
                  << duration.count() << "us\n===========================================" << std::endl << std::endl;
    }

    // end timer for test cases and output result
    auto totalStop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(totalStop - totalStart);
    std::cout << "* Time taken to execute " << v.size() << " test cases: ~"
              << duration.count() << "ms" << std::endl;
    return 0;
}
