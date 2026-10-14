#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

// An index card: unique index number, keyword, and note text
class Card {
public:
    int index;
    std::string keyword;
    std::string note;

    Card() : index(-1), keyword(""), note("") {}
    Card(int i) : index(i), keyword(""), note("") {}
    Card(int i, const std::string& k, const std::string& n)
        : index(i), keyword(k), note(n) {}

    // Cards are sorted in the tree by their unique index number
    bool operator<(const Card& other) const { return index < other.index; }
};

inline std::ostream& operator<<(std::ostream& out, const Card& c) {
    out << "[" << c.index << "] " << c.keyword << ": " << c.note;
    return out;
}

#endif
