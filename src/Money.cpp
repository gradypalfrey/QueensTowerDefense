//
// Created by Vanya Kootchin on 2021-11-23.
//

#include "Money.h"

Money::Money(){
    this->amount = 0;
}

Money::Money(int m){
    this->amount = m;
}

int Money::getAmount() {
    return this->amount;
}

void Money::setAmount(int m){
    this->amount = m;
}