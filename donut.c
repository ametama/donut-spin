#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define M_PI 3.14159265358979323846
#define R 12
#define r 5

// Cat on my keyboard:                                                                                                           
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

double or_zbuf[50][50];
char or_buf[50][50];

int main() {
    const double sqrthree = sqrt(3);
    const char illumination[12] = ".,-~:;=!*#$@";
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            or_zbuf[i][j] = 50;
            or_buf[i][j] = or_buf[i][j] = ' ';
        }
        or_buf[i][49] = '\0';
    }

    int kc = 0;
    while (1) {
        kc = (kc + 1) % 256;
        char buf[50][50];
        double zbuf[50][50];
        for (int s = 0; s < 50; s++) {
            strcpy(buf[s], or_buf[s]);
            memcpy(zbuf, or_zbuf, sizeof(double) * 50 * 50);
        }
        double c = M_PI * sin(M_PI / 128 * kc);
        double d = M_PI * cos(M_PI / 128 * kc);
        for (int k = 0; k < 128; k++) {
            double b = k * M_PI / 64;
            for (int l = 0; l < 64; l++) {
                double a = l * M_PI / 32;

                double x = cos(c) * cos(b) * (cos(a) * r + R) - sin(c) * sin(a) * r;
                double y = cos(d) * (sin(c) * cos(b) * (cos(a) * r + R) + cos(c) * sin(a) * r) - sin(d) * (sin(b) * (cos(a) * r + R));
                double z = sin(d) * (sin(c) * cos(b) * (cos(a) * r + R) + cos(c) * sin(a) * r) + cos(d) * (sin(b) * (cos(a) * r + R));

                double nx = x - cos(c) * cos(b) * R;
                double ny = y - cos(d) * sin(c) * cos(b) * R - sin(d) * sin(b) * R;
                double nz = z - sin(d) * sin(c) * cos(b) * R + cos(d) * sin(b) * R;

                x = x * 27 / (z + 30);
                y = y * 27 / (z + 30);

                if (zbuf[((int) x) + 25][((int) y) + 25] < z) continue;
                zbuf[((int) x) + 25][((int) y) + 25] = z;

                double shade_intensity = (-nx + ny - nz) / (sqrt(pow(nx, 2) + pow(ny, 2) + pow(nz, 2)) * sqrthree);
                if (shade_intensity < 0) shade_intensity = 0;
                buf[((int) x) + 25][((int) y) + 25] = illumination[(int) ((shade_intensity) * 12)];
            }
        }

        for (int i = 0; i < 50; i++) {
            printf("%s\n", buf[i]);
        }
        usleep(40000);
    }
}
