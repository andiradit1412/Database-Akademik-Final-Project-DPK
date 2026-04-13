#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef filedata_h
#include "filedata.h"
#endif

Mahasiswa* inputDataMahasiswa(int *jumlah) {
    printf("Masukkan jumlah mahasiswa: ");
    scanf("%d", jumlah);
    bersihkanBufferInput();

    // Alokasi dinamis
    Mahasiswa *data = (Mahasiswa*) malloc((*jumlah) * sizeof(Mahasiswa));
    if (!data) {
        printf("Alokasi memori gagal!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *jumlah; i++) {
        printf("\nMahasiswa #%d\n", i + 1);

        printf("NIM    : ");
        fgets(data[i].nim, 20, stdin);
        data[i].nim[strcspn(data[i].nim, "\n")] = '\0';

        printf("Nama   : ");
        fgets(data[i].nama, MAX_NAME_LEN, stdin);
        data[i].nama[strcspn(data[i].nama, "\n")] = '\0'; // hapus newline

        printf("Prodi  : ");
        fgets(data[i].prodi, MAX_PRODI_LEN, stdin);
        data[i].prodi[strcspn(data[i].prodi, "\n")] = '\0';

        printf("IPK    : ");
        scanf("%f", &data[i].ipk);
        bersihkanBufferInput();
    }

    return data;
}

void simpanKeFileCSV(Mahasiswa *mhs, int jumlah, const char *namaFile) {
    FILE *fp = fopen(namaFile, "a");
    if (!fp) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
    }

    fprintf(fp, "nim,nama,prodi,ipk\n");

    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%s,%s,%s,%.2f\n",
                mhs[i].nim, mhs[i].nama, mhs[i].prodi, mhs[i].ipk);
    }

    fclose(fp);
    printf("\nData berhasil disimpan ke file '%s'\n", namaFile);
}

void bacaDariFileCSV(const char *namaFile) {
    FILE *fp = fopen(namaFile, "r");
    if (!fp) {
        printf("File '%s' tidak ditemukan!\n", namaFile);
        return;
    }

    char baris[256];
    int barisKe = 0;

    printf("\n=== Data Mahasiswa dari File ===\n");

    while (fgets(baris, sizeof(baris), fp)) {
        if (barisKe == 0) {
            printf("%s", baris); 
        } else {
            printf("%s", baris); 
        }
        barisKe++;
    }

    fclose(fp);
}

void bersihkanBufferInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

MataKuliah* inputMataKuliah(int *jumlah) {
    printf("Masukan jumlah mata kuliah: ");
    scanf("%d", jumlah);
    bersihkanBufferInput();

    MataKuliah *mk = malloc((*jumlah) * sizeof(MataKuliah));
    if (!mk) {
       printf("Alokasi memori gagal!\n");
        exit(EXIT_FAILURE); 
    }

    for (int i = 0; i < *jumlah; i++){
        printf("\nMata Kuliah #%d\n", i + 1);

        printf("Kode : ");
        fgets(mk[i].kode, 10, stdin);
        mk[i].kode[strcspn(mk[i].kode, "\n")] = '\0';

        printf("Nama : ");
        fgets(mk[i].nama, 100, stdin);
        mk[i].nama[strcspn(mk[i].nama, "\n")] = '\0';

        printf("SKS : ");
        scanf("%d", &mk[i].sks);
        bersihkanBufferInput();
    }


    return mk;
}

void simpanMataKuliahCSV(MataKuliah *mk, int jumlah, const char *namaFile) {
    FILE *fp = fopen(namaFile, "w");
    if (!fp) {
        printf("Gagal membuka file!\n");
        return;
    }

    fprintf(fp, "Kode,Nama,SKS\n");

    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%s,%s,%d\n", mk[i].kode, mk[i].nama, mk[i].sks);
    }

    fclose(fp);
    printf("Data mata kuliah berhasil disimpan ke file '%s'!\n", namaFile);
}

void bacaMataKuliahCSV(const char *namaFile) {
    FILE *fp = fopen(namaFile, "r");
    if (!fp) {
        printf("File '%s' tidak ditemukan!\n", namaFile);
        return;
    }

    char baris[256];
    int barisKe = 0;

    printf("\n=== DATA MATA KULIAH DARI FILE ===\n");

    while (fgets(baris, sizeof(baris), fp)) {
        printf("%s", baris);
        barisKe++;
    }

    fclose(fp);
}

int loadMataKuliah(MataKuliah *mk, const char *namaFile) {
    FILE *fp = fopen(namaFile, "r");
    if (!fp) {
        printf("File '%s' tidak ditemukan!\n", namaFile);
        return 0;
    }

    char baris[256];
    int count = 0;

    fgets(baris, sizeof(baris), fp);  // Lewati header

    while (fgets(baris, sizeof(baris), fp)) {
        sscanf(baris, "%9[^,],%99[^,],%d", mk[count].kode, mk[count].nama,&mk[count].sks); count++;
    }

    fclose(fp);
    return count;
}

void tampilkanDaftarMK(MataKuliah *mk, int jumlah) {
    printf("\n=== DAFTAR MATA KULIAH ===\n");
    for (int i = 0; i < jumlah; i++) {
        printf("%d. %s - %s - %d SKS\n", i + 1, mk[i].kode, mk[i].nama, mk[i].sks);
    }
}

void inputKRS(KRS *k, MataKuliah *mk, int jumlahMK) {
    printf("Masukkan NIM Mahasiswa: ");
    fgets(k->nimMahasiswa, 20, stdin);
    k->nimMahasiswa[strcspn(k->nimMahasiswa, "\n")] = '\0';
    bersihkanBufferInput();

    printf("Jumlah mata kuliah yang diambil: ");
    scanf("%d", &k->jumlahMatkul);
    bersihkanBufferInput();

    for (int i = 0; i < k->jumlahMatkul; i++) {
        int pilih;
        printf("Pilih matkul ke-%d (1-%d): ", i + 1, jumlahMK);
        scanf("%d", &pilih);
        bersihkanBufferInput();

        if (pilih < 1 || pilih > jumlahMK) {
            printf("Pilihan tidak valid!\n");
            i--;
            continue;
        }

        strcpy(k->kodeMatkul[i], mk[pilih - 1].kode);
        strcpy(k->namaMatkul[i], mk[pilih - 1].nama);
    }

    printf("\nKRS berhasil dibuat\n");
}

void simpanKRSCsv(KRS *k, const char *namaFile) {
    FILE *fp = fopen(namaFile, "a");
    if (!fp) {
        printf("Gagal membuka file KRS!\n");
        return;
    }

    for (int i = 0; i < k->jumlahMatkul; i++) {
        fprintf(fp, "%s,%s,%s\n", k->nimMahasiswa, k->kodeMatkul[i], k->namaMatkul[i]);
    }
    
    fclose(fp);
    printf("KRS berhasil disimpan ke file '%s'!\n", namaFile);
}    