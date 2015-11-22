#pragma once
#include <vector>
#include "network.h"

//using namespace std;

struct Question
{
    std::string text;
    std::string ID;
    time_t creation_time; //the number of seconds since 1970-01-01 00:00:00 UTC.
};

struct Answer {
    std::string text;
    std::string ID_answer;
    time_t creation_time;
    std::string ID_question;
};

struct Question_with_Answers{
    Question q;
    std::vector<Answer> answers;

};

class Protocol{
public:
    Protocol(const NetworkLayer &network, const std::string &url):
        _network(network),
        _url(url)
    {}
    Question get_last_question();
    std::vector<Question> get_list_of_questions();
    std::vector<Answer> get_list_of_answers();
    std::vector<Question_with_Answers> get_list();
    Question get_question_ID(std::string id);
    Answer get_answer_ID(std::string id);
    std::vector<std::string> get_questionsID();
    std::vector<Question> get_new_questions(int limit);
    std::vector<std::string> get_answersID();
    std::vector<Answer> get_new_answers(int limit);
private:
    std::string _url;
    NetworkLayer _network;

};
