#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Licensing.h"
#include "CardTypeEvaluator.h"
using namespace std;
int main() {
    int playerCount;
    cout << "請輸入玩家數量: ";
    cin >> playerCount;

    srand(static_cast<unsigned int>(time(nullptr)));

    Licensing licensing(playerCount);
    licensing.shuffle();

    for (int i = 0; i < playerCount; ++i) {
        Card* hand = licensing.deal();
        cout << "玩家 " << i + 1 << " 的手牌: ";
        for (int j = 0; j < 5; ++j) {
            cout << hand[j].value << hand[j].suit << " ";
        }
        cout << endl;

        const char* type = CardTypeEvaluator::evaluateHand(hand);
        cout << "牌型: " << type << endl;
        delete[] hand;
    }

    return 0;
}
