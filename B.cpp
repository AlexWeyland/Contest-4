#include <vector>
#include <iostream>

using std::vector;

struct Position {
public:
    int ordinate_;
    int abscissa_;

public:
    void PrintPosition() const {
        std::cout << ordinate_ << ' ' << abscissa_;
    }

    inline bool operator==(const Position &one) const {
        return one.abscissa_ == abscissa_ && one.ordinate_ == ordinate_;
    }

private:
    friend struct Threesome;
};

struct Threesome {
public:
    Position position_;
    bool last_turn_;
    char direction_;

    inline bool operator==(const Threesome &one) const {
        return one.position_ == position_ && one.last_turn_ == last_turn_
               && one.direction_ == direction_;
    }

private:
    friend class Check;
};

Threesome new_where = {{0, 0}, true, 'a'};
Threesome where = {{0, 0}, true, 'a'};

class Check {
public:
    bool lu_ = false;
    bool lr_ = false;
    bool ld_ = false;
    bool ll_ = false;
    bool ru_ = false;
    bool rr_ = false;
    bool rd_ = false;
    bool rl_ = false;

public:
    void Add(const Threesome &where) {
        if (where.last_turn_ == false) {
            if (where.direction_ == 'u') {
                lu_ = true;
            } else if (where.direction_ == 'r') {
                lr_ = true;
            } else if (where.direction_ == 'd') {
                ld_ = true;
            } else if (where.direction_ == 'l') {
                ll_ = true;
            }
        } else {
            if (where.direction_ == 'u') {
                ru_ = true;
            } else if (where.direction_ == 'r') {
                rr_ = true;
            } else if (where.direction_ == 'd') {
                rd_ = true;
            } else if (where.direction_ == 'l') {
                rl_ = true;
            }
        }
    }

    bool InFathers(const Threesome &where) const {
        if (where.last_turn_ == false) {
            if (where.direction_ == 'u') {
                if (lu_ == true) {
                    return true;
                }
            } else if (where.direction_ == 'r') {
                if (lr_ == true) {
                    return true;
                }
            } else if (where.direction_ == 'd') {
                if (ld_ == true) {
                    return true;
                }
            } else if (where.direction_ == 'l') {
                if (ll_ == true) {
                    return true;
                }
            }
        } else {
            if (where.direction_ == 'u') {
                if (ru_ == true) {
                    return true;
                }
            } else if (where.direction_ == 'r') {
                if (rr_ == true) {
                    return true;
                }
            } else if (where.direction_ == 'd') {
                if (rd_ == true) {
                    return true;
                }
            } else if (where.direction_ == 'l') {
                if (rl_ == true) {
                    return true;
                }
            }
        }
        return false;
    }
};


Threesome TurnLeft(const Threesome &where) {
    Threesome new_where = where;
    if (where.direction_ == 'u') {
        new_where.direction_ = 'l';
        new_where.position_ = {where.position_.ordinate_, where.position_.abscissa_ - 1};
    }
    if (where.direction_ == 'r') {
        new_where.direction_ = 'u';
        new_where.position_ = {where.position_.ordinate_ - 1, where.position_.abscissa_};
    }
    if (where.direction_ == 'd') {
        new_where.direction_ = 'r';
        new_where.position_ = {where.position_.ordinate_, where.position_.abscissa_ + 1};
    }
    if (where.direction_ == 'l') {
        new_where.direction_ = 'd';
        new_where.position_ = {where.position_.ordinate_ + 1, where.position_.abscissa_};
    }
    new_where.last_turn_ = false;
    return new_where;
}

Threesome TurnRight(const Threesome &where) {
    Threesome new_where = where;
    if (where.direction_ == 'u') {
        new_where.direction_ = 'r';
        new_where.position_ = {where.position_.ordinate_, where.position_.abscissa_ + 1};
    }
    if (where.direction_ == 'r') {
        new_where.direction_ = 'd';
        new_where.position_ = {where.position_.ordinate_ + 1, where.position_.abscissa_};
    }
    if (where.direction_ == 'd') {
        new_where.direction_ = 'l';
        new_where.position_ = {where.position_.ordinate_, where.position_.abscissa_ - 1};
    }
    if (where.direction_ == 'l') {
        new_where.direction_ = 'u';
        new_where.position_ = {where.position_.ordinate_ - 1, where.position_.abscissa_};
    }
    new_where.last_turn_ = true;
    return new_where;
}

Threesome TurnOver(const Threesome &where) {
    Threesome new_where = where;
    if (where.direction_ == 'u') {
        new_where.direction_ = 'd';
        new_where.position_ = {where.position_.ordinate_ + 1, where.position_.abscissa_};
    }
    if (where.direction_ == 'r') {
        new_where.direction_ = 'l';
        new_where.position_ = {where.position_.ordinate_, where.position_.abscissa_ - 1};
    }
    if (where.direction_ == 'd') {
        new_where.direction_ = 'u';
        new_where.position_ = {where.position_.ordinate_ - 1, where.position_.abscissa_};
    }
    if (where.direction_ == 'l') {
        new_where.direction_ = 'r';
        new_where.position_ = {where.position_.ordinate_, where.position_.abscissa_ + 1};
    }

    return new_where;
}

bool InFathers(const Threesome &new_where, const vector<vector<Check>> &fathers) {
    return (fathers[new_where.position_.ordinate_ - 1]
    [new_where.position_.abscissa_ - 1].InFathers(new_where));
}

void BFS(const int &nn, const int &mm, const vector<vector<char>> &country,
         const Position &finish, const Position &start, char &color,
         vector<vector<Check>> &fathers,
         vector<Threesome> &future_free_people, vector<int> &quant, int &step) {
    if (color == 'w') {
        new_where = {start, true, 'a'};
        color = 'b';
        if (start.ordinate_ > 1 && country[start.ordinate_ - 2][start.abscissa_ - 1] == '.') {
            new_where.direction_ = 'u';
            new_where.position_ = {start.ordinate_ - 1, start.abscissa_};
            new_where.last_turn_ = true;
            future_free_people.push_back(new_where);
            quant.push_back(0);
            fathers[start.ordinate_ - 2][start.abscissa_ - 1].Add(new_where);
            new_where.last_turn_ = false;
            future_free_people.push_back(new_where);
            quant.push_back(0);
            fathers[start.ordinate_ - 2][start.abscissa_ - 1].Add(new_where);
        }

        if (start.ordinate_ < nn && country[start.ordinate_][start.abscissa_ - 1] == '.') {
            new_where.direction_ = 'd';
            new_where.position_ = {start.ordinate_ + 1, start.abscissa_};
            new_where.last_turn_ = true;
            future_free_people.push_back(new_where);
            quant.push_back(0);
            fathers[start.ordinate_][start.abscissa_ - 1].Add(new_where);
            new_where.last_turn_ = false;
            future_free_people.push_back(new_where);
            quant.push_back(0);
            fathers[start.ordinate_][start.abscissa_ - 1].Add(new_where);
        }
        if (start.abscissa_ > 1 && country[start.ordinate_ - 1][start.abscissa_ - 2] == '.') {
            new_where.direction_ = 'l';
            new_where.position_ = {start.ordinate_, start.abscissa_ - 1};
            new_where.last_turn_ = true;
            future_free_people.push_back(new_where);
            quant.push_back(0);
            fathers[start.ordinate_ - 1][start.abscissa_ - 2].Add(new_where);
            new_where.last_turn_ = false;
            future_free_people.push_back(new_where);
            quant.push_back(0);
            fathers[start.ordinate_ - 1][start.abscissa_ - 2].Add(new_where);
        }
        if (start.abscissa_ < mm && country[start.ordinate_ - 1][start.abscissa_] == '.') {
            new_where.direction_ = 'r';
            new_where.position_ = {start.ordinate_, start.abscissa_ + 1};
            new_where.last_turn_ = true;
            future_free_people.push_back(new_where);
            quant.push_back(0);
            fathers[start.ordinate_ - 1][start.abscissa_].Add(new_where);
            new_where.last_turn_ = false;
            future_free_people.push_back(new_where);
            quant.push_back(0);
            fathers[start.ordinate_ - 1][start.abscissa_].Add(new_where);
        }
    }

    while (!(future_free_people.size() == static_cast<size_t>(step))) {

        where = future_free_people[step + 1];
        ++step;
        new_where = where;

        if (where.position_ == finish) {
            color = 'u';
            return;
        }

        if (where.direction_ == 'u') {
//            move forward
            if (where.position_.ordinate_ > 1 &&
                country[where.position_.ordinate_ - 2][where.position_.abscissa_ - 1] == '.') {
                new_where.position_ = {where.position_.ordinate_ - 1, where.position_.abscissa_};
                new_where.last_turn_ = where.last_turn_;
                new_where.direction_ = where.direction_;
                if (InFathers(new_where, fathers) == false) {
                    fathers[where.position_.ordinate_ - 2]
                    [where.position_.abscissa_ - 1].Add(new_where);
                    future_free_people.push_back(new_where);
                    quant.push_back(step);
                }
            }
//            turn left
            if (where.last_turn_ == true) {
                if (where.position_.abscissa_ > 1 &&
                    country[where.position_.ordinate_ - 1][where.position_.abscissa_ - 2] == '.') {
                    new_where = TurnLeft(where);
                    if (InFathers(new_where, fathers) == false) {
                        fathers[where.position_.ordinate_ - 1]
                        [where.position_.abscissa_ - 2].Add(new_where);
                        future_free_people.push_back(new_where);
                        quant.push_back(step);
                    }
                }
            }
//            turn right
            if (where.last_turn_ == false) {

                if (where.position_.abscissa_ < mm &&
                    country[where.position_.ordinate_ - 1][where.position_.abscissa_] == '.') {
                    new_where = TurnRight(where);
                    if (InFathers(new_where, fathers) == false) {
                        fathers[where.position_.ordinate_ - 1]
                        [where.position_.abscissa_].Add(new_where);
                        future_free_people.push_back(new_where);
                        quant.push_back(step);
                    }
                }
            }

//            turn over
            if (!(where.position_ == start)) {
                new_where = TurnOver(where);
                if (InFathers(new_where, fathers) == false) {
                    fathers[new_where.position_.ordinate_ - 1]
                    [new_where.position_.abscissa_ - 1].Add(new_where);
                    future_free_people.push_back(new_where);
                    quant.push_back(step);
                }
            }
        }

        if (where.direction_ == 'r') {
            //            move forward
            if (where.position_.abscissa_ < mm &&
                country[where.position_.ordinate_ - 1][where.position_.abscissa_] == '.') {
                new_where.position_ = {where.position_.ordinate_, where.position_.abscissa_ + 1};
                new_where.last_turn_ = where.last_turn_;
                new_where.direction_ = where.direction_;
                if (InFathers(new_where, fathers) == false) {
                    fathers[where.position_.ordinate_ - 1]
                    [where.position_.abscissa_].Add(new_where);
                    future_free_people.push_back(new_where);
                    quant.push_back(step);
                }
            }
//            turn left
            if (where.last_turn_ == true) {
                if (where.position_.ordinate_ > 1 &&
                    country[where.position_.ordinate_ - 2][where.position_.abscissa_ - 1] == '.') {
                    new_where = TurnLeft(where);
                    if (InFathers(new_where, fathers) == false) {
                        fathers[where.position_.ordinate_ - 2]
                        [where.position_.abscissa_ - 1].Add(new_where);
                        future_free_people.push_back(new_where);
                        quant.push_back(step);
                    }
                }
            }
//            turn right
            if (where.last_turn_ == false) {
                if (where.position_.ordinate_ < nn &&
                    country[where.position_.ordinate_][where.position_.abscissa_ - 1] == '.') {
                    new_where = TurnRight(where);
                    if (InFathers(new_where, fathers) == false) {
                        fathers[where.position_.ordinate_]
                        [where.position_.abscissa_ - 1].Add(new_where);
                        future_free_people.push_back(new_where);
                        quant.push_back(step);
                    }
                }
            }

//            turn over
            if (!(where.position_ == start)) {
                new_where = TurnOver(where);
                if (InFathers(new_where, fathers) == false) {
                    future_free_people.push_back(new_where);
                    fathers[new_where.position_.ordinate_ - 1]
                    [new_where.position_.abscissa_ - 1].Add(new_where);
                    quant.push_back(step);
                }
            }
        }

        if (where.direction_ == 'd') {
            //            move forward

            if (where.position_.ordinate_ < nn &&
                country[where.position_.ordinate_][where.position_.abscissa_ - 1] == '.') {
                new_where.position_ = {where.position_.ordinate_ + 1, where.position_.abscissa_};
                new_where.last_turn_ = where.last_turn_;
                new_where.direction_ = where.direction_;
                if (InFathers(new_where, fathers) == false) {
                    future_free_people.push_back(new_where);
                    fathers[where.position_.ordinate_]
                    [where.position_.abscissa_ - 1].Add(new_where);
                    quant.push_back(step);
                }
            }
//            turn left
            if (where.last_turn_ == true) {
                if (where.position_.abscissa_ < mm &&
                    country[where.position_.ordinate_ - 1][where.position_.abscissa_] == '.') {
                    new_where = TurnLeft(where);
                    if (InFathers(new_where, fathers) == false) {
                        fathers[where.position_.ordinate_ - 1]
                        [where.position_.abscissa_].Add(new_where);
                        future_free_people.push_back(new_where);
                        quant.push_back(step);
                    }
                }
            }
//            turn right
            if (where.last_turn_ == false) {
                if (where.position_.abscissa_ > 1 &&
                    country[where.position_.ordinate_ - 1][where.position_.abscissa_ - 2] == '.') {
                    new_where = TurnRight(where);
                    if (InFathers(new_where, fathers) == false) {
                        fathers[where.position_.ordinate_ - 1]
                        [where.position_.abscissa_ - 2].Add(new_where);
                        future_free_people.push_back(new_where);
                        quant.push_back(step);
                    }
                }
            }

//            turn over
            if (!(where.position_ == start)) {
                new_where = TurnOver(where);
                if (InFathers(new_where, fathers) == false) {
                    future_free_people.push_back(new_where);
                    fathers[new_where.position_.ordinate_ - 1]
                    [new_where.position_.abscissa_ - 1].Add(new_where);
                    quant.push_back(step);
                }
            }
        }
        if (where.direction_ == 'l') {
            //            move forward
            if (where.position_.abscissa_ > 1 &&
                country[where.position_.ordinate_ - 1][where.position_.abscissa_ - 2] == '.') {
                new_where.position_ = {where.position_.ordinate_, where.position_.abscissa_ - 1};
                new_where.last_turn_ = where.last_turn_;
                new_where.direction_ = where.direction_;
                if (InFathers(new_where, fathers) == false) {
                    fathers[where.position_.ordinate_ - 1]
                    [where.position_.abscissa_ - 2].Add(new_where);
                    future_free_people.push_back(new_where);
                    quant.push_back(step);
                }
            }
//            turn left
            if (where.last_turn_ == true) {
                if (where.position_.ordinate_ < nn &&
                    country[where.position_.ordinate_][where.position_.abscissa_ - 1] == '.') {
                    new_where = TurnLeft(where);
                    if (InFathers(new_where, fathers) == false) {
                        fathers[where.position_.ordinate_]
                        [where.position_.abscissa_ - 1].Add(new_where);
                        future_free_people.push_back(new_where);
                        quant.push_back(step);
                    }
                }
            }
//            turn right
            if (where.last_turn_ == false) {
                if (where.position_.ordinate_ > 1 &&
                    country[where.position_.ordinate_ - 2][where.position_.abscissa_ - 1] == '.') {
                    new_where = TurnRight(where);
                    if (InFathers(new_where, fathers) == false) {
                        fathers[where.position_.ordinate_ - 2]
                        [where.position_.abscissa_ - 1].Add(new_where);
                        future_free_people.push_back(new_where);
                        quant.push_back(step);
                    }
                }
            }

//            turn over
            if (!(where.position_ == start)) {
                new_where = TurnOver(where);
                if (InFathers(new_where, fathers) == false) {
                    future_free_people.push_back(new_where);
                    fathers[new_where.position_.ordinate_ - 1]
                    [new_where.position_.abscissa_ - 1].Add(new_where);
                    quant.push_back(step);
                }
            }
        }
    }
}

void PrintSteps(const vector<Threesome> &future_free_people, const vector<int> &quant,
                const Position &start, const Position &finish) {
    vector<Position> answer;
    answer.reserve(quant.size() + 1);
    int index = 0;
    while (!(future_free_people[index].position_ == finish)) {
        ++index;
    }
    while (index > 0) {
        answer.push_back(future_free_people[index].position_);
        index = quant[index];
    }
    std::cout << answer.size();
    std::cout << "\n";
    start.PrintPosition();
    std::cout << "\n";
    for (size_t item = answer.size() - 1; item > 0; --item) {
        answer[item].PrintPosition();
        std::cout << "\n";
    }
    answer[0].PrintPosition();
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t nn, mm;
    std::cin >> nn >> mm;
    vector<vector<char>> country;
    country.resize(nn, vector<char>(mm));
    for (size_t ordinate = 0; ordinate < nn; ++ordinate) {
        for (size_t abscissa = 0; abscissa < mm; ++abscissa) {
            std::cin >> country[ordinate][abscissa];
        }
    }
    int abscissa, ordinate;
    std::cin >> ordinate >> abscissa;
    Position start = {ordinate, abscissa};
    std::cin >> ordinate >> abscissa;
    Position finish = {ordinate, abscissa};
    char color = 'w';
    vector<vector<Check>> fathers;
    fathers.resize(nn, vector<Check>(mm,
                                     {false, false, false, false, false, false, false, false}));
    vector<Threesome> future_free_people;
    future_free_people.reserve(nn * mm);
    future_free_people.push_back(where);
    vector<int> quant;
    quant.reserve(nn * mm);
    int step = 0;
    quant.push_back(0);
    if (start == finish) {
        std::cout << 0 << '\n';
        start.PrintPosition();
    } else {
        BFS(nn, mm, country, finish, start, color, fathers, future_free_people,
            quant, step);
        if (color == 'u') {
            PrintSteps(future_free_people, quant, start, finish);
        } else {
            std::cout << -1;
        }
    }
    return 0;
}
