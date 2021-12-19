//
// Created by Vanya Kootchin on 2021-11-23.
//

#ifndef GGTOWERDEFENCE_MONEY_H
#define GGTOWERDEFENCE_MONEY_H


class Money {
private:
    int     amount;
public:
    Money();
    Money(int);
    int     getAmount();
    void    setAmount(int);
};


#endif //GGTOWERDEFENCE_MONEY_H
