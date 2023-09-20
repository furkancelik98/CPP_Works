/*

Metin Ters Çevirme Programı
Bu program, kullanıcının girdiği metni ters çevirir, metindeki kelime sayısını ve karakter sayısını hesaplar, ardından sonuçları ekrana yazdırır.

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream> // <sstream> başlık dosyasını eklemeyi unutmayın

std::string tersCevir(const std::string& metin) {
    std::string tersMetin = metin;
    std::reverse(tersMetin.begin(), tersMetin.end());
    return tersMetin;
}

int main() {
    std::string girilenMetin;

    std::cout << "Lütfen bir metin girin: ";
    std::getline(std::cin, girilenMetin);

    std::string tersMetin = tersCevir(girilenMetin);
    std::cout << "Ters Çevrilmiş Metin: " << tersMetin << std::endl;

    std::vector<std::string> kelimeler;
    std::istringstream iss(girilenMetin); // Sorun giderildi
    std::string kelime;
    while (iss >> kelime) {
        kelimeler.push_back(kelime);
    }
    int kelimeSayisi = kelimeler.size();

    int karakterSayisi = girilenMetin.length();

    std::cout << "Kelime Sayısı: " << kelimeSayisi << std::endl;
    std::cout << "Karakter Sayısı: " << karakterSayisi << std::endl;

    return 0;
}
