/*
* Author Tarık COŞKUN
* Number 152120161092
* E-mail tarikcoskun@hotmail.com.tr
*/



NOT: "DupShell", doğru çalışıp doğru çıktılar üretmesine rağmen "Pretest", konsoldaki kursor(>) işaretini de text dosyasına
     koyduğu için dosyaları farklı olarak algılıyor. Karşılaştırılan her iki "DupShell" text dosyasına bakıldığında
     değerlerin eşleştiği ve çıktıların aynı olduğu görülmektedir.



Dosyaların Listesi
_____________________________________________________________________________________________________________________________



1)MakeCopy.c            :   AÇIKLAMA :      Komut ekranından girilen argümanlara göre, bir kaynak dosyadaki bulunan tüm
 *                                          içeriği, verilen buffer boyutunun limitleri ile kaynak dosyaya kopyalar.
 *
 *
 * BAŞLATMA             :       ./MakeCopy <sourceFile> <destinationFile> <bufferSize>



2)ForkCopy.c            :   AÇIKLAMA :      Main process, bir adet child process yaratır ve MakeCopy programı üzerinden
 *                                          child processe kopyalama yaptırır. Child process bitene kadar bekler.
 *
 *
 * BAŞLATMA             :       ./ForkCopy <sourceFile> <destinationFile> <bufferSize>



3)PipeCopy.c            :   AÇIKLAMA :      Main process, bir adet pipe oluşturur ve ardından iki adet child process
 *                                          yaratır. Child processlerden biri okuma ucu, diğeri ise yazma ucu olarak
 *                                          veri aktarımı yapar ve dosyadan dosyaya aynı şekilde içeriği kopyalar.
 *
 * BAŞLATMA             :       ./PipeCopy <sourceFile> <destinationFile> <bufferSize>



4)CompareTime.c         :   AÇIKLAMA :       MakeCopy, ForkCopy ve PipeCopy nin çalışma sürelerini gösterir.
 *
 *
 *
 * BAŞLATMA             :       ./ComapareTime <ProgramToTest> <sourceFile> <destinationFile> <bufferSize>



5)MyShell.c             :   AÇIKLAMA :       Komut ekranını taklit edebilmek için, kullanıcıdan girdi alır ve bir adet
 *                                           child process üretir. Bu girdiyi, child process üzerinde execlp() fonksiyonu
 *                                           ile calistirir. Main process childi bekler, girdiye göre işlemleri tekrarlar.
 *
 * BAŞLATMA             :       ./MyShell



6)MoreShell.c           :   AÇIKLAMA :       MyShelle aynı davranışı sergiler ancak yapılan girdide opsiyonlu bir kullanım
 *                                           var ise gerekli ayrıştırmayı yapar ve execvp() fonksiyonu ile çalıştırır.
 *
 *
 * BAŞLATMA             :       ./MoreShell



7)DupShell.c            :   AÇIKLAMA :       MoreShelle aynı davranışı sergiler ancak yapılan girdide pipe lı bir kullanım
 *                                           var ise gerekli ayrıştırmayı yapar. dup2() fonksiyonu, bir pipe ile aktif edilip
 *                                           ilk komutun çıktısı diğer uçtan yakalanır ve girdi olarak kullanılır.
 *
 * BAŞLATMA             :	./DupShell



8)Prj1header.h          : Gerekli header dosyaları



9)Output.txt            : Konsol ekranı çıktısı



10) Prj1README          : Dosyaların Listesi
