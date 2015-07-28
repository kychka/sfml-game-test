#include <iostream>
#include <random>

using namespace std;

int main(int argc, char* argv[]) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> uid(0, 50);
    
    char ch;
    auto guess = 0;
    int secret = uid(gen);
    cout << "I've put forth the number. Can you guess it?\n";
    do {
        cin >> guess;
        if(guess == secret) {
            cout << "Good!";
            break;
        }
        else {
            if(guess < secret) cout << "No! Too small...\n";
            else cout << "Too big...\n";
        }
        cout << "Continue? (Y/n)\n";
        cin >> ch;
        if(ch == 'n' || ch == 'N') {
            cout << "LOOSER!\n";
            break;
        }
    } while (true);
}
