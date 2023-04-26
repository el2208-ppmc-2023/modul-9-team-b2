/*EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
*Modul : 9 - Tugas Besar
*Kelompok : B2
*Hari dan Tanggal : 27 April 2023
*Asisten (NIM) : Muhammad Daffa Rasyid (13220059)
*Nama File : main.h
*Deskripsi : file yang berisikan deklarasi tipe data bentukan 
*            serta fungsi-fungsi yang dibutuhkan di dalam file main.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define max_char 100
#define max 200
#define PI 3.14159265359
#define rBumi 6371.0 //dalam KM

// Tipe bentukan untuk posisi. Variabel x untuk lintang dan variabel y untuk bujur.
typedef struct{
    double x;
    double y;
} Koordinat;

// Tipe bentukan untuk identitas sebuah markas.
typedef struct {
    char nama[max_char];
    Koordinat posisi;
} Markas;

// Stack untuk menyimpan convex hull.
typedef struct Stack{
    Markas markas;
    struct Stack* next;
} Stack;

// Fungsi untuk menukar posisi.
void swap(Markas* a, Markas* b){
    Markas temp = *a;
    *a = *b;
    *b = temp;
}

// Fungsi yang digunakan untuk menghitung nilai perkalian cross dari tiga titik.
double cross_product(Koordinat a, Koordinat b, Koordinat c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

// Fungsi untuk mencari nilai bujur yang terkecil dari sebuah array bertipe Markas.
int smallest_y_index(Markas* markas, int n){
    int index = 0;
    for(int i = 0; i < n; i++){
        if(markas[i].posisi.y<markas[index].posisi.y){
            index = i;
        }
    }

    return index;
}

// Fungsi untuk mencari sudut dari dua titik.
double angle(Koordinat base, Koordinat point){
    return (180/PI)*atan2(point.y-base.y,point.x-base.x);
}

// Fungsi untuk mengurutkan array bertipe markas berdasarkan sudutnya terhadap titik yang letatknya berada paling bawah. 
// Urutan dimulai dari yang paling kecil menuju yang paling besar.
void sort_CC(Markas* markas, int n){
    int smallest_y = smallest_y_index(markas, n);
    swap(&markas[0], &markas[smallest_y]);

    for(int i = 1; i < n-1; i++){
        double min = angle(markas[0].posisi, markas[i].posisi);
        int idx_min = i;
        for(int j = i+1; j < n-1; j++){
            if(angle(markas[0].posisi, markas[j].posisi)<min){
                min = angle(markas[0].posisi, markas[j].posisi);
                idx_min = j;
            }
        }
        swap(&markas[i],&markas[idx_min]);
    }
}

// Fungsi untuk menambahkan elemen pada stack.
void push(Stack** stack, Markas* markas){
    Stack* new_element = (Stack*) malloc (sizeof(Stack));
    new_element->markas = *markas;
    new_element->next = *stack;
    *stack = new_element;
} 

// Fungsi untuk mengambil elemen kedua dari atas sebuah stack.
Markas next_top(Stack* stack){
    return stack->next->markas;
}

// Fungsi untuk mengubah derajat menjadi radian.
double to_radians(double degrees) {
    return degrees * PI / 180.0;
}

// Fungsi untuk menghitung jarak menurut formula haversine.
double haversine(double lat1, double lon1, double lat2, double lon2) {
   double dlon, dlat, a, c, distance;

    dlon = to_radians(lon2 - lon1);
    dlat = to_radians(lat2 - lat1);

    a = pow(sin(dlat / 2), 2) + cos(to_radians(lat1)) * cos(to_radians(lat2)) * pow(sin(dlon / 2), 2);
    c = 2 * atan2(sqrt(a), sqrt(1 - a));
    distance = rBumi * c;

    return distance;
}
