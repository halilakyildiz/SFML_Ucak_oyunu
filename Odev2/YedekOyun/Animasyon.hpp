#pragma once
#include<vector>
#include<SFML/Graphics.hpp>
#include <map>
enum class AnimasyonTuru { Sabit, Cok, Yuru, Zipla, IleriZipla, SabitYukariCapraz, SabitYukari, YuruCaprazYukari };
enum class YON { SOL = -1, SAG = 1 };
class Animasyon
{
public:
	Animasyon();
	void ciz(sf::RenderWindow& pencere);
	void olustur(sf::Texture kaplama[], int sayi, float boyut,sf::Vector2i,sf::Vector2i);
	/*void olustur(sf::Texture& kaplama,
		sf::Vector2i konum,
		sf::Vector2i boyut,
		int cerceveSayisi);*/
	void guncelle();
	void DurumAta(bool,bool);
	void konum(sf::Vector2f konum);
	sf::Vector2f boyutGetir();
private:
	bool					m_durum;
	bool					m_hazirla;
	std::vector<sf::Sprite> m_spriteListesi;
	unsigned  int			m_spriteSayisi;
	unsigned int			m_spriteIndeks;
	sf::Vector2f			m_konum;
};

typedef std::map< sf::String , Animasyon> AnimasyonHaritasi;