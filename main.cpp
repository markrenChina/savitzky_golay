#include <iostream>
#include <vector>
#include "Eigen/Dense"

/**
 * @author markrenChina
 */
using namespace Eigen;
using namespace std;

int vander(int M, int N, MatrixXd &res) {
    MatrixXd move_box(2 * M + 1, N);
    for (int i = -M; i <= M; ++i) {
        for (int j = 0; j < N; ++j) {
            move_box(i + M, j) = pow(i, j);
        }
    }
    res = move_box;
    return 0;
}

int generalized_inverse(MatrixXd &mat, MatrixXd &res) {
    MatrixXd matTranspose = mat.transpose();
    MatrixXd matTMmat = matTranspose * mat;
    MatrixXd inverseMatTMmat = matTMmat.inverse();
    res = inverseMatTMmat * matTranspose;
    return 0;
}

int savitzky_golay(vector<double> &data, int M, int N, vector<double> &res) {
    MatrixXd move_box;
    vander(M, N, move_box);
    cout << move_box << endl;
    MatrixXd gen_inv;
    generalized_inverse(move_box, gen_inv);
    cout << gen_inv << endl;
    res = data;
    //校验
    if (data.size() <= 2 * M + 1) {
        cout << "the length of the input_data is too short!" << endl;
        return 101;
    }

    if (2 * M + 1 <= N) {
        cout << "box size is too small!" << endl;
        return 102;
    }

    for (int i = M; i < data.size() - M; ++i) {
        MatrixXd y_box_value(2 * M + 1, 1);
        for (int j = -M; j <= M; ++j) {
            y_box_value(j + M, 0) = data[i + j];
        }

        MatrixXd ls_sol = gen_inv * y_box_value;
        MatrixXd result = move_box * ls_sol;
        res[i] = result(M, 0);
        if (i == M) {
            for (int k = 0; k < M; k++) {
                res[k] = result(k, 0);
            }
        } else if (i == (data.size() - M - 1)) {
            for (int k = 1; k < M + 1; k++) {
                res[i + k] = result(k + M, 0);
            }
        }
    }

    return 0;
}


int main() {

    int M = 2;
    int N = 3;

    vector<double> test_data(150);
    test_data = {594, 2909, 3457, 3844, 4153, 4444, 4653, 4866, 5072, 5255, 5446, 5645, 5826, 6007, 6214, 6410, 6593,
                 6810, 6976,
                 7183, 7368, 7560, 7748, 7941, 8135, 8330, 8515, 8688, 8863, 9070, 9240, 9407, 9578, 9748, 9909, 10067,
                 10247,
                 10444, 10600, 10734, 10886, 11019, 11161, 11296, 11438, 11580, 11696, 11815, 11939, 12054, 12179,
                 12266, 12400,
                 12519, 12629, 12748, 12866, 13004, 13120, 13216, 13336, 13447, 13545, 13671, 13770, 13899, 14006,
                 14138, 14295,
                 14446, 14620, 14841, 15065, 15389, 15682, 16088, 16508, 16944, 17347, 17669, 17843, 17836, 17682,
                 17430, 17172,
                 17009, 16812, 16667, 16577, 16498, 16461, 16435, 16410, 16409, 16399, 16401, 16412, 16470, 16469,
                 16501, 16532,
                 16609, 16646, 16721, 16754, 16807, 16868, 16960, 17042, 17121, 17198, 17308, 17434, 17574, 17742,
                 17957, 18220,
                 18472, 18835, 19182, 19512, 19826, 20024, 20076, 20011, 19856, 19638, 19470, 19311, 19221, 19147,
                 19108, 19118,
                 19084, 19106, 19113, 19153, 19200, 19283, 19348, 19440, 19571, 19675, 19872, 20031, 20226, 20405,
                 20617, 20858,
                 21064};

    vector<double> sgData;
    savitzky_golay(test_data, 2, 3, sgData);

    for (int i = 0; i < sgData.size(); ++i) {
        cout << i << "  " << sgData[i] << endl;
    }


    return 0;
}
