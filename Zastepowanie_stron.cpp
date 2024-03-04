#include <iostream>
#include <fstream>
using namespace std;

void FIFO()
{
    int pages[] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 1, 2, 0 }; // Tablica stron
    int cache_size = 3;  // Liczba ramek w pamieci podrecznej
    int page_faults = 0;  // Zmienna uzywana do sledzenia liczby bledow stron
    int cache[10000];  // Tablica reprezentujaca pamiec podreczna
    int page_number;
    int cache_hits = 0; // Zmienna do sledzenia liczby trafien
    int j;

    page_number = sizeof(pages) / sizeof(pages[0]); // Obliczanie ilosci stron

    cout << "Kolejka \t Pamiec podreczna" << endl;
    for (int i = 0; i < cache_size; i++)
        cache[i] = -1; // Inicjalizacja pamieci podrecznej na -1, co oznacza pusta ramke
    for (int i = 0; i < page_number; i++) {
        
        for ( j = 0; j < cache_size; j++)
            if (cache[j] == pages[i]) {  // Sprawdzanie czy strona jest juz w pamieci podrecznej
                cache_hits++; // Jesli tak to zwiekszanie liczby trafien
                break;
            }
        if (j == cache_size) { // Jesli strona nie jest w pamieci podrecznej
            cache[page_faults % cache_size] = pages[i]; // Usuwam istniejaca strone zeby zrobic miejsce dla nowej
            page_faults++; // Zwiekszanie liczby bledow stron
        }
        cout << pages[i] << "\t\t";
        for (int k = 0; k < cache_size; k++)        //wypisywanie ramki
        {
            if (cache[k] != -1)
                cout << cache[k] << " ";
            else
                cout << "- ";
        }
        cout << endl;
    }
    cout << "\t\t FIFO " << endl;
    cout << "Ilosc bledow stron: " << page_faults << endl;
    cout << "Ilosc trafien: " << cache_hits << endl; // Wypisanie liczby trafien
   

    //zapisywanie do pliku
    ofstream zapis;
    zapis.open("FIFO_wyniki.txt", ios::app);
    zapis << "\t\t FIFO " << endl;
    zapis << "Ilość ramek:  " << cache_size << endl;
    zapis << "Ilosc bledow stron: " << page_faults << endl;
    zapis << "Ilosc trafien: " << cache_hits << endl;
    zapis.close();
}

void LRU()
{
    int cache[10000], page_faults = 0, cache_hits = 0;
    int pages[] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 1, 2, 0 }; // Tablica stron
    int cache_size =3;  // Liczba ramek w pamieci podrecznej
    int page_number;
    page_number = sizeof(pages) / sizeof(pages[0]);
   

    for (int i = 0; i < cache_size; i++)
        cache[i] = -1; // zainicjuj każdy element tablicy "cache" na -1, co oznacza pustą ramkę

    int time[10000];
    for (int i = 0; i < page_number; i++)
        time[i] = 0;
    // inicjuj tablicę "time" 

    cout << "Strona\t Pamiec podreczna" << endl;
    for (int i = 0; i < page_number; i++)           //Pętla przechodzi przez każdą stronę w tablicy "pages"
    {
        int j;
        for (j = 0; j < cache_size; j++)                //Pętla sprawdza, czy bieżąca strona jest już w pamięci podręcznej. 
                                                        //Jeśli tak, to licznik trafień (cache_hits) jest zwiększany i aktualizuje się czas dostępności danej strony.
        {
            if (cache[j] == pages[i])
            {
                cache_hits++;
                time[j] = i;
                break;
            }
        }

        if (j == cache_size)
        {
            int least_time = INT_MAX;                               //Jeśli bieżąca strona nie znajduje się w pamięci podręcznej, to pętla szuka najstarszej strony, 
                                                                    //która jest już w pamięci podręcznej i jest gotowa do usunięcia.
            int least_time_index;
            for (int j = 0; j < cache_size; j++)    
            {
                if (time[j] < least_time)
                {
                    least_time = time[j];
                    least_time_index = j;
                }
            }
            cache[least_time_index] = pages[i];                 //Strona jest wstawiana do pamięci podręcznej w miejscu najstarszej strony 
                                                                //i licznik błędów stron (page_faults) jest zwiększany.
            time[least_time_index] = i;
            page_faults++;                              
        }

        cout << pages[i] << "\t\t";                      //   Wypisuje bieżącą stronę oraz zawartość pamięci podręcznej.
        for (int k = 0; k < cache_size; k++)
        {
            if (cache[k] != -1)
                cout << cache[k] << " ";
            else
                cout << "- ";
        }
        cout << endl;
    }
    cout << "\t\t LRU " << endl;
    cout << "Liczba bledow stron: " << page_faults << endl;
    cout << "Liczba trafien: " << cache_hits << endl; // Wypisanie liczby trafień

    //zapisywanie do pliku
    ofstream zapis;
    zapis.open("LRU_wyniki.txt", ios::app);
    zapis << "\t\t LRU " << endl;
    zapis << "Ilość ramek:  " << cache_size << endl;
    zapis << "Ilosc bledow stron: " << page_faults << endl;
    zapis << "Ilosc trafien: " << cache_hits << endl;
    zapis.close();
}



int main()
{
    int check;
    cout << "Ktory algorytm chcesz uzyc? 1-FIFO 2-LRU ";
    cin >> check;

    switch(check) 
    {
    case 1:
        FIFO();
        break;
    case 2:
        LRU();
        break;
    }
   
    
    return 0;


}