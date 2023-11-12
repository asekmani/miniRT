#define _CRT_SECURE_NO_WARNINGS  // Pour désactiver les avertissements liés aux fonctions "sécurisées" dans Visual Studio
#include <stdio.h>
#include <stdlib.h>


void save_img(const char* filename, const unsigned char* pixels, int W, int H)
{
unsigned char bmpfileheader [14] = { 'B', 'M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
unsigned char bepinfoheader [40] ={40,0,0,0,0,0,0,0,0,0,0,0, 1,0, 24,0};
unsigned char beppad[3] = { 0,0,0 };
int filesize = 54 + 3 * W * H;

bmpfileheader[2] = (unsigned char)(filesize);
bmpfileheader[3] = (unsigned char)(filesize >> 8);
bmpfileheader[4] = (unsigned char)(filesize >> 16);
bmpfileheader[5] = (unsigned char)(filesize >> 24);

bepinfoheader[4] = (unsigned char)(W);
bepinfoheader[5] = (unsigned char)(W >> 8);
bepinfoheader[6] = (unsigned char)(W >> 16);
bepinfoheader[7] = (unsigned char)(W >> 24);
bepinfoheader[8] = (unsigned char)(H);
bepinfoheader[9] = (unsigned char)(H >> 8);
bepinfoheader[10] = (unsigned char)(W >> 16);
bepinfoheader[11] = (unsigned char)(W >> 24);

FILE* f;
f = fopen(filename, "wb");
fwrite(bmpfileheader, 1, 14, f);
fwrite(bepinfoheader, 1, 40, f);
unsigned char* bgr_pixels = (unsigned char*)malloc(W * H * 3);
for(int i = 0; i < W*H; i++){
    bgr_pixels[i * 3] = pixels[i * 3 + 2];
    bgr_pixels[i * 3 + 1] = pixels[i * 3 + 1];
    bgr_pixels[i * 3 + 2] = pixels[i * 3];
}
for(int i=0; i < H; i++){
    fwrite(&bgr_pixels[0] + (W * (H - i - 1) * 3), 3, W, f);
    fwrite(beppad, 1, (4 - (W * 3) % 4) % 4, f);
}
fclose(f);
}