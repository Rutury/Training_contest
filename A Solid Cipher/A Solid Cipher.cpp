#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Candidate
{
public:
    static const int words_in_name = 3;
    static const int numbers_in_day = 3;
    string name[words_in_name];
    int day[numbers_in_day];

    Candidate(const string& data_in_csv) {
        istringstream data_stream(data_in_csv);
        string cur_word;
        for (int i = 0; getline(data_stream, cur_word, ',') && i < words_in_name + numbers_in_day; i++) {
            if (i < words_in_name) {
                name[i] = cur_word;
            }
            else {
                day[i - words_in_name] = stoi(cur_word);
            }
        }
    }

    int count_uniq_words() {
        set<char> letters;
        for (string& word : name) {
            for (char letter : word) {
                letters.insert(letter);
            }
        }
        return letters.size();
    }

    int sum_digits_in_d_m() {
        int sum = 0;
        for (int i = 0; i < 2; i++) {
            for (int x = day[i]; x > 0; x /= 10) {
                sum += x % 10;
            }
        }
        return sum;
    }

    int get_cipher() {
        int cipher = 0;
        cipher += count_uniq_words();
        cipher += 64 * sum_digits_in_d_m();
        cipher += 256 * (toupper(name[0][0]) - 'A' + 1);
        return cipher % (16 * 16 * 16); 
    }
};

int main() {
    int N;
    string input;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> input;
        Candidate candidate(input);
        int n_digits = 3;
        cout << hex << setw(n_digits) << setfill('0') << uppercase << candidate.get_cipher() << ' ';
    }
    return 0;
}
