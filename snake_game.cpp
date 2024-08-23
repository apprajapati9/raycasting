#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>  // For usleep
#include <vector>
#include<utility>

const int BOARD_X = 50;
const int BOARD_Y = 10;

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


struct Snake{
    int x;
    int y;

    Snake* next;

    void print() const {
        cout << "Snake position (" << x << ", " << y << ")" << endl;
    }
};

Snake *head = nullptr;
Snake *tail = nullptr;

void printHeadAndTail(Snake *h, Snake *t){
    cout << "Head points x->" << h->x << " y->" << h->y << endl; 
    cout << "Tail points x->" << t->x << " y->" << t->y << endl; 
}

void printSnakelength(Snake *head){
    Snake* temp = head;
    while(temp != nullptr){
        cout << "x " << temp->x << " y "  <<  temp->y << endl;
        temp = temp->next;
    }
}

//incrase length 
void increaseSize(Snake *head, Snake * s){
    Snake* temp = head; 
    
    if(temp->next == nullptr){
        temp->next = s;
        tail = temp->next;
        return;
    }

    // while(temp){
    //     temp = temp->next;
    // }
    // temp->next = s; 
    tail->next = s;
    tail = tail->next;
}

// 
void boardRedraw(int x, int y, direction dir){ //5, 2
    clearScreen();
    int row = BOARD_X; //10 col  x row 
    int column = BOARD_Y; //5. row. y col 
    
    cout << "x " << x << " y " << y << endl; 

    vector<vector<int> > vector2d;
    vector<pair<int, int> > pairs;

    Snake *temp = head;


    
    while(temp){
        cout << "node->x " << temp->x << " node->y " << temp->y << endl;
        int tx = temp->x;
        int ty = temp->y; 
        temp = temp->next;
        
        if(temp == nullptr){
            break;
        }
        if(dir == UP){
            temp->y = ty - 1;
            temp->x = head->x;
        }
        if(dir == DOWN) {
            temp->y = ty + 1;
            temp->x = head->x;
        }

        if(dir == LEFT){
            temp->x = tx - 1;
            temp-> y = head->y;
        }
        if(dir == RIGHT){
            temp->x = tx+ 1;
            temp->y = head->y;
        }

        int x = temp->x;
        int y = temp->y;

        pair<int, int> mPair(x, y);
        vector<int> v;
        v.push_back(y);
        v.push_back(x);

        pairs.push_back(mPair);
        vector2d.push_back(v);
    }
    
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


// snake add(const snake& p1, const snake& p2) {
//     return snake(p1.x + p2.x, p1.y + p2.y);
// }

void updateSnake(Snake* s, direction &dir) {
    
    int prevX = s->x;
    int prevY = s->y; 

    cout << "prev " << prevX << " prevY " << prevY << endl;

    if(dir == UP){
        cout << "updatedSnake up";
       // s.x = x;
        if(s->y == 0){
            s->y = BOARD_Y;
        }else{
            s->y = s->y-1;
        }
    }

    if(dir == DOWN){
        cout << "updatedSnake down";
       // s->x = x;
        if(s->y == BOARD_Y){
            s->y = 0;
        }else{
            s->y = s->y+1;
        }
    }

    if(dir == LEFT){
        cout << "updatedSnake left";
       // s->x = x;
        if(s->x == 0){
            s->x = BOARD_X;
        }else{
            s->x = s->x-1;
        }
    }

    if(dir == RIGHT){
        cout << "updatedSnake RIGHT";
       // s->x = x;
        if(s->x == BOARD_X){
            s->x = 0;
        }else{
            s->x = s->x+1;
        }
    }

    
    s->print();
    boardRedraw(s->x, s->y, dir);
    //cout << dir << endl;
}


int main() {

    Snake *snake = new Snake();
    snake->x = 10;
    snake->y = 5;

    head = snake;
    tail = snake;

    Snake *snake2 = new Snake();
    snake2->x = 11;
    snake2->y = 5;

    Snake *snake3 = new Snake();
    snake3->x = 12;
    snake3->y = 5;

    Snake *snake4 = new Snake();
    snake4->x = 13;
    snake4->y = 5;

    increaseSize(head, snake2);
    increaseSize(head, snake3);
    increaseSize(head, snake4);

    //head->next = snake2;
    printSnakelength(head);
    printHeadAndTail(head, tail);
    
    
    
    
    //snake.print();
    
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
                if (ch == 'q' || ch == 'Q') {  // Exit on 'q' key
                    break;
                }
            }
            
            
        }
        updateSnake(head, dir);
    }

    return 0;
}