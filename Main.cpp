#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>

class Studentas {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> pazymiai;
    int egzaminas;
    mutable double galutinis;
    bool naudotiVidurki;

public:
    Studentas(const std::string& vardas, const std::string& pavarde, const std::vector<int>& pazymiai, int egzaminas)
        : vardas(vardas), pavarde(pavarde), pazymiai(pazymiai), egzaminas(egzaminas), naudotiVidurki(true) {}

    void SetNaudotiVidurki(bool naudoti) {
        naudotiVidurki = naudoti;
    }

    void SkaiciuotiGalutiniBala() const {
        if (naudotiVidurki) {
            double suma = 0.0;
            for (int pazymys : pazymiai) {
                suma += pazymys;
            }
            double vidurkis = suma / pazymiai.size();
            galutinis = 0.4 * vidurkis + 0.6 * egzaminas;
        }
        else {
            std::vector<int> temp_pazymiai = pazymiai;
            std::sort(temp_pazymiai.begin(), temp_pazymiai.end());

            if (temp_pazymiai.size() % 2 == 0) {
                int index1 = temp_pazymiai.size() / 2 - 1;
                int index2 = temp_pazymiai.size() / 2;
                galutinis = 0.4 * (temp_pazymiai[index1] + temp_pazymiai[index2]) / 2 + 0.6 * egzaminas;
            }
            else {
                int index = temp_pazymiai.size() / 2;
                galutinis = 0.4 * temp_pazymiai[index] + 0.6 * egzaminas;
            }
        }
    }

    void SpausdintiDuomenis() const {
        std::cout << pavarde << "\t\t" << vardas << "\t\t" << std::fixed << std::setprecision(2) << galutinis;
        if (naudotiVidurki) {
            std::cout << " (Vid.)";
        }
        else {
            std::cout << " (Med.)";
        }
        std::cout << std::endl;
    }

    static Studentas GeneruotiAtsitiktiniusDuomenis() {
        std::string vardas = "Vardas";
        std::string pavarde = "Pavarde";
        std::vector<int> pazymiai;
        for (int i = 0; i < 5; ++i) {
            pazymiai.push_back(1 + rand() % 10);
        }
        int egzaminas = 1 + rand() % 10;
        return Studentas(vardas, pavarde, pazymiai, egzaminas);
    }
};

int main() {
    std::vector<Studentas> studentai;

    char pasirinkimas;
    std::cout << "Ar norite patys ivesti duomenis (Iveskite 'P') ar juos sugeneruoti atsitiktinai (Iveskite 'S')? ";
    std::cin >> pasirinkimas;

    if (pasirinkimas == 'P' || pasirinkimas == 'p') {
        // ... (jūsų esamas kodas vartotojo įvedimui)
    }
    else if (pasirinkimas == 'S' || pasirinkimas == 's') {
        std::cout << "Generuojami atsitiktiniai duomenys." << std::endl;
        std::cout << "Iveskite kiek studentu sugeneruoti: ";
        int kiekis;
        std::cin >> kiekis;

        srand(time(NULL));
        for (int i = 0; i < kiekis; ++i) {
            studentai.push_back(Studentas::GeneruotiAtsitiktiniusDuomenis());
        }
    }

    // Leidžiame vartotojui pasirinkti balo skaičiavimo metodą
    char baloSkaiciavimoMetodas;
    std::cout << "Pasirinkite balo skaičiavimo metodą (V - vidurkis, M - mediana): ";
    std::cin >> baloSkaiciavimoMetodas;

    // Skaičiuojame galutinius balus ir juos išvedame
    for (Studentas& studentas : studentai) {
        studentas.SetNaudotiVidurki((baloSkaiciavimoMetodas == 'V' || baloSkaiciavimoMetodas == 'v'));
        studentas.SkaiciuotiGalutiniBala();
        studentas.SpausdintiDuomenis();
    }

    return 0;
}
