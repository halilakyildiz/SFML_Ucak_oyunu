#include "Karakter.hpp"
#include<iostream>

Karakter::Karakter()
{
	//m_aktifAnimasyon = "sabit";
	m_konum.x = 300;
	m_konum.y = 630;
	m_durum = true;
	m_animasyonlar = new Animasyon[2];
	//m_animasyonlar[m_aktifAnimasyon].konum(m_konum);
	//m_animasyon.konum(m_konum);
	m_animasyonlar[m_aktifAnimasyon].konum(m_konum);
	m_animasyonSayisi = 0;
	m_aktifAnimasyon = 0;
	m_karakterIsim = "";
}

Karakter::~Karakter()
{
}

void Karakter::olustur(sf::String dizin,int resim_sayisi, sf::Vector2i konum, sf::Vector2i size,int baslangic, sf::String isim)
{
	m_karakterIsim = isim;
	float boyut; 
	if (isim!="mermi" && isim!="efekt")
		boyut = (float)50 / size.x;
	else if(isim=="efekt")
		boyut = (float)60 / size.x;
	else
		boyut = (float)5 / size.x;

	if (isim == "dusman")
		boyut *= -1;

	m_karakterPixelGenislik = size.x*boyut;
	m_karakterPixelYukseklik = size.y*boyut;
	if (m_animasyonSayisi == 0) {
		if (resim_sayisi > 1) {

			m_kaplama = new sf::Texture[resim_sayisi];

			for (int i = 0; i < resim_sayisi; i++) {
				sf::Image resim;

				if(baslangic)
					resim.loadFromFile(dizin + std::to_string(i + 1) + ".png");
				else
					resim.loadFromFile(dizin + std::to_string(i) + ".png");
				auto renk = resim.getPixel(0, 0);
				resim.createMaskFromColor(renk);
				m_kaplama[i].loadFromImage(resim);

			}
			m_animasyonlar[m_animasyonSayisi].olustur(m_kaplama, resim_sayisi,boyut, konum, size);
			m_animasyonSayisi++;
		}
		else {
			m_kaplama = new sf::Texture[resim_sayisi];
			sf::Image resim;
			resim.loadFromFile(dizin);
			auto renk = resim.getPixel(0, 0);
			resim.createMaskFromColor(renk);
			m_kaplama[0].loadFromImage(resim);

			m_animasyonlar[m_animasyonSayisi].olustur(m_kaplama, resim_sayisi,boyut, konum, size);
			m_animasyonSayisi++;
		}
	}
	//*********************************************************************************************************
	else {

			if (resim_sayisi > 1) {

				m_kaplama2 = new sf::Texture[resim_sayisi];

				for (int i = 0; i < resim_sayisi; i++) {
					sf::Image resim;

					if (baslangic)
						resim.loadFromFile(dizin + std::to_string(i + 1) + ".png");
					else
						resim.loadFromFile(dizin + std::to_string(i) + ".png");
					auto renk = resim.getPixel(0, 0);
					resim.createMaskFromColor(renk);
					m_kaplama2[i].loadFromImage(resim);

				}
				m_animasyonlar[m_animasyonSayisi].olustur(m_kaplama2, resim_sayisi,boyut, konum, size);
				m_animasyonSayisi++;
			}
			else {
				m_kaplama2 = new sf::Texture[resim_sayisi];
				sf::Image resim;
				resim.loadFromFile(dizin);
				auto renk = resim.getPixel(0, 0);
				resim.createMaskFromColor(renk);
				m_kaplama2[0].loadFromImage(resim);

				m_animasyonlar[m_animasyonSayisi].olustur(m_kaplama2, resim_sayisi,boyut, konum, size);
				m_animasyonSayisi++;
			}		
	}
}

void Karakter::Ciz(sf::RenderWindow & pencere)
{
	m_animasyonlar[m_aktifAnimasyon].ciz(pencere);
}

void Karakter::animasyonGuncelle()
{
	//m_animasyonlar[m_aktifAnimasyon].guncelle();
	m_animasyonlar[m_aktifAnimasyon].guncelle();
}

void Karakter::SagaGit()
{
	if (m_konum.x <= 400- m_karakterPixelGenislik) {
		m_konum.x += 3;
		//m_animasyonlar[m_aktifAnimasyon].konum(m_konum);
		m_animasyonlar[m_aktifAnimasyon].konum(m_konum);
	}
}
void Karakter::YukariGit()
{
	if (m_konum.y >= 0) {
		m_konum.y -= 3;
		//m_animasyonlar[m_aktifAnimasyon].konum(m_konum);
		m_animasyonlar[m_aktifAnimasyon].konum(m_konum);
		m_animasyonlar[m_aktifAnimasyon + 1].konum({ m_konum.x - 20,m_konum.y });
	}
	else
		m_durum = false;		
}
void Karakter::SolaGit()
{
	if (m_konum.x >= 0) {
		m_konum.x -= 3;
		//m_animasyonlar[m_aktifAnimasyon].konum(m_konum);
		m_animasyonlar[m_aktifAnimasyon].konum(m_konum);
	}	
}
void Karakter::Sil()
{
	delete[] m_kaplama;
	//delete[] m_animasyonlar;
}
sf::Vector2f Karakter::KonumGetir()
{
	return m_konum;
}
int Karakter::GenislikGetir()
{
	return m_karakterPixelGenislik;
}
int Karakter::YukseklikGetir()
{
	return m_karakterPixelYukseklik;
}
void Karakter::AsagiGit()
{
	if (m_konum.y <= 700 - m_karakterPixelYukseklik) {
		m_konum.y += 3;
		//m_animasyon.konum(m_konum);
		m_animasyonlar[m_aktifAnimasyon].konum(m_konum);
	}
}
void Karakter::Konum(sf::Vector2f konum)
{
	m_konum = konum;
	m_animasyonlar[m_aktifAnimasyon].konum(m_konum);
	//m_animasyon.konum(m_konum);
}
bool Karakter::DurumGetir()
{
	return m_durum;
}
void Karakter::DurumAta(bool d)
{
	m_durum = d;
	if (m_animasyonSayisi == 1)
		m_animasyonlar[0].DurumAta(d,false);
	else {
		m_animasyonlar[0].DurumAta(d,false);
		m_animasyonlar[1].DurumAta(!d, true);
	}
}
void Karakter::solaYuru()
{
}
//void Karakter::solaYuru()
//{
//	m_aktifAnimasyon = "solaYuru";
//	m_konum.x -= 1;
//}
//
//void Karakter::sagaYuru()
//{
//	m_aktifAnimasyon = "sagaYuru";
//	m_konum.x += 1;
//}
//
//void Karakter::sabit()
//{
//	m_aktifAnimasyon = "sabit";
//}
