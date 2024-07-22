#include<iostream>
#include<string>
#include<vector>
#include<set>

using namespace std;

class TPerson {
private:
    string name[3];
    int birthDate[3];

    int countSymbolsInName() {
        set<char> symbols;
        for (string& namePart : name) {
            for (char symbol : namePart) {
                symbols.insert(symbol);
            }
        }
        return symbols.size();
    }

    int sumDigitsInBirthDate() {
        int sum = 0;
        for (int i = 0; i < 2; i++) {
            int birthDatePart = birthDate[i];
            while (birthDatePart > 0) {
                sum += birthDatePart % 10;
                birthDatePart /= 10;
            }
        }
        return sum;
    }

    static int readFromToComma(const string& fromStr, int i, string& toStr) {
        toStr = "";
        while (fromStr[i] && fromStr[i] != ',') {
            toStr += fromStr[i];
            i++;
        }
        return i + 1;
    }

    static int readIntFromToComma(const string& fromStr, int i, int& toInt) {
        string str;
        i = readFromToComma(fromStr, i, str);
        toInt = stoi(str);
        return i;
    }

    static string toHex(int x) {
        string ans;
        int d = 16 * 16;
        while (d > 0) {
            if (x / d < 10) {
                ans += '0' + x / d;
            }
            else {
                ans += 'A' + x / d - 10;
            }
            x %= d;
            d /= 16;
        }
        return ans;
    }

public:
    TPerson(const string& csv) {
        int i = 0;
        for (string& namePart : name) {
            i = readFromToComma(csv, i, namePart);
        }
        for (int& birthDatePart : birthDate) {
            i = readIntFromToComma(csv, i, birthDatePart);
        }
    }

    string GetCipher() {
        int fullCipher = countSymbolsInName() + 64 * sumDigitsInBirthDate() + 256 * (toupper(name[0][0]) - 'A' + 1);
        return toHex(fullCipher % 4096); // 16^3 = 4096
    }
};

int main()
{
    int N;
    cin >> N;
    while (N > 0) {
        string inputCSV;
        cin >> inputCSV;
        TPerson Person(inputCSV);
        cout << Person.GetCipher();

        N--;
        if (N > 0) {
            cout << " ";
        }
        else {
            cout << endl;
        }
    }
    return 0;
}
