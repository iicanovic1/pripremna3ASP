#include <iostream>
using std::cout;

template <typename T>
struct Cvor{
    T element;
    Cvor *sljedeci;

    Cvor (const T &element1, Cvor *sljedeci1 ):
            element(element1),sljedeci(sljedeci1){}
    Cvor(const Cvor &cvor){
        element=cvor.element;
        sljedeci=cvor.sljedeci;
    }


};

template <typename T> class Stek{
private:
    Cvor<T> *Vrh;
    int velicina;

public:
    Stek() : Vrh(nullptr) , velicina(0){}
    Stek(const Stek<T> &s);
    ~Stek(){ Unisti(); }
    void Unisti();
    Stek &operator = (const Stek<T> &s);
    void stavi(const T &element){
        Vrh = new Cvor<T>(element, Vrh); velicina++;
    }
    T skini();
    T &vrh()const;
    void brisi();
    bool JeLiPrazan() const {return Vrh == nullptr;}
    int brojElemenata()const {return  velicina;}
    template<typename T1>
    friend void ispisiStek ( Stek<T1> lista);

};

template<typename T>
void ispisiStek(Stek<T> stek) {
    std::cout << "Podaci liste ispod " << std::endl <<
              "duzina : " << stek.brojElemenata() <<std::endl ;
    if(stek.brojElemenata() == 0) {
        std::cout << "Prazan stek nista za prikazati" << std::endl;
        throw std::domain_error("Prazan stek nista za prikazati");
    }
    std::cout <<  "Elementi :" << std::endl;
    Cvor<T> * privremeni = stek.Vrh;
    while (privremeni != nullptr){
        std::cout << privremeni->element<<" ";
        privremeni = privremeni->sljedeci;
    }
    std::cout << "\n" << "Element na vrhu : " << stek.vrh() << "\n";
}

template<typename T>
T Stek<T>::skini() {
    if(Vrh == nullptr)
        throw std::domain_error("Prazan stek");
    T element(Vrh->element);
    Cvor<T> *p = Vrh->sljedeci;
    delete Vrh;
    Vrh = p;
    velicina--;
    return element;
}

template<typename T>
void Stek<T>::Unisti() {
    while (!JeLiPrazan())
        skini();
}

template<typename T>
T &Stek<T>::vrh() const {
    return Vrh->element;
}

template<typename T>
void Stek<T>::brisi() {
    this->Unisti();
}

template<typename T>
Stek<T>::Stek(const Stek<T> &s) {
    Cvor<T>* pomocniNova = nullptr;
    Cvor<T>* pomocniStara = s.Vrh;
    Vrh = nullptr;
    velicina = s.velicina;
    while (pomocniStara != nullptr){
        Cvor<T> * pomocniCvor = new Cvor<T>(pomocniStara->element, nullptr);
        if(Vrh == nullptr) Vrh = pomocniCvor;
        else pomocniNova->sljedeci = pomocniCvor;

        pomocniNova  = pomocniCvor;
        pomocniStara = pomocniStara->sljedeci;
    }
}

template<typename T>
Stek<T> &Stek<T>::operator=(const Stek<T> &s) {
    if(this == &s) return *this;
    brisi();
    Cvor<T>* pomocniNova = nullptr;
    Cvor<T>* pomocniStara = s.Vrh;
    Vrh = nullptr;
    velicina = s.velicina;
    while (pomocniStara != nullptr){
        Cvor<T> * pomocniCvor = new Cvor<T>(pomocniStara->element, nullptr);
        if(Vrh == nullptr) Vrh = pomocniCvor;
        else pomocniNova->sljedeci = pomocniCvor;

        pomocniNova  = pomocniCvor;
        pomocniStara = pomocniStara->sljedeci;
    }
    return *this;
}

//testtne FUNKCIJE

template <typename T>
bool testKonstruktoraSteka(){
    Stek<int> testniStek ;
    ispisiStek<int>(testniStek);
    return true;
}

template<typename T>
bool testStaviNaStek_VrhSteka_i_brojElemenata(){
    Stek<int> testniStek ;;
    testniStek.stavi(1);
    testniStek.stavi(2);
    testniStek.stavi(3);
    testniStek.stavi(4);
    ispisiStek<int>(testniStek);
    return true;
}

template<typename T>
bool testSkiniSaSteka() {
    Stek<int> testniStek;;
    testniStek.stavi(1);
    testniStek.stavi(2);
    testniStek.stavi(3);
    testniStek.stavi(4);
    ispisiStek<int>(testniStek);
    testniStek.skini();
    testniStek.skini();
    ispisiStek<int>(testniStek);
    return true;
}

template<typename T>
bool testBrisiStek() {
    Stek<int> testniStek;;
    testniStek.stavi(1);
    testniStek.stavi(2);
    testniStek.stavi(3);
    testniStek.stavi(4);
    ispisiStek<int>(testniStek);
    testniStek.brisi();
    ispisiStek<int>(testniStek);
    return true;
}
int main() {
    testKonstruktoraSteka<int>();
    testBrisiStek<int>();
    testSkiniSaSteka<int>();
    testStaviNaStek_VrhSteka_i_brojElemenata<int>();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
