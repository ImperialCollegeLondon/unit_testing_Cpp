#include <iostream>

double calculate_norm(int array[])
{
}

double norm_stub(int array[])
{
    return 10.0;
}

void normalize_v1(int array[], int length)
{
    double norm{calculate_norm(array)};

    for (int i{0}; i < length; ++i)
    {
        array[i] /= norm;
    }
}

void normalize_v2(
    int array[],
    int length,
    std::function<double(int[])> func = calculate_norm
    )
{
    double norm{func(array)};

    for (int i{0}; i < length; ++i)
    {
        array[i] /= norm;
    }
}

// This is to be completed
TEST(NormalizeTest, ResultCorrect) {

    double factor{norm_stub([])};
    int length{3};
    int input[length]{1, 2, 3};
    int copy[length]{1, 2, 3};

    normalize_v2(input, length, norm_stub);

    for (int i{0}; i < length; ++i)
    {
        EXPECT_EQ(input[i] * factor, copy[i]);
    }

}
