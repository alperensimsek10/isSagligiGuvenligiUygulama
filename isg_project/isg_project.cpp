#include <iostream>
using namespace std;

#define SIZE 10

struct Node {
    int id;
    string ad;
    string soyad;
    string bolum;
    Node *next;
};

struct IslemStack {
    Node *top = NULL;
    int count = 0;
};

struct GeriStack {
    int choices[SIZE];
    int ids[SIZE];
    string names[SIZE];
    string lastNames[SIZE];
    string departments[SIZE];

    int index = -1;
};

GeriStack gStack;

void ekle(IslemStack *stk, int id, string ad, string soyad, string bolum) {
    Node *ogrenci = new Node();
    ogrenci->id = id;
    ogrenci->ad = ad;
    ogrenci->soyad = soyad;
    ogrenci->bolum = bolum;

    if (stk->count == SIZE) {
        cout << "Kontenjan dolu, kayit yapilamadi!" << endl;
    } else if (stk->count == 0) {
        stk->top = ogrenci;
        stk->top->next = NULL;
        cout << id << " numarali ogrenci kursa kayit edildi" << endl;
        stk->count++;

        gStack.index++;
        gStack.ids[gStack.index] = id;
        gStack.names[gStack.index] = ad;
        gStack.lastNames[gStack.index] = soyad;
        gStack.departments[gStack.index] = bolum;

        gStack.choices[gStack.index] = 2;

    } else {
        ogrenci->next = stk->top;
        stk->top = ogrenci;
        cout << id << " numarali ogrenci kursa kayit edildi" << endl;
        stk->count++;

        gStack.index++;
        gStack.ids[gStack.index] = id;
        gStack.names[gStack.index] = ad;
        gStack.lastNames[gStack.index] = soyad;
        gStack.departments[gStack.index] = bolum;

        gStack.choices[gStack.index] = 2;
    }
}

void sil(IslemStack *stk) {
    if (stk->count == 0) {
        cout << "Kursta kayitli ogrenci yok" << endl;
    } else {
        gStack.index++;
        gStack.ids[gStack.index] = stk->top->id;
        gStack.names[gStack.index] = stk->top->ad;
        gStack.lastNames[gStack.index] = stk->top->soyad;
        gStack.departments[gStack.index] = stk->top->bolum;

        gStack.choices[gStack.index] = 1;

        cout << stk->top->id << " numarali ogrenci silindi" << endl;
        Node *temp = stk->top->next;
        delete stk->top;
        stk->top = temp;
        stk->count--;
    }
}

void yazdir(IslemStack *stk) {
    system("cls");
    if (stk->count == 0) {
        cout << "Kursta kayitli ogrenci yok" << endl;
    } else {
        Node *temp = stk->top;
        cout << "ISG kursuna kayitli ogrenciler: " << endl;
        while (temp != NULL) {
            cout << temp->id << " " << temp->ad << " " << temp->soyad << " " << temp->bolum << endl;
            temp = temp->next;
        }
    }
}

void geriAl(IslemStack *stk) {
    int id;
    string ad, soyad, bolum;

    id = gStack.ids[gStack.index];
    ad = gStack.names[gStack.index];
    soyad = gStack.lastNames[gStack.index];
    bolum = gStack.departments[gStack.index];

    int secim = gStack.choices[gStack.index];

    if (secim == 2) {
        cout << id << " numarali ogrencinin eklenmesi islemi geri alindi" << endl;
        Node *temp = stk->top->next;
        delete stk->top;
        stk->top = temp;
        stk->count--;
        gStack.choices[gStack.index] = -1;
    } else if (secim == 1) {
        Node *eleman = new Node();
        eleman->id = id;
        eleman->ad = ad;
        eleman->soyad = soyad;
        eleman->bolum = bolum;

        eleman->next = stk->top;
        stk->top = eleman;
        cout << id << " numarali ogrencinin silinme islemi geri alindi" << endl;
        stk->count++;
        gStack.choices[gStack.index] = -1;
    }
    if (secim == 0) {
        cout << "Lutfen islemi giriniz (EKLE/SIL)" << endl;
    }
    gStack.index--;
}

int main() {
    IslemStack iStack;
    GeriStack gStack;

    int id, secim;
    string ad, soyad, bolum;

    while (true) {
        cout << endl;
        cout << "ISG kurs kayit uygulamasi" << endl;
        cout << "1-- Ogrenci Ekle" << endl;
        cout << "2-- Ogrenci Sil" << endl;
        cout << "3-- Yazdir" << endl;
        cout << "4-- Geri Al" << endl;
        cout << "0-- CIKIS" << endl;
        cin >> secim;

        switch (secim) {
            case 1:
                cout << "ISG kursuna kayit edilecek ogrenci bilgilerini giriniz:" << endl;
                cout << " numara: "; cin >> id;
                cout << " ad: "; cin >> ad;
                cout << " soyad: "; cin >> soyad;
                cout << " bolum: "; cin >> bolum;
                ekle(&iStack, id, ad, soyad, bolum);
                break;

            case 2:
                sil(&iStack);
                break;

            case 3:
                yazdir(&iStack);
                break;

            case 4:
                geriAl(&iStack);
                break;

            case 0:
                cout << "Programdan cikiliyor..." << endl;
                return 0;

            default:
                cout << "Hatali Islem Yaptiniz" << endl;
                break;
        }
    }

    return 0;
}

