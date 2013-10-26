//////////////////////////////////////////////////////////////////////////////////////
/// \brief      C++ for C Programmers - Home Work #1.
/// \author     Carlos Sampaio
/// \date       18/10/2013
///
///             The exercise objective is to convert a simple C program to C++.
///
//////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
using namespace std;

/// Width of main data vector.
const int DATA_WIDTH = 40;

/// \brief  Initialize a vector of variable size.
///         The value of each position will be its respective index.
/// \param  size    The vector size.
/// \return         The created vector.
///
inline vector<int> init_vector(int size)
{
    vector<int> data(size);
    for(int i = 0; i < size; ++i)
        data[i] = i;
    return data;
}

/// \brief  Sum all positions of a given vector.
/// \param  input   The vector to be calculated.
/// \return         The total sum.
///
int sum(vector<int> &input)
{
    int result = 0;
    for(int i = 0; i < input.size(); ++i)
        result = result + input[i];
    return result;
}

/// \brief  Main function.
/// \param  argc    Number of command line arguments
/// \param  argv    Array of command line arguments
/// \return         Exit code, 0 upon success
///
int main(int argc, char *argv[])
{
    vector<int> data;                   // Vector with input data.
    int accum;                          // Accumulated value of all data vector positions.

    data = init_vector(DATA_WIDTH);     // Initialize vector.
    accum = sum(data);                  // Do the calculation.

    cout << "Sum is " << accum << endl; // Output answer to the system.

    return 0;
}
