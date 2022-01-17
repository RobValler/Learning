/*****************************************************************

 *****************************************************************/

#include<iostream>
#include <gtest/gtest.h>

TEST(Tester, Test_Func)
{

}

int main(int argc, char *argv[])
{
    int result;
    testing::InitGoogleTest(&argc, argv);

    ///< Test filters
    //::testing::GTEST_FLAG(filter) = "*Test_*";
    result = RUN_ALL_TESTS();
    return result;
}
