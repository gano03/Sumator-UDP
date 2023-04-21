# Sumator-UDP

Serwer napisany w języku C pod system Linux.
Serwer UDP posiada funkcję "operation", w której walidację przechodzi przesłany ciąg znaków.
W pętli, która trwa aż do końca długości łańcucha znaków inkremenrowany jest wskaźnik, kóry 
początkowo był ustawiony na początku łańcucha. Do zamiany znaku ASCII na usnigned long int służy funkcja
"strtoul", ponieważ nie ignoruje znaku przy liczbach. W momencie napotkania spacji wskaźnik jest inkrementowany i 
zostaje wywołane continue.
W przypadku błędnej tranformacji na liczbę, funkcja zwróci NULL.

Fukcja "main" odpowiada za utowrzenie gniazdka sieciowego i utworzenie instancj struktury sockkaddr_in.
Serwer nadaje na porcie 2020.
Następnie za pomocą funkcji "bind" adresy z instancji struktury sockaddr_in zostają przypisane do utworzonego gniazdka sieciowego.
W pętli wysłąne przez klienta datagramy zostają odbierane za pomocą funckji "recfrom"
Bufor zostaje przekazany funckji "operation", która zwraca sumę i po przekonweratowaniu na bufor znakowy zwraca klientowi
za pomocą funckji "sendto".
W przypadku wyslania niedozwolonych znaków, czyli innych niż cyfry i spacje, serwer zwróci komunikat "ERROR"
Do wysyłanych datagramów można również dopisać CRLF "\r\n" na końcu.

Kompilacja programu:

    gcc serwer.c -o serwer
    

Uruchomienie programu:
    
    ./serwer
    
    
Testowanie programu:
    
    Serwer można przetestować na jednym urządzeniu programem netcat wpisując w terminalu linuxowym:
    ncat -u 127.0.0.1 2020
    gdy uruchomiony jest serwer.

