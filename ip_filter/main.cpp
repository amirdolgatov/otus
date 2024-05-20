#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <array>
#include <iterator>
#include <algorithm>
#include <cstring>
#include "version.h"

///// Аналог функции find_first_of()
//inline int firstOccurrence(const std::string& str, int begin, int end, char c){
//
//    for( ;  str[begin] != c && begin != end; begin++)
//        ;
//    if(str[begin] == c)
//        return begin;
//    return -1;
//}

///// Функция отсечет участок строки перед первым появлением символа \t и вставит в заданный контейнер
//void firstWordGetter(const std::string& str, std::vector<std::string>& strings_ip){
//    auto i = firstOccurrence(str, 0, str.size(), '\t');
//    strings_ip.push_back(str.substr(0, i));
//}


void printVector(std::vector<std::string>& vec){
    for (auto& it: vec) {
        std::cout << it << std::endl;
    }
}

class ArrayCompare{
public:
    bool operator()(const std::array<int, 4>& lhs, const std::array<int, 4>& rhs ){ /// константность ссылок обязательна
        auto left = lhs.begin();
        auto right = rhs.begin();
        while(left != lhs.end() && right != rhs.end()){
            if(*left > *right)
                return true;
            else if(*left == *right){
                left++;
                right++;
                continue;
            }
            return false;
        }
        return false;
    }
};


std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);

    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

using dividedString = std::vector<std::string>;
using ipArray = std::array<int, 4>;


int main() {

    std::vector<dividedString> strings_ip;
    std::map< ipArray, dividedString, ArrayCompare> stringMap;

    for(std::string line; std::getline(std::cin, line); )
    {
        std::vector<std::string> v = split(line, '\t');
        strings_ip.push_back(split(v.at(0), '.'));
    }

    for (auto& partedStr: strings_ip){
        ipArray ip;
        for(int i = 0; i < partedStr.size(); ++i){
            ip[i] = std::stoi(partedStr[i]);
        }
        stringMap.insert({ip, partedStr});
    }



//    Начальная сортировка
//    std::sort(strings_ip.begin(), strings_ip.end(), [](std::string& left, std::string& right){
//        int a1 = 0, a2 = 1;
//        int b1 = 0, b2 = 1;
//        int octetLeft, octetRight;
//
//        while (a2 > 0 && b2 > 0){
//            a2  = firstOccurrence(left, a1, left.size(), '.');
//            b2  = firstOccurrence(right,b1, right.size(), '.');
//            if(a2 == -1 && b2 == -1){
//                octetLeft = std::stoi(left.substr(a1, left.size()));
//                octetRight = std::stoi(right.substr(b1, right.size()));
//            }
//            else{
//                octetLeft = std::stoi(left.substr(a1, a2 - a1));
//                octetRight = std::stoi(right.substr(b1, b2 - b1));
//            }
//
//            if (octetLeft > octetRight)
//                return true;
//
//            else if (octetLeft == octetRight){
//                a1 = a2 + 1;
//                b1 = b2 + 1;
//            }
//
//            else
//                return false;
//
//        }
//        return false;
//    });

    printVector(strings_ip);

    /// Отбор строк с первым байтом 1
    std::for_each(strings_ip.begin(), strings_ip.end(), [](std::string& str){
        auto a = firstOccurrence(str, 0, str.size(), '.');
        if(std::stoi(str.substr(0, a)) == 1)
            std::cout << str << std::endl;
    });

    /// Отбор строк с байтами 46, 70
    std::for_each(strings_ip.begin(), strings_ip.end(), [](std::string& str){
        auto a1 = firstOccurrence(str, 0, str.size(), '.');
        if(std::stoi(str.substr(0, a1)) == 46){
            auto a2 = firstOccurrence(str, a1 + 1, str.size(), '.');
            if (std::stoi(str.substr(a1 + 1, a2)) == 70)
                std::cout << str << std::endl;
        }
    });

    /// Отбор строк содержащих байтом 46
    std::for_each(strings_ip.begin(), strings_ip.end(), [](std::string& str){
        int a1 = 0, a2 = 1;
        int octet;

        while (a2 > 0){
            a2  = firstOccurrence(str, a1, str.size(), '.');
            if(a2 == -1){
                octet = std::stoi(str.substr(a1, str.size()));
            }
            else{
                octet = std::stoi(str.substr(a1, a2 - a1));
            }

            if (octet == 46){
                std::cout << str << std::endl;
                return;
            }

            a1 = a2 + 1;

        }
        return;
    });

    return 0;
}
