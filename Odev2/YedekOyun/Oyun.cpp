#include "Oyun.hpp"
#include<iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

bool kontrol = false;
Oyun::Oyun()
{
	m_cerceveSayisi = 0;
	m_dusmanAraligi = 0;
	//aplama.loadFromFile("./resimler/hero.png");
	m_mermiAraligi = 0;
	m_mermiSayisi = 0;
	m_kapalimi = false;
	m_carpismaOldumu = false;
	m_yeniOyunTiklandimi = false;

	m_cerceveSuresi = 1.0f / 60.0f;
	menuAyarla();
	artis = 0;
	auto boyut = m_pencere.pencereGetir().getSize();
	m_sahne.olustur(boyut.x, boyut.y, m_hucreBoyutu);

	m_ucak.olustur("./resimler/uzay/user/", 8, { 25,30 }, { 448,482 },1,"ucak");
	m_efekt.olustur("./resimler/uzay/Effects/1_", 17, { 58,48 }, { 172,144 }, 0, "efekt");
	m_efekt.Konum({ 20,20 });
	
}

Oyun::~Oyun()
{
	for (int i = 0; i < m_mermiler.size(); i++)
		m_mermiler[i].Sil();
}

void Oyun::btnYeniOyunTikla()
{
	m_yeniOyunTiklandimi = true;
}

void Oyun::btnCikisTikla()
{
	m_kapalimi = true;
}

void Oyun::girisKontrol()
{
	m_pencere.olayKontrol();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_ucak.SagaGit();

	//raket.raket_artis = 4.0f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_ucak.SolaGit();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_ucak.YukariGit();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_ucak.AsagiGit();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (m_mermiAraligi >= 15) {
			Karakter	m_MermiUcak;
			m_MermiUcak.olustur("./resimler/uzay/bullet.png", 1, { 46,24 }, { 34,96 },0,"mermi");
			m_MermiUcak.olustur("./resimler/uzay/Effects/1_", 17, { 58,48 }, { 172,144 }, 0,"efekt");
			auto konum = m_ucak.KonumGetir();
			m_MermiUcak.Konum({ konum.x + (m_ucak.GenislikGetir() / 2 - (0.3f * 46) / 2)+2,konum.y - (0.3f * 96) +15 });
			m_mermiler.push_back(m_MermiUcak);
			kontrol = true;
			m_mermiAraligi = 0;
		}
	}

}
int efekt_kontrol = 0;
void Oyun::sahneGuncelle()
{

	if (m_gecenSure.asSeconds() >= m_cerceveSuresi)
	{
		m_dusmanAraligi++;
		m_mermiAraligi++;
		girisKontrol();
		m_gecenSure = sf::seconds(0);
		if (m_cerceveSayisi > 6) {
			//k.animasyonGuncelle();
			if (kontrol) {
				for (int i = 0; i < m_mermiler.size(); i++) {
					if(m_mermiler[i].DurumGetir())
					m_mermiler[i].animasyonGuncelle();
				}
					
			}
			m_ucak.animasyonGuncelle();
			if (m_carpismaOldumu) {
				efekt_kontrol++;
				m_efekt.Konum(m_vurulanDusman);
				m_efekt.animasyonGuncelle();
				if (efekt_kontrol == 10) {
					efekt_kontrol = 0;
					m_carpismaOldumu = false;
				}
			}
			m_efekt.animasyonGuncelle();
			m_cerceveSayisi = 0;
			if (m_dusmanlar.size() > 0) {
				for (int i = 0; i < m_dusmanlar.size(); i++) {
					if (m_dusmanlar[i].DurumGetir())
						m_dusmanlar[i].animasyonGuncelle();
				}
			}
		}
		m_cerceveSayisi++;
		if (m_dusmanAraligi > 80) {
			DusmanOlustur();
			m_dusmanAraligi = 0;
		}			
		MermiHareket();
		DusmanHareket();
		DusmanVuruldumu() ;
		KullaniciVuruldumu();
		//dusman.AsagiGit();

	}
}

void Oyun::sahneCiz()
{
	m_pencere.cizimeBasla();
	if (m_yeniOyunTiklandimi)
	{
		m_sahne.ciz(m_pencere.pencereGetir());
		m_ucak.Ciz(m_pencere.pencereGetir());
		if (m_carpismaOldumu) {
			m_efekt.Ciz(m_pencere.pencereGetir());
		}
		
		if (kontrol) {
			for (int i = 0; i < m_mermiler.size(); i++) {
				if (m_mermiler[i].DurumGetir())
				m_mermiler[i].Ciz(m_pencere.pencereGetir());
			}
				
		}
		if (m_dusmanlar.size() > 0) {
			for (int i = 0; i < m_dusmanlar.size(); i++) {
				if (m_dusmanlar[i].DurumGetir())
					m_dusmanlar[i].Ciz(m_pencere.pencereGetir());
			}
				
		}
	}
	else
	{
		menuCiz();
	}
	m_pencere.cizimiBitir();
}

void Oyun::saatiYenidenBaslat()
{
	m_gecenSure += m_saat.restart();
}

bool Oyun::bittimi()
{
	if (m_kapalimi) {
		return true;
	}
	return m_pencere.kapandimi();
}



void Oyun::menuAyarla()
{
	auto fonk = std::bind(&Oyun::btnYeniOyunTikla, this);
	m_btnYeniOyun.tiklaFonksiyonuEkle(fonk);
	auto fonk1 = std::bind(&Oyun::btnCikisTikla, this);
	m_btnCikis.tiklaFonksiyonuEkle(fonk1);

	if (m_font.loadFromFile("alev.ttf") != false)
	{
		m_btnCikis.font(m_font);
		m_btnYeniOyun.font(m_font);
	}
	m_btnYeniOyun.renk(sf::Color::Red);
	m_btnCikis.renk(sf::Color::Red);

	m_btnYeniOyun.yazi("Yeni Oyun");
	m_btnCikis.yazi("Cikis");

	auto sahneBoyut = m_pencere.pencereGetir().getSize();
	auto btnBoyut = m_btnYeniOyun.boyutGetir();

	float x = (sahneBoyut.x - btnBoyut.x) / 2.0f;
	float y = (sahneBoyut.y - btnBoyut.y) / 2.0f;
	m_btnYeniOyun.konum(x, y);
	m_btnCikis.boyut(btnBoyut.x, btnBoyut.y);

	m_btnCikis.konum(x, y + 50);

	m_pencere.aracEkle(&m_btnYeniOyun);
	m_pencere.aracEkle(&m_btnCikis);
}

void Oyun::menuCiz()
{
	m_btnCikis.ciz(m_pencere.pencereGetir());
	m_btnYeniOyun.ciz(m_pencere.pencereGetir());
}

void Oyun::MermiHareket()
{
	for (int i = 0; i < m_mermiler.size(); i++) {
		m_mermiler[i].YukariGit();
	}
	//m_ucakMermi.YukariGit();
}

void Oyun::DusmanHareket()
{
	for (int i = 0; i < m_dusmanlar.size(); i++) {
		m_dusmanlar[i].AsagiGit();
	}
}

void Oyun::DusmanOlustur()
{
	Karakter	dusman;
	int random = rand() % 5;
	switch (random)
	{
	case 0:
		dusman.olustur("./resimler/uzay/yarasaucak/", 4, { 58,65 }, { 384,431 }, 1, "dusman");
		break;
	case 1:
		dusman.olustur("./resimler/uzay/comm/", 3, { 230,225 }, { 583,570 }, 1, "dusman");
		break;
	case 2:
		dusman.olustur("./resimler/uzay/smallship/", 5, { 70,28 }, { 483,521 }, 1, "dusman");
		break;
	case 3:
		dusman.olustur("./resimler/uzay/Spacebombs/", 3, { 53,63 }, { 158,113 }, 1, "dusman");
		break;
	case 4:
		dusman.olustur("./resimler/uzay/Spacemines/", 2, { 8,9 }, { 230,230 }, 1, "dusman");
		break;
	}
	//dusman.olustur("./resimler/uzay/yarasaucak/", 4, { 58,65 }, { 384,431 }, 1, "dusman");
	float x = rand() % (350-50+1)+50;
	dusman.Konum({ x,0 });
	m_dusmanlar.push_back(dusman);
}

void Oyun::DusmanVuruldumu()
{
	int dusman_pixel = 0;
	int mermi_pixel = 0;
	for (int i = 0; i < m_mermiler.size(); i++) {
		auto mermi_konum = m_mermiler[i].KonumGetir();
		mermi_pixel = m_mermiler[i].GenislikGetir();
		for (int j = 0; j < m_dusmanlar.size(); j++) {
			auto dusman_konum = m_dusmanlar[j].KonumGetir();
			dusman_pixel = m_dusmanlar[j].GenislikGetir();

			if (m_mermiler[i].DurumGetir() && m_dusmanlar[j].DurumGetir()) {
				if (mermi_konum.x + mermi_pixel >= dusman_konum.x
					&& mermi_konum.x <= dusman_konum.x
					&& mermi_konum.y <= dusman_konum.y) {

						m_carpismaOldumu = true;
						m_vurulanDusman = { m_dusmanlar[j].KonumGetir().x - m_efekt.GenislikGetir() / 2-20,m_dusmanlar[j].KonumGetir().y-m_efekt.GenislikGetir()/2-20 };
						m_mermiler[i].DurumAta(false);
						m_dusmanlar[j].DurumAta(false);
						//std::cout << "girdi\n";
						return;
				}
			}
		}
	}
}

void Oyun::KullaniciVuruldumu()
{
	int kullanici_pixel = 0;
	int dusman_pixel = 0;
	for (int i = 0; i < m_dusmanlar.size(); i++) {

		auto dusman_konum = m_dusmanlar[i].KonumGetir();
		dusman_pixel = m_dusmanlar[i].GenislikGetir();

		auto kullanici_konum = m_ucak.KonumGetir();
		kullanici_pixel = m_ucak.GenislikGetir();
		if (m_dusmanlar[i].DurumGetir()) {
			if (kullanici_konum.x <= dusman_konum.x &&
				kullanici_konum.x + kullanici_pixel >= dusman_konum.x + dusman_pixel &&
				dusman_konum.y >= kullanici_konum.y && dusman_konum.y <= kullanici_konum.y + kullanici_pixel) {
				std::cout << "girdi\n";
				m_kapalimi = true;
				return;
			}
		}
	}
}


