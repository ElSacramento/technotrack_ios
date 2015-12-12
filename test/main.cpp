#include "network.h"
#include "protocol.h"
#include "business_logic.h"
#include <iostream>
#include <boost/range/algorithm/copy.hpp>
#include <iterator>
#include <boost/range/adaptors.hpp>

int main()
{
        Business_Logic first;
        //first.update_chat();
        //first.get_Answer_by_ID("3");
        first.update_questions();
        //first.update_chat();
        //first.update_answers();
        return 0;
}
