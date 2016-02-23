MSP430 ile MP3 Player Similasyonu
---------------------------------

**Özet:**  MCU ile SD karttan okunan mp3 dosyaları oynatılmaktadır. İleri/geri sarma stop ve equlazier gibi temel özellikler desteklenmektedir.  

**Kullanılan Kaynaklar:**
1. LCD ekran  
2. SD kart okuyucu  
3. Çizgi Tagem MSP430 Eğitim Kiti üzerindeki butonlar  

**Açıklama**  
Program  döngü içerisinde hafıza kartının içeriğini kontrol edip, dosya listesini okumaktadır. Hafıza kartı FAT16 dosya sistemi olmalıdır. MP3 uzantılı dosyaların içerisinde “01:28” gibi 5 karakterli süre bilgisi bulunmaktadır. Hafıza kartı çıkarıldığı zaman LCD ekranda uyarı mesajı çıkmaktadır. Açıldığı zaman ilk parçada duraklatılmış şekilde beklemektedir. 
 
MCU ve kaynaklarının bağlantıları aşağıdaki gibidir.

    P1_0 -> STOP - ON/OFF
    P2_0 -> sd cs_pin
    P1_1 -> UART               
    P2_1 -> BUG
    P1_2 -> UART               
    P2_2 -> BUG
    P1_3 -> EQU                 
    P2_3 -> PLAY/PAUSE
    P1_4 -> lcd D4              
    P2_4 -> NEXT
    P1_5 -> lcd D5, sd SCLK     
    P2_5 -> PREV
    P1_6 -> lcd D6, sd D0       
    P2_6 -> lcd en
    P1_7 -> lcd D7, sd D1       
    P2_7 -> lcd rs

**Buton Fonksiyonları:**  
**STOP:** Durdurma işlevi yapar ve 2. Defa basıldığı zaman ekranı kapatır.  
**EQU:** Üst satırdaki equlazier animasyonunu açar ve kapatır. Sadece parça oynatılırken gözükür.  
**PLAY/PAUSE:** Parçayı oynatır veya bekletme yapar.  
**NEXT:** Sonraki parçayı açar. 1 saniyeden uzun basılırsa ileri sarmayı açar ve tekrar basıldığı zaman çalmaya devam eder. Parça sonuna gelindiği zaman sonraki parçaya geçer.  
**PREV:** Önceki parçayı açar. 1 saniyeden uzun basılırsa geri sarmayı açar ve tekrar basıldığı zaman çalmaya devam eder. Parça başına geldiği zaman duraklatır.  

**Algoritma Fonksiyon Açıklamaları:**  
**setup:** Kullanılacak butonlar INPUT_PULLUP olarak tanımlanmaktadır.  
**loop:** Ana döngü aşağıdaki 3 fonksiyonu sürekli çalıştırmaktadır. Bu sayede buton basıldığı anda yada saniyelik değişimlerde anlık tepki alınıp, LCD ekrana göz yormayan güncellemeler yapılabilmektedir.  
**checkButton:** Buton kontrolü yapılmaktadır.  
**checkState:** Cihazın durumuna göre işlemlerin devamını uygular.   
  
**Tanımlı State Değerleri:**  
ST_STOP , ST_PLAY, ST_PAUSE,  ST_PREV, ST_NEXT, ST_OFF, ST_NOSD  
**refreshLCD:** LCD ekrana basılacak görüntüyü oluşturur.  
**checkButton:** Dizi içerisinde tanımlı olan bütün butonlar tek tek kontrol edilmektedir. Basılı olduğu tespit edilen buton bulunursa, buton milisaniye sayacına zaman değeri atanır, butonun bırakılmasına tanımlı diğer sonsuz döngüye giriş yapılır ve bu süre içerisinde sadece refreshLCD ile ekran yenilemesi yapılmaktadır. Buton milisaniye sayacı 1 saniyeyi geçtiği zaman ise buton için tanımlı olan ikinci fonksiyon işleme alınır. Bütün butonlar global değişken olan state değişkenini değerini değiştirmektedir ve bir sonraki loopda programın akışını belirlemektedir.  
**refreshLCD:** state isimli değişkenin içeriğine göre LCD ekranın içeriğini oluşturmaktadır. Çalma, geri/ileri sarma durumlarında sadece timer çalıştırılmaktadır. Kapama ve SD kart hatası hariç diğer durumlarda ise bilgiler ortak method ile ekrana yazılmaktadır.  
**readSD:** SD kart içerisindeki tüm dosyaları taramaktadır. track isimli global değişkenin değerine göre seçilen dosya içeriği ve dosya ismi okunmakta ve ekrana yazılmaktadır.  
**readFile:** Açılan dosyanın içeriği okumaktadır. Süre bilgileri dosya içerisindedir.  
**checkTimer:** Çalma durumlarında 1 saniyede, ileri ve geri sarma durumlarında ise 100 ms süreyle zamanı değiştirmektedir.  
**generateTimer:** Sayısal değer olan zaman bilgisini stringe çevirmektedir.  

    time[0] = (minute / 10) + '0';  
    time[1] = (minute % 10) + '0';  
    time[2] = ':';  
    time[3] = (second / 10) + '0';  
    time[4] = (second % 10) + '0';  
    time[5] = '\0';  
