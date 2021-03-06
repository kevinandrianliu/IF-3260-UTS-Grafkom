#include <cerrno>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>
#include <thread>
#include <cstring>
#include <ctime>
#include <mutex>
#include "util/func_util.h"
#include "objects.h"
#include "objects_util.h"
#include "file.h"

using namespace std;

char menu_bar_option_selection = -1;
char menu_bar_selection = 0;
int key_code = 0x00;
bool refresh_screen = false;
bool accessing_menu_bar = false;
bool out = false;

void userInput(int fd){
    ssize_t n;
    struct input_event ev;

    while(1){
        n = read(fd, &ev, sizeof ev);
        if (n == (ssize_t)-1){
            if (errno == EINTR){
                continue;
            } else {
                break;
            }
        } else if (n != sizeof ev){
            errno = EIO;
            break;
        }

        if (ev.type == EV_KEY && ev.value == 1){
            switch (ev.code){
                case(105):  // KEY_LEFT
                    if (accessing_menu_bar){
                        if (menu_bar_selection > 0){
                            menu_bar_selection--;
                        }
                        menu_bar_option_selection = -1;
                        refresh_screen = true;
                    }
                    break;
                case(106):  // KEY_RIGHT
                    if (accessing_menu_bar){
                        if (menu_bar_selection < 3){
                            menu_bar_selection++;
                        }
                        menu_bar_option_selection = -1;
                        refresh_screen = true;
                    }
                    break;
                case(103):  // KEY_UP
                    if (accessing_menu_bar){
                        if (menu_bar_option_selection >= 0){
                            menu_bar_option_selection--;
                        }
                        refresh_screen = true;
                    }
                    break;
                case(108):  // KEY_DOWN
                    if (accessing_menu_bar){
                        menu_bar_option_selection++;
                        refresh_screen = true;
                    }
                    break;
                case(1):    // KEY_ESC
                    out = true;
                    break;
                case(KEY_RIGHTALT):
                case(KEY_LEFTALT):
                    accessing_menu_bar = !accessing_menu_bar;
                    menu_bar_selection = 0;
                    menu_bar_option_selection = -1;
                    refresh_screen = true;
                    break;
                default:
                    break;
            }

            key_code = ev.code;
        }

        if (out){
            break;
        }
    }
}

void clearVector(vector<Line *> *line_vector, vector<Polygon *> *polygon_vector){
    for (vector<Line *>::iterator it = (*line_vector).begin(); it != (*line_vector).end(); it++){
        delete *it;
    }
    (*line_vector).clear();

    for (vector<Polygon *>::iterator it = (*polygon_vector).begin(); it != (*polygon_vector).end(); it++){
        delete *it;
    }
    (*polygon_vector).clear();
}

void drawMenuBar(WINDOW** menu_bar_options_window,WINDOW * menu_bar_window){  
    char ** menu_bar_options;
    int menu_bar_options_size;

    switch(menu_bar_selection){
        case(0):
            menu_bar_options_size = 4;
            menu_bar_options = (char**) malloc (4 * sizeof (char *));
            menu_bar_options[0] = "New";
            menu_bar_options[1] = "Open";
            menu_bar_options[2] = "Save";
            menu_bar_options[3] = "Exit";
            break;
        case(1):
            menu_bar_options_size = 6;
            menu_bar_options = (char**) malloc (6 * sizeof (char *));
            menu_bar_options[0] = "Zoom in";
            menu_bar_options[1] = "Zoom out";
            menu_bar_options[2] = "Pan left";
            menu_bar_options[3] = "Pan right";
            menu_bar_options[4] = "Pan top";
            menu_bar_options[5] = "Pan bottom";
            break;
        case(2):
            menu_bar_options_size = 3;
            menu_bar_options = (char**) malloc (3 * sizeof (char *));
            menu_bar_options[0] = "Color";
            menu_bar_options[1] = "Line thickness";
            menu_bar_options[2] = "Line style";
            break;
        case(3):
            menu_bar_options_size = 4;
            menu_bar_options = (char**) malloc (4 * sizeof (char *));
            menu_bar_options[0] = "Add line";
            menu_bar_options[1] = "Add polygon";
            menu_bar_options[2] = "Select";
            menu_bar_options[3] = "Delete";
            break;
        default:
            break;
    }
    
    if (menu_bar_option_selection >= menu_bar_options_size){
        menu_bar_option_selection = menu_bar_options_size - 1;
    }

    refresh();

    wbkgd(menu_bar_window, COLOR_PAIR(1));
    if (menu_bar_selection == 0 && accessing_menu_bar){
        wattron(menu_bar_window,COLOR_PAIR(2));
    }
    mvwprintw(menu_bar_window,0,1,"File");
    wattroff(menu_bar_window,COLOR_PAIR(2));
    if (menu_bar_selection == 1 && accessing_menu_bar){
        wattron(menu_bar_window,COLOR_PAIR(2));
    }
    mvwprintw(menu_bar_window,0,9,"View");
    wattroff(menu_bar_window,COLOR_PAIR(2));
    if (menu_bar_selection == 2 && accessing_menu_bar){
        wattron(menu_bar_window,COLOR_PAIR(2));
    }
    mvwprintw(menu_bar_window,0,17,"Attribute");
    wattroff(menu_bar_window,COLOR_PAIR(2));
    if (menu_bar_selection == 3 && accessing_menu_bar){
        wattron(menu_bar_window,COLOR_PAIR(2));
    }
    mvwprintw(menu_bar_window,0,30,"Object");
    wattroff(menu_bar_window,COLOR_PAIR(2));
    wrefresh(menu_bar_window);
    if (menu_bar_option_selection >= 0){
        wbkgd(menu_bar_options_window[menu_bar_selection], COLOR_PAIR(1));
        wborder(menu_bar_options_window[menu_bar_selection],0,0,' ',0,ACS_VLINE,ACS_VLINE,0,0);
        for (int i = 0; i < menu_bar_options_size; i++){
            if (i == menu_bar_option_selection){
                wattron(menu_bar_options_window[menu_bar_selection],COLOR_PAIR(2));
            }
            mvwprintw(menu_bar_options_window[menu_bar_selection],i,1,menu_bar_options[i]);
            wattroff(menu_bar_options_window[menu_bar_selection],COLOR_PAIR(2));
        }
        wrefresh(menu_bar_options_window[menu_bar_selection]);
    }
}

void printToFile(char * filename){
    vector<Line *> line;

    line.push_back(new Line(new Point(100,100),new Point(200,200)));
    line.push_back(new Line(new Point(1,1),new Point(2,2)));

    ofstream file;
    file.open("lines.txt");
    
    for (vector<Line *>::iterator it = line.begin(); it != line.end(); it++){
        Point *P1 = (*it)->getP1();
        Point *P2 = (*it)->getP2();

        file << P1->getX() << ' ' << P1->getY() << '|' << P2->getX() << ' ' << P2->getY() << endl;
    }

    file.close();
}

int main(int argc, char** argv){
    int fbfd;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize;
    char *fbp;
	char c;
	string prev_color;
	int prev_dash;
	int prev_thickness;
	mutex mtx;
	bool hasRendered=true;

    vector<Line *> line;
    vector<Polygon *> polygon;

    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        // Framebuffer can't be opened
        exit(1);
    }

    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        // Error reading fixed screen information
        exit(2);
    }

    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        // Error reading variable screen information
        exit(3);
    }

    // Calculating the screen size in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the framebuffer into memory
    fbp = (char *) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        // Mapping failed
        exit(4);
    }
	const char *dev = "/dev/input/event4";
    int fd = open(dev, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        return EXIT_FAILURE;
    }

    thread inputter (userInput,fd);

    struct RGB basic_color;
    basic_color.r = 255;
    basic_color.g = 255;
    basic_color.b = 255;

    vector<Line *> line_vector;
    vector<Polygon *> polygon_vector;

    initscr();
    noecho();
    start_color();
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    init_pair(2,COLOR_WHITE,COLOR_RED);

    int max_x_screen, max_y_screen;
    getmaxyx(stdscr,max_y_screen,max_x_screen);

    WINDOW ** menu_bar_options_window = (WINDOW**) malloc (4*sizeof(WINDOW*));
    menu_bar_options_window[0] = newwin(5,18,1,0);
    menu_bar_options_window[1] = newwin(7,18,1,8);
    menu_bar_options_window[2] = newwin(4,18,1,16);
    menu_bar_options_window[3] = newwin(5,18,1,29);
    WINDOW * menu_bar_window = newwin(1,max_x_screen,0,0);

    Line * selected_line = nullptr;
    Polygon * selected_polygon = nullptr;

    clear();
    while(1){
        if (refresh_screen){
            clear();
            drawMenuBar(menu_bar_options_window,menu_bar_window);
            refresh_screen = false;

            for (vector<Polygon *>::iterator it = polygon_vector.begin(); it != polygon_vector.end(); it++){
                (*it)->render(fbp,vinfo,finfo);
            }
            for (vector<Line *>::iterator it = line_vector.begin(); it != line_vector.end(); it++){
                (*it)->render(fbp,vinfo,finfo);
            }
            renderHorizontalBar(&line_vector,&polygon_vector,basic_color,fbp,vinfo,finfo);
            renderVerticalBar(&line_vector,&polygon_vector,basic_color,fbp,vinfo,finfo);
        }
        
        if (accessing_menu_bar && key_code == 28){
            if (menu_bar_selection == 0){
                WINDOW * window = newwin(10,40,max_y_screen/2-5,max_x_screen/2-20);
                char dummy[100];
                char test[100];
                memset(test,'\0',100);

                box(window,0,0);
                wbkgd(window,COLOR_PAIR(1));

                wrefresh(window);
                mvscanw(30,30,dummy);

                echo();
                switch (menu_bar_option_selection){
                    case(0):    // NEW
                        clearVector(&line_vector, &polygon_vector);
                        break;
                    case(1):    // OPEN
                    {
                        mvwprintw(window,3,11,"Enter line file to open");
                        wattron(window,A_REVERSE);
                        mvwprintw(window,5,2,"                                    ");
                        wrefresh(window);
                        mvwgetstr(window,5,2,test);
                        wattroff(window,A_REVERSE);

                        clearVector(&line_vector, &polygon_vector);
                        line_vector = load_lines(test);

                        mvwprintw(window,3,11,"Enter polygon file to open");
                        wattron(window,A_REVERSE);
                        mvwprintw(window,5,2,"                                    ");
                        wrefresh(window);
                        mvwgetstr(window,5,2,test);
                        wattroff(window,A_REVERSE);
                        
                        polygon_vector = load_polygons(test);
                        break;
                    }
                    case(2):    // SAVE
                    {
                        mvwprintw(window,3,13,"Enter filename for line");
                        wattron(window,A_REVERSE);
                        mvwprintw(window,5,2,"                                    ");
                        wrefresh(window);
                        mvwgetstr(window,5,2,test);
                        wattroff(window,A_REVERSE);

                        save_lines(&line_vector,test);

                        mvwprintw(window,3,13,"Enter filename for polygon");
                        wattron(window,A_REVERSE);
                        mvwprintw(window,5,2,"                                    ");
                        wrefresh(window);
                        mvwgetstr(window,5,2,test);
                        wattroff(window,A_REVERSE);

                        save_polygons(&polygon_vector,test);

                        break;
                    }
                    case(3):    // EXIT
                        out = true;
                        break;
                    default:
                        break;
                }
                noecho();
                wbkgd(window,COLOR_BLACK);
                wclear(window);
                wrefresh(window);
            } else if (menu_bar_selection == 1){
                switch(menu_bar_option_selection){
                    case 0:
                        for (vector<Line *>::iterator it = line_vector.begin(); it != line_vector.end(); it++){
                            (*it)->zoomIn(2);
                        }
                        for (vector<Polygon *>::iterator it = polygon_vector.begin(); it != polygon_vector.end(); it++){
                            (*it)->zoomIn(2);
                        }
                        break;
                    case 1:
                        for (vector<Line *>::iterator it = line_vector.begin(); it != line_vector.end(); it++){
                            (*it)->zoomOut(2);
                        }
                        for (vector<Polygon *>::iterator it = polygon_vector.begin(); it != polygon_vector.end(); it++){
                            (*it)->zoomOut(2);
                        }
                        break;
                    case 2:
                        for (vector<Line *>::iterator it = line_vector.begin(); it != line_vector.end(); it++){
                            (*it)->pan(2);
                        }
                        for (vector<Polygon *>::iterator it = polygon_vector.begin(); it != polygon_vector.end(); it++){
                            (*it)->pan(2);
                        }
                        // PAN LEFT 2
                        break;
                    case 3:
                        for (vector<Line *>::iterator it = line_vector.begin(); it != line_vector.end(); it++){
                            (*it)->pan(1);
                        }
                        for (vector<Polygon *>::iterator it = polygon_vector.begin(); it != polygon_vector.end(); it++){
                            (*it)->pan(1);
                        }
                        // PAN RIGHT 1
                        break;
                    case 4:
                        for (vector<Line *>::iterator it = line_vector.begin(); it != line_vector.end(); it++){
                            (*it)->pan(3);
                        }
                        for (vector<Polygon *>::iterator it = polygon_vector.begin(); it != polygon_vector.end(); it++){
                            (*it)->pan(3);
                        }
                        // PAN TOP 3
                        break;
                    case 5:
                        for (vector<Line *>::iterator it = line_vector.begin(); it != line_vector.end(); it++){
                            (*it)->pan(4);
                        }
                        for (vector<Polygon *>::iterator it = polygon_vector.begin(); it != polygon_vector.end(); it++){
                            (*it)->pan(4);
                        }
                        // PAN BOTTOM 4
                        break;
                    default:
                        break;
                }
                refresh_screen = true;
            } else if (menu_bar_selection == 2){
                WINDOW * window = newwin(10,40,max_y_screen/2-5,max_x_screen/2-20);
                char dummy[100];
                char P1[20];
                char P2[20];
                memset(P1, '\0', 20);
                memset(P2, '\0', 20);

                box(window,0,0);
                wbkgd(window,COLOR_PAIR(1));

                wrefresh(window);
                mvscanw(30,30,dummy);

                echo();
                switch(menu_bar_option_selection){
                    case 0:
                        if (selected_line != nullptr){
                            key_code = 0x00;
                            int selection = 0;
                            char * colors[8];
                            colors[0] = "Green";
                            colors[1] = "White";
                            colors[2] = "Yellow";
                            colors[3] = "Red";
                            colors[4] = "Magenta";
                            colors[5] = "Purple";
                            colors[6] = "Light Blue";
                            colors[7] = "Orange";
                            
                            bool exit_from_loop = false;
                            struct RGB rgb;

                            while(1){
                                werase(window);
                                mvwprintw(window,3,3,"Color: ");
                                mvwprintw(window,3,10,colors[selection]);
                                switch(key_code){
                                    case(105):
                                    {
                                        selection--;

                                        if (selection <= 0)
                                            selection = 1;
                                        key_code = 0x00;
                                        break;
                                    }
                                    case(106):
                                    {
                                        selection++;

                                        if (selection >= 7)
                                            selection = 7;
                                        key_code = 0x00;
                                        break;
                                    }
                                    case(28):
                                    {
                                        exit_from_loop = true;
                                        key_code = 0x00;
                                        break;
                                    }
                                    default:
                                        key_code = 0x00;
                                        break;
                                }
                                wrefresh(window);

                                switch(selection){
                                    case(0):
                                        rgb.r = 0;
                                        rgb.g = 255;
                                        rgb.b = 0;
                                        break;
                                    case(1):
                                        rgb.r = 255;
                                        rgb.g = 255;
                                        rgb.b = 255;
                                        break;
                                    case(2):
                                        rgb.r = 255;
                                        rgb.g = 255;
                                        rgb.b = 0;
                                        break;
                                    case(3):
                                        rgb.r = 255;
                                        rgb.g = 0;
                                        rgb.b = 0;
                                        break;
                                    case(4):
                                        rgb.r = 255;
                                        rgb.g = 0;
                                        rgb.b = 255;
                                        break;
                                    case(5):
                                        rgb.r = 128;
                                        rgb.g = 0;
                                        rgb.b = 128;
                                        break;
                                    case(6):
                                        rgb.r = 64;
                                        rgb.g = 224;
                                        rgb.b = 208;
                                        break;
                                    case(7):
                                        rgb.r = 255;
                                        rgb.g = 99;
                                        rgb.b = 71;
                                        break;
                                    default:
                                        break;
                                }
                                if (exit_from_loop)
                                    break;
                            }

                            selected_line->setRGB(rgb);
                        }
                        break;
                    case 1:
                        if (selected_line != nullptr){
                            key_code = 0x00;
                            int thickness = selected_line->getThickness();
                            char thickness_string[2];
                            bool exit_from_loop = false;

                            while(1){
                                werase(window);
                                mvwprintw(window,3,3,"Thickness: ");
                                sprintf(thickness_string,"%d",thickness);
                                mvwprintw(window,3,14,thickness_string);
                                switch(key_code){
                                    case(105):
                                    {
                                        thickness--;

                                        if (thickness <= 1)
                                            thickness = 1;
                                        key_code = 0x00;
                                        break;
                                    }
                                    case(106):
                                    {
                                        thickness++;

                                        if (thickness >= 3)
                                            thickness = 3;
                                        key_code = 0x00;
                                        break;
                                    }
                                    case(28):
                                    {
                                        exit_from_loop = true;
                                        key_code = 0x00;
                                        break;
                                    }
                                    default:
                                        key_code = 0x00;
                                        break;
                                }
                                wrefresh(window);

                                if (exit_from_loop)
                                    break;
                            }

                            selected_line->setThickness(thickness);
                        }
                        break;
                    case 2:
                        if (selected_line != nullptr){
                            key_code = 0x00;
                            int dash = selected_line->getDash();
                            char dash_string[2];
                            bool exit_from_loop = false;

                            while(1){
                                werase(window);
                                mvwprintw(window,3,3,"Dash: ");
                                sprintf(dash_string,"%d",dash);
                                mvwprintw(window,3,9,dash_string);
                                switch(key_code){
                                    case(105):
                                    {
                                        dash--;

                                        if (dash <= 0)
                                            dash = 0;
                                        key_code = 0x00;
                                        break;
                                    }
                                    case(106):
                                    {
                                        dash++;

                                        if (dash >= 5)
                                            dash = 5;
                                        key_code = 0x00;
                                        break;
                                    }
                                    case(28):
                                    {
                                        exit_from_loop = true;
                                        key_code = 0x00;
                                        break;
                                    }
                                    default:
                                        key_code = 0x00;
                                        break;
                                }
                                wrefresh(window);

                                if (exit_from_loop)
                                    break;
                            }

                            selected_line->setDash(dash);
                        }
                        break;
                    default:
                        break;
                }
                noecho();

                wbkgd(window,COLOR_BLACK);
                wclear(window);
                wrefresh(window);
                
            } else if (menu_bar_selection == 3){
                WINDOW * window = newwin(10,40,max_y_screen/2-5,max_x_screen/2-20);
                char dummy[100];
                char P1[20];
                char P2[20];
                memset(P1, '\0', 20);
                memset(P2, '\0', 20);

                box(window,0,0);
                wbkgd(window,COLOR_PAIR(1));

                wrefresh(window);
                mvscanw(30,30,dummy);

                echo();
                switch(menu_bar_option_selection){
                    case 0:
                    {
                        mvwprintw(window,3,3,"Point 1: ");
                        mvwprintw(window,5,3,"Point 2: ");
                        wattron(window,A_REVERSE);
                        mvwprintw(window,3,12,"            ");
                        mvwprintw(window,5,12,"            ");
                        wrefresh(window);
                        mvwgetstr(window,3,12,P1);
                        mvwgetstr(window,5,12,P2);

                        Line * line = parseToLine(P1,P2);
                        line_vector.push_back(line);
                        
                        wattroff(window,A_REVERSE);
                        cout << "Point 1: " << (*line).getP1()->getX() << "," << (*line).getP1()->getY() << endl;
                        cout << "Point 2: " << (*line).getP2()->getX() << "," << (*line).getP2()->getY() << endl;
                        break;
                    }
                    case 1:
                    {   
                        Polygon * polygon = new Polygon(basic_color);
                        while(true){
                            mvwprintw(window,3,3,"Point: ");
                            wattron(window,A_REVERSE);
                            mvwprintw(window,3,10,"            ");
                            wrefresh(window);
                            mvwgetstr(window,3,10,P1);

                            Point * point = new Point(0,0);
                            if (parseToPoint(point,P1)){
                                polygon->addPoint(point);
                                wattroff(window,A_REVERSE);
                            } else {
                                wattroff(window,A_REVERSE);
                                break;
                            }
                        }
                        polygon_vector.push_back(polygon);
                        break;
                    }
                    case 2:
                    {
                        bool exit_from_loop = false;
                        char* text_container[2];
                        text_container[0] = "Lines";
                        text_container[1] = "Vector";
                        
                        int i = 0;
                        int selection = 0;
                        char selection_string[3];
                        key_code = 0x00;
                        while(1){
                            werase(window);
                            mvwprintw(window,3,3,"Going through: ");
                            mvwprintw(window,3,19,text_container[i]);
                            switch(key_code){
                                case(KEY_TAB):
                                {
                                    selection = 0;
                                    i = !i;
                                    key_code = 0x00;
                                    break;
                                }
                                case(105):
                                {
                                    selection--;

                                    if (selection <= 0)
                                        selection = 0;
                                    key_code = 0x00;
                                    break;
                                }
                                case(106):
                                {
                                    int size;
                                    if (i == 0)
                                        size = line_vector.size();
                                    else
                                        size = polygon_vector.size();
                                    selection++;

                                    if (selection >= size)
                                        selection = size - 1;
                                    key_code = 0x00;
                                    break;
                                }
                                case(28):
                                {
                                    exit_from_loop = true;
                                    key_code = 0x00;
                                    break;
                                }
                                default:
                                    key_code = 0x00;
                                    break;
                            }

                            mvwprintw(window,5,3,"Index: ");
                            sprintf(selection_string,"%d",selection);
                            mvwprintw(window,5,19,selection_string);
                            wrefresh(window);

                            if (exit_from_loop)
                                break;
                        }
                        if (i == 0){
                            selected_line = selectLine(&line_vector,selection);
                            selected_polygon = nullptr;
                        } else {
                            selected_polygon = selectPolygon(&polygon_vector,selection);
                            selected_line = nullptr;
                        }
                        break;
                    }
                    case 3:
                        if (selected_line != nullptr){
                            mvwprintw(window,3,3,"Deleted selected line");
                            int position = 0;
                            for (vector<Line *>::iterator it = line_vector.begin(); it != line_vector.end(); it++){
                                if (selected_line == (*it))
                                    break;
                                else
                                    position++;
                            }

                            deleteLine(&line_vector,position);
                            delete(selected_line);
                            selected_line = nullptr;
                        } else if (selected_polygon != nullptr){
                            mvwprintw(window,3,3,"Deleted selected polygon");
                            int position = 0;
                            for (vector<Polygon *>::iterator it = polygon_vector.begin(); it != polygon_vector.end(); it++){
                                if (selected_polygon == (*it))
                                    break;
                                else
                                    position++;
                            }

                            deletePolygon(&polygon_vector,position);
                            delete(selected_polygon);
                            selected_polygon = nullptr;
                        }
                        wrefresh(window);
                        break;
                    default:
                        break;
                }
                noecho();

                wbkgd(window,COLOR_BLACK);
                wclear(window);
                wrefresh(window);
            }

            key_code = 0x00;
            for (vector<Polygon *>::iterator it = polygon_vector.begin(); it != polygon_vector.end(); it++){
                (*it)->render(fbp,vinfo,finfo);
            }
            for (vector<Line *>::iterator it = line_vector.begin(); it != line_vector.end(); it++){
                (*it)->render(fbp,vinfo,finfo);
            }
        }

        if (out){
            break;
        }
    }

    delwin(menu_bar_options_window[0]);
    delwin(menu_bar_options_window[1]);
    delwin(menu_bar_options_window[2]);
    delwin(menu_bar_options_window[3]);
    
    free(menu_bar_options_window);
    endwin();

    munmap(fbp, screensize);

    close(fbfd);

    inputter.join();

    return 0;
}
