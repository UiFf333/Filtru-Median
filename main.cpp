#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void file_reading(ifstream &fin, int &width, int &height, int &max_level, int **&image, string &text) {
    string file_type;
    text = "";
    fin >> file_type;
    fin>>ws;
    if (fin.peek() == '#') {
        getline(fin, text);
        fin >> width >> height >> max_level;
    } else {
        fin >> width >> height >> max_level;
    }

    image = new int *[height];
    for (int i = 0; i < height; i++) {
        image[i] = new int[width];
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fin >> image[i][j];
        }
    }
}

void bubbleSort(vector<int> &arr) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void merge(vector<int> &arr, int left,
           int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int> &arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int **rearange_image(int **&image, int const &witdth, int const &height, string const &algorithm, int const &size) {
    vector<int> vecini;
    int **new_image = new int *[height];
    int offset=size/2;
    for (int i = 0; i < height; i++) {
        new_image[i] = new int[witdth];
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < witdth; j++) {
            for (int m = i -offset; m <= i +offset; m++) {
                for (int n = j -offset; n <= j +offset; n++) {
                    int x = m;
                    int y = n;
                    if (x < 0) x = 0;
                    if (x >= height) x = height - 1;

                    if (y < 0) y = 0;
                    if (y >= witdth) y = witdth - 1;
                    vecini.push_back(image[x][y]);
                }
            }
            if (algorithm == "merge") {
                mergeSort(vecini, 0, vecini.size() - 1);
            } else {
                bubbleSort(vecini);
            }
            new_image[i][j] = vecini[vecini.size() / 2];
            vecini.clear();
        }
    }
    return new_image;
}

void generate_output(ofstream &fout, int **&image, int const &witdth, int const &height, const int &max_level) {
    fout << "P2" << endl;
    fout << witdth << " " << height << " " << endl << max_level << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < witdth; j++) {
            fout << image[i][j] << " ";
        }
        fout << endl;
    }
}


int main() {
    string ifile, ofile, algorithm, text;
    int size, witdth, height, max_level;
    cin >> algorithm >> size >> ifile >> ofile;
    ifstream fin(ifile);
    if (!fin.is_open()) return 1;
    ofstream fout(ofile);
    int **image;
    int **new_image;
    file_reading(fin, witdth, height, max_level, image, text);
    new_image = rearange_image(image, witdth, height, algorithm,size);
    generate_output(fout, new_image, witdth, height, max_level);
    for (int i = 0; i < height; i++) {
        delete[] new_image[i];
        delete[] image[i];
    }
    delete[] new_image;
    delete[] image;
    return 0;
}
