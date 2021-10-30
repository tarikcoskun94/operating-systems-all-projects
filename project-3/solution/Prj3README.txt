/*
* Author Tarık COŞKUN
* Number 152120161092
* E-mail tarikcoskun@hotmail.com.tr
*/



KARŞILAŞTIRMA	: Uygulamayı yapmadan önce beklentim, işlemlerin threadlere verilerek daha kısa süreceği yönündeydi. Fakat uygulamayı
		  çalıştırıp süreleri kıyasladığım zaman multi-thread olarak daha yavaş çalıştığını gözlemledim. Farklı dizi uzunlukları
		  ile testler yaptım. Çıkarımım ise,"Divide-Conquer and Merge" şeklinde işleyen algoritmaların tamamının multi-thread
		  yapıda daha yavaş çalışacağıdır. Çünkü her threadin ürettiği sonucun da kendi arasında tekrar bir merge işlemine tabii
		  olması gerekiyor. Yani (n) tane thread üzerine işlemleri bölersek, en son adım olarak (n-1) tane de merge işlemi yapmak
		  zorundayız. Sonuç olarak, paralelleştrilmeye uygun, ancak paralelleştirildiği takdirde zaman kazandırmaktan ziyade küçük
		  bir miktar zaman bile keybettirdiğini gözlemledim.



Dosyaların Listesi
_________________________________________________________________________________________________________________________________________



1)MergesortSingle.cpp		:   AÇIKLAMA	: Tek bir thread üzerinden sıralama yaptıran uygulama.
 *
 *
 * DERLEME			:       g++ MergesortSingle.cpp -pthread
 * BAŞLATMA			:       ./a.out



2)MergesortMulti.cpp		:   AÇIKLAMA	: 2 ve 3 adet thread seçenekleri ile sıralama yaptıran uygulama.
 *
 *
 * DERLEME			:       g++ MergesortMulti.cpp -pthread
 * BAŞLATMA			:       ./a.out



8)Prj3header.h			: Gerekli header dosyaları



9)Output.txt			: Konsol ekranı çıktıları. Değişik dizi uzunlukları ile test edilmiş çıktı sonuçlarını barındırır.



10) Prj1README.txt		: Dosyaların Listesi
