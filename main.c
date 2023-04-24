/*EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
*Modul : 9 - Tugas Besar
*Kelompok : B2
*Hari dan Tanggal : 24 April 2023
*Asisten (NIM) : Muhammad Daffa Rasyid (13220059)
*Nama File : main.c
*Deskripsi : Program yang dapat membaca lokasi markas negara api kemudian membuat perbatasan efektif seluas-luasnya
dengan jarak antar markas tidak lebih dari 2500 km. Output nya adalah perbatasan efektif negara api dengan semua
markas-markas yang menjadi batasnya, keliling perbatasan efektif, dan markas-markas negara api yang berada di luar
perbatasan efektif.
*/

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(){
    //Membaca file csv.
    Markas *data_markas;
    data_markas = (Markas*) malloc(sizeof(Markas));

    FILE* stream = fopen("D:\\SEMESTER 4\\PPMC\\markas.csv", "r");

    // Memindahkan data dari file eksternal ke array.
    char line[255]; 
    char* token; 
    int banyak_elemen = 1; 
    int i = 0;
    fgets(line, 255, stream);

    while(fgets(line, 255, stream)) {
      token = strtok(line,","); strcpy(data_markas[i].nama,token);
      token = strtok(NULL, ","); data_markas[i].posisi.x = atof(token);
      token = strtok(NULL, "\n"); data_markas[i].posisi.y= atof(token);
      banyak_elemen++;
      i++;
      data_markas = realloc(data_markas, (banyak_elemen)*sizeof(Markas));
    }

    fclose(stream);
    
     // Mencari markas yang memiliki posisi paling bawah (bujur atau y paling rendah) dan mengurutkan array berdasarkan sudut yang dibentuk 
    // secara counterclockwise terhadap markas yang paling bawah tersebut.
    sort_CC(data_markas, 20);

    // Melakukan Convex hull.
    Stack* hull = (Stack*) malloc(sizeof(Stack));
    hull = NULL;
    Stack* luar = (Stack*) malloc(sizeof(Stack));
    luar = NULL;
    double jarak = 0;

    push(&hull, &data_markas[0]);
    push(&hull, &data_markas[1]);

    for(int j = 2; j < 20; j++){
        while(cross_product(next_top(hull).posisi,hull->markas.posisi,data_markas[j].posisi) <= 0){
            hull = hull->next;
        }
        if(haversine(hull->markas.posisi.x, hull->markas.posisi.y, data_markas[j].posisi.x, data_markas[j].posisi.y) <= 2500){
            push(&hull, &data_markas[j]);
        } else {
            push(&luar, &data_markas[j]);
        }
    }

    // Menampilkan hasil kepada pengguna.
    printf("Markas Efektif: \n");
    while(hull != NULL){
        printf("Nama: %s\n", hull->markas.nama);
        printf("Lintang: %f\n",hull->markas.posisi.x);
        printf("Bujur: %f\n\n", hull->markas.posisi.y);
        Markas temp = hull->markas;
        hull = hull->next;
        if(hull != NULL){
            jarak = jarak + haversine(hull->markas.posisi.x, hull->markas.posisi.y, temp.posisi.x, temp.posisi.y);
        }
    }

    printf("Jarak markas efektif: %f\n\n", jarak);

    printf("Markas di luar: \n");
    while(luar != NULL){
    printf("Nama: %s\n", luar->markas.nama);
    printf("Lintang: %f\n",luar->markas.posisi.x);
    printf("Bujur: %f\n\n", luar->markas.posisi.y);
    luar = luar->next;
    }

    return 0;
}
