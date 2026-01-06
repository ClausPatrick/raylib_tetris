#include "scoring.h"


#define NAME_LENGTH 4 
#define DATE_LENGTH 13

static char log_buffer[1024];
static const char SCORE_FILE[] = "scorefile.txt";



Scoring::Scoring(){}
Scoring::~Scoring(){}


void Scoring::get_timestamp(char* date_string, size_t l_date){
    time_t timer;
    struct tm* tm_info;
    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(date_string, l_date, "%y%m%d%H%M%S", tm_info);
    date_string[l_date - 1] = '\0';
}

void Scoring::create_random_score(size_t* score, char* name, char* date){
    const char name_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    *score = (size_t) rand() % 1000;
    name[0] = name_set[(rand() % 26)];
    name[1] = name_set[(rand() % 26)];
    name[2] = name_set[(rand() % 26)];
    name[3] = '\0';
    get_timestamp(date, DATE_LENGTH);
    sprintf(log_buffer, "%s: s/n/d '%ld', '%s', '%s'.", __func__, *score, name, date);
    logger(log_buffer, 4);
}

void Scoring::insert_into_set(size_t score, const char* name, size_t l_name, const char* date, size_t l_date){
    Q_Node qn;
    qn.score = score;
    for (size_t c=0; c<l_name; c++){
        qn.name[c] = name[c];
    }
    for (size_t c=0; c<l_date; c++){
        qn.date[c] = date[c];
    }
    m_set.insert(qn); // Add new item to set
}


void Scoring::submit(size_t score, const char* name){
    char date[DATE_LENGTH];
    get_timestamp(date, DATE_LENGTH);
    sprintf(log_buffer, "%s: s/n/d '%ld', '%s', '%s'.", __func__, score, name, date);
    logger(log_buffer, 4);
    //m_set.insert(score, name, NAME_LENGTH, date, DATE_LENGTH); // Add new item to set
    insert_into_set(score, name, NAME_LENGTH, date, DATE_LENGTH); // Add new item to set

}

int  Scoring::parse_line(char* line, char* r_score, char* r_name, char* r_date){
    int ret_val = 0;
    uint8_t segment = 0;
    char* buffer_array[3];
    buffer_array[0] = r_score;
    buffer_array[1] = r_name;
    buffer_array[2] = r_date;
    size_t s_len[3] = {0};

    char c;
    size_t index = 0;
    size_t cursor = 0;
    do {
        c = line[cursor];
        if (c==','){
            buffer_array[segment][index] = '\0';
            s_len[segment] = index;
            segment++;
            index = 0;
        }else if (c=='\0' || c=='\n'){
            buffer_array[segment][index] = '\0';
            s_len[segment] = index;
        }else{
            //printf("(%c/%d/%d)<c>\n", c, index, segment);
            buffer_array[segment][index] = c;
            index++;
        }
        cursor++;
    } while(c != '\0');
    if (s_len[0]==0 || s_len[1]==0 || s_len[2]==0){
        sprintf(log_buffer, "%s: error seg len: {%ld, %ld, %ld}.", __func__, s_len[0], s_len[1], s_len[2]);
        logger(log_buffer, 3);
        sprintf(log_buffer, "%s: on line: '%s'.", __func__, line);
        logger(log_buffer, 3);
        ret_val = -1;
    }
    sprintf(log_buffer, "%s: s/n/d '%s', '%s', '%s'.", __func__, r_score, r_name, r_date);
    logger(log_buffer, 4);
    return ret_val;
}

void Scoring::clear_scores(){
    FILE* fptr;
    fptr = fopen(SCORE_FILE, "w");
    if (fptr==NULL){
        printf("%s: File write error on '%s'.\n", __func__, SCORE_FILE);
    }else{
        fclose(fptr);
    }
}

void Scoring::dump_scores(){
    size_t score;
    char name[NAME_LENGTH];
    char date[DATE_LENGTH];
    FILE* fptr;
    fptr = fopen(SCORE_FILE, "w");
    if (fptr==NULL){
        printf("%s: File write error on '%s'.\n", __func__, SCORE_FILE);
    }else{
        //char buffer[127];
//        while (!queue.is_empty()){
//            queue.pop(&score, name, NAME_LENGTH, date, DATE_LENGTH);
//            sprintf(log_buffer, "%s: pop result: s/n/d '%ld', '%s', '%s'.", __func__, score, name, date);
//            logger(log_buffer, 4);
//            fprintf(fptr, "%ld,%s,%s\n", score, name, date);
//        }
        for (Q_Node qn : m_set){
            fprintf(fptr, "%ld,%s,%s\n", qn.score, qn.name, qn.date);
        }

    fclose(fptr);
    }
}
void Scoring::fetch_scores(){
    FILE* fptr;
    fptr = fopen(SCORE_FILE, "r");
    if (fptr==NULL){
        printf("%s: File write error.\n", __func__);
    }else{
        char buffer[127];
        char score_buffer[8]; 
        char name_buffer[NAME_LENGTH];
        char date_buffer[DATE_LENGTH];
        while(fgets(buffer, 127, fptr)){
            sprintf(log_buffer, "%s: buffer: '%s'.", __func__, buffer);
            logger(log_buffer, 4);
            //printf("buffer: \n%s", buffer);
            int r = parse_line(buffer, score_buffer, name_buffer, date_buffer);
            if (r == 0){
                size_t score = std::stoi(std::string(score_buffer));
                insert_into_set(score, name_buffer, NAME_LENGTH, date_buffer, DATE_LENGTH);
            }else{
                sprintf(log_buffer, "%s: parse_line result: s/n/d '%s', '%s', '%s'.", __func__, score_buffer, name_buffer, date_buffer);
                logger(log_buffer, 4);
            }

        }
        fclose(fptr);
    }
}

//int Scoring::get_ranking(size_t rank, size_t* score, char* name, size_t l_name, char* date, size_t l_date){
int Scoring::get_ranking(size_t rank, size_t* score, char* name, char* date){
    if (m_set.size() == 0 || rank >= m_set.size()){
        return -1;
    }
    size_t i = 0;
    for (Q_Node qn : m_set){
        if (i == rank){
            *score = qn.score;
            for (size_t c=0; c<4; c++){
                name[c] = qn.name[c];
            }
            for (size_t c=0; c<12; c++){
                date[c] = qn.date[c];
            }
            break;
        }
        i++;
    }
    sprintf(log_buffer, "%s: rank: %ld, s/n/d '%ld', '%s', '%s'.", __func__, rank, *score, name, date);
    logger(log_buffer, 4);
    return 0;
}


