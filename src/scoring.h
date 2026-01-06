#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <string.h>
#include <time.h>
#include <vector>
#include "c_logger.h"
#include <set>

struct Q_Node{
    size_t score;
    char name[8];
    char date[16];
    bool operator<(const Q_Node& other) const{
        if (score != other.score){
            return score > other.score;
        }else{
            return strcmp(date, other.date) < 0;
        }
    }
};



class Scoring{
    public:
        Scoring();
        ~Scoring();
        Scoring(const Scoring&) = delete;
        Scoring& operator=(const Scoring&) = delete;
        Scoring(Scoring&&) = delete;
        Scoring& operator=(Scoring&&) = delete;

        void get_timestamp(char* date_string, size_t l_date);
        void create_random_score(size_t* score, char* name, char* date);
        int  parse_line(char* line, char* r_score, char* r_name, char* r_date);
        void submit(size_t score, const char* name);  // out of p_queue into file
        /* Writing queue content into file. */
        void dump_scores();
        void clear_scores();
        /* Reading file content into queue. */
        void fetch_scores();
        //int get_ranking(size_t rank, size_t* score, char* name, size_t l_name, char* date, size_t l_date);
        int get_ranking(size_t rank, size_t* score, char* name, char* date);

    private:
        void insert_into_set(size_t score, const char* name, size_t l_name, const char* date, size_t l_date);
        std::multiset<Q_Node> m_set;

};

