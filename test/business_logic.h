#pragma once
#include <vector>
#include "protocol.h"

class Business_Logic{
public:
    void update_questions();
    void update_answers();
    void get_Answer_by_ID(std::string id);
    void get_Question_by_ID(std::string id);
    void get_all_answers();
    void get_all_questions();
private:
    std::vector<Question> questions;
    std::vector<Answer> answers;
    //Answer answer;
    //Question question;
    std::vector<std::string> questions_ID;
    std::vector<std::string> answers_ID;
};

