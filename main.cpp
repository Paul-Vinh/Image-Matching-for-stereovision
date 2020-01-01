#include "image.h"

// important constants
int horiz = 8;
int verti = 8;
int height = 2*verti+1;
int width = 2*horiz+1;
int interval = 30;

int main()
{
    int W = 540, H = 540; // size of the images
    Point p2;

    vector<Point> pts(20); // array storing all the different points
    vector<Point> pts_corres(20);
    pts.clear();
    pts_corres.clear();
    Color coul[20] = {GREEN, RED, BLUE, YELLOW, PURPLE, ORANGE, BLACK, WHITE, CYAN, MAGENTA,
                     GREEN, RED, BLUE, YELLOW, PURPLE, ORANGE, BLACK, WHITE, CYAN, MAGENTA}; // colour array

    Window w = openWindow(W, H, "Image 1", 200, 150);
    Window w2 = openWindow(W, H, "Image 2", 800, 150);
    setActiveWindow(w);

    // --- Convert the 2 images in Black & White ---
    char* name = srcPath("image_1.jpg");
    byte* N = color_to_bw(name, W, H); // image array
    putGreyImage(0, 0, N, W, H); // print the 1st image

    setActiveWindow(w2);
    name = srcPath("image_2.jpg");
    byte* N1 = color_to_bw(name, W, H); // image array
    putGreyImage(0, 0, N1, W, H); // print the 2nd image

    setActiveWindow(w);
    int x0, y0;
    int val = 0;
    Point p;
    while(getMouse(x0, y0) == 1) {
        cout << "Coordinates of the clicked points : " << "(" << x0 << "," << y0 << ")" << endl;
        p.x = x0;
        p.y = y0;
        pts.push_back(p);
        fillCircle(p.x, p.y, 5, coul[val]);
        val++;
    }

    cout << "---- Ongoing calculation ----" << endl;

    for(int index=0; index<pts.size(); index++) {

    byte *N2 = new byte[width*height];
    byte *N3 = new byte[width*height];
    int dim = (W*H);
    vector<double> v(dim);
    v.clear();
    vector<int> vx(dim);
    vx.clear();
    vector<int> vy(dim);
    vy.clear();

    // Creation of the patch corresponding to the clicked point (initial image)
    int k = 0;
    for(int i=pts[index].y-verti; i<pts[index].y+verti+1; i++) {
        for(int j=pts[index].x-horiz; j<pts[index].x+horiz+1; j++) {
            N2[k] = N[i*W+j];
            k++;
        }
    }

    // layout of all the possible zones (kernel 40 x 40 around the inital pixel)
    for(int i=pts[index].x - interval; i<=pts[index].x + interval-height; i++) {
        for(int j=pts[index].y - interval; j<=pts[index].y + interval-width; j++) {

            int m = 0;
            for(int k=j; k<j+height; k++) {
                for(int l=i; l<i+width; l++) {
                    N3[m] = N1[k*W+l];
                    m++;
                }
            }

            // ZNCC
            double moy1 = mean(N2, width, height);
            double moy2 = mean(N3, width, height);
            double ecart1 = standard_dev(N2, width, height);
            double ecart2 = standard_dev(N3, width, height);


            double e = 0.0;
            for(int q=0; q<width; q++) {
                for(int r=0; r<height; r++) {
                    e += (double(N2[q*width+r]) - moy1) / ecart1 * (double(N3[q*width+r]) - moy2) / ecart2;
                }
            }
            e = e/(width*height);
            v.push_back(e);
            vx.push_back(i);
            vy.push_back(j);
        }
    }

    int ind = std::max_element(v.begin(),v.end()) - v.begin(); // index of the maximum element of the array (ZNCC)
    setActiveWindow(w2);
    fillCircle(vx[ind] + verti, vy[ind] + horiz, 5, coul[index]);
    cout << "Coordinates of the corresponding point : (" << vx[ind] + verti << "," << vy[ind] + horiz << ")" << endl;
    p2.x = vx[ind] + verti;
    p2.y = vy[ind] + horiz;
    pts_corres.push_back(p2);
}

    ofstream fichier("pairing.txt", ios::trunc);  // empty file is open to write on it

    if(fichier)
    {
        fichier << pts.size() << endl;
        for(int k=0; k<pts.size(); k++) {
            fichier << pts[k].x << " " << pts[k].y << " " << pts_corres[k].x << " " << pts_corres[k].y << endl;
        }
    }
    else
        cerr << "The file cannot be opened !" << endl;


    fichier.close(); // .txt file closed

    endGraphics();
	return 0;
}
