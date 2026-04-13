
#ifndef filedata_h //agar supaya tidak diinclude lebih dari sekali
#include "filedata.h"   
#endif

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
int main() {
    int jumlahMhs;
    Mahasiswa *daftarMhs = inputDataMahasiswa(&jumlahMhs);

    simpanKeFileCSV(daftarMhs, jumlahMhs, FILE_NAME);
    
    printf("\n=== DATA MAHASISWA ===\n");
    bacaDariFileCSV(FILE_NAME);


    int jumlahMK;
    MataKuliah *daftarMK = inputMataKuliah(&jumlahMK);

    simpanMataKuliahCSV(daftarMK, jumlahMK, "matakuliah.csv");
    free(daftarMK);

    printf("\n=== DATA MATA KULIAH ===\n");
    bacaMataKuliahCSV("matakuliah.csv");

    
    MataKuliah mk[50];
    int totalMK = loadMataKuliah(mk, "matakuliah.csv");

    if (totalMK > 0) {
        tampilkanDaftarMK(mk, totalMK);

        KRS k;
        inputKRS(&k, mk, totalMK);
        simpanKRSCsv(&k, "krs.csv");
    } else {
        printf("Belum ada data mata kuliah!\n");
    }


    printf("\n=== DATA KRS===\n");

    FILE *fp = fopen("krs.csv", "r");
    if (!fp) {
        printf("Belum ada file KRS.\n");
        return 0;
    }

    char nim[20], kode[20];
    char namaMatkulList[20][100];
    int count = 0;

    while (fscanf(fp, "%[^,],%s\n", nim, kode) == 2) {
        for (int j = 0; j < totalMK; j++) {
            if (strcmp(mk[j].kode, kode) == 0) {
                strcpy(namaMatkulList[count], mk[j].nama);
                count++;
                break;
            }
        }
    }
    fclose(fp);

    for (int i = 0; i < jumlahMhs; i++) {
        if (strcmp(daftarMhs[i].nim, nim) == 0) {

            printf("\nMahasiswa dengan data:\n");
            printf("NIM            : %s\n", daftarMhs[i].nim);
            printf("Nama           : %s\n", daftarMhs[i].nama);
            printf("Program Studi  : %s\n", daftarMhs[i].prodi);
            printf("IPK            : %.2f\n", daftarMhs[i].ipk);

            break;
        }
    }

    printf("\nMengambil Mata Kuliah:\n");
    for (int i = 0; i < count; i++) {
        printf("- %s\n", namaMatkulList[i]);
    }
    free(daftarMhs);

    return 0;
}
