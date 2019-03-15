#include "func_util.h"
#include <cmath>
#include <algorithm>

using namespace std;

// **** BRESENHAM ****

// Draws a line between two points with Bresenham algorithm
void bresenham(int x0, int y0, int x1, int y1, struct RGB rgb, char * framebuffer, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    // Swaps the points if first point is on the right of second point
    if (x0 > x1){
        int x_temp;
        int y_temp;

        x_temp = x0;
        y_temp = y0;
        x0 = x1;
        y0 = y1;
        x1 = x_temp;
        y1 = y_temp;
    }

    // Checks if the points make vertical line
    if ((x1 - x0) == 0){
        for (int y = y0; y <= y1; y++){
            if ((x1 < 0)||(y < 0)||(x1 > 1024)||(y > 768)) {
                break;
            } else {
            long int mem_location = (x1 + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + vinfo.yoffset) * finfo.line_length;

            pixelColor(rgb,framebuffer,mem_location);}
        }
    } else {
        float gradien = (y1 - y0)/(x1 - x0);
        if ((abs(gradien) >= 0) && (abs(gradien) <= 1)){
        // Line made are close to x-axis
            int y = y0;
            int eps = 0;

            if (y1 >= y0){
                int dx = x1 - x0;
                int dy = y1 - y0;
                for (int x = x0; x <= x1; x++){
                    if ((x < 0)||(y < 0)||(x > 1024)||(y > 768)) {
                        break;
                    }
                    long int mem_location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + vinfo.yoffset) * finfo.line_length;

                    pixelColor(rgb,framebuffer,mem_location);

                    eps += dy;
                    if ((eps << 1) >= dx){
                        y++;
                        eps -= dx;
                    }
                }
            } else {    //y1 < y0
                int dx = x1 - x0;
                int dy = y0 - y1;
                for (int x = x0; x <= x1; x++){
                    if ((x < 0)||(y < 0)||(x > 1024)||(y > 768)) {
                        break;
                    }
                    long int mem_location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + vinfo.yoffset) * finfo.line_length;

                    pixelColor(rgb,framebuffer,mem_location);

                    eps += dy;
                    if ((eps << 1) >= dx){
                        y--;
                        eps -= dx;
                    }
                }
            }
        } else {
        // Line made are close to y-axis
            int x = x0;
            int eps = 0;

            if (y1 >= y0){
                int dx = x1 - x0;
                int dy = y1 - y0;

                for (int y = y0; y <= y1; y++){
                    if ((x < 0)||(y < 0)||(x > 1024)||(y > 768)) {
                        break;
                    }   
                    long int mem_location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + vinfo.yoffset) * finfo.line_length;

                    pixelColor(rgb,framebuffer,mem_location);

                    eps += dx;
                    if ((eps << 1) >= dy){
                        x++;
                        eps -= dy;
                    }
                }
            } else {    //y1 < y0
                int dx = x1 - x0;
                int dy = y0 - y1;

                for (int y = y0; y >= y1; y--){
                    if ((x < 0)||(y < 0)||(x > 1024)||(y > 768)) {
                        break;
                    }
                    long int mem_location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + vinfo.yoffset) * finfo.line_length;

                    pixelColor(rgb,framebuffer,mem_location);

                    eps += dx;
                    if ((eps << 1) >= dy){
                        x++;
                        eps -= dy;
                    }
                }
            }
        }
    }
}
void bresenham(int x0, int y0, int x1, int y1, struct RGB rgb, int dash, int thickness, char * framebuffer, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	int counter = 0;
	bool draw = true;
    // Swaps the points if first point is on the right of second point
    if (x0 > x1){
        int x_temp;
        int y_temp;

        x_temp = x0;
        y_temp = y0;
        x0 = x1;
        y0 = y1;
        x1 = x_temp;
        y1 = y_temp;
    }

    // Checks if the points make vertical line
    if ((x1 - x0) == 0){
		int xmin = x1-thickness < 0? 0:x1-thickness;
		int xmax = x1+thickness > 1024? 1024:x1+thickness; 
		for (int i = xmin; i < xmax; i++){ 
		    for (int y = y0; y <= y1; y++){
                if ((i < 0)||(y < 0)||(i > 1024)||(y > 768)) {
                    break;
                }
				if(dash!=0){
					counter++;
				    long int mem_location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + vinfo.yoffset) * finfo.line_length;
		            if(draw){
		    			pixelColor(rgb,framebuffer,mem_location);
					}
					if(counter % dash == 0){
						draw = !draw;
					}
				}
				else {
					long int mem_location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + 	vinfo.yoffset) * finfo.line_length;
					pixelColor(rgb,framebuffer,mem_location);
				}
		    }
		}
    } else if((y1-y0)==0){
        int ymin = y1-thickness < 0? 0:x1-thickness;
		int ymax = y1+thickness > 768? 768:x1+thickness; 
		for (int i = ymin; i < ymax; i++){ 
		    for (int x = x0; x <= x1; x++){
                if ((x < 0)||(i < 0)||(x > 1024)||(i > 768)) {
                    break;
                }
				if(dash!=0){
					counter++;
				    long int mem_location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (i + vinfo.yoffset) * finfo.line_length;
		            if(draw){
		    			pixelColor(rgb,framebuffer,mem_location);
					}
					if(counter % dash == 0){
						draw = !draw;
					}
				}
				else {
					long int mem_location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (i + vinfo.yoffset) * finfo.line_length;
					pixelColor(rgb,framebuffer,mem_location);
				}
		    }
		}
    } else {
        float gradien = (y1 - y0)/(x1 - x0);
        if ((abs(gradien) >= 0) && (abs(gradien) <= 1)){
        // Line made are close to x-axis
            int y = y0;
            int eps = 0;

            if (y1 >= y0){
                int dx = x1 - x0;
                int dy = y1 - y0;
                for (int x = x0; x <= x1; x++){
					int xmin = x-thickness < 0? 0:x-thickness;
					int xmax = x+thickness > 1024? 1024:x+thickness;
					for (int i = xmin; i < xmax ; i++){
                        if ((i < 0)||(y < 0)||(i > 1024)||(y > 768)) {
                            break;
                        }
						if(dash!=0){
							counter++;
							long int mem_location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + vinfo.yoffset) * finfo.line_length;
					        if(draw){
								pixelColor(rgb,framebuffer,mem_location);
							}
							if(counter % dash == 0){
								draw = !draw;
							}
						}
						else {
							long int mem_location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + 	vinfo.yoffset) * finfo.line_length;
							pixelColor(rgb,framebuffer,mem_location);
						}
					}

                    eps += dy;
                    if ((eps << 1) >= dx){
                        y++;
                        eps -= dx;
                    }
                }
            } else {    //y1 < y0
                int dx = x1 - x0;
                int dy = y0 - y1;
                for (int x = x0; x <= x1; x++){
					int xmin = x-thickness < 0? 0:x-thickness;
					int xmax = x+thickness > 1024? 1024:x+thickness;
					for (int i = xmin; i < xmax ; i++){
                        if ((i < 0)||(y < 0)||(i > 1024)||(y > 768)) {
                            break;
                        }
						if(dash!=0){
							counter++;
							long int mem_location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + vinfo.yoffset) * finfo.line_length;
					        if(draw){
								pixelColor(rgb,framebuffer,mem_location);
							}
							if(counter % dash == 0){
								draw = !draw;
							}
						}
						else {
							long int mem_location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + 	vinfo.yoffset) * finfo.line_length;
							pixelColor(rgb,framebuffer,mem_location);
						}
					}
                    eps += dy;
                    if ((eps << 1) >= dx){
                        y--;
                        eps -= dx;
                    }
                }
            }
        } else {
        // Line made are close to y-axis
            int x = x0;
            int eps = 0;

            if (y1 >= y0){
                int dx = x1 - x0;
                int dy = y1 - y0;

                for (int y = y0; y <= y1; y++){
					int xmin = x-thickness < 0? 0:x-thickness;
					int xmax = x+thickness > 1024? 1024:x+thickness;
					for (int i = xmin; i < xmax ; i++){
                        if ((i < 0)||(y < 0)||(i > 1024)||(y > 768)) {
                            break;
                        }
						if(dash!=0){
							counter++;
							long int mem_location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + vinfo.yoffset) * finfo.line_length;
					        if(draw){
								pixelColor(rgb,framebuffer,mem_location);
							}
							if(counter % dash == 0){
								draw = !draw;
							}
						}
						else {
							long int mem_location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + 	vinfo.yoffset) * finfo.line_length;
							pixelColor(rgb,framebuffer,mem_location);
						}
					}
                    eps += dx;
                    if ((eps << 1) >= dy){
                        x++;
                        eps -= dy;
                    }
                }
            } else {    //y1 < y0
                int dx = x1 - x0;
                int dy = y0 - y1;
				
                for (int y = y0; y >= y1; y--){
					int xmin = x-thickness < 0? 0:x-thickness;
					int xmax = x+thickness > 1024? 1024:x+thickness;
					for (int i = xmin; i < xmax ; i++){
                        if ((i < 0)||(y < 0)||(i > 1024)||(y > 768)) {
                            break;
                        }
						if(dash!=0){
							counter++;
							long int mem_location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + vinfo.yoffset) * finfo.line_length;
					        if(draw){
								pixelColor(rgb,framebuffer,mem_location);
							}
							if(counter % dash == 0){
								draw = !draw;
							}
						}
						else {
							long int mem_location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + 	vinfo.yoffset) * finfo.line_length;
							pixelColor(rgb,framebuffer,mem_location);
						}
					}
                    eps += dx;
                    if ((eps << 1) >= dy){
                        x++;
                        eps -= dy;
                    }
                }
            }
        }
    }
}

// **** RASTER SCAN ****

// Checks if there is a colored pixel in 3 pixels on the top and 3 pixels on the bottom
char checkPixelAround(int x, int y, char * fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    long int mem_location;
    int max_x;

    char pixel_up = false;
    char pixel_down = false;

    for (int i = x-1; i < x + 2; i++){
        if (!(pixel_up)){
            mem_location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y - 1 + vinfo.yoffset) * finfo.line_length;
            if ((*(fbp + mem_location) || *(fbp + mem_location + 1) || *(fbp + mem_location + 2)) > 0x00){
                pixel_up = true;
            }
        }
        if (!(pixel_down)){
            mem_location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + 1 + vinfo.yoffset) * finfo.line_length;
            if ((*(fbp + mem_location) || *(fbp + mem_location + 1) || *(fbp + mem_location + 2)) > 0x00){
                pixel_down = true;
            }
        }
    }

    return (pixel_up && pixel_down);
}

// Fills the are within a polygon with color
void rasterScan(int x_min, int y_min, int x_max, int y_max, struct RGB rgb, char * fbp, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
	char fill_flag = 0;  // 0 = Don't fill, 1 = Fill
    long int mem_location;

    // Assumes x is not filled from the top or bottom of screen
    for (int j = y_min; j <= y_max; j++){
        for (int i = x_min; i <= x_max; i++){
            mem_location = (i + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (j + vinfo.yoffset) * finfo.line_length;

            if ((*(fbp + mem_location) || *(fbp + mem_location + 1) || *(fbp + mem_location + 2)) == 0x00){
                if (fill_flag){
                    pixelColor(rgb,fbp,mem_location);
                }
            } else {
                if (checkPixelAround(i, j, fbp, vinfo, finfo)){
                    if (fill_flag) {
                        pixelColor(rgb,fbp,mem_location);
                    }

                    fill_flag = !(fill_flag);
                }
            }
        }
    }
}

// **** OTHER ****

// Fills framebuffer with desired color
void pixelColor(struct RGB rgb, char *fbp, long int location){
    *(fbp + location) = rgb.b;         // blue
    *(fbp + location + 1) = rgb.g;     // green
    *(fbp + location + 2) = rgb.r;     // red
    *(fbp + location + 3) = 0;
}

// Clears the screen with the specified screen dimension
void clear_screen(unsigned int x_size, unsigned int y_size, char * framebuffer, struct fb_var_screeninfo vinfo, struct fb_fix_screeninfo finfo){
    long int mem_location;

    for (int y = 0; y < y_size; y++){
        for (int x = 0; x < x_size; x++){
            mem_location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + vinfo.yoffset) * finfo.line_length;

            *(framebuffer + mem_location) = 0;
            *(framebuffer + mem_location + 1) = 0;
            *(framebuffer + mem_location + 2) = 0;
            *(framebuffer + mem_location + 3) = 0;
        }
    }
}
