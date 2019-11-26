#include <iostream>

using namespace std;

void setXY(int x, int y){
    printf("%c[%d;%df", 0x1B, y, x);
}

int main(){

    const int h = 10, w = 20;
    bool map[w][h];
    for (int i = 0; i < w; i++){
        for (int j = 0; j < h; j++){
            if (i == 0){
                map[i][j] = 1;
            } else if (j == 0){
                map[i][j] = 1;
            } else if (j == h-1){
                map[i][j] = 1;
            } else if (i == w-1){
                map[i][j] = 1;
            } else {
                map[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            if (map[i][j] == 1){
                setXY(i+2,j+2);
                cout <<"#";
            } else {
                setXY(i+2,j+2);
                cout <<" ";
            }
        }
    }

    // for (int i = 0; i < h; i++){
    //     for (int j = 0; j < w; j++){
    //         cout <<map[i][j];
    //     }
    //     cout <<endl;
    // }

    return 0;
}