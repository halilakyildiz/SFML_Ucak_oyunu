#include "Animasyon.hpp"
#include<iostream>
Animasyon::Animasyon()
{
	m_spriteSayisi = 0;
	m_spriteIndeks = 0;
	m_konum = sf::Vector2f(0, 0);
	m_durum = true;
	m_hazirla = false;
}

void Animasyon::ciz(sf::RenderWindow& pencere)
{
	if (m_durum) {
		/*if (m_hazirla) {
			if (m_spriteIndeks == m_spriteSayisi)
				m_durum = false;
		}
		m_spriteIndeks++;
		if (m_spriteIndeks == m_spriteSayisi)
			m_spriteIndeks = 0;*/
		m_spriteListesi[m_spriteIndeks].setPosition(m_konum);
		//std::cout << "index : " << m_spriteIndeks << std::endl;
		pencere.draw(m_spriteListesi[m_spriteIndeks]);
	}
	
}

void Animasyon::olustur(sf::Texture kaplama[],int sayi,float boyut, sf::Vector2i konum, sf::Vector2i size) {
	
	
	//std::cout << boyut << std::endl;
	//if (sayi > 1) {
		for (int k = 0; k < sayi; k++) {
			sf::Sprite sprite;
			sprite.setTexture(kaplama[k]);
			sprite.setTextureRect(sf::IntRect(konum, size));
		//	sprite.setTextureRect(sf::IntRect({ 25,30 }, { 448,482 }));
			sprite.setScale({ boyut,boyut });
			/*if (boyut < 0)
				sprite.setOrigin(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);*/
			
			m_spriteListesi.push_back(sprite);
		}

		m_spriteSayisi = sayi;
}


void Animasyon::guncelle()
{	
	if (m_durum) {
		if (m_hazirla) {
			if (m_spriteIndeks == m_spriteSayisi)
				m_durum = false;
		}		
			m_spriteIndeks++;
			if (m_spriteIndeks == m_spriteSayisi)
				m_spriteIndeks = 0;	
		
	}
	
	//m_spriteIndeks = (m_spriteIndeks) % m_spriteSayisi;

}

void Animasyon::DurumAta(bool d,bool h)
{
	m_durum = d;
	m_hazirla = h;
}

void Animasyon::konum(sf::Vector2f konum)
{
	//konum.y -= m_spriteListesi[0].getLocalBounds().height;
	m_konum = konum;
}

sf::Vector2f Animasyon::boyutGetir()
{
	sf::Vector2f boyut(m_spriteListesi[0].getLocalBounds().width,
		m_spriteListesi[0].getLocalBounds().height);
	return boyut;
}
