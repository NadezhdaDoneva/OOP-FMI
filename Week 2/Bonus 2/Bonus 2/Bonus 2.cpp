﻿// Bonus 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<cstring>
#include<fstream>

enum class ErrorInCatalog {
    catalog_not_open,
    read_from_empty_catalog,
    movie_not_in_catalog,
    no_error_occurred
};

struct SafeAnswer {
    int number = 0;
    ErrorInCatalog error;
};

struct Movie {
    char name[128];
    unsigned int price;
};

//1
SafeAnswer getNumberOfMovies(const char* catalogName) {
    SafeAnswer answer;

    //open the file
    std::ifstream file(catalogName);

    //checking for errors
    //check if the file can be opened
    if (!file.is_open()) {
        answer.error = ErrorInCatalog::catalog_not_open;
        return answer;
    }

    //count lines
    bool isEmpty = true;
    char tempLine[1024];
    while (file.getline(tempLine, 1024)) {
        answer.number++;
        isEmpty = false;
    }

    //check if the file is empty
    if (isEmpty) {
        answer.error = ErrorInCatalog::read_from_empty_catalog;
        file.close();
        return answer;
    }

    //else no error occurred and return answer
    answer.error = ErrorInCatalog::no_error_occurred;
    file.close();
    return answer;
}

//2
SafeAnswer averagePrice(const char* catalogName) {
    SafeAnswer answer;
    //open the file
    std::ifstream file(catalogName);
    
    //check if the file can be opened
    if (!file.is_open()) {
        answer.error = ErrorInCatalog::catalog_not_open;
        return answer;
    }

    //check if the file is empty
    int countOfMovies = getNumberOfMovies(catalogName).number;
    if (countOfMovies == 0) {
        answer.error = ErrorInCatalog::read_from_empty_catalog;
        file.close();
        return answer;
    }

    //average price logic
    unsigned int sumOfPrices = 0;
    char tempMovieName[1024];
    int tempMoviePrice;
    while (!file.eof()) {
        file >> tempMovieName >> tempMoviePrice;
        sumOfPrices += tempMoviePrice;
    }

    //else no error occurred and return answer
    answer.error = ErrorInCatalog::no_error_occurred;
    answer.number = sumOfPrices / countOfMovies;
    file.close();
    return answer;
}

//3
SafeAnswer getMoviePrice(const char* catalogName, const char* movieName) {
    SafeAnswer answer;
    //open file
    std::ifstream file(catalogName);

    //check if the file can be opened
    if (!file.is_open()) {
        answer.error = ErrorInCatalog::catalog_not_open;
        return answer;
    }

    //check if the file is empty
    unsigned countOfMovies = getNumberOfMovies(catalogName).number;
    if (countOfMovies == 0) {
        answer.error = ErrorInCatalog::read_from_empty_catalog;
        file.close();
        return answer;
    }

    //find movie price logic
    char tempMovieName[1024];
    int tempMoviePrice;
    while (!file.eof()) {
        file >> tempMovieName >> tempMoviePrice;
        if (strcmp(tempMovieName, movieName) == 0) {
            answer.number = tempMoviePrice;
            break;
        }
    }

    //check if movie is not in the catalog
    if (answer.number == 0) {
        answer.error = ErrorInCatalog::movie_not_in_catalog;
        file.close();
        return answer;
    }
   
    //else no error occurred and return answer
    answer.error = ErrorInCatalog::no_error_occurred;
    file.close();
    return answer;
}

//4
Movie* saveMoviesInArray(std::ifstream& file, int numberOfMovies) {
    Movie* moviesArr = new Movie[numberOfMovies];
    
    char tempMovieName[1024];
    int tempMoviePrice;
    int idx = 0;
    while (idx < numberOfMovies) {
        file >> tempMovieName >> tempMoviePrice;
        strcpy_s(moviesArr[idx].name, tempMovieName);
        moviesArr[idx].price = tempMoviePrice;
        idx++;
    }
    return moviesArr;
}

void freeMoviesFromArray(Movie*& moviesArray) {
    delete[] moviesArray;
}

//5
void sortMoviesInArray(Movie*& moviesArray, int numberOfMovies) {
    //selection sort for prices
    for (size_t i = 0; i < numberOfMovies - 1; i++) {
        int minPriceIdx = i;
        for (size_t j = i; j < numberOfMovies; j++)
        {
            if (moviesArray[j].price < moviesArray[minPriceIdx].price)
                minPriceIdx = j;
        }
        if (minPriceIdx != i) {
            std::swap(moviesArray[i], moviesArray[minPriceIdx]);
        }
    }
}

//6
ErrorInCatalog saveMoviesSorted(const char* catalogName, const char* catalogSortedName) {
    //open files for reading and writing
    std::ifstream firstFile(catalogName);
    std::ofstream secondFile(catalogSortedName);

    //check if the files can be opened
    if (!firstFile.is_open() || !secondFile.is_open()) {
        return ErrorInCatalog::catalog_not_open;
    }

    //check if the file is empty
    unsigned countOfMovies = getNumberOfMovies(catalogName).number;
    if (countOfMovies == 0) {
        firstFile.close();
        return ErrorInCatalog::read_from_empty_catalog;
    }

    //get array of movies and sort it
    Movie* movieArr = saveMoviesInArray(firstFile, countOfMovies);
    sortMoviesInArray(movieArr, countOfMovies);
    //write in the second file
    for (size_t i = 0; i < countOfMovies; i++) {
        secondFile << movieArr[i].name << " " << movieArr[i].price << "\n";
    }

    //dealocate memory and return no error
    freeMoviesFromArray(movieArr);
    firstFile.close();
    secondFile.close();
    return ErrorInCatalog::no_error_occurred;
}

int main() {
    SafeAnswer safeNumberOfMovies = getNumberOfMovies("movieCatalog.txt");
    if (safeNumberOfMovies.error == ErrorInCatalog::no_error_occurred) {
        std::cout << "The number of movies is: " << safeNumberOfMovies.number << std::endl;
    }
    SafeAnswer safeAveragePrice = averagePrice("movieCatalog.txt");
    if (safeAveragePrice.error == ErrorInCatalog::no_error_occurred) {
        std::cout << "The average price is: " << safeAveragePrice.number << std::endl;
    }
    
    SafeAnswer safePrice = getMoviePrice("movieCatalog.txt", "Black-bullet");
    if (safePrice.error == ErrorInCatalog::no_error_occurred) {
        std::cout << "The price for the Black bullet movies is: " << safePrice.number << std::endl;
    }
    
    ErrorInCatalog errorSorting = saveMoviesSorted("movieCatalog.txt", "movieCatalogSorted.txt");
    if (errorSorting == ErrorInCatalog::no_error_occurred) {
        std::cout << "Look the content of the movieCatalogSorted.txt file" << std::endl;
    }
}