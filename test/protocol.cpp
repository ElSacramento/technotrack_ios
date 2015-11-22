#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "protocol.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
using boost::property_tree::ptree;

//questions
Question parseQuestion(const ptree &node)
{
        return Question{
                .text = node.get<std::string>("text", ""),
                .creation_time = node.get<time_t>("ts"),
                .ID = node.get<std::string>("ID")
        };
}

Question Protocol::get_last_question(){
    std::string json = _network.fetch_url(_url);

    ptree parsedJson;
    std::stringstream stream(json);
    boost::property_tree::read_json(stream, parsedJson);
    return parseQuestion(parsedJson);
}

std::vector<Question> parseQuestions(const ptree &node){
    std::vector<Question> result;
//    std::function<Question (const ptree::value_type &)> parse = std::bind(parseQuestion, std::bind(&ptree::value_type::second, std::placeholders::_1));
//    std::transform(std::begin(node), std::end(node), std::back_inserter(result), parse);
    boost::transform(node | boost::adaptors::map_values, std::back_inserter(result), parseQuestion);
    return result;
}

std::vector<Question> Protocol::get_list_of_questions(){
    std::string json = _network.fetch_url(_url);

    ptree parsedJson;
    std::stringstream stream(json);
    boost::property_tree::read_json(stream, parsedJson);
    return parseQuestions(parsedJson.get_child("questions"));
}

Question parseQuestion_ID(const ptree &node, std::string id) {
    std::vector<Question> result;
    boost::transform(node | boost::adaptors::map_values, std::back_inserter(result), parseQuestion);
    auto it = std::find_if(result.begin(), result.end(), [id](Question x){return (x.ID == id);});
    return *it;
}

Question Protocol::get_question_ID(std::string id){
    std::string json = _network.fetch_url(_url);
    ptree parsedJson;
    std::stringstream stream(json);
    boost::property_tree::read_json(stream, parsedJson);
    return parseQuestion_ID(parsedJson.get_child("questions"), id);
}

std::vector<std::string> Protocol::get_questionsID(){
    std::string json = _network.fetch_url(_url);
    ptree parsedJson;
    std::stringstream stream(json);
    boost::property_tree::read_json(stream, parsedJson);
    std::vector<std::string> result;
    std::vector<Question> questions = parseQuestions(parsedJson.get_child("questions"));
    boost::transform(questions, std::back_inserter(result), [](Question x){return x.ID;});
    return result;
}

std::vector<Question> Protocol::get_new_questions(int limit){
    std::string json = _network.fetch_url(_url);
    ptree parsedJson;
    std::stringstream stream(json);
    boost::property_tree::read_json(stream, parsedJson);
    std::vector<Question> result(parseQuestions(parsedJson.get_child("questions")));
    result.erase(result.begin(), result.end()-limit);
    return result;
}






//answers
Answer parseAnswer(const ptree &node) {
    return Answer{
            .text = node.get<std::string>("text", ""), //c++11
            .creation_time = node.get<time_t>("ts"),
            .ID_question = node.get<std::string>("ID_q"),
            .ID_answer = node.get<std::string>("ID_a")
    };
}

std::vector<Answer> parseAnswers(const ptree &node){
    std::vector<Answer> result;
    boost::transform(node | boost::adaptors::map_values, std::back_inserter(result), parseAnswer);
    return result;
}

std::vector<Answer> Protocol::get_list_of_answers(){
    std::string json = _network.fetch_url(_url);

    ptree parsedJson;
    std::stringstream stream(json);
    boost::property_tree::read_json(stream, parsedJson);
    return parseAnswers(parsedJson.get_child("answers"));
}

Answer parseAnswer_ID(const ptree &node, std::string id) {
    std::vector<Answer> result;
    boost::transform(node | boost::adaptors::map_values, std::back_inserter(result), parseAnswer);
    auto it = std::find_if(result.begin(), result.end(), [id](Answer x){return (x.ID_answer == id);});
    return *it;
}

Answer Protocol::get_answer_ID(std::string id){
    std::string json = _network.fetch_url(_url);
    ptree parsedJson;
    std::stringstream stream(json);
    boost::property_tree::read_json(stream, parsedJson);
    return parseAnswer_ID(parsedJson.get_child("answers"), id);
}

std::vector<std::string> Protocol::get_answersID(){
    std::string json = _network.fetch_url(_url);
    ptree parsedJson;
    std::stringstream stream(json);
    boost::property_tree::read_json(stream, parsedJson);
    std::vector<std::string> result;
    std::vector<Answer> answers = parseAnswers(parsedJson.get_child("answers"));
    boost::transform(answers, std::back_inserter(result), [](Answer x){return x.ID_answer;});
    return result;
}

std::vector<Answer> Protocol::get_new_answers(int limit){
    std::string json = _network.fetch_url(_url);
    ptree parsedJson;
    std::stringstream stream(json);
    boost::property_tree::read_json(stream, parsedJson);
    std::vector<Answer> result(parseAnswers(parsedJson.get_child("answers")));
    result.erase(result.begin(), result.end()-limit);
    return result;
}






//additionally
Question_with_Answers parseElement(const ptree &node) {
    std::vector<Question_with_Answers> result;
    Question q = parseQuestion(node);
    std::vector<Answer> v= parseAnswers(node.get_child("answers"));
    return Question_with_Answers{.q = q, .answers = v};
}

std::vector<Question_with_Answers> parseList(const ptree &node){
    std::vector<Question_with_Answers> result;
    boost::transform(node | boost::adaptors::map_values, std::back_inserter(result), parseElement);
    return result;
}

std::vector<Question_with_Answers> Protocol::get_list(){
    std::string json = _network.fetch_url(_url);

    ptree parsedJson;
    std::stringstream stream(json);
    boost::property_tree::read_json(stream, parsedJson);
    return parseList(parsedJson.get_child("questions"));
}
