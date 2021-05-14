#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main(void) {
    int i, n, j, max = 0;
    char s1[15], s2[15], c;
    double x, y, z;
    n = 3;
    //scanf_s("%d", &n);
    struct ways {
        char cyout[15];
        char cygo[15];
        int num;
        int dist;
        int sp;
        int ns;
    };
    struct ways train[3];
        for (i = 0; i < n; i++) {

            gets_s(s1);
            char * pch = strtok_s(s1, " ");
            
            printf(pch);
            //gets(s2);
            for (j = 0; j < 15; j++) {

                for (int k = 0; k < 5; ++k) 
                {
                    train[i].cyout[j] = *pch;
                    pch = strtok(NULL, " ");
                }


                train[i].cyout[j] = s1[j];
                //train[i].cygo[j]=s2[j];
            }
            scanf_s("%d %d %d %d", &train[i].num, &train[i].dist, &train[i].sp, &train[i].ns);
        }
    for (i = 0; i < n; i++) {
        //puts(train[i].cyout);
        //puts(train[i].cygo);
        printf("%5d%5d%5d%5d\n", train[i].num, train[i].dist, train[i].sp, train[i].ns);
    }
        return 0;
}