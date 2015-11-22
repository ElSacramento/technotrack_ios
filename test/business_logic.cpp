#include "business_logic.h"
#include <iostream>
#include "time.h"
#include "math.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
using namespace std;

void Business_Logic::update_questions(){
    NetworkLayer network;
    Protocol protocol_questions(network, "questions.dat");
    time_t current_time;
    time_t time_for_last_update;
    while(true) {
        if (abs(difftime(time_for_last_update, time(&current_time))) > 10){
            std::vector<std::string> currentIDs(protocol_questions.get_questionsID());
            boost::copy(protocol_questions.get_new_questions(currentIDs.size() - this->questions_ID.size()) | boost::adaptors::transformed(std::mem_fn(&Question::text)), std::ostream_iterator<std::string>(std::cout, "\n"));
            this->questions_ID = currentIDs;
            time(&time_for_last_update);
        }
    }
}

void Business_Logic::update_answers(){
    NetworkLayer network;
    Protocol protocol_answers(network, "answers.dat");
    time_t current_time;
    time_t time_for_last_update;
    while(true) {
        if (abs(difftime(time_for_last_update, time(&current_time))) > 10){
            std::vector<std::string> currentIDs(protocol_answers.get_answersID());
            boost::copy(protocol_answers.get_new_answers(currentIDs.size() - this->answers_ID.size()) | boost::adaptors::transformed(std::mem_fn(&Answer::text)), std::ostream_iterator<std::string>(std::cout, "\n"));
            this->answers_ID = currentIDs;
            time(&time_for_last_update);
        }
    }
}

void Business_Logic::get_all_questions(){
    NetworkLayer network;
    Protocol protocol_questions(network, "questions.dat");
    boost::copy(protocol_questions.get_list_of_questions() | boost::adaptors::transformed(std::mem_fn(&Question::text)), std::ostream_iterator<std::string>(std::cout, "\n"));
}

void Business_Logic::get_all_answers(){
    NetworkLayer network;
    Protocol protocol_answers(network, "answers.dat");
    boost::copy(protocol_answers.get_list_of_answers() | boost::adaptors::transformed(std::mem_fn(&Answer::text)), std::ostream_iterator<std::string>(std::cout, "\n"));
}

void Business_Logic::get_Answer_by_ID(std::string id){
    NetworkLayer network;
    Protocol protocol_answers(network, "answers.dat");
    cout << protocol_answers.get_answer_ID(id).text << endl;
}

void Business_Logic::get_Question_by_ID(std::string id){
    NetworkLayer network;
    Protocol protocol_questions(network, "questions.dat");
    cout << protocol_questions.get_question_ID(id).text << endl;
}
