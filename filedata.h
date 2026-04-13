#define MAX_NAME_LEN 100
#define MAX_PRODI_LEN 50
#define FILE_NAME "data_mahasiswa.csv"

typedef struct {
    char nim[20];
    char nama[MAX_NAME_LEN];
    char prodi[MAX_PRODI_LEN];
    float ipk;
} Mahasiswa;

Mahasiswa* inputDataMahasiswa(int *jumlah);
void simpanKeFileCSV(Mahasiswa *mhs, int jumlah, const char *namaFile);
void bacaDariFileCSV(const char *namaFile);
int loadMahasiswa(Mahasiswa *m, const char *namaFile);
void bersihkanBufferInput();

typedef struct {
    int sks;
    char kode[10];
    char nama[100];
} MataKuliah;

MataKuliah* inputMataKuliah(int *jumlah);
void simpanMataKuliahCSV(MataKuliah *mk, int jumlah, const char *namafile);
void bacaMataKuliahCSV(const char *namafile);

int loadMataKuliah(MataKuliah *mk, const char *namaFile);
void tampilkanDaftarMK(MataKuliah *mk, int jumlah);

typedef struct {
    char nimMahasiswa[20];
    int jumlahMatkul;
    char kodeMatkul[20][10];
    char namaMatkul[20][100];
} KRS;

void inputKRS(KRS *k, MataKuliah *mk, int jumlahMK);
void simpanKRSCsv(KRS *k, const char *namaFile);
