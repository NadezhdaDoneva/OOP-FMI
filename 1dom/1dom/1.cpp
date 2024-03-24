// 1dom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <assert.h>
#include <iomanip>

namespace GlobalConstants {
    constexpr int MAX_FIELD_SIZE = 50;
    constexpr int MAX_FIELDS_ROW = 15;
    constexpr int ROWS_MAX_SIZE = 100;
    constexpr int TAG_MAX_SIZE = 7;
}

enum class FieldTag {
    Th,
    Td,
    Table,
    Tr,
    Unknown
};

struct Field {
    FieldTag fieldTag;
    char fieldName[GlobalConstants::MAX_FIELD_SIZE];
};

typedef Field Row[GlobalConstants::MAX_FIELDS_ROW];

struct Table {
    Row rows[GlobalConstants::ROWS_MAX_SIZE];
    size_t rowsCount = 0;
    size_t collsCount = 0;
    unsigned arrColsCount[GlobalConstants::MAX_FIELDS_ROW] = { 0 };
};


void add(Table& table, size_t rowIdx, const Row& rowToAdd) {
    assert(table.rowsCount + 1 <= GlobalConstants::ROWS_MAX_SIZE);
    assert(rowIdx <= GlobalConstants::ROWS_MAX_SIZE);

    table.rowsCount++;

    //put rowToAdd on last place
    for (size_t i = 0; i < table.collsCount; i++) {
        table.rows[table.rowsCount - 1][i] = rowToAdd[i];
    }
    table.arrColsCount[table.rowsCount - 1] = table.collsCount;

    //swap with previous until reaching the idx where we want it to be
    while (table.rows[rowIdx] > table.rows[rowIdx - 1]) {
        std::swap(table.rows[rowIdx], table.rows[rowIdx - 1]);
        std::swap(table.arrColsCount[rowIdx], table.arrColsCount[rowIdx - 1]);
        rowIdx--;
    }
}


void removeRow(Table& table, size_t rowIdx) {
    if (rowIdx < 1 || rowIdx > table.rowsCount) {
        std::cout << "Unvalid idx!" << std::endl;
        return;
    }

    //swap until the row we want to remove reaches last position and than reducing the size, so we remove it
    for (size_t i = rowIdx - 1; i < table.rowsCount - 1; i++) {
        std::swap(table.rows[i], table.rows[i + 1]);
        std::swap(table.arrColsCount[i], table.arrColsCount[i + 1]);
    }
    table.rowsCount--;
}

void edit(Table& table, size_t rowNumber, size_t colNumber, const char* newValue) {
    if (rowNumber > table.rowsCount || colNumber > table.arrColsCount[rowNumber]) {
        std::cout << "Unvalid idx!";
        return;
    }
    strcpy_s(table.rows[rowNumber - 1][colNumber - 1].fieldName, newValue);
}

void readClosingTag(std::ifstream& ifs, bool& isClosingTr) {
    char closingTag[GlobalConstants::TAG_MAX_SIZE];
    ifs.getline(closingTag, GlobalConstants::TAG_MAX_SIZE, '>');
    if (strcmp(closingTag, "/tr") == 0) {
        isClosingTr = true;
    }
}

//bool isNumber(char ch){
//    return ch >= '0' && ch <= '9';
//}
//
//int charToInt(char ch) {
//    return ch - '0';
//}
//
//char toChar(int num){
//    return num;
//}
//
//void parseBuff(char* buff) {
//    char newBuff[GlobalConstants::MAX_FIELD_SIZE];
//    int refBuff;
//    size_t idx = 0;
//    unsigned mult = 1;
//    for (size_t i = 0; i < strlen(buff); i++) {
//        if (buff[i] == '&' && buff[i + 1] == '#') {
//            i += 2;
//            while (i < strlen(buff) && isNumber(buff[i]))
//            {
//                refBuff= refBuff * mult + charToInt(buff[i]);
//                mult *= 10;
//                i++;
//            }
//            char ref = toChar(refBuff);
//            
//        }
//        else {
//            newBuff[idx] = buff[idx];
//            idx++;
//        }
//    }
//}

//parse the content of each field and append it to the resultTable
void parseField(std::ifstream& ifs, Table& resultTable, bool& isClosingTr) {
    char buff[GlobalConstants::MAX_FIELD_SIZE];
    ifs.getline(buff, GlobalConstants::MAX_FIELD_SIZE, '<');
    strcpy_s(resultTable.rows[resultTable.rowsCount][resultTable.collsCount].fieldName, buff);
    //std::cout << resultTable.rows[resultTable.rowsCount][resultTable.collsCount].fieldName;
    readClosingTag(ifs, isClosingTr);
}

//parsing each row - get if the tag of each field is header or data tag and append this info to the resultTable
void parseRow(std::ifstream& ifs, Table& resultTable, bool& isClosingTr) {
    char buff[GlobalConstants::MAX_FIELD_SIZE];
    ifs.getline(buff, GlobalConstants::MAX_FIELD_SIZE, '<');
    ifs.getline(buff, GlobalConstants::MAX_FIELD_SIZE, '>');

    if (strcmp(buff, "th") == 0) {
        resultTable.rows[resultTable.rowsCount][resultTable.collsCount].fieldTag = FieldTag::Th;
        parseField(ifs, resultTable, isClosingTr);
        resultTable.arrColsCount[resultTable.rowsCount]++;
        resultTable.collsCount++;
    }
    else if (strcmp(buff, "td") == 0) {
        resultTable.rows[resultTable.rowsCount][resultTable.collsCount].fieldTag = FieldTag::Td;
        parseField(ifs, resultTable, isClosingTr);
        resultTable.arrColsCount[resultTable.rowsCount]++;
        resultTable.collsCount++;
    }
    else if (strcmp(buff, "/tr") == 0) {
        isClosingTr = true;
    }

}

//read tag and if "tr" - pass the table to parse the row until the closing "\tr" apperars
void readRowFieldTag(std::ifstream& ifs, Table& resultTable) {
    char tag[GlobalConstants::TAG_MAX_SIZE];
    ifs.getline(tag, GlobalConstants::TAG_MAX_SIZE, '>');
    bool isClosingTr = false;

    if (strcmp(tag, "tr") == 0) {
        resultTable.collsCount = 0;
        while (true) {
            if (isClosingTr || strcmp(tag, "/table") == 0) {
                break;
            }
            parseRow(ifs, resultTable, isClosingTr);
        }
        resultTable.rowsCount++;
    }
}

//creating table, passing it to be parsed, and returning the table
Table parseFromFile(std::ifstream& ifs) {
    Table resultTable;

    while (!ifs.eof()) {
        char symbol;
        ifs.get(symbol);

        if (symbol == '<')
        {
            readRowFieldTag(ifs, resultTable);
        }
    }
    return resultTable;
}

//a func to check if the file is open and pass it to parsing
Table parseFromFile(const char* fileName) {
    std::ifstream ifs(fileName);

    if (!ifs.is_open()) {
        std::cout << "the file can not be opened" << std::endl;
        return {};
    }

    return parseFromFile(ifs);
}


void printTable(const Table& table)
{
    for (int i = 0; i < table.rowsCount; i++)
    {
        for (int j = 0; j < table.arrColsCount[i]; j++)
        {
            if (table.rows[i][j].fieldTag == FieldTag::Th) {
                std::cout << "|" << "*" << table.rows[i][j].fieldName << "*         ";
            }
            else {
                std::cout << "|" << table.rows[i][j].fieldName << "         ";
            }
            if (j == table.arrColsCount[i] - 1) {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
    }
}


int main()
{
    Table myTable = parseFromFile("table.txt");
    printTable(myTable);
    std::cout << std::endl;

    std::cout << "Edited table (change 2x1 to Eli): " << std::endl;
    edit(myTable, 2, 1, "Eli");
    printTable(myTable);
    std::cout << std::endl;

    std::cout << "Remove first row:" << std::endl;;
    removeRow(myTable, 1);
    printTable(myTable);

}

