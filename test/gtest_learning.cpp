/*****************************************************************
 * Copyright (C) 2017-2023 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include "setup.h"

#include <gtest/gtest.h>
#include <vector>

#include "cluster.h"


TEST(Proto, type)
{
    std::vector<std::vector<int>> data ={
        {0, 0, 0},
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0},
    };

    CNeuralCluster cluster;
    cluster.Setup(2, 3, 3, 1);
    cluster.Train(data);
    cluster.Store();
    cluster.Load();
    EXPECT_EQ(cluster.Test(data), true);

}

//TEST(Learning, XOR_Example)
//{
//    std::vector<SGateFormat> XORInputOutput
//    {
//        {0, 0, 0},
//        {0, 1, 1},
//        {1, 0, 1},
//        {1, 1, 0},
//    };

//    CSetupNeuralCluster test;
//    test.Setup(XORInputOutput);
//    test.Train();
//    test.Test();
//}

//TEST(Learning, NOR_Example)
//{
//    std::vector<SGateFormat> NORInputOutput
//    {
//        {0, 0, 1},
//        {0, 1, 0},
//        {1, 0, 0},
//        {1, 1, 0},
//    };

//    CSetupNeuralCluster test;
//    test.Setup(NORInputOutput);
//    test.Train();
//    test.Test();
//}

//TEST(Learning, OR_Example)
//{
//    std::vector<SGateFormat> ORInputOutput
//    {
//        {0, 0, 0},
//        {0, 1, 1},
//        {1, 0, 1},
//        {1, 1, 1},
//    };

//    CSetupNeuralCluster test;
//    test.Setup(ORInputOutput);
//    test.Train();
//    test.Test();
//}

//TEST(Learning, AND_Example)
//{
//    std::vector<SGateFormat> ANDInputOutput
//    {
//        {0, 0, 0},
//        {0, 1, 0},
//        {1, 0, 0},
//        {1, 1, 1},
//    };

//    CSetupNeuralCluster test;
//    test.Setup(ANDInputOutput);
//    test.Train();
//    test.Test();
//}

//TEST(Learning, NAND_Example)
//{
//    std::vector<SGateFormat> NANDInputOutput
//    {
//        {0, 0, 1},
//        {0, 1, 1},
//        {1, 0, 1},
//        {1, 1, 0},
//    };

//    CSetupNeuralCluster test;
//    test.Setup(NANDInputOutput);
//    test.Train();
//    test.Test();
//}

