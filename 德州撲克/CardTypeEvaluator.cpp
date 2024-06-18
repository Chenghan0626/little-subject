#include "CardTypeEvaluator.h"
#include <algorithm>
void CardTypeEvaluator::sortHand(Card* hand) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4 - i; ++j) {
            if (hand[j].value > hand[j + 1].value) {
                std::swap(hand[j], hand[j + 1]);
            }
        }
    }
}
const char* CardTypeEvaluator::evaluateHand(Card* hand) {
    sortHand(hand);
    if (isRoyalFlush(hand)) return "Royal Flush";
    if (isStraightFlush(hand)) return "Straight Flush";
    if (isFourOfAKind(hand)) return "Four of a Kind";
    if (isFullHouse(hand)) return "Full House";
    if (isFlush(hand)) return "Flush";
    if (isStraight(hand)) return "Straight";
    if (isThreeOfAKind(hand)) return "Three of a Kind";
    if (isTwoPair(hand)) return "Two Pair";
    if (isPair(hand)) return "Pair";
    return "High Card";
}
int CardTypeEvaluator::getHandRank(const char* type) {
    if (strcmp(type, "Royal Flush") == 0) return 10;
    if (strcmp(type, "Straight Flush") == 0) return 9;
    if (strcmp(type, "Four of a Kind") == 0) return 8;
    if (strcmp(type, "Full House") == 0) return 7;
    if (strcmp(type, "Flush") == 0) return 6;
    if (strcmp(type, "Straight") == 0) return 5;
    if (strcmp(type, "Three of a Kind") == 0) return 4;
    if (strcmp(type, "Two Pair") == 0) return 3;
    if (strcmp(type, "Pair") == 0) return 2;
    return 1;
}
int CardTypeEvaluator::compareHands(Card* hand1, Card* hand2) {
    sortHand(hand1);
    sortHand(hand2);

    const char* type1 = evaluateHand(hand1);
    const char* type2 = evaluateHand(hand2);

    int rank1 = getHandRank(type1);
    int rank2 = getHandRank(type2);

    if (rank1 != rank2) {
        return rank1 > rank2 ? 1 : -1;
    }
    switch (rank1) {
    case 10: 
    case 9:
    case 5:
        return hand1[4].value - hand2[4].value;

    case 8:
        return hand1[2].value - hand2[2].value; 
    case 7: 
        if (hand1[2].value != hand2[2].value)
            return hand1[2].value - hand2[2].value;
        return hand1[0].value - hand2[0].value;

    case 6: 
    case 1: 
        for (int i = 4; i >= 0; --i) {
            if (hand1[i].value != hand2[i].value)
                return hand1[i].value - hand2[i].value;
        }
        return 0;

    case 4: 
        if (hand1[2].value != hand2[2].value)
            return hand1[2].value - hand2[2].value;
        if (hand1[4].value != hand2[4].value)
            return hand1[4].value - hand2[4].value;
        return hand1[3].value - hand2[3].value;

    case 3: 
        if (hand1[3].value != hand2[3].value)
            return hand1[3].value - hand2[3].value;
        if (hand1[1].value != hand2[1].value)
            return hand1[1].value - hand2[1].value;
        return hand1[4].value - hand2[4].value;

    case 2: 
        if (hand1[1].value != hand2[1].value)
            return hand1[1].value - hand2[1].value;
        if (hand1[4].value != hand2[4].value)
            return hand1[4].value - hand2[4].value;
        if (hand1[3].value != hand2[3].value)
            return hand1[3].value - hand2[3].value;
        return hand1[2].value - hand2[2].value;

    default:
        return 0;
    }
}
bool CardTypeEvaluator::isRoyalFlush(const Card* hand) {
    if (!isStraightFlush(hand)) return false;
    return hand[0].value == 10 && hand[1].value == 11 && hand[2].value == 12 && hand[3].value == 13 && hand[4].value == 1;
}
bool CardTypeEvaluator::isStraightFlush(const Card* hand) {
    if (!isFlush(hand)) return false;
    return isStraight(hand);
}
bool CardTypeEvaluator::isFourOfAKind(const Card* hand) {
    for (int i = 0; i <= 1; ++i) {
        if (hand[i].value == hand[i + 1].value && hand[i].value == hand[i + 2].value && hand[i].value == hand[i + 3].value) {
            return true;
        }
    }
    return false;
}
bool CardTypeEvaluator::isFullHouse(const Card* hand) {
    if ((hand[0].value == hand[1].value && hand[0].value == hand[2].value && hand[3].value == hand[4].value) ||
        (hand[0].value == hand[1].value && hand[2].value == hand[3].value && hand[2].value == hand[4].value)) {
        return true;
    }
    return false;
}
bool CardTypeEvaluator::isFlush(const Card* hand) {
    char suit = hand[0].suit;
    for (int i = 1; i < 5; ++i) {
        if (hand[i].suit != suit) return false;
    }
    return true;
}
bool CardTypeEvaluator::isStraight(const Card* hand) {
    for (int i = 0; i < 4; ++i) {
        if (hand[i].value + 1 != hand[i + 1].value) {
            return false;
        }
    }
    return true;
}
bool CardTypeEvaluator::isThreeOfAKind(const Card* hand) {
    for (int i = 0; i <= 2; ++i) {
        if (hand[i].value == hand[i + 1].value && hand[i].value == hand[i + 2].value) {
            return true;
        }
    }
    return false;
}
bool CardTypeEvaluator::isTwoPair(const Card* hand) {
    int pairs = 0;
    for (int i = 0; i < 4; ++i) {
        if (hand[i].value == hand[i + 1].value) {
            ++pairs;
            ++i;
        }
    }
    return pairs == 2;
}
bool CardTypeEvaluator::isPair(const Card* hand) {
    for (int i = 0; i < 4; ++i) {
        if (hand[i].value == hand[i + 1].value) {
            return true;
        }
    }
    return false;
}
