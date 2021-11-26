#include<stdint.h>
#include<math.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb-master/stb_image.h"
#include "stb-master/stb_image_resize.h"
#include "stb-master/stb_image_write.h"

#define NUM_CHANNELS 3
#define SIZE_DIFF 10
#define true 1
#define false 0

uint8_t get_batch_bin(int m,int batch_size,uint8_t* image,int x,int y,int sensitivity){
    int s = (x*batch_size+pow(batch_size,2)*m*y)*NUM_CHANNELS;
    int u = 0;
    int R_sum = 0;
    int G_sum = 0;
    int B_sum = 0;
    for(char i = 0;i<batch_size;i++){
        u = batch_size*m*i*NUM_CHANNELS;
        for(char j = 0;j<batch_size;j++){
            int pos = j*NUM_CHANNELS+u+s;
            R_sum+=image[pos];
            G_sum+=image[pos+1];
            B_sum+=image[pos+2];
        }
    }
    int del = pow(batch_size,2);
    R_sum/=del;
    G_sum/=del;
    B_sum/=del;
    int avg = (R_sum+G_sum+B_sum)/3;
    if(avg > 200) return true;
    return false;
}

// 1->path_in 2->nonogram_size 3->path_out 4->sensitivity
int main(int argc,char**argv){
    
    int width,height,bpp;
    char* path_in = argv[1];
    char* path_out = argv[3];
    /*Sensitivity used in interpolation
    *TODO should implement auto-sensitivity feature
    */
    int sensitivity = atoi(argv[4]);

    //Number of rows and columns used for interpolation
    int row_col_cnt = atoi(argv[2]);

    //code will only work if pic_size%batch_size==0
    int nonogram_width = row_col_cnt*SIZE_DIFF;
    int nonogram_height = row_col_cnt*SIZE_DIFF;;


    //counters for iterating over image
    int max = nonogram_height/row_col_cnt;


    uint8_t* image = stbi_load(path_in,&width,&height,&bpp,3);
    uint8_t* nonogram_ready = (uint8_t*)malloc(nonogram_width*nonogram_height*NUM_CHANNELS);
    //Resize
    if(stbir_resize_uint8(image,width,height,0,nonogram_ready,nonogram_width,nonogram_height,0,NUM_CHANNELS)==-1){
        return -1;
    }

    /*
    *This part of the code is for generating result image and populating it by extracting average colour of
    *batch which size is defined as row_col_cnt^2.
    */

    uint8_t* result = (uint8_t*)malloc(row_col_cnt*row_col_cnt*NUM_CHANNELS*sizeof(uint8_t));
    
    for(int i = 0;i<row_col_cnt;i++){
        for(int j = 0;j<row_col_cnt;j++){
            char should_colour = get_batch_bin(row_col_cnt,max,nonogram_ready,i,j,sensitivity);
            int pos = (j*row_col_cnt+i)*NUM_CHANNELS;
            if(should_colour){
                result[pos] = 255;
                result[pos+1] = 255;
                result[pos+2] = 255;
            }
            else{
                 result[pos] = 0;
                result[pos+1] = 0;
                result[pos+2] = 0;
            }
        }
    }
    //Save image
    if(stbi_write_png(path_out,row_col_cnt,row_col_cnt,NUM_CHANNELS,result,row_col_cnt*NUM_CHANNELS)==-1){
        return -1;
    }
    return 0;
}