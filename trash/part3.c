#include "cub3d.h"
#include <math.h>

#define WIDTH 1024
#define HEIGHT 512
#define MAP_WIDTH  8
#define MAP_HEIGHT 8
#define TILE_SIZE  64
#define TILE_SIZE_TEXTURE  32
#define BORDER_COLOR 0x000000
#define DARK_GREY    0x404040
#define PLAYER_COLOR 0xFF0000
#define PLAYER_SIZE  10
#define PI  3.14159265359
#define P2  (PI / 2)
#define P3  (3 * P2)
#define NUM_RAYS 64
#define FOV (PI / 3)
#define SPEED 30  // Base movement speed
#define SENSITIVITY 3  // Rotation sensitivity


int All_Textures[]=               //all 32x32 textures
{
 //Checkerboard
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
 //Brick
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 //Window
 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,    
       
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 

 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,   
       
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
 //Door
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,   
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,     

 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,    
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,    
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,   
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,  

 0,0,0,0,0,0,0,0, 0,0,0,0,0,1,0,1, 1,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,1,1,1,1,0,1, 1,0,1,1,1,1,0,0, 0,0,0,0,0,0,0,0,   
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 
 
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,     
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,   
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,         
};


// int mapW[] = {
//     1,1,1,1,1,1,1,1,
//     1,0,1,0,0,0,1,1,
//     1,0,1,0,0,0,0,1,
//     1,0,1,0,0,0,0,1,
//     1,0,0,0,0,0,0,1,
//     1,0,0,0,0,1,0,1,
//     1,0,0,0,0,0,0,1,
//     1,1,1,1,1,1,1,1,
// };

int mapW[]=          //walls
{
 1,1,1,1,1,3,1,1,
 1,0,0,1,0,0,0,1,
 1,0,0,4,0,2,0,1,
 1,1,4,1,0,0,0,1,
 2,0,0,0,0,0,0,1,
 2,0,0,0,0,1,0,1,
 2,0,0,0,0,0,0,1,
 1,1,3,1,3,1,3,1,	
};

int mapF[]=          //floors
{
 1,2,1,2,1,2,1,2,
 2,1,2,1,2,1,2,1,
 1,2,1,2,1,2,1,2,
 2,1,2,1,2,1,2,1,
 1,2,1,2,1,2,1,2,
 2,1,2,1,2,1,2,1,
 1,2,1,2,1,2,1,2,
 2,1,2,1,2,1,2,1,
};

// int mapF[]=          //floors
// {
//  0,0,0,0,0,0,0,0,
//  0,0,0,0,1,1,0,0,
//  0,0,0,0,2,0,0,0,
//  0,0,0,0,0,0,0,0,
//  0,0,2,0,0,0,0,0,
//  0,0,0,0,0,0,0,0,
//  0,1,1,1,1,0,0,0,
//  0,0,0,0,0,0,0,0,	
// };

int mapC[]=          //ceiling
{
 0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,1,0,
 0,1,3,1,0,0,0,0,
 0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,	
};




int close_window(t_var *data)
{
    if (data->mlx && data->win)
        mlx_destroy_window(data->mlx, data->win);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    exit(0);
    return 0;
}

void put_pixel(char *addr, int x, int y, int color, int bpp, int line_len)
{
    int offset = y * line_len + x * (bpp / 8);
    *(unsigned int *)(addr + offset) = color;
}

void draw_tile(char *addr, int x, int y, int tile_color, int bpp, int line_len)
{
    for (int i = 0; i < TILE_SIZE; i++)
    {
        for (int j = 0; j < TILE_SIZE; j++)
        {
            int draw_x = x * TILE_SIZE + j;
            int draw_y = y * TILE_SIZE + i;
            int color = (i == 0 || i == TILE_SIZE - 1 || j == 0 || j == TILE_SIZE - 1) ? BORDER_COLOR : tile_color;
            put_pixel(addr, draw_x, draw_y, color, bpp, line_len);
        }
    }
}

void draw_player(char *addr, t_var *data, int bpp, int line_len)
{
    for (int y = data->py; y < data->py + PLAYER_SIZE; y++)
        for (int x = data->px; x < data->px + PLAYER_SIZE; x++)
            put_pixel(addr, x, y, PLAYER_COLOR, bpp, line_len);
}

void draw_player_direction(char *addr, t_var *data, int bpp, int line_len)
{
    int line_length = 30;
    int thickness = 3; // Line thickness
    int start_x = data->px + PLAYER_SIZE / 2;
    int start_y = data->py + PLAYER_SIZE / 2;
    int end_x = start_x + cos(data->pa) * line_length;
    int end_y = start_y + sin(data->pa) * line_length;

    int dx = end_x - start_x;
    int dy = end_y - start_y;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;
    float x = start_x;
    float y = start_y;

    for (int i = 0; i <= steps; i++) {
        for (int t = -thickness / 2; t < thickness / 2; t++) {
            put_pixel(addr, (int)(x + t), (int)y, 0x00FF00, bpp, line_len); // Green line
        }
        x += x_inc;
        y += y_inc;
    }
}


void cast_horizontal_ray(t_var *data, float ra, float *hx, float *hy, float *disH)
{
	int dof = 0;
	float ry, rx, yo, xo, aTan = -1 / tan(ra);

	*disH = 1e30;
	*hx = data->px;
	*hy = data->py;

	if (ra > PI) {
		ry = (((int)data->py >> 6) << 6) - 0.0001;
		rx = (data->py - ry) * aTan + data->px;
		yo = -64;
		xo = -yo * aTan;
	} else if (ra < PI) {
		ry = (((int)data->py >> 6) << 6) + 64;
		rx = (data->py - ry) * aTan + data->px;
		yo = 64;
		xo = -yo * aTan;
	} else return;

	while (dof < 8) {
		int mx = (int)(rx) >> 6;
		int my = (int)(ry) >> 6;
		int mp = my * MAP_WIDTH + mx;
		if (mp >= 0 && mp < MAP_WIDTH * MAP_HEIGHT && mapW[mp] >= 1) {
			*hx = rx;
			*hy = ry;
			*disH = sqrtf((*hx - data->px) * (*hx - data->px) + (*hy - data->py) * (*hy - data->py));
			break;
		}
		rx += xo;
		ry += yo;
		dof++;
	}
}
void cast_vertical_ray(t_var *data, float ra, float *vx, float *vy, float *disV)
{
	int dof = 0;
	float rx, ry, xo, yo, nTan = -tan(ra);

	*disV = 1e30;
	*vx = data->px;
	*vy = data->py;

	if (ra > P2 && ra < P3) {
		rx = (((int)data->px >> 6) << 6) - 0.0001;
		ry = (data->px - rx) * nTan + data->py;
		xo = -64;
		yo = -xo * nTan;
	} else if (ra < P2 || ra > P3) {
		rx = (((int)data->px >> 6) << 6) + 64;
		ry = (data->px - rx) * nTan + data->py;
		xo = 64;
		yo = -xo * nTan;
	} else return;

	while (dof < 8) {
		int mx = (int)(rx) >> 6;
		int my = (int)(ry) >> 6;
		int mp = my * MAP_WIDTH + mx;
		if (mp >= 0 && mp < MAP_WIDTH * MAP_HEIGHT && mapW[mp] >= 1) {
			*vx = rx;
			*vy = ry;
			*disV = sqrtf((*vx - data->px) * (*vx - data->px) + (*vy - data->py) * (*vy - data->py));
			break;
		}
		rx += xo;
		ry += yo;
		dof++;
	}
}
void draw_single_ray(t_var *data, char *addr, int bpp, int line_len, float x1, float y1, float x2, float y2, int color)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	int steps = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy);

	if (steps == 0) return;

	float x_inc = dx / steps;
	float y_inc = dy / steps;
	for (int i = 0; i <= steps; i++) {
		put_pixel(addr, (int)x1, (int)y1, color, bpp, line_len);
		x1 += x_inc;
		y1 += y_inc;
	}
}

int get_texture_color(int tex_num, int tex_x, int tex_y) {
    // Ensure tex_x and tex_y are within bounds
    if (tex_x < 0 || tex_x >= TILE_SIZE_TEXTURE || tex_y < 0 || tex_y >= TILE_SIZE_TEXTURE) {
        return 0x000000;  // Default to black if out-of-bounds
    }

    // Correctly index the texture data
    int tex_value = All_Textures[tex_num * TILE_SIZE_TEXTURE * TILE_SIZE_TEXTURE + tex_y * TILE_SIZE_TEXTURE + tex_x];

    // Map texture number to color
    switch (tex_num) {
        case 0: // Texture 1
            return (tex_value == 0) ? 0xFF0000 : 0x000000;  // Red for tex_value 0, else black

        case 1: // Texture 2
            return (tex_value == 0) ? 0xFFFF00 : 0x000000;  // Yellow for tex_value 0, else black

        case 2: // Texture 3
            return (tex_value == 0) ? 0x00FF00 : 0x000000;  // Green for tex_value 0, else black

        case 3: // Texture 4
            return (tex_value == 0) ? 0x0000FF : 0x000000;  // Blue for tex_value 0, else black

        default:
            return 0x000000;  // Default to black if tex_num is invalid
    }
}

void calculate_wall_projection(t_var *data, float dist, int r, float *lineH, float *lineOffset) {
    int view_start = WIDTH - 512;
    
    // Distance correction for vertical line height
    float corrected_dist = dist * cos(data->pa - (data->pa - FOV / 2 + r * (FOV / NUM_RAYS)));
    
    // Calculate the height of the wall based on the distance
    *lineH = (TILE_SIZE * 320) / corrected_dist;
    if (*lineH > HEIGHT) *lineH = HEIGHT;
    *lineOffset = (HEIGHT - *lineH) / 2;
}

void get_wall_texture_info(float hitX, float hitY, int side, int *tex_num, int *texX) {
    // Select the texture based on the map value at the current position
    int map_x = (int)(hitX / TILE_SIZE);
    int map_y = (int)(hitY / TILE_SIZE);
    int map_value = mapW[map_y * MAP_WIDTH + map_x];

    // Map map_value to corresponding texture number
    if (map_value == 1) {
        *tex_num = 0;
    } else if (map_value == 2) {
        *tex_num = 1;
    } else if (map_value == 3) {
        *tex_num = 2;
    } else if (map_value == 4) {
        *tex_num = 3;
    }

    // Calculate texture X based on hit position within the block
    float wallX;
    if (side == 0) { // Vertical hit (east/west wall)
        wallX = hitY - (int)(hitY / TILE_SIZE) * TILE_SIZE;
    } else { // Horizontal hit (north/south wall)
        wallX = hitX - (int)(hitX / TILE_SIZE) * TILE_SIZE;
    }
    
    // Scale world position (0-64) to texture X (0-32)
    *texX = (int)(wallX * (TILE_SIZE_TEXTURE / (float)TILE_SIZE));
    *texX %= TILE_SIZE_TEXTURE;
}

void adjust_texture_orientation(int side, float hitX, float hitY, t_var *data, int *texX) {
    if (side == 0) { // Vertical walls (east/west)
        // Flip texture for west walls to maintain consistent orientation
        if (hitX < data->px) {
            *texX = TILE_SIZE_TEXTURE - *texX - 1;
        }
    } else { // Horizontal walls (north/south)
        // Flip texture for south walls to maintain consistent orientation
        if (hitY > data->py) {
            *texX = TILE_SIZE_TEXTURE - *texX - 1;
        }
    }
}

void get_floor_texture_info(float floorX, float floorY, int *tex_num) {
    // Get the grid coordinates (tile grid, not world-space)
    int map_x = (int)(floorX / TILE_SIZE); // Divide by TILE_SIZE to convert to grid position
    int map_y = (int)(floorY / TILE_SIZE); // Same for Y coordinate

    // Ensure we're within map bounds (just in case)
    if (map_x < 0) map_x = 0;
    if (map_y < 0) map_y = 0;
    if (map_x >= MAP_WIDTH) map_x = MAP_WIDTH - 1;
    if (map_y >= MAP_HEIGHT) map_y = MAP_HEIGHT - 1;

    // Checkerboard pattern: alternate textures based on tile position
    if ((map_x + map_y) % 2 == 0) {
        *tex_num = 0;  // Use texture 0 for even grid tiles
    } else {
        *tex_num = 1;  // Use texture 1 for odd grid tiles
    }
}


void draw_vertical_slice(t_var *data, char *addr, int bpp, int line_len, int startX, float lineH, 
    float lineOffset, int tex_num, int texX, float dist, int r) {
    float ty = 0;
    float ty_step = (float)TILE_SIZE_TEXTURE / lineH;

    int ceiling_color = 0x333366;

    for (int y = 0; y < HEIGHT; y++) {
        int color;
        if (y < lineOffset) {
            color = ceiling_color;
        }
        else if (y > lineOffset + lineH) {
            // Calculate floor distance
            float ray_angle = data->pa - (FOV / 2) + (FOV * r / NUM_RAYS);
            float floor_dist = (HEIGHT / (2.0f * y - HEIGHT)) / cos(ray_angle - data->pa);

            // Calculate exact floor position
            float floorX = data->px + floor_dist * cos(ray_angle);
            float floorY = data->py + floor_dist * sin(ray_angle);

            // Get floor texture info based on map grid
            int floor_tex_num;
            get_floor_texture_info(floorX, floorY, &floor_tex_num);

            // Calculate texture coordinates within the current tile
            float tile_relative_x = floorX - (int)floorX;
            float tile_relative_y = floorY - (int)floorY;
            int texX_floor = (int)(tile_relative_x * TILE_SIZE_TEXTURE);
            int texY_floor = (int)(tile_relative_y * TILE_SIZE_TEXTURE);

            // Sample texture
            int texColor = get_texture_color(floor_tex_num, texX_floor, texY_floor);
            color = texColor;
        }
        else {
            int texY = (int)ty % TILE_SIZE_TEXTURE;
            int texColor = get_texture_color(tex_num, texX, texY);
            color = texColor;
            ty += ty_step;
        }

        for (int x = 0; x < (512 / NUM_RAYS); x++)
            put_pixel(addr, startX + x, y, color, bpp, line_len);
    }
}

void draw_3d_view(t_var *data, char *addr, int bpp, int line_len, float dist, int r, float hitX, float hitY, int side) {
    int view_start = WIDTH - 512;
    int startX = view_start + r * (512 / NUM_RAYS);
    
    // Calculate wall projection
    float lineH, lineOffset;
    calculate_wall_projection(data, dist, r, &lineH, &lineOffset);
    
    // Get texture information
    int tex_num, texX;
    get_wall_texture_info(hitX, hitY, side, &tex_num, &texX);

    // Adjust texture orientation
    adjust_texture_orientation(side, hitX, hitY, data, &texX);
    
    // Draw the vertical slice
    draw_vertical_slice(data, addr, bpp, line_len, startX, lineH, lineOffset, tex_num, texX, dist, r);
}

void draw_rays(t_var *data, char *addr, int bpp, int line_len)
{
    float ra = data->pa - (FOV / 2);
    if (ra < 0) ra += 2 * PI;
    if (ra > 2 * PI) ra -= 2 * PI;

    for (int r = 0; r < NUM_RAYS; r++) {
        float hx, hy, disH, vx, vy, disV;
        cast_horizontal_ray(data, ra, &hx, &hy, &disH);
        cast_vertical_ray(data, ra, &vx, &vy, &disV);

        // Choose the closest hit
        float rx = disV < disH ? vx : hx;
        float ry = disV < disH ? vy : hy;
        float dist = disV < disH ? disV : disH;

        // Determine if the hit is on a vertical or horizontal wall (side = 0 for vertical, side = 1 for horizontal)
        int side = (disV < disH) ? 0 : 1;

        // Draw the ray for debugging or visualization
        draw_single_ray(data, addr, bpp, line_len,
            data->px + PLAYER_SIZE / 2,
            data->py + PLAYER_SIZE / 2,
            rx, ry, 0x00FFFF); // Cyan ray

        // Call draw_3d_view with hitX, hitY, and side
        draw_3d_view(data, addr, bpp, line_len, dist, r, rx, ry, side);

        ra += FOV / NUM_RAYS;
        if (ra < 0) ra += 2 * PI;
        if (ra > 2 * PI) ra -= 2 * PI;
    }
}


// Handle key press event
int handle_keypress(int keysym, t_var *data)
{
    if (keysym == XK_Escape)
    {
        close_window(data);
    }
    else if (keysym == XK_a)
        data->move_a = 1;
    else if (keysym == XK_d)
        data->move_d = 1;
    else if (keysym == XK_w)
        data->move_w = 1;
    else if (keysym == XK_s)
        data->move_s = 1;
    else if (keysym == XK_e) // Handle 'E' key press for opening door
    {
        // Check if there's a door in front of the player
        int player_tile_x = (int)(data->px / TILE_SIZE);  // X position in map
        int player_tile_y = (int)(data->py / TILE_SIZE);  // Y position in map

        // Calculate the direction the player is facing
        float dirX = cos(data->pa); // Direction in X
        float dirY = sin(data->pa); // Direction in Y

        // Check if the tile in front of the player is a door (tile 4)
        int door_x = (int)(data->px + dirX * TILE_SIZE) / TILE_SIZE;
        int door_y = (int)(data->py + dirY * TILE_SIZE) / TILE_SIZE;

        // If the tile in front is a door, change it to empty space
        if (mapW[door_y * MAP_WIDTH + door_x] == 4)
        {
            mapW[door_y * MAP_WIDTH + door_x] = 0; // Open the door (change to empty space)
            printf("Door opened!\n"); // Optionally print a message
        }
    }

    return 0;
}

// Handle key release event
int handle_keyrelease(int keysym, t_var *data)
{
    if (keysym == XK_a)
        data->move_a = 0;
    else if (keysym == XK_d)
        data->move_d = 0;
    else if (keysym == XK_w)
        data->move_w = 0;
    else if (keysym == XK_s)
        data->move_s = 0;

    return 0;
}

double get_delta_time(t_var *data)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    // Calculate the difference in seconds and microseconds
    double delta_time = (current_time.tv_sec - data->last_time.tv_sec) +
                        (current_time.tv_usec - data->last_time.tv_usec) / 1000000.0;

    // Update the last_time to the current time
    data->last_time = current_time;

    return delta_time;
}

int is_wall(float x, float y)
{
    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);
    if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
        return 1;
    return mapW[map_y * MAP_WIDTH + map_x] != 0;
}

void update_movement(t_var *data)
{
    double fps = get_delta_time(data);  // Get delta time (fps) between frames
    // Use delta_time (fps) to adjust movement speed
    float move_speed = SPEED * fps;
    float next_x, next_y;
    float offset = 10;

    if (data->move_w)
    {
        next_x = data->px + data->pdx * move_speed;
        next_y = data->py + data->pdy * move_speed;
        if (!is_wall(next_x + offset, data->py) && !is_wall(next_x - offset, data->py))
            data->px = next_x;
        if (!is_wall(data->px, next_y + offset) && !is_wall(data->px, next_y - offset))
            data->py = next_y;
    }
    if (data->move_s)
    {
        next_x = data->px - data->pdx * move_speed;
        next_y = data->py - data->pdy * move_speed;
        if (!is_wall(next_x + offset, data->py) && !is_wall(next_x - offset, data->py))
            data->px = next_x;
        if (!is_wall(data->px, next_y + offset) && !is_wall(data->px, next_y - offset))
            data->py = next_y;
    }
    if (data->move_a)
    {
        data->pa -= SENSITIVITY * fps;
        if (data->pa < 0) data->pa += 2 * PI;
        data->pdx = cos(data->pa) * 5;
        data->pdy = sin(data->pa) * 5;
    }
    if (data->move_d)
    {
        data->pa += SENSITIVITY * fps;
        if (data->pa > 2 * PI) data->pa -= 2 * PI;
        data->pdx = cos(data->pa) * 5;
        data->pdy = sin(data->pa) * 5;
    }
}

void render_scene(t_var *data)
{
    void *img;
    char *addr;
    int bpp, line_len, endian;

    img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);

    // Fill background
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(addr, x, y, DARK_GREY, bpp, line_len);

    // Draw map
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int tile = mapW[y * MAP_WIDTH + x];
            int color;

            // Assign color based on tile value
            if (tile == 1) {
                color = 0xFFFFFF;  // White for walls (1)
            } else if (tile == 2) {
                color = 0x006400;  // Dark Green for tile (2)
            } else if (tile == 3) {
                color = 0x00008B;  // Dark Blue for tile (3)
            } else if (tile == 4) {
                color = 0x3E2B1D;  // brown for tile (4)
            } else {
                color = DARK_GREY;  // Default color for other tiles
            }

            // Draw the tile with the selected color
            draw_tile(addr, x, y, color, bpp, line_len);
        }
    }


    // Draw player
    draw_player(addr, data, bpp, line_len);

    // Draw player direction
    draw_player_direction(addr, data, bpp, line_len);

	//raycast
	draw_rays(data, addr, bpp, line_len);

    //movement
    update_movement(data);

    mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
    mlx_destroy_image(data->mlx, img);
}

// Main loop function
int loop_hook(t_var *data)
{
    render_scene(data);  // This will be called continuously
    return 0;
}

int create_visual(t_cub *cub3)
{
    t_var data = {0};

    data.px = 270;
    data.py = 250;
    data.pa = P2;
    data.pdx = cos(data.pa) * 5;
    data.pdy = sin(data.pa) * 5;

    data.mlx = mlx_init();
    if (!data.mlx)
        return 1;

    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "cub3d");
    if (!data.win)
        return 1;

    mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &close_window, &data);
    mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);
    mlx_hook(data.win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
    mlx_loop_hook(data.mlx, loop_hook, &data);  // This starts the render loop
    mlx_loop(data.mlx);  // This is the main loop
    return 0;
}
