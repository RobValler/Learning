/*****************************************************************
 * Copyright (C) 2017-2023 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include<iostream>
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    int result;
    testing::InitGoogleTest(&argc, argv);

    ///< Test filters
    //::testing::GTEST_FLAG(filter) = "*Test_*";
    result = RUN_ALL_TESTS();
    return result;
}
