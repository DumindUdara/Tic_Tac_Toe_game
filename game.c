#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

//X = 1, O= -1


//grid
int grid[9]= {0};



//function prototype

void start();
//void input(char* name_1, char* name_2);
void play_phase_1(char* name_1, char* name_2);
int request_placement(char* name , int type);
int placement(int c_position, int type);

void play_phase_2(char* name_1, char* name_2, int next_move);
int request_movement(char* name, int tp);
int movement(int c_position, char n_position, int type);

int* collision_check(int check_position);
int* empty_check(int pos);
int* type_check(int pos , int type);
int* jump_check(int cpos, int npos);
//int* diagonal_check();
//no_valid_moves_available(); - if a party doesnt have any valid moves, the game is instantly declared a draw

void win_check(char* name_1, char* name_2);

void display();




//global variables
char name1[15];
char name2[15];







//main
int main(){


    start();
    play_phase_1(name1, name2);  //plcement



    return 0;
}


//Play
void start(){


    //wellcome note
    /*
    inset here

    */


   //requesting player names
    printf("Select Player");
    printf("\nX Player enter your name:");
    scanf("%[^\n]%*c", name1);
    printf("\nO Player enter your name:");
    scanf("%[^\n]%*c", name2);

}


//placing the pieces
void play_phase_1(char* name_1, char* name_2){
    int input_1, input_2;
    int c_1=0,c_2=0;

    //choosing who goes first
    srand(time(0));
    int starter = rand()%2+1;

    if(starter == 1){
        printf("\n%s start the game",name_1);
        display();
        request_placement(name1, 1);
        display();
        request_placement(name2, -1);
        display();
        request_placement(name1, 1);
        display();
        request_placement(name2, -1);
        display();
        request_placement(name1, 1);
        display();
        win_check(name1,name2);
        request_placement(name2, -1);
        display();
        win_check(name1, name2);
        play_phase_2(name1, name2, 1);
    }
    else{
        ;
        printf("\n%s start the game",name_2);
        display();
        request_placement(name2, -1);
        display();
        request_placement(name1, 1);
        display();
        request_placement(name2, -1);
        display();
        request_placement(name1, 1);
        display();
        request_placement(name2, -1);
        display();
        win_check(name1, name2);
        request_placement(name1, 1);
        display();
        win_check(name1, name2);
        play_phase_2(name1,name2,2);
    }

}

//request placements
int request_placement(char* name, int type){
    int input;
    int invalid_input=0;
    printf("\n%s place the piece on the grid ",name);
    scanf("%d", &input);
    invalid_input = placement(input, type);
    if(invalid_input == 1){
        request_placement(name, type);
    }
    else{
        return 0;
    }

}


//movement phase
void play_phase_2(char* name_1, char* name_2,int next_move){
    int cpos, npos, tp;
    char draw, new_game;

    if(next_move == 1){
        request_movement(name_1, 1);
        display();
        win_check(name1, name2);
        request_movement(name_2,-1);
        display();
        win_check(name1, name2);
        request_movement(name_1, 1);
        display();
        win_check(name1, name2);
        request_movement(name_2,-1);
        display();
        win_check(name1, name2);
        request_movement(name_1, 1);
        display();
        win_check(name1, name2);
        request_movement(name_2,-1);
        display();
        win_check(name1, name2);
        printf("\nDo you want to declare a draw ?");
        scanf(" %c", &draw);
        if(draw == 'y'){
            printf("\nDo you want to start a new game ?");
            scanf(" %c",&new_game);
            if(new_game == 'y'){
                for(int l = 0; l<9; l++){
                    grid[l] = 0;
                }
                play_phase_1(name1,name2);
            }
            else if(new_game == 'n'){
                exit(0);
            }
        }
        else if(draw == 'n'){
            play_phase_2(name1, name2, 1);
        }

    }
    else if(next_move == 2){
        request_movement(name_2, -1);
        display();
        win_check(name1, name2);
        request_movement(name_1, 1);
        display();
        win_check(name1, name2);
        request_movement(name_2, -1);
        display();
        win_check(name1, name2);
        request_movement(name_1, 1);
        display();
        win_check(name1, name2);
        request_movement(name_2, -1);
        display();
        win_check(name1, name2);
        request_movement(name_1, 1);
        display();
        win_check(name1, name2);
        printf("\nDo you want to declare a draw ?");
        scanf(" %c", &draw);
        if(draw == 'y'){
            printf("\nDo you want to start a new game ?");
            scanf(" %c",&new_game);
            if(new_game == 'y'){
                for(int l = 0; l<9; l++){
                    grid[l] = 0;
                }
                play_phase_1(name1,name2);
            }
            else if(new_game == 'n'){
                exit(0);
            }
        }
        else if(draw == 'n'){
            play_phase_2(name1, name2, 2);
        }
    }
}

//request movements - similar functon to the request placements function
int request_movement(char* name, int tp){
    int cpos, npos;
    int error;

    printf("\n%s Enter the current position on the grid : ", name);
    scanf(" %d", &cpos);
    printf("\n%s Enter the next position on the grid : ", name);
    scanf(" %d", &npos);
    error = movement(cpos, npos, tp);
    if(error == 1){
        printf("\n%s, your current location input is invalid !", name);
        request_movement(name, tp);
    }
    else if(error == 2){
        printf("\n%s, your next location input is invalid !", name);
        request_movement(name, tp);
    }

}



//move
int movement(int c_position, char n_position, int type){


    //moving already existing pieces
    int* e = empty_check(c_position);
    int* t = type_check(c_position, type);
    if(*e == 1 || *t == 1){
        printf("\nInvalid input !\n");
        return 1;
    }
    else{
        int* jump = jump_check(c_position, n_position);
        int* col_2 = collision_check(n_position);
        if(*col_2 == 1 || *jump == 1){
            printf("\ninvalid move !\n");
            return 2;
        }
        else{
            *(grid+n_position-1) = *(grid+c_position-1);
            *(grid+c_position-1) = 0;
        }
    }
}

//placement
int placement(int c_position, int type){


    int* col_1 = collision_check(c_position);
    if(*col_1 == 0){
        if(type == 1){
            *(grid+c_position-1)= 1;
            return 0;
        }
        else if(type == -1){
            *(grid+c_position-1) = -1;
            return 0;
        }
    }
    else if(*col_1 == 1){
        printf("\nInvalid Placement !\n");
        return 1;
    }

}

//collision check
int collision = 0;
int* pcollision = &collision;
int* collision_check(int check_position){
    if(check_position>9){
        collision = 1;
        return pcollision;
    }

    else if( (*(grid+check_position-1) == 1) || (*(grid+check_position-1) == -1) ){
        collision = 1;
        return pcollision;
    }
    else{
        collision = 0;
        return pcollision;
    }
}

//empty cell check
int empty;
int* pempty = &empty;
int* empty_check(int pos){

    if(*(grid+pos-1) == 0){
        //printf("\nempty cell ");
        empty = 1;
        return pempty;
    }
    else{
        //printf("\nnot empty");
        empty = 0;
        return pempty;
    }


}

//check for the picece type
int type_cheking;
int* ptype = &type_cheking;
int* type_check(int pos, int type){
    if(*(grid+pos-1) == type){
        //same type
        type_cheking = 0;
        return ptype;
    }
    else if(*(grid+pos-1) != type){
        //not same type
        type_cheking = 1;
        return ptype;
    }
}

//jump check
int jump_cheking;
int* pjump_cheking = &jump_cheking;
int* jump_check(int cpos, int npos){
    int jump_grid[9][9] = {
        {1,0,1,0,0,1,1,1,1},
        {0,1,0,1,0,1,1,1,1},
        {1,0,1,1,0,0,1,1,1},
        {0,1,1,1,0,1,0,1,1},
        {0,0,0,0,1,0,0,0,0},
        {1,1,0,1,0,1,1,1,0},
        {1,1,1,0,0,1,1,0,1},
        {1,1,1,1,0,1,0,1,0},
        {1,1,1,1,0,0,1,0,1}
    };

    if(jump_grid[cpos-1][npos-1] == 1){

        jump_cheking = 1;
        return pjump_cheking;
    }
    else{

        jump_cheking = 0;
        return pjump_cheking;
    }

}


//win conditions check
void win_check(char* name_1, char* name_2){
    int win = 0;
    int winner= 0;
    char replay;

    int h1,h2,h3,v1,v2,v3,d1,d2;
    h1 = grid[0] + grid[1] + grid[2];
    h2 = grid[3] + grid[4] + grid[5];
    h3 = grid[6] + grid[7] + grid[8];
    v1 = grid[0] + grid[3] + grid[6];
    v2 = grid[1] + grid[4] + grid[7];
    v3 = grid[2] + grid[5] + grid[8];
    d1 = grid[0] + grid[4] + grid[8];
    d2 = grid[2] + grid[4] + grid[6];


    if(h1 == 3 || h2 == 3 || h3 == 3 || v1==3 || v2 == 3 || v3 == 3|| d1 == 3 || d2 == 3){
        win = 1;
        winner = 1;
    }
    else if(h1 == -3 || h2 == -3 || h3 == -3 || v1==-3 || v2 == -3 || v3 == -3|| d1 == -3 || d2 == -3){
        win =1;
        winner = 2;
    }


   if(win == 1){
       if(winner == 1){
            printf("\n%s is the winner !", name_1);
            printf("\nDo you want to play again: (y/n)");
            scanf(" %c", &replay);
            if(replay == 'n'){
                exit(0);

            }
            else if(replay == 'y'){
                for(int i = 0; i<9; i++){
                    grid[i] = 0;
                }
                play_phase_1(name1, name2);

            }

        }
        else{
            printf("\n%s is the winner !", name_2);
            printf("\nDo you want to play again: (y/n)");
            scanf(" %c",&replay);
            if(replay == 'n'){
                exit(0);

            }
            else if(replay == 'y'){
                for(int i = 0; i<9; i++){
                    grid[i] = 0;
                }
                play_phase_1(name1, name2);
            }


        }
   }
}


//display
void display(){
    char x_o_grid[9];
    for(int j = 0; j<9; j++){
        if(grid[j]==1){
            x_o_grid[j]= 'X';
        }
        else if(grid[j] ==-1){
            x_o_grid[j] = 'O';
        }
        else{
            x_o_grid[j] = ' ';
        }
    }

    printf("\n|   %c\t|   %c\t|   %c\t|",x_o_grid[0],x_o_grid[1],x_o_grid[2]);
    printf("\n|   %c\t|   %c\t|   %c\t|",x_o_grid[3],x_o_grid[4],x_o_grid[5]);
    printf("\n|   %c\t|   %c\t|   %c\t|",x_o_grid[6],x_o_grid[7],x_o_grid[8]);

}

