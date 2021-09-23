#pragma once

#include "Pencere.hpp"
#include "Buton.hpp"
#include "Sahne.hpp"
#include"Karakter.hpp"

class Oyun
{
public:
	Oyun();
	~Oyun();
	void btnYeniOyunTikla();
	void btnCikisTikla();
	void girisKontrol();
	void sahneGuncelle();
	void sahneCiz();
	void saatiYenidenBaslat();
	bool bittimi();
	void menuAyarla();
	void menuCiz();
	void MermiHareket();
	void DusmanHareket();
	void DusmanOlustur();
	void DusmanVuruldumu();
	void KullaniciVuruldumu();
private:
	int			m_dusmanAraligi;
	int			m_mermiAraligi;
	Pencere		m_pencere;
	Buton		m_btnYeniOyun;
	Buton		m_btnCikis;
	Sahne		m_sahne;

	sf::Font	m_font;
	sf::Clock	m_saat;
	sf::Time	m_gecenSure;
	sf::Texture yildiz;
	sf::Sprite yildizSprite;
	sf::Vector2f			m_vurulanDusman;
	Karakter	m_ucak;
	Karakter	m_efekt;
	
	std::vector<Karakter>	m_mermiler;
	std::vector<Karakter>	m_dusmanlar;

	bool		m_carpismaOldumu;
	int			m_mermiSayisi;
	int			m_cerceveSayisi;
	int			artis;
	bool		m_kapalimi;
	bool		m_yeniOyunTiklandimi;
	float		m_cerceveSuresi;
	float		m_hucreBoyutu;
	float		m_alinanMesafe;
};