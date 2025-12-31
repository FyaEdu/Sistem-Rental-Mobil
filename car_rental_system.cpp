#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class Mobil
class Mobil {
private:
    string plat;
    string merk;
    string model;
    double harga_per_hari;
    bool tersedia;

public:
    // Constructor
    Mobil(string p, string m, string mdl, double harga) 
        : plat(p), merk(m), model(mdl), harga_per_hari(harga), tersedia(true) {}
    
    // Getter methods
    string get_plat() { return plat; }
    double get_harga() { return harga_per_hari; }
    bool is_tersedia() { return tersedia; }
    
    // Display info
    void get_info() {
        cout << "Plat: " << plat << " | Merk: " << merk 
             << " | Model: " << model << " | Harga: Rp" << harga_per_hari 
             << "/hari | Status: " << (tersedia ? "Tersedia" : "Disewa") << endl;
    }
    
    // Rental operations
    void sewa() { tersedia = false; }
    void kembalikan() { tersedia = true; }
};

// Class Pelanggan
class Pelanggan {
public:
    string nama;
    string ktp;
    
    Pelanggan(string n, string k) : nama(n), ktp(k) {}
    
    void get_info() {
        cout << "Nama: " << nama << " | KTP: " << ktp << endl;
    }
};

// Class TransaksiRental
class TransaksiRental {
private:
    Pelanggan* pelanggan;
    Mobil* mobil;
    int lama_sewa;
    string tanggal_mulai;
    double total_biaya;

public:
    TransaksiRental(Pelanggan* p, Mobil* m, int lama, string tanggal) 
        : pelanggan(p), mobil(m), lama_sewa(lama), tanggal_mulai(tanggal) {
        total_biaya = lama_sewa * mobil->get_harga();
    }
    
    void tampilkan_struk() {
        cout << "\n========== STRUK RENTAL MOBIL ==========" << endl;
        cout << "Pelanggan: " << pelanggan->nama << endl;
        cout << "Mobil: " << mobil->get_plat() << endl;
        cout << "Tanggal Mulai: " << tanggal_mulai << endl;
        cout << "Lama Sewa: " << lama_sewa << " hari" << endl;
        cout << "Total Biaya: Rp" << total_biaya << endl;
        cout << "========================================\n" << endl;
    }
};

// Class SistemRental
class SistemRental {
private:
    vector<Mobil*> daftar_mobil;
    vector<TransaksiRental*> daftar_transaksi;

public:
    void tambah_mobil(Mobil* mobil) {
        daftar_mobil.push_back(mobil);
        cout << "Mobil berhasil ditambahkan!" << endl;
    }
    
    void tampilkan_mobil() {
        cout << "\n=== DAFTAR MOBIL TERSEDIA ===" << endl;
        for (auto mobil : daftar_mobil) {
            if (mobil->is_tersedia()) {
                mobil->get_info();
            }
        }
        cout << endl;
    }
    
    void sewa_mobil(string plat, Pelanggan* pelanggan, int lama_sewa) {
        for (auto mobil : daftar_mobil) {
            if (mobil->get_plat() == plat && mobil->is_tersedia()) {
                mobil->sewa();
                TransaksiRental* transaksi = new TransaksiRental(
                    pelanggan, mobil, lama_sewa, "30-12-2024"
                );
                daftar_transaksi.push_back(transaksi);
                transaksi->tampilkan_struk();
                return;
            }
        }
        cout << "Mobil tidak tersedia atau tidak ditemukan!" << endl;
    }
    
    void kembalikan_mobil(string plat) {
        for (auto mobil : daftar_mobil) {
            if (mobil->get_plat() == plat) {
                mobil->kembalikan();
                cout << "Mobil " << plat << " berhasil dikembalikan!" << endl;
                return;
            }
        }
        cout << "Mobil tidak ditemukan!" << endl;
    }
};

// Main Program
int main() {
    // 1. Inisialisasi sistem
    SistemRental sistem;
    
    // 2. Tambah mobil ke inventaris
    Mobil* mobil1 = new Mobil("B1234XYZ", "Toyota", "Avanza", 350000);
    Mobil* mobil2 = new Mobil("B5678ABC", "Honda", "Jazz", 400000);
    Mobil* mobil3 = new Mobil("B9012DEF", "Suzuki", "Ertiga", 380000);
    
    sistem.tambah_mobil(mobil1);
    sistem.tambah_mobil(mobil2);
    sistem.tambah_mobil(mobil3);
    
    // 3. Tampilkan mobil tersedia
    sistem.tampilkan_mobil();
    
    // 4. Buat pelanggan
    Pelanggan* pelanggan1 = new Pelanggan("Budi Santoso", "3201234567890123");
    
    // 5. Sewa mobil
    sistem.sewa_mobil("B1234XYZ", pelanggan1, 3);
    
    // 6. Tampilkan mobil tersedia setelah rental
    sistem.tampilkan_mobil();
    
    // 7. Kembalikan mobil
    sistem.kembalikan_mobil("B1234XYZ");
    
    // 8. Tampilkan mobil tersedia setelah pengembalian
    sistem.tampilkan_mobil();
    
    return 0;
}
