#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>


/*==========================Defines==========================*/

#define MAXLIN 22
#define MAXCOL 59

/*==========================Vairables=========================*/

char joy;
char map[MAXLIN][MAXCOL];
struct gamer{
    int x, y;
    int alive;

};
struct gamer player;
struct gamer robot[100];

int n_enemies, score, master_quit=0, enable_mv=0, kill=0;
char p;

void move_human()
{
    //initscr();
    __fpurge(stdin);
	p = getchar();
    //endwin();
    printf("\n%c\n",p);
	int m=1;
    switch(p)
    {
        case 'q':/*Cima e esquerda (Diagonal)*/
            {
                if(map[(player.x-1)][(player.y-1)]!='*' && player.y>0 && player.x>0)
                {
                	
                	m=safe_loc();
                	if(m==0)
	                {
	                    player.x--;
	                    player.y--;
	                    enable_mv=1;
	                }
                }
                
                break;
            }
        case 'w':/*Cima*/
            {
                if(map[(player.x-1)][(player.y)]!='*'&& player.x>0)
                {
                	m=safe_loc();
                	if(m==0)
                	{
	                    player.x--;
	                    enable_mv=1;
	                }
                }
                
                break;
            }
        case 'e':/*Cima e direita (Diagonal)*/
            {
                if(map[(player.x-1)][(player.y+1)]!='*'&& player.y<58 && player.x>0)
                {
                	m=safe_loc();
                	if(m==0)
                	{
	                    player.x--;
	                    player.y++;
	                    enable_mv=1;
	                }
                }
                
                break;
            }
        case 'a':/*esquerda*/
            {
                if(map[(player.x)][(player.y-1)]!='*' && player.y>0)
                {
                	m=safe_loc();
                	if(m==0)
                	{
	                    player.y--;
	                    enable_mv=1;
	                }
                }
                
                break;
            }
        case 'd':/*direita*/
            {
                if(map[(player.x)][(player.y+1)]!='*' && player.y<58)
                {
                	m=safe_loc();
                	if(m==0)
                	{
	                    player.y++;
	                    enable_mv=1;
	                }
                }
                
                break;
            }
        case 'z':/*Baixo e Esquerda (diagonal)*/
            {
                if(map[(player.x+1)][(player.y-1)]!='*' && player.y>0 && player.x<21)
                {
                	m=safe_loc();
                	if(m==0)
                	{
	                    player.x++;
	                    player.y--;
	                    enable_mv=1;
	                }
                }
                
                break;
            }
        case 'x':/*Baixo*/
            {
                if(map[(player.x+1)][(player.y)]!='*' && player.x<21)
                {
                	m=safe_loc();
                	if(m==0)
                	{
					    player.x++;
                    	enable_mv=1;
                    }
                }
                
                break;
            }
        case 'c':/*Baixo e Direita (Diagonal)*/
            {   
                if(map[(player.x+1)][(player.y+1)]!='*' && player.y<58 && player.x<21)
                {
                	m=safe_loc();
                	if(m==0)
                	{
	                    player.x++;
	                    player.y++;
	                    enable_mv=1;
	                }
                }
                
                break;
            }
        case 't':/*teleporte aleatorio*/
            {
                player.x=rand()%MAXLIN;
                player.y=rand()%MAXCOL;
                enable_mv=1;
                printf("\nTeleporte!");
                usleep(500000);
                break;
            }
        
        case 'h':/*manual do jogo*/
            {
                //help();
                //__fpurge(stdin);
                getchar();
                break;
            }
        case 'n':
        	{
        		printf("Redraw map? ");
        		while(1)
				{
					__fpurge(stdin);
					char q;
					q=getchar();
					if(q=='y')
					{
						new_map_enemies();
						print_map();
						break;
					}
					if(q=='n')
					{
						break;
					}
					
				}
				break;	
			}
		case 'k':
			{
				printf(" Auto-kill? ");
				while(1)
				{
					__fpurge(stdin);
					char q;
					q=getchar();
					if(q=='y')
					{
						kill=1;
						break;
					}
					if(q=='n')
					{
						break;
					}
					
				}    
				break;
			}
        case 27:
        	{
        		printf(" Really quit? ");
        		while(1)
				{
					__fpurge(stdin);
					char q;
					q=getchar();
					if(q=='y')
					{
						master_quit=1;
						break;
					}
					if(q=='n')
					{
						master_quit=0;
						break;
					}
					
				}    
				break;		
			}
        default:
            {
                printf("\nComando Invalido\n");
                __fpurge(stdin);
                usleep(500000);
                break;
            }
            
    
    }
    if(player.x<0)
        player.x=0;
    if(player.x>21)
        player.x=21;
    if(player.y<0)
        player.y=0;
    if(player.y>58)
        player.y=58;
    

}

int safe_loc()
{
	int b, test_loc=0;
	
	switch(p)
	{
		case 'q':
			{
				
				for(b=0;b<n_enemies;b++)
				{
					if((((player.x-1)==robot[b].x) && ((player.y-1)==robot[b].y)) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==robot[b].x && (player.y-1)==(robot[b].y-1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==robot[b].x && (player.y-1)==(robot[b].y+1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x-1) && (player.y-1)==robot[b].y && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x-1) && (player.y-1)==(robot[b].y-1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x-1) && (player.y-1)==(robot[b].y+1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x+1) && (player.y-1)==robot[b].y && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x+1) && (player.y-1)==(robot[b].y+1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x+1) && (player.y-1)==(robot[b].y-1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					
				}
				
				break;
			}
			case 'w':
			{
				
				for(b=0;b<n_enemies;b++)
				{
					if((((player.x-1)==robot[b].x) && ((player.y)==robot[b].y)) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==robot[b].x && (player.y)==(robot[b].y-1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==robot[b].x && (player.y)==(robot[b].y+1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x-1) && (player.y)==robot[b].y && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x-1) && (player.y)==(robot[b].y-1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x-1) && (player.y)==(robot[b].y+1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x+1) && (player.y)==robot[b].y && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x+1) && (player.y)==(robot[b].y+1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x+1) && (player.y)==(robot[b].y-1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					
				}
				
				break;
			}
		case 'e':
			{
				for(b=0;b<n_enemies;b++)
				{
					if((((player.x-1)==robot[b].x) && ((player.y+1)==robot[b].y)) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==robot[b].x && (player.y+1)==(robot[b].y-1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==robot[b].x && (player.y+1)==(robot[b].y+1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x-1) && (player.y+1)==robot[b].y && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x-1) && (player.y+1)==(robot[b].y-1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x-1) && (player.y+1)==(robot[b].y+1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x+1) && (player.y+1)==robot[b].y && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x+1) && (player.y+1)==(robot[b].y+1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					if((player.x-1)==(robot[b].x+1) && (player.y+1)==(robot[b].y-1) && robot[b].alive==1)
					{
						test_loc=1;
					}
					
				}
				break;
			}
			case 'a':
				{
					for(b=0;b<n_enemies;b++)
					{
						if((((player.x)==robot[b].x) && ((player.y-1)==robot[b].y)) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==robot[b].x && (player.y-1)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==robot[b].x && (player.y-1)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==(robot[b].x-1) && (player.y-1)==robot[b].y && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==(robot[b].x-1) && (player.y-1)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==(robot[b].x-1) && (player.y-1)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==(robot[b].x+1) && (player.y-1)==robot[b].y && robot[b].alive==1) 
						{
							test_loc=1;
						}
						if((player.x)==(robot[b].x+1) && (player.y-1)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==(robot[b].x+1) && (player.y-1)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
					
					}
					break;
				}
			case 'd':
				{
					for(b=0;b<n_enemies;b++)
					{
						if((((player.x)==robot[b].x) && ((player.y+1)==robot[b].y)) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==robot[b].x && (player.y+1)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==robot[b].x && (player.y+1)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==(robot[b].x-1) && (player.y+1)==robot[b].y && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==(robot[b].x-1) && (player.y+1)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==(robot[b].x-1) && (player.y+1)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==(robot[b].x+1) && (player.y+1)==robot[b].y && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==(robot[b].x+1) && (player.y+1)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x)==(robot[b].x+1) && (player.y+1)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
					
					}
					break;
				}
			case 'z':
				{
					for(b=0;b<n_enemies;b++)
					{
						if((((player.x+1)==robot[b].x) && ((player.y-1)==robot[b].y)) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==robot[b].x && (player.y-1)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==robot[b].x && (player.y-1)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x-1) && (player.y-1)==robot[b].y && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x-1) && (player.y-1)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x-1) && (player.y-1)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x+1) && (player.y-1)==robot[b].y && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x+1) && (player.y-1)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x+1) && (player.y-1)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
					
					}                	
					break;
				}
			case 'x':
				{
					for(b=0;b<n_enemies;b++)
					{
						if((((player.x+1)==robot[b].x) && ((player.y)==robot[b].y)) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==robot[b].x && (player.y)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==robot[b].x && (player.y)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x-1) && (player.y)==robot[b].y && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x-1) && (player.y)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x-1) && (player.y)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x+1) && (player.y)==robot[b].y && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x+1) && (player.y)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x+1) && (player.y)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
					
					}   
					break;
				}
				case 'c':
					{
						for(b=0;b<n_enemies;b++)
					{
						if((((player.x+1)==robot[b].x) && ((player.y+1)==robot[b].y && robot[b].alive==1)))
						{
							test_loc=1;
						}
						if((player.x+1)==robot[b].x && (player.y+1)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==robot[b].x && (player.y+1)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x-1) && (player.y+1)==robot[b].y && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x-1) && (player.y+1)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x-1) && (player.y+1)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x+1) && (player.y+1)==robot[b].y && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x+1) && (player.y+1)==(robot[b].y+1) && robot[b].alive==1)
						{
							test_loc=1;
						}
						if((player.x+1)==(robot[b].x+1) && (player.y+1)==(robot[b].y-1) && robot[b].alive==1)
						{
							test_loc=1;
						}
					
					}   
					break;
					}
	}
	return test_loc;
}

void move_enemies()
{
    int a;
    {
        enable_mv=0;
        for(a=0;a<(n_enemies);a++)
        {
            if(robot[a].alive==1)
            {
                if(player.x>robot[a].x)
                    robot[a].x++;
                else if(player.x<robot[a].x)
                    robot[a].x--;

                if(player.y>robot[a].y)
                    robot[a].y++;
                else if(player.y<robot[a].y)
                    robot[a].y--;
            }                  
        }
	}
}

void print_map()
{
	int i,j,n;
	
	for(i=0;i<MAXLIN;i++)
	{
		
		for(j=0;j<MAXCOL;j++)
		{
			for(n=0;n<n_enemies;n++)
			{
				
				if(i==player.x && j==player.y)
	            {
	                map[i][j]='@';
	                break;                
	            }
	            else if(i==robot[n].x && j==robot[n].y && robot[n].alive==0)
	        	{
					map[i][j]='*';
					break;
				}
	            else if(i==robot[n].x && j==robot[n].y && robot[n].alive==1)
	            {
	                map[i][j]='+';
	                break; 
	        	}
	        	else
	        		map[i][j]=' ';
        	}
		}
	
	}
	//system("cls");
	printf("\e[H\e[2J");
	printf("+-----------------------------------------------------------+ Directions:\n");
	for(i=0;i<MAXLIN;i++)
	{
		printf("|");
		for(j=0;j<MAXCOL;j++)
		{
			printf("%c",map[i][j]);
		}
		printf("|");
		extern_words(i);
		printf("\n");
	}	
	printf("+-----------------------------------------------------------+  ");
	usleep(300000);
}

int test_enemies()
{
	int f, temp_life=0;
	for(f=0;f<n_enemies;f++)
    {
        int teste;    
        for(teste=0;teste<n_enemies;teste++)
        {
            if(robot[f].x==robot[teste].x && robot[f].y==robot[teste].y && f!=teste && robot[f].alive==1)
            {
                robot[f].alive=0;
                robot[teste].alive=0;
            }
        }
        
    }
    for(f=0;f<n_enemies;f++)
    {
    	temp_life+=robot[f].alive;
	}
            return temp_life;
}


void extern_words(int a)
{
		if(a==1)
			printf(" q w e ");
		if(a==2)
			printf("  \\|/ ");
		if(a==3)
			printf(" a- -d ");
		if(a==4)
			printf("  /|\\ ");
		if(a==5)
			printf(" z x c ");
		if(a==7)
			printf(" Commands:");
		if(a==9)
			printf(" k: auto-kill");
		if(a==10)
			printf(" t: teleport");
		if(a==11)
			printf(" Esc: quit");
		if(a==12)
			printf(" n: new map");
		if(a==14)
			printf(" Legend: ");
		if(a==16)
			printf(" +: robot");
		if(a==17)
			printf(" *: junk heap");
		if(a==18)
			printf(" @: you ");
		if(a==20)
			printf(" Score: %d", score);
}

void new_map_enemies()
{
	int f;
	for(f=0;f<n_enemies;f++)
        {
            robot[f].x=rand()%MAXLIN;
            robot[f].y=rand()%MAXCOL;
            robot[f].alive=1;
        }
}


int main()
{	
    //initscr(); 	
	n_enemies=0;
	srand(time(NULL));
	player.x=rand()%MAXLIN;
    player.y=rand()%MAXCOL; /*inicializa o player numa posição qualquer*/
    int temp_life,lvl=0;
    do{
    	int f;
    	if(kill==1)
    	{
    		kill=0;
    		n_enemies=10;
    		lvl=1;
    	}
		else
			n_enemies+=10;
			lvl++;
    	new_map_enemies();
        print_map();
        temp_life=1;
        do{
        	
			move_human();
			if(enable_mv==1)
			{
				move_enemies();
				print_map();
				temp_life=test_enemies();
				enable_mv=0;
			}
			        	        	
		}while(temp_life!=0 && master_quit==0 && kill==0);
		for(f=0;f<n_enemies;f++)
			robot[f].alive=0;		
	}while(master_quit==0);
	printf("\nLevel: %d", lvl);
	__fpurge(stdin);
	getchar();
	return EXIT_SUCCESS;
}

/*+-----------------------------------------------------------+ Directions:
|                                                           |
|                                                           | y k u
|                                                           |  \|/
|                                                           | h- -l
|                                                           |  /|\
|                                                           | b j n
|                                                          +|
|                +        +  +                 +        + +@| Commands:
|                                                           |
|        +                                                  | w:  wait for end
|                                                           | t:  teleport
|                                                           | q:  quit
|                                                           | ^L: redraw screen
|                                                           |
|                                                           | Legend:
|                                                           |
|                         +      +                          | +:  robot
|                                                           | *:  junk heap
|                                                           | @:  you
|                                                           |
|                                                           | Score: 0
|                                                           |
+-----------------------------------------------------------+*/

