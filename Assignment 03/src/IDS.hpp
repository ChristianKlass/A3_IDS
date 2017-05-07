//
//  IDS.hpp
//  Assignment 03
//
//  Created by Mark Klass on 7/5/17.
//  Copyright © 2017 Juicy Apps. All rights reserved.
//

#ifndef IDS_hpp
#define IDS_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Entry.hpp"

int init();
int readEntry(std::string);

std::vector<Entry> entries;

std::string entryFile = "Entry.txt";

#endif /* IDS_hpp */
