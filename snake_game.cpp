#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>  // For usleep


using namespace std;

// Function to check if a key has been pressed
bool kbhit() {
    struct termios oldt, newt;
    int ch;
    bool ret = false;

    // Get current terminal attributes
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set stdin to non-blocking mode
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    // Check if a key is available
    ch = getchar();
    if (ch != EOF) {
        ret = true;
        ungetc(ch, stdin);  // Put the character back to the input stream
    }

    // Restore terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ret;
}

void clearScreen() {
    std::cout << "\033[2J\033[H"; // Clear screen and move cursor to the top-left corner
    std::cout.flush(); // Ensure that the output is written immediately
}

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

// 
void boardRedraw(int bx, int by, int x, int y, direction dir){ //5, 2
    clearScreen();
    int row = bx; //10 col  x row 
    int column = by; //5. row. y col 
    
    cout << "x " << x << " y " << y << endl; 
    
    // if(dir == UP){
        cout << "direction " << dir << endl;
        
        for(int i = 0; i <= column; i++){
            for(int j = 0; j <= row; j++){
                if(i == y && j == x){
                    cout << "X";
                }
                else cout << ".";
            }
            cout << endl;
        }
    //}
    
    if(dir == DOWN){
        cout << "direction " << dir << endl; 
    }

    // for(int i = 1 ; i <= column; i++){
    //         for(int j = 1; j <= row; j++){
               
    //             if(x==i && y ==j ){
    //                 cout << "X";
    //             }else{
    //                 cout << ".";
    //             }
    //         }
    //         cout << endl;
    //     }
}




struct Snake{
    int x;
    int y;

    int boardx = 50;
    int boardy = 10;
    
    void print() const {
        cout << "Snake position (" << x << ", " << y << ")" << endl;
    }
};

// snake add(const snake& p1, const snake& p2) {
//     return snake(p1.x + p2.x, p1.y + p2.y);
// }

void updateSnake(Snake& s, direction &dir) {
    
    
    if(dir == UP){
        cout << "updatedSnake up";
       // s.x = x;
        if(s.y == 0){
            s.y = s.boardy;
        }else{
            s.y = s.y-1;
        }
    }

    if(dir == DOWN){
        cout << "updatedSnake down";
       // s.x = x;
        if(s.y == s.boardy){
            s.y = 0;
        }else{
            s.y = s.y+1;
        }
    }

    if(dir == LEFT){
        cout << "updatedSnake left";
       // s.x = x;
        if(s.x == 0){
            s.x = s.boardx;
        }else{
            s.x = s.x-1;
        }
    }

    if(dir == RIGHT){
        cout << "updatedSnake RIGHT";
       // s.x = x;
        if(s.x == s.boardx){
            s.x = 0;
        }else{
            s.x = s.x+1;
        }
    }

    
    s.print();
    boardRedraw(s.boardx, s.boardy, s.x, s.y, dir);
    //cout << dir << endl;
}


int main() {

    Snake snake;
    snake.x = 10;
    snake.y = 5;
    
    snake.print();
    
    direction dir = UP; //default direction. 
    
    while (true) {
        usleep(100000);
       
        if (kbhit()) {
            int ch = getchar();  // Read the first character

            if (ch == '\033') {  // Check for ESC character (beginning of arrow key sequence)
                getchar();      // Skip '[' character
                switch (getchar()) {  // Read the arrow key identifier
                    case 'A':
                        std::cout << "Up Arrow" << std::endl;
                        //clearScreen();
                        dir = UP;
                        //updateSnake(snake, dir);
                        //boardRedraw(1,1,dir);
                        break;
                    case 'B':
                        std::cout << "Down Arrow" << std::endl;
                        //clearScreen();
                        dir = DOWN;
                        //boardRedraw(10,20,dir);
                        break;
                    case 'C':
                        std::cout << "Right Arrow" << std::endl;
                        dir = RIGHT;
                        break;
                    case 'D':
                        std::cout << "Left Arrow" << std::endl;
                        dir = LEFT;
                        break;
                    default:
                        //boardRedraw(10,5, dir);
                        //std::cout << "Unknown key sequence" << std::endl;
                        break;
                }
            } else {
                
                //std::cout << "Key pressed: " << (char)ch << std::endl;
                if (ch == 'q') {  // Exit on 'q' key
                    break;
                }
            }
            
            
        }
        updateSnake(snake, dir);
    }

    return 0;
}