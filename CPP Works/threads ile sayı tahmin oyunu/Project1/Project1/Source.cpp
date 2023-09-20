/*
Bu kod, basit bir "Sayı tahmin etme" oyununu temsil eder ve iki thread kullanır:
Birinci thread (RastgeleSayiUret) rastgele bir sayı üretir ve bu sayıyı rastgeleSayi değişkenine atar. Bu thread sadece bir kez 
çalışır ve oyunun başında rastgele bir sayı oluşturur. İkinci thread (KullaniciTahmin) kullanıcı ile etkileşimde bulunur. Kullanıcıdan 
tahminler alır ve bu tahminleri rastgeleSayi ile karşılaştırarak kullanıcıya bilgi verir. Oyuncu doğru tahminde bulunana veya oyun sona erdiğinde 
thread de sona erer. Thread'ler, aynı anda farklı görevleri gerçekleştirmek için kullanılır. Burada rastgele sayı üretme işlemi ve kullanıcı ile 
etkileşim işlemi farklı threadlerde çalışır. Thread kullanılarak oyunun daha interaktif ve hızlı çalışmasına olanak tanır. Örneğin, 
rastgele sayı üretimi kullanıcı tahminlerini beklerken arka planda gerçekleşebilir. "join" işlevleri, threadlerin ana thread tarafından 
beklendiği yere kadar çalışmasını engeller. Bu, her iki thread tamamlanmadan önce ana thread tarafından sonlandırılmamasını sağlar.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

bool oyunDevamEdiyor = true;
int rastgeleSayi;

void RastgeleSayiUret() {
    srand(time(0));
    rastgeleSayi = rand() % 100 + 1;
}

void KullaniciTahmin() {
    int tahmin;
    int denemeSayisi = 0;

    cout << "1 ile 100 arasinda bir sayiyi tahmin et!" << endl;

    while (oyunDevamEdiyor) {
        cout << "Tahmininizi girin: ";
        cin >> tahmin;

        denemeSayisi++;

        if (tahmin < rastgeleSayi) {
            cout << "Daha yuksek bir sayi tahmin edin." << endl;
        }
        else if (tahmin > rastgeleSayi) {
            cout << "Daha dusuk bir sayi tahmin edin." << endl;
        }
        else {
            cout << "Tebrikler! " << rastgeleSayi << " sayisini " << denemeSayisi << " denemede buldunuz." << endl;
            oyunDevamEdiyor = false;
        }
    }
}

int main() {
    thread rastgeleSayiThread(RastgeleSayiUret);
    thread kullaniciTahminThread(KullaniciTahmin);

    rastgeleSayiThread.join();
    kullaniciTahminThread.join();

    return 0;
}
