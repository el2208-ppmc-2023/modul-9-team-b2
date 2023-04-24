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
