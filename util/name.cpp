#include "name.h"
#include "func_util.h"

void render_a(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    long int location;

    //16x20
    for (int j = 0; j < 4; j++) {
        if (j + y >= vinfo.yres)
            break;
        for (int i = 4; i < 12; i++) {
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (int j = 8; j < 12; j++) {
        if (j + y >= vinfo.yres)
            break;
        for (int i = 4; i < 12; i++) {
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (int j = 4; j < 20; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 0; i < 4; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (int j = 4; j < 20; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 12; i < 16; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
}
void render_b(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	    long int location;
    int xx, yy;   
    for (yy = y; yy < y+4; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+16; xx++) {
            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
	    
        }
    }
    for (yy = y+4; yy < y+8; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {
            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
	for (xx = x+16; xx < x+20; xx++) {
        if (yy >= vinfo.yres)
            break;
            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }	
    for (yy = y+8; yy < y+12; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+16; xx++) {
            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (yy = y+12; yy < y+16; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {   
            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
	for (xx = x+16; xx < x+20; xx++) {
        if (yy >= vinfo.yres)
            break;
        location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
    for (yy = y+16; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+16; xx++) { 
            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }

}

void render_c(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    long int location;

    for (int j = 0; j < 4; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 4; i < 16; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (int j = 4; j < 16; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 0; i < 4; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (int j = 16; j < 20; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 4; i < 16; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
}

void render_d(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	    long int location;
    int xx,yy;    
    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {
	       location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (yy = y; yy < y+4; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+12; xx++) {
	       location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (yy = y+16; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+12; xx++) {
	       location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (yy = y+4; yy < y+16; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+12; xx < x+16; xx++) {
	       location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    

}
void render_e(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    long int location;

    for (int j = 0; j < 20; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 0; i < 4; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (int i = 4; i < 16; i++){
        for (int j = 0; j < 4; j++){
            if (j + y >= vinfo.yres)
                break;
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
        for (int j = 16; j < 20; j++){
            if (j + y >= vinfo.yres)
                break;
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (int j = 8; j < 12; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 4; i < 12; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
}
void render_f(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	long int location;
    int xx, yy;

    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);
        }
    }

    for (yy = y; yy < y+4; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+16; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }
    for (yy = y+8; yy < y+12; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);
        }
    }

}
void render_g(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    long int location;

    for (int j = 0; j < 4; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 4; i < 16; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (int j = 4; j < 16; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 0; i < 4; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (int j = 16; j < 20; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 4; i < 16; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (int j = 8; j < 16; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 12; i < 16; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (int j = 8; j < 12; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 8; i < 12; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
}

void render_h(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    long int location;
    int xx, yy;

    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+12; xx < x+16; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y+8; yy < y+12; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+4; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }
}

void render_i(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	long int location;
    int xx, yy;

    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

}
void render_j(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    long int location;

    for (int j = 0; j < 16; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 12; i < 16; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (int j = 16; j < 20; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 4; i < 12; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (int j = 12; j < 16; j++){
        if (j + y >= vinfo.yres)
            break;
        for (int i = 0; i < 4; i++){
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+j+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
}
void render_k(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	    long int location;
    int xx,yy;  
    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        } 
    }
    for (yy = y; yy < y+4; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+12; xx < x+16; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }
    for (yy = y+4; yy < y+8; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+8; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y+8; yy < y+12; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+8; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y+12; yy < y+16; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+8; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }
    for (yy = y+16; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+12; xx < x+16; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

 

}
void render_l(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	long int location;
    int xx, yy;

    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y+16; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);
    
        }
    }

}

void render_m(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	    long int location;
    int xx,yy;    
    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {
            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
	for (xx = x+17; xx < x+20; xx++) {
        if (yy >= vinfo.yres)
            break;
            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (yy = y+4; yy < y+8; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+4; xx < x+8; xx++) {
            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
	for (xx = x+12; xx < x+16; xx++) {
        if (yy >= vinfo.yres)
            break;
            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }
    for (yy = y+8; yy < y+12; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+8; xx < x+12; xx++) {
            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (yy+vinfo.yoffset) * finfo.line_length;
            pixelColor(rgb,fbp,location);
        }
    }

}
void render_n(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	long int location;
    int xx, yy;

    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+12; xx < x+16; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y+8; yy < y+12; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+4; xx < x+8; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }
    for (yy = y+12; yy < y+16; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+8; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }


}
void render_o(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    long int location;
    int i, j;

    //Mengikuti ukuran karakter 16x20 pixel

    for (i = 4; i < 12; i++) {
        for (j = 0; j < 4; j++) {
            if ((j + y) >= vinfo.yres)
                break;
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
        for (j = 16; j < 20; j++) {
            if ((j + y) >= vinfo.yres)
                break;
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
    for (j=4; j<16; j++) {
        if ((j + y) >= vinfo.yres)
                break;
        for (i = 0; i < 4; i++) {
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
        for (i = 12; i < 16; i++) {
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
}
void render_p(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	    long int location;
    int xx, yy;

    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y; yy < y+4; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y+4; yy < y+8; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+12; xx < x+16; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }
    for (yy = y+8; yy < y+12; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

}
void render_r(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	long int location;
    int xx, yy;

    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y; yy < y+4; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y+4; yy < y+8; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+12; xx < x+16; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }
    for (yy = y+8; yy < y+12; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }
    for (yy = y+12; yy < y+16; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+8; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }
    for (yy = y+16; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+12; xx < x+16; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }


}
void render_s(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    long int location;
    int i, j;

    //Mengikuti ukuran karakter 16x20 pixel

    for (j = 0; j < 4; j++) {
        if ((j + y) >= vinfo.yres)
            break;
        for (i = 4; i < 16; i++) {
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
    for (j=4; j<8; j++) {
        if ((j + y) >= vinfo.yres)
            break;
        for (i = 0; i < 4; i++) {
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
    for (j=8; j<12; j++) {
        if ((j + y) >= vinfo.yres)
            break;
        for (i = 4; i < 12; i++) {
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
    for (j=12; j<16; j++) {
        if ((j + y) >= vinfo.yres)
            break;
        for (i = 12; i < 16; i++) {
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
    for (j=16; j<20; j++) {
        if ((j + y) >= vinfo.yres)
            break;
        for (i = 0; i < 12; i++) {
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
}
void render_t(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    long int location;
    int i, j;

    //Mengikuti ukuran karakter 16x20 pixel
    for (j = 0; j < 4; j++) {
        if ((j + y) >= vinfo.yres)
            break;
        for (i = 0; i < 12; i++) {
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
    for (j=4; j<20; j++) {
        if ((j + y) >= vinfo.yres)
            break;
        for (i = 4; i < 8; i++) {
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
}
void render_u(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	long int location;
    int xx, yy;

    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+12; xx < x+16; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y+16; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+16; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

}
//draw V letter
void render_v(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo) {

    long int location;
    int xx, yy;

    for (yy = y; yy < y+16; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y; yy < y+16; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+12; xx < x+16; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y+12; yy < y+16; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+16; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }
    for (yy = y+16; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+4; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

}
void render_w(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    long int location;
    int i, j;

    //Mengikuti ukuran karakter 20x20 pixel

    for (j=0; j<16; j++) {
        for (i = 0; i < 4; i++) {
			if (j + y >= vinfo.yres)
		        break;
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
        for (i = 16; i < 20; i++) {
			if (j + y >= vinfo.yres)
		        break;
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
    for (j = 8; j < 16; j++) {
        for (i = 8; i < 12; i++) {
			if (j + y >= vinfo.yres)
		        break;
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
    for (j = 16; j < 20; j++) {
        for (i = 4; i < 8; i++) {
			if (j + y >= vinfo.yres)
		        break;
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
    for (j = 16; j < 20; j++) {
        for (i = 12; i < 16; i++) {
			if (j + y >= vinfo.yres)
		        break;
            location = (x+i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                               (y+j+vinfo.yoffset) * finfo.line_length;
        pixelColor(rgb,fbp,location);
        }
    }
}
void render_y(int x, int y, struct RGB rgb, char *fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	long int location;
    int xx, yy;

    for (yy = y; yy < y+12; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+4; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y; yy < y+12; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+8; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }

    for (yy = y+8; yy < y+12; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x; xx < x+12; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);

        }
    }
    for (yy = y+8; yy < y+20; yy++){
        if (yy >= vinfo.yres)
            break;
        for (xx = x+4; xx < x+8; xx++) {

            location = (xx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (yy+vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,fbp,location);
        }
    }
}