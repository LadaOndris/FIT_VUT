//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Ladislav Ondris <xondri07@stud.fit.vutbr.cz>
// $Date:       $2019-02-19
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Ladislav Ondris
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//


class MatrixTest : public ::testing::Test
{
protected:

    Matrix matrixImplicit1by1 = Matrix();
    Matrix matrix2by5 = Matrix(2,5);
    Matrix matrix80by24 = Matrix(80, 24);
    
    virtual void SetUp() {
    
    }
};

TEST_F(MatrixTest, Construction) {
    Matrix matrix;
    EXPECT_ANY_THROW(matrix = Matrix(0, 0));
    EXPECT_ANY_THROW(matrix = Matrix(0, 10));
    EXPECT_ANY_THROW(matrix = Matrix(20, 0));
    EXPECT_ANY_THROW(matrix = Matrix(-1, -1));
    EXPECT_NO_THROW(matrix = Matrix(80, 24));
}

TEST_F(MatrixTest, Set_CertainIndex) {
    // correct indexes
    EXPECT_TRUE(matrixImplicit1by1.set(0, 0, 1));
    // incorrect indexes
    EXPECT_FALSE(matrixImplicit1by1.set(0, 1, 1));
    EXPECT_FALSE(matrixImplicit1by1.set(1, 0, 1));
    EXPECT_FALSE(matrixImplicit1by1.set(1, 1, 1));
    EXPECT_FALSE(matrixImplicit1by1.set(-1, -1, 1));

    // correct indexes
    EXPECT_TRUE(matrix2by5.set(1, 4, 1));
    EXPECT_TRUE(matrix2by5.set(0, 0, 1));
    EXPECT_TRUE(matrix2by5.set(1, 2, 1));
    // incorrect indexes
    EXPECT_FALSE(matrix2by5.set(2, 4, 1));
    EXPECT_FALSE(matrix2by5.set(1, 5, 1));
    EXPECT_FALSE(matrix2by5.set(4, 1, 1));
    EXPECT_FALSE(matrix2by5.set(-1, 0, 1));

    // correct indexes
    EXPECT_TRUE(matrix80by24.set(79, 23, 1));
    EXPECT_TRUE(matrix80by24.set(0, 0, 1));
    EXPECT_TRUE(matrix80by24.set(20, 20, 1));
    // incorrect indexes
    EXPECT_FALSE(matrix80by24.set(80, 24, 1));
    EXPECT_FALSE(matrix80by24.set(100, 100, 1));
    EXPECT_FALSE(matrix80by24.set(-1, -1, 1));
}

TEST_F(MatrixTest, Set_WithVector) {
    // correct size of a vector
    EXPECT_TRUE(matrixImplicit1by1.set({ { 1 } }));
    EXPECT_TRUE(matrixImplicit1by1.set({ { -999 } }));
    EXPECT_TRUE(matrixImplicit1by1.set({ { -999.45646541 } }));
    // incorrect size of a vector
    EXPECT_FALSE(matrixImplicit1by1.set({ { } }));
    EXPECT_FALSE(matrixImplicit1by1.set({ { 1, 2 } }));
    EXPECT_FALSE(matrixImplicit1by1.set({ { 1 }, { 2 } }));
    EXPECT_FALSE(matrixImplicit1by1.set({ { 1, 2 }, { 1, 2 } }));
    EXPECT_FALSE(matrixImplicit1by1.set({ { 1.456, -4.546 }, { 1.55, 2 } }));

    
    // correct size of a vector
    EXPECT_TRUE(matrix2by5.set({ { 1, 2, 3, 4, 5 }, { 5, 4, 3, 2, 1 } }));
    EXPECT_TRUE(matrix2by5.set({ { 1, 2.45, -3.975, 4.575, 5 }, { 5, -4, 3.5, 2.875, 1 } }));
    // incorrect size of a vector
    EXPECT_FALSE(matrix2by5.set({ { 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2 }, { 1, 2 } }));
    EXPECT_FALSE(matrix2by5.set({ { 1, 2 }, { 1, 2 } }));
    
    // correct size of a vector
    std::vector<std::vector<double>> values(80);
    for (int i = 0; i < 80; i++) {
        values[i].resize(24);
    }
    EXPECT_TRUE(matrix80by24.set(values));
    // incorrect size of a vector
    values.resize(79);
    EXPECT_FALSE(matrix80by24.set(values));
}

TEST_F(MatrixTest, Get) {
    EXPECT_NO_THROW(matrixImplicit1by1.get(0, 0));
    EXPECT_ANY_THROW(matrixImplicit1by1.get(10000, 1000000));
    EXPECT_ANY_THROW(matrixImplicit1by1.get(1, 0));
    
    EXPECT_NO_THROW(matrix2by5.get(0, 0));
    EXPECT_NO_THROW(matrix2by5.get(1, 4));
    EXPECT_NO_THROW(matrix2by5.get(1, 1));
    EXPECT_ANY_THROW(matrix2by5.get(-1, 0));
    EXPECT_ANY_THROW(matrix2by5.get(100, 0));
    EXPECT_ANY_THROW(matrix2by5.get(4, 1));
    EXPECT_ANY_THROW(matrix2by5.get(2, 5));
    
    EXPECT_NO_THROW(matrix80by24.get(79, 1));
    EXPECT_NO_THROW(matrix80by24.get(79, 23));
    EXPECT_ANY_THROW(matrix80by24.get(80, 1));
}

TEST_F(MatrixTest, EqualsOperator) {
    Matrix matrix = Matrix(80, 24);
    ASSERT_NO_THROW(matrix == matrix80by24);
    ASSERT_ANY_THROW(matrix2by5 == matrix80by24);

    // compare the same matrices, change value of one matrix and compare again
    ASSERT_TRUE(matrix == matrix80by24);
    matrix80by24.set(50, 10, 10);
    ASSERT_FALSE(matrix == matrix80by24);
    
    // compare same sized matrices with the same items
    matrix = Matrix(1, 1);
    ASSERT_NO_THROW(matrix == matrixImplicit1by1);
    ASSERT_ANY_THROW(matrix80by24 == matrixImplicit1by1);
    
    matrix.set({ { 1 } });
    matrixImplicit1by1.set({ { 1 }});
    ASSERT_TRUE(matrix == matrixImplicit1by1);
    matrix.set({ { 0 } });
    ASSERT_FALSE(matrix == matrixImplicit1by1);
}

TEST_F(MatrixTest, PlusOperator) {
    // add two matrices and compare the result with the expected matrix
    Matrix matrix1 = Matrix(2, 3);
    matrix1.set({ { 1, 2, 3 },
                  { 1, 2, 3 }});
    Matrix matrix2 = Matrix(2, 3);
    matrix2.set({ { 1, 1, 1 },
                  { 1, -2, 0 }});
    Matrix expected_matrix = Matrix(2, 3);
    expected_matrix.set({ { 2, 3, 4 },
                          { 2, 0, 3 }});
    Matrix result = matrix1 + matrix2;
    //ASSERT_NO_THROW(result = matrix1 + matrix2);
    EXPECT_TRUE(result == expected_matrix);

    // size of the matrices is not the same
    EXPECT_ANY_THROW(matrix1 + matrix80by24);
    EXPECT_ANY_THROW(matrix2by5 + Matrix(1, 1));
}

TEST_F(MatrixTest, TimesMatrixOperator) {
    // matrices with incorrect sizes
    EXPECT_ANY_THROW(matrix80by24 * matrix2by5);
    
    // zero matrix times any matrix is all zeroes
    Matrix result;
    Matrix matrix5by2 = Matrix(5, 2);
    matrix5by2.set({ { 1, -2 },
                     { 3, -20 },
                     { 4, 4 },
                     { 2, 3},
                     { 5, 7 } });
    Matrix expected = Matrix(2, 2);
    expected.set({ { 0, 0 },
                   { 0, 0 } });
    EXPECT_TRUE((matrix2by5 * matrix5by2) == expected);

    
    // create, multiply two matrices and compare the result
    // with an expected matrix
    Matrix matrix1 = Matrix(2, 5);
    matrix1.set({ { 1, -2, 3, -20, 4 },
                  { 4, 2, 3, 5, 7 } });
    Matrix matrix2 = Matrix(5, 2);
    matrix2.set({ { 3, 2 },
                  { 1, -4 },
                  { -8, 2 },
                  { 1, 0 },
                  { 2, 2 } });
    expected.set({ { -35, 24 },
                   { 9, 20 } });
    
    EXPECT_TRUE((matrix1 * matrix2) == expected);
    EXPECT_ANY_THROW((matrix2 * matrix1) == expected);
    
    // change the expected to a wrong matrix
    expected.set({ { -35, 24 }, { 9, 19 } });
    EXPECT_FALSE((matrix1 * matrix2) == expected);
}

TEST_F(MatrixTest, TimesConstantOperator) {
    Matrix matrix1 = Matrix(2, 5);
    matrix1.set({ { 1, -2, 3, -20, 4 },
                  { 4, 2, 3, 5, 7 } });
    Matrix expected = Matrix(2, 5);     // multiplied by -157
    expected.set({ { -157, 314, -471, 3140, -628 },
                   { -628, -314, -471, -785, -1099 } });
    ASSERT_TRUE(matrix1 * -157 == expected);
    ASSERT_FALSE(matrix1 * 157 == expected);

    expected.set({ { 0, 0, 0, 0, 0 },
                   { 0, 0, 0, 0, 0 } });
    ASSERT_TRUE(matrix1 * 0 == expected);
    ASSERT_FALSE(matrix1 * 1 == expected);
}

TEST_F(MatrixTest, SolveEquation_Erorrs) {
    // the size of vector must be the same as the number of rows of the matrix
    Matrix a = Matrix(2,2);
    a.set({{7, 5}, {3,-2}});
    EXPECT_ANY_THROW(a.solveEquation({3}));
    EXPECT_ANY_THROW(a.solveEquation({1,2,3}));
    EXPECT_NO_THROW(a.solveEquation({1,2}));

    // the matrix is not a square matrix
    a = Matrix(2,3);
    a.set({{7, 5, 3}, {-2, 1, 2}});
    EXPECT_ANY_THROW(a.solveEquation({1, 2, 3}));

    // matrix is singular
    a = Matrix(3,3);
    a.set({{1, 2, 3}, {2, 4, 6}, {5, 7, 9}});
    EXPECT_ANY_THROW(a.solveEquation({1, 4, 3}));
}

TEST_F(MatrixTest, SolveEquation_1by1) {
    Matrix a = Matrix();
    a.set(0, 0, 5);
    std::vector<double> expected_result = { -3 };
    std::vector<double> result = a.solveEquation({ -15 });
    EXPECT_TRUE(result == expected_result);
}

TEST_F(MatrixTest, SolveEquation_2by2) {
    Matrix a = Matrix(2,2);
    a.set({{7, 5}, {3,-2}});
    std::vector<double> expected_result = {4,-5};
    std::vector<double> result = a.solveEquation({3,22});
    EXPECT_TRUE(result == expected_result);
}

TEST_F(MatrixTest, SolveEquation_7by7) {
    Matrix a = Matrix(7,7);
    a.set( {{-1, 2, 4, 5, 1, 5, 4},
            {3, -4, -7, 2, 8, -5, 1},
            {-7, 2, 5, -4, 7, 8, 1},
            {-7, 4, 1, -5, 4, 1, 2},
            {8, 1, 2, -4, 1, 5, -5},
            {1, -5, 1, -9, 2, -1, -1},
            {-1, 1, -1, -1, -1, 1, 4}});
    

    std::vector<double> expected_result = {4, 5, -2, 4, -3, 1, 2};
    std::vector<double> result = a.solveEquation({28, -13, -55, -37, 9, -68, 11});
    EXPECT_TRUE(result == expected_result);
}


/*** Konec souboru white_box_tests.cpp ***/
