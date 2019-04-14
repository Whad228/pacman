#include <iostream>
using namespace std;
const int height = 19, width = 19;
const int wall = 1, pass = 0;

bool deadend(int x, int y, int** maze, int height, int width){
    int a = 0;

    if(x != 1){
        if(maze[y][x-2] == pass)
            a+=1;
    }
    else a+=1;

    if(y != 1){
        if(maze[y-2][x] == pass)
            a+=1;
    }
    else a+=1;

    if(x != width-2){
        if(maze[y][x+2] == pass)
            a+=1;
    }
    else a+=1;

    if(y != height-2){
        if(maze[y+2][x] == pass)
            a+=1;
    }
    else a+=1;

    if(a == 4)
        return 1;
    else
        return 0;
}


void visual(int** maze, int height, int width){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++)
            switch(maze[i][j]){
                case wall: cout<< "0 "; break;
                case pass: cout<< "  "; break;
            }
        cout<<endl;
    }
    cout<<endl;
}

int** mazemake(int height, int width){
    int x, y, c, a;
    bool b;

    int** maze = new int*[height];
    for(int i = 0; i < height; i++)
        maze[i] = new int[width];

    for(int i = 0; i < height; i++) // Массив заполняется ноликами
        for(int j = 0; j < width; j++)
            maze[i][j] = wall;
//    x = 5;
//    y = 5;
    x = 1;
    y = 1;
    a = 0; // Точка начала и счетчик
    while(a < 10000000){ // ???????костыль
        maze[y][x] = pass;
        a++;
        while(1){ // Бесконечный цикл, который прерывается только тупиком
            c = rand()%4; //  алгоритм проходит
            switch(c){  // по две клетки в одном направлении за прыжок
                case 0: if(y != 1)
                        if(maze[y-2][x] == wall){ // Вверх
                            maze[y-1][x] = pass;
                            maze[y-2][x] = pass;
                            y-=2;
                        }
                case 1: if(y != height-2)
                        if(maze[y+2][x] == wall){ // Вниз
                            maze[y+1][x] = pass;
                            maze[y+2][x] = pass;
                            y+=2;
                        }
                case 2: if(x != 1)
                        if(maze[y][x-2] == wall){ // Налево
                            maze[y][x-1] = pass;
                            maze[y][x-2] = pass;
                            x-=2;
                        }
                case 3: if(x != width-2)
                        if(maze[y][x+2] == wall){ // Направо
                            maze[y][x+1] = pass;
                            maze[y][x+2] = pass;
                            x+=2;
                        }
            }
            if(deadend(x, y, maze, height, width))
                break;
        }

        if(deadend(x, y, maze, height, width)) // Вытаскиваем алгоритм из тупика
            do {
                x = 2*(rand()%((width-1)/2))+1;
                y = 2*(rand()%((height-1)/2))+1;
            }
            while(maze[y][x] != pass);
    }

    const int prob = 50;
    for (int i = 3; i < height-2; i+=2) {
        for (int j = 3; j < width-2; j+=2) {
            //cout << "(" << i << ", " << j << ")" << endl;
            //cout << maze[i-1][j] << ", " << maze[i][j-1] << ", " << maze[i][j+1] << ", " << maze[i+1][j] << endl;
            int tupik[4] = {maze[i-1][j], maze[i][j-1], maze[i][j+1], maze[i+1][j]};
            int sum =0;
            for (int k = 0; k < 4; k++) {
                sum += tupik[k];
            }
            if (sum >= 3) {
                int generate_probab = rand()%100;
                if (1) {
                    c = rand()%4;
                    switch(c){
                        case 0: if(maze[i-1][j] == wall){ // Вверх
                                    maze[i-1][j] = pass;
                                }
                        case 1: if(maze[i+1][j] == wall){ // Вниз
                                    maze[i+1][j] = pass;
                                }
                        case 2: if(maze[i][j-1] == wall){ // Налево
                                    maze[i][j-1] = pass;
                                }
                        case 3: if(maze[i][j+1] == wall){ // Направо
                                    maze[i][j+1] = pass;
                                }
                        default:break;
                    }
                }
            }
        }
    }

    return maze;
};

int main() {
    srand((unsigned)time(NULL));
    int** newmaze = mazemake(height, width);
    visual(newmaze, height, width);
}
