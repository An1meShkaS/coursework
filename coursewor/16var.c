#include <stdio.h>
#include <math.h>
#include <locale.h>
struct Metric {
    float znach[6];
    int est[6];
    int series;
};
struct Incident {
    int time;
    int type;
    int count;
};
int main() {
    setlocale(LC_ALL, ".UTF8");
    float L = 0.8;
    struct Metric mem;  mem.series = 0;
    struct Metric dsk;  dsk.series = 0;
    struct Metric net;  net.series = 0;
    for (int i = 0; i <= 5; i++) {
        mem.est[i] = 0;
        dsk.est[i] = 0;
        net.est[i] = 0;
    }
    mem.znach[1] = 41.9; mem.est[1] = 1;
    mem.znach[3] = 48.3; mem.est[3] = 1;
    mem.znach[4] = 48.8; mem.est[4] = 1;
    mem.znach[5] = 49.3; mem.est[5] = 1;
    dsk.znach[1] = 57.4; dsk.est[1] = 1;
    dsk.znach[2] = 55.4; dsk.est[2] = 1;
    dsk.znach[3] = 53.4; dsk.est[3] = 1;
    dsk.znach[4] = 51.4; dsk.est[4] = 1;
    dsk.znach[5] = 54.8; dsk.est[5] = 1;
    net.znach[1] = 30.2; net.est[1] = 1;
    net.znach[2] = 29.5; net.est[2] = 1;
    net.znach[3] = 34.1; net.est[3] = 1;
    net.znach[5] = 32.6; net.est[5] = 1;
    struct Incident incidents[6];
    int incident_count = 0;
    printf(" == РЕЗУЛЬТАТЫ ПРОГРАММЫ (КТ1) ==\n\n");
    for (int t = 1; t <= 5; t++) {
        int bad_now = 0;
        printf("Takt t = %d:\n", t);
        if (mem.est[t] == 0) {
            printf("  MEM: пропуск\n");
        }
        else {
            if (t > 1 && mem.est[t - 1] == 1) {
                float Q = mem.znach[t] - mem.znach[t - 1];
                if (fabs(Q) > L) mem.series++;
                else mem.series = 0;
            }
            else {
                mem.series = 0;
            }
            if (mem.series >= 2) {
                printf("  MEM: предупреждение\n");
                bad_now++;
            }
            else {
                printf("  MEM: норма\n");
            }
        }
        if (dsk.est[t] == 0) {
            printf("  DSK: пропуск\n");
        }
        else {
            if (t > 1 && dsk.est[t - 1] == 1) {
                float Q = dsk.znach[t] - dsk.znach[t - 1];
                if (fabs(Q) > L) dsk.series++;
                else dsk.series = 0;
            }
            else {
                dsk.series = 0;
            }
            if (dsk.series >= 2) {
                printf("  DSK: предупреждение\n");
                bad_now++;
            }
            else {
                printf("  DSK: норма\n");
            }
        }
        if (net.est[t] == 0) {
            printf("  NET:пропуск\n");
        }
        else {
            if (t > 1 && net.est[t - 1] == 1) {
                float Q = net.znach[t] - net.znach[t - 1];
                if (fabs(Q) > L) net.series++;
                else net.series = 0;
            }
            else {
                net.series = 0;
            }
            if (net.series >= 2) {
                printf("  NET: предупреждение\n");
                bad_now++;
            }
            else {
                printf("  NET: норма\n");
            }
        }
        if (bad_now >= 2) {
            printf("=> инцидент!\n");
            incidents[incident_count].time = t;
            incidents[incident_count].type = 1;
            incidents[incident_count].count = bad_now;
            incident_count++;
        }
        else {
            printf("=> Статус: инцидента нет\n");
        }
        printf("\n");
    }
    printf("ИТОГ:\n");
    printf("количество инцидентов: %d\n", incident_count);
    return 0;
}
