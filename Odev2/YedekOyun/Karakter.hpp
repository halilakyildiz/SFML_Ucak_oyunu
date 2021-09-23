#pragma once
#include "Animasyon.hpp"
#include <vector>

class Karakter
{
public:
	Karakter();
	~Karakter();
	void olustur(sf::String dosyaIsmi, int resim_sayis,sf::Vector2i konum,sf::Vector2i size,int baslangic,sf::String);
	void Ciz(sf::RenderWindow& pencere);
	void animasyonGuncelle();
	void SolaGit();
	void Sil();
	sf::Vector2f KonumGetir();
	int GenislikGetir();
	int YukseklikGetir();
	void SagaGit();
	void YukariGit();
	void AsagiGit();
	void Konum(sf::Vector2f);
	bool DurumGetir();
	void DurumAta(bool);
	void solaYuru();
	void sagaYuru();
	void sabit();
private:
	int						m_karakterPixelGenislik, m_karakterPixelYukseklik;
	bool					m_durum;
	int						m_animasyonSayisi;
	int						m_aktifAnimasyon;
	sf::String				m_karakterIsim;

	sf::Vector2f			m_konum;
	
	sf::Texture				*m_kaplama;
	sf::Texture				*m_kaplama2;
	//Animasyon				m_animasyon;
	Animasyon				*m_animasyonlar;
	std::vector<sf::Sprite>		resimler;
};
