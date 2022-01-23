#ifndef SCENA_H
#define SCENA_H
#include "Torgraf.h"
#include "Autograf.h"
#include "Tor.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>

/** Klasa sceny ktora pojawi sie w wyswietlanym oknie */
class Scena : public QGraphicsScene
{
private:
    Torgraf *torgraf;
    Auto *car;
    QLabel *label;
    QGraphicsItem *item;
    std::vector<Autograf*> Autagraf;
    Autograf *autograf;
    QPushButton * start;
    QTableWidget *tabela;

public:
    /** Konstruktor klasy Scena ze wskzanikiem do klasy QT opisujacej sceny */
    Scena(QObject *parent);

    /** Metoda dodajaca tor na scene
     * @param wskaznik do toru logicznego */
    void dodajtor(Tor *tor);

    /** Metoda dodajaca auto na scene
     * @param car - wskaznik do auta
     * @param sc - sciezka do pliku grafiki auta
     * @param kierunek - startowy zwrot auta
     * */
    void dodajauto(Auto *car, QString sc, float kierunek);

    /** Metoda usuwajaca auto ze sceny
     * @param i - numer auta w vectorze aut graficznych*/
    void usunautograf(int i);

    /** Metoda pomocnicza przy inicjalizowaniu tabeli wynikow
     * @param t - liczba rzedow tabeli
     * */
    void inicjalizacjatabeli(int t);

    /** Metoda obslugujaca tabele
     * @param t- okresla nr rzedu w tabeli
     * @param okrazenie - okresla biezace okrazenie auta
     * @param czyukonczyl - informacja o tym czy dany kierowca ukonczyl wyscig
     * @param czypopsuty - informacja o tym czy dane auto sie popsulo
     * @param postep - postep ukonczenia biezacego okrazenia w porcentach
     * */
    void ustawpozycje(int t, std::string kierowca, int okrazenie, bool czyukonczyl, bool czypopsuty, int postep);

    /** Metoda sprawiajaca ze tabela wynikow pojawia sie na scenie
     * @param parametr okreslajacy wysokoc tabeli */
    void wlacztablicewynikow(float rozmiartab);

    /** Metoda sprawdzajaca biezace okrazenie oraz czy wyscig zostal zakonczony
     * @param t1 - nr biezacego okrazenia prowadzacego auta
     * @param t2 - nr biezacego okrazenia wyscigu
     * @param czykoniec - okresla czy ktoes auto ukonczylo wyscig lub wszystkie sie popsuly
     * */
    void progresokrazen(int t1, int t2, bool czykoniec);

    /** Getter vectora aut graficznych*/
    std::vector<Autograf*> getvectorautagraf() const;

    /** Getter auta graficznego
     * @param i - numer auta w vectorze
     * */
    Autograf* getautograf(int i) const;

    /** Getter przycisku startu */
    QPushButton* getstartbutton() const;






};

#endif // SCENA_H
