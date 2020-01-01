#include "image.h"

double mean(byte* P, int width, int height) {
    /*
    Compute the mean of a byte array
    */
    double moy = 0.0;
    double tot = double(width*height);
    for(int i=0; i<width; i++) {
        for(int j=0; j<height; j++) {
            moy += double(P[i*width+j]);
        }
    }
    return(moy/tot);
}

double standard_dev(byte* P, int width, int height) {
    /*
    Compute the standard deviation of a byte array
    */
    double ecart = 0.0;
    double moy = mean(P, width, height);
    double tot = double(width*height);

    for(int i=0; i<width; i++) {
        for(int j=0; j<height; j++) {
            ecart += (double(P[i*width+j]) - moy) * (double(P[i*width+j]) - moy);
        }
    }
    return(sqrt(moy/tot));
}

byte* color_to_bw(char* name, int W, int H) {
    /*
    Convert a RGB image to a Black & White image
    */
    byte *R,*G,*B;
    byte *N = new byte[W*H];

    loadColorImage(name,R,G,B,W,H); // load the image
    for(int i=0; i<W; i++) {
        for(int j=0; j<H; j++) {
            N[i*H+j] = (R[i*H+j]+G[i*H+j]+B[i*H+j]) / 3;
        }
    }
    return(N);
}



