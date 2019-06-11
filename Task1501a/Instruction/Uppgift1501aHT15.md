
Uppgift 1501a
======
Programmering med handledningstid  
_Ulrik Eklund, 2015-11-11_

Syfte med uppgiften:
------
Studenterna ska använda moderna utvecklingshjälpmedel för programutveckling för inbyggda system, som IDE (Integrated Development Environment), utvecklingskort och versionshanteringssystem.   
Uppgiften görs normalt två och två, men det går bra att jobba ensam också.

Det rekommenderas att ha ett eget USB-minne för katalogerna som med dina personliga kod repositories även om det inte är nödvändigt, all kod du gjort i labben kommer att finnas ”i molnet” när du är klar.

Som vanligt så innehåller all mjukvara buggar, troligtvis även det exempelprojekt som labben utgår ifrån (och till och med denna labbhandledning). Se det som en del av labben att eliminera eventuella existerande buggar om de påträffas!

Krav för godkänt:
------
Ha genomfört följande moment enligt denna handledning:

1. Skapa ett eget lokalt repository baserat på det gemensamma repot på github som finns för uppgiften.
2. Starta Atmel Studio, modifiera källkoden i projektet, kompilera och ladda ner den till utvecklingskortet. Modifiera och köra programmet till alla tester passeras.
3. Committa filerna till ditt personliga repo, synka med github, och göra en ”pull request” till det centrala kursrepot.

Läraren kommer att kolla alla pull requests vid veckans slut, efter uppsamlingslabbarna vid terminens slut och vid kursens slut. **Det kommer inte att bedömas några laborationer utanför kursen!**

Lämpliga förberedelser
------

1. Labben kommer att innehålla grundläggande C-programmering, så repetera vad som gåtts igenom i kursen datateknik från första året. Mer specifikt kommer du att behöva
    1. Förstå deklarationer, tilldelning och bit-operationer på variabler (sektion 1 i [1]) + integers med fix storlek [2].
    2. Känna till vilka hårdvaruregister som används att styra digitala utgångar på en SAM3X8E Cortex-M3 microcontroller (sektion 31 i [3]).
    3. Förstå pekare (allmänt i sektion 3 i [1]), framförallt hur man använder pekare för att komma åt hårdvaruregister [5].
    4. Känna till hur pinnarna på Arduino Due förhåller sig till utgångarna på SAM3X8E [4]
    5. Hur man skapar större projekt med flera filer (sektion 5 i [1]).
    6. Tester för C-funktioner [6]
2. Det finns ett diagnostiskt test på It’s learning. Gör det innan du går till labbsalen som en koll på att du kan grunderna! Du kommer inte att bli godkänd på labben utan att ha fått godkänt på testet.
3. Läs igenom grunderna i versionshantering med git, t.ex. denna självstudiekurs: <http://try.github.io/levels/1/challenges/1> 
4. Du skall också ha läst igenom hela denna handledning innan du går till labbsalen!

Även om du har förberett dig genom att läsa all teori är det ovanligt att du kommer att hinna göra klart uppgiften på 4 timmar (gäller alla labbuppgifterna i kursen).  Det går att skriva den mesta koden, eliminera kompileringsfel mm. utan att ha tillgång till något utvecklingskort.  

Förutsättningar för att kunna börja på uppgiften
------
1. Om annan dator än labbsalens dator används (t.ex. egen dator) måste följande program finnas installerat på den datorn:
    1. Atmel Studio 6.2 (finns endast för Windows), med terminal-fönstret installerat som en plug-in. Om du använder Atmel Studio 7.0 så måste du ha en fristående terminal installerad (det finns en i Arduino)
    2. Bossac flashprogrammeringsdriver, inklusive DOS-macro (finns om man laddar ner uppgiftens repo från Github)
    3. En Git-klient, t.ex. [git-scm](https://git-scm.com ), [Github client](http://windows.github.com/) eller [TortoiseGit](http://code.google.com/p/tortoisegit/) (för andra operativsystem än Windows finns andra Git-klienter). Helst där du kan skriva git-kommandon via en kommandorad.
2. Alla studenter i labbgruppen måste också ha registrerat en användare på [github](http://www.github.com/)! Om du redan har en, använd den!
Meddela Ulrik på _ulrik.eklund@mah.se_ vilka era githubanvändare är.

**Gör det här innan ni kommer till labbsalen, ödsla inte tiden ni sitter där på saker ni kan göra hemma!**

Versionshantering med Git
------

Grunderna hur man arbetar med git-klienten för Windows finns på
<https://help.github.com/articles/getting-started-with-github-for-windows>

<https://help.github.com/articles/synchronizing-repositories>

Själva uppgiften
------

### Skapa ett personligt repo för denna programmeringsuppgift med hjälp av Git

För att fortsätta jobba och ändå ha kontroll på vem som gör vad så låter vi Git hålla reda på det för alla studenter och lärare i kursen, vilket är en av Gits styrkor (och varför det används i projekt med hundratals utvecklare, t.ex. open-source-projektet Linux).

Det finns ett centralt repo för kursen på github med webbadressen:  <https://github.com/MalmoUniversity-DA264A/Task1501a>

1. Skapa en lokal ”fork” av detta repository på kursuppgiftens webbsida (se <https://guides.github.com/activities/forking/>). Då kan du jobba vidare på ditt eget projekt i ett eget repository utan att oroa dig för att förstöra kursens gemensamma repot. Enklast är att skapa en fork från githubs webbgränssnitt till kursrepot

![Figur 1: Fork-knappen på githubs webbsida](fork.png)

2. Ange att du skall forka repot till din egen användare på github (den har du redan skapat). I resten av handledningen kallas denna användare _StudentNN_.

3. Än så länge finns bara ditt nya repo på github-servern, men du vill ju kunna jobba med projektet lokalt på din dator. Därför måste du klona det nyligen skapade repot till din lokala dator, vilket betyder att du skapar en identisk kopia som hela tiden kan synkas med github med kommandona pull och push.  
Välj en katalog på datorn där du vill ha din lokala kopia av repot.  
Klona repot på github repo till din valda katalog på datorn med hjälp av github-bash.  Adressen du ska använda finns under HTTPS clone URL. Kommandoraden blir i Unix eller gitbash om man står i önskad katalog:
    
    >git clone https://github.com/StudentNN/Task1501a.git

där `StudentNN` är ditt användarnamn på github.

![Figur 2: Adressen till ett kodreps på githubs webbsida.](cloneAddress.png)

Under labben är det enklast om man jobbar mot ett och samma forkade repo i hela labben, även om det tillhör bara en specifik student. Om ni är två som vill jobba med varsitt lokalt repo kan ni ge båda studenterna rättigheter att jobba mot samma repo och sen klona repot på github till två olika datorer.

![Figur 3: Översikt över hur man forkar, klonar och synkar kodrepor i kursen. Kursens gemensamma repo är rött, ditt privata repo är blått.](repoOverview.png)

### Arbetskatalogen för denna uppgiften

I katalogen `Task1501a` finns denna handledning i mappen `Instruction` och en projektmapp för Atmel studio vid namn `ProjectDigitalIO`

### Använda Git

Med jämna mellanrum vill man committa sina ändringar till sitt lokala repo (Steg 3 i Figur 3). Git-shell-kommando:

    >git commit –am ”mywork”

Varje commit bör vara en ”unit of functionality” som alltid kompilerar, t.ex. refaktorera namnet på en funktion, en ny feature, eller förbättrad dokumentation. Varje commit måste också ha en beskrivande kommentar så man vet vad det faktiskt var man ändrade (Ett fullt realistiskt exempel kan ses på <http://xkcd.com/1296/>).  
Git sparar alla tidigare commits, så man kan närsomhelst backa till ett tidigare commit-tillfälle om det skulle behövas.

Om en fil aldrig har blivit committad tidigare måste man ange att den ska adderas till Git-repot.

    >git add filnamn.xxx

eller
 
    >git add --all
    
Efter man gjort det första gången håller Git reda på att filen ”ingår” i repot (men den måste committas första gången ändå!). Git-klienterna burkar hålla reda på nyskapade filer i katalogerna som tillhör repot och frågar om de ska adderas.

### Bygga labbsetup

Utrustning:

- Utvecklingskort Arduino Due
- USB-kabel (USB <-> USB micro)

Vi ska använda några av de digitala utgångarna, varav den kopplad till pinne 13 driver den oranga lysdioden som finns på Due-kortet.  
_Vilken I/O-port på processorn driver denna utgång (se <http://arduino.cc/en/Hacking/PinMappingSAM3X>)?_

Due-kortet kan drivas med strömmen genom en USB-kabel från datorn om man inte behöver för mycket effekt till utgångarna och det räcker gott för denna labben.  USB-kabeln kopplas till USB-micro-kontakten märkt PROGRAMMING. När man programmerar eller ”flashar” kortet gör man det också genom samma USB-kabel.

### Labbens programmeringsuppgift

Om du lyckats med att klona git-repot finns det nu i katalogen `Task1501a\ProjectDigitalIO` på din lokala dator en projektfil för Atmel Studio:  `ProjectDigitalIO.atsln`  
Öppna den genom antingen genom att dubbelklicka eller genom ”open project” inifrån Atmel Studio. Filerna är strukturerade som följer

Labben går ut på att ni ska skriva funktioner som passerar de testfall som finns definierade i projektet.  
Testa att kompilera projektet under menyn ”Build”. Det här kollar främst att syntaxen är rätt, variabler är definierade och lite annat. C har annars få begräsningar vad som är rätt eller fel i språket.

Du bör inte få några varningar om du använder samma version på utvecklingsmiljön som projektet gjort hittills (varningar som kan finnas är ”bara” för att en del variabler är definierade som aldrig används i den här labben, så vi bryr oss inte om dem). 

Ladda ner den färdiga binärfilen till Due-kortet via USB-kabeln med kommandot Arduino Due(Debug) under Tools-menyn.  
Finns inte det kommandot i menyn följ instruktionerna som finns som kommentarer i bat-filen som finns i projektkatalogen (den går att öppna med en vanlig editor och bygger på <https://github.com/ctbenergy/BossacArduinoDue>). Du måste givetvis uppdatera sökvägarna till var bossac.exe och bat-filen ligger på jsut din dator.
Både bossac-programmet och bat-filen finns i katalogen i uppgiftens git-repo.

### Test-driven utveckling (Test-Driven Development TDD)
Wikipedia har en bra introduktion till tesdriven utveckling: <http://en.wikipedia.org/wiki/Test-driven_development>
Rent generellt ser processen ut som nedan.
![](tddCycle.png)

I den här labben är några av stegen redan givna för alla testerna. I detalj så kommer ni att genomföra följande steg för varje test.

#### Förberedelse

1. Gör på en testlista. Det är redan gjort för den här labben och ser ut som följer:
    1. Port B utgång 27 initialiserad som en digital utgång = pin 13 på Due-kortet = lysdioden
    2. Sätt pin 13 till hög
    3. Pin 13 till låg
    4. Pin 22 initialiserad som digital utgång (Due pinne 22)
    5. Pin 22 till hög
    6. Pin 22 till låg
    7. Pin 13 och pin 22 initialiseras som utgångar
    8. Pin 13 och pin 22 båda till höga
    9. Pin 13 och pin 22 båda till låg

2. Skapa en .c–fil och en .h-fil med funktionerna som skall testas, detta är modulen som skall testas (också redan gjort: `digitalIO.h` och `digitalIO.c`)

#### Testcykeln

3. Välj ett test från testlistan (gör det i samma ordning som de står i `test_digitalIO.c`)
4. Skriv/uppdatera testfilen för funktionen som ska testas (redan gjort för testerna 4-9)
5. Skriv/uppdatera en ”runner-fil” som exekverar valda tester (den första testen körs i `main.c`, de andra är bortkommenterade i det ursprungliga projektet)
6. Bygg projektet (kompilering + länkning)
7. Ladda ner den färdiga binärfilen med programmet till Due-kortet
8. Kör programmet på Due-kortet
9. Det första testet, samt test 2 och 3 kommer bli godkända. Kör ni däremot de andra testerna kommer de att fallerera. För att resultatet ska synas måste terminalfönstret inuti Atmel Studio vara installerat.
10. Skriv programkoden för test 1-3 i test_digitalIO.h. Ni kan antingen kolla i unity.c för att använda ett lämpligt test eller ta hjälp från de testerna som redan är skrivna.
11. Skriv programkoden så att funktionen klarar av testet (lägg till kod i `digitalIO.c`). 
12. Kompilera och kör
13. Se testen/testerna passera, annars upprepa 8-9.
14. Städa och eventuellt kommentera din kod om det inte redan är gjort.

#### Samla ihop resultaten från TDD-cykeln

15. Commit till ditt personliga repo (valfritt)
16. Upprepa testcykeln tills alla tester i testlistan är implementerade. Då är även de två funktionerna färdigprogrammerade!

### Exempel på hur det ser ut för de tester som redan har implementerad kod

Hela projektet är organiserat som följer: Projektet har två kataloger som man jobbar mot, `src` och `test`. Funktionerna man utvecklar ligger i `src`.  
Testrunner-filen och filen(erna) med testerna ligger i katalogen test. Testramverket unity ligger i katalogen unity.  
När man sen vill använda sina testade filer i produktionssystemet behöver man bara filerna i src-katalogen. Testfilerna används alltså bara under utveckling.

#### En enkel testfil
Alla testfunktioner är av typen

```c
void test_TheFunctionsdoesSomethingUseful(void);
```

Dessa tester deklareras snyggast i en motsvarande h-fil för att inkluderas i runner-filen (se nedan).

Ta för vana att döpa testfilen för att testa `Module.c` till `test_Module.c` 
I det här projektet heter filen med c-koden för testerna `test_digitalIO.c` 
Den innehåller totalt 9 tester:

1. Det första testet kollar att initieringsfunktionen för utgång PB27 har initierats korrekt för att kunna användas som en digital utgång. Det görs genom att läsa av en status-bit för port B.
2. Det andra testet kollar att funktionen som sätter utgången till hög faktiskt gör det, också genom att läsa av en status-bit som ger det faktiska värdet på rätt utgång.

Resterande tester är uppbyggda på samma sätt, men är bortkommenterade. Så fort du har klarat av ett test kan du inkludera nästa test genom att ta bort kommenteraren för det testet.

#### Testrunner-filen som kör testerna

Filen som kör testerna  (runner-filen) är i det här fallet `main.c`  
Eftersom det är den här filen som allting körs ifrån måste den innehålla `main()`. Den måste också innehålla all nödvändig initiering av Due-kortet själv, många av de initialisationsfunktionerna kommer från Atmels ASF-bibliotek.

Det står kommenterat i main()var själva testramverket Unity börjar användas. Det är här det första testet körs.  
När man lägger till fler tester görs det efter befintliga tester, men innan UnityEnd();

#### Se resultatet från testerna

Eftersom det inte finns någon naturlig bildskärm kopplad till Due-kortet måste man få ut testresultaten på annat sätt.

I början på testrunner-filen finns hur man initierar att Due-kortet skriver på COM-porten på PC:n via USB-kabeln (`configure_console(void)`). Det gör det möjligt att använda terminalfönstret inifrån Atmel Studio som output för putchar() som Unity använder sig av. Men Terminalfönstret konkurrerar med Bossac om COM-porten så när man laddar ner sin binärfil till DUE-kortet måste terminalfönstret vara o-connectat (i Atmel Studio 6.2 görs detta automatiskt).  
Så fort man laddat ner sin binärfil till Due så startar ju programmet och därför missar man utskriften innan man gjort connect igen. Gör connect och tryck på reset-knappen för att starta testrunner-programmet om igen.

Om allt funkar som det ska ser du att Unity meddelar resultatet från testerna i terminalfönstret. Det går också att spara resultaten från terminalfönstret i en fil, vilket kommer att utnyttjas till inlämningen.

#### Själva koden som utvecklas

De funktioner som ska programmeras ligger i src-katalogen. I filen `digitalIO.c` finns två funktioner definierade

```c
void pinMode(int pinNumber, mode_definition mode)
void digitalWrite(int pinNumber, int value)
```

men det första testfallet gäller bara den första av dessa funktioner.

Titta på tabell 31-2 på sidan 629 i referensmanualen för SAM3X8E-processorn [3] som sitter på Due-kortet. Där finns ett programmeringsexempel för vilka register som används för att styra de digitala utgångarna
##### void pinMode(int pinNumber, mode_definition mode)
Konfigurerar en (1) utpekad pinne på Due-kortet att fungera som antingen en in- eller utgång. I den här uppgiften behöver funktionen bara programmeras för att konfigurera utgångar!  
Behöver man konfigurera två pinnar så får man anropa samma funktion två gånger med olika argument på pinNumber. Givetvis så skall det andra anropet inte ändra konfigurationer för den första pinnen (om det inte är samma pinne förstås).  
De register som behöver användas är (se sida 642 + 643 i [3]):

Offset | Register | Name | Access | Reset
---|---|---|---|---
0x0000 | PIO Enable Register | PIO_PER | Write-only | -
0x0010 | Output Enable Register | PIO_OER | Write-only | -

För att komma åt register på en speciell minnesadress kan man använda en pekare med följande deklaration

```c
/* defines the address for enabling the output pins of port B register with base adress 0x400E1000*/
uint32_t *const p_PIOB_OER = (uint32_t *) (0x400E1000U + 0x0010U);
```

Sen kan man sätta en enstaka bit i detta register med maskning på följande sätt: 
 
```c
*p_PIOB_OER |= 0x000000040;
```

##### int digitalWrite(int pinNumber, int value)

Funktionen ska sätt en utgång på Due-kortet till hög eller låg, förutsatt att pinnen tidigare har satts som en utgång med pinMode.  
De register som behövs för detta är ([sida 660-661][3]):

Offset | Register | Name | Access | Reset 
---|---|---|---|---
0x0030 | Set Output Data Register | PIO_SODR | Write-only | –
0x0034 | Clear Output Data Register| PIO_CODR| Write-only | -

När du har uppdaterat de två funktionerna i `digitalIO.c` så att alla nio testerna passeras har du klarat av all programmering (men det är lite kvar med själva inlämningen för att få godkänt). Glöm inte att spara ner testutskriften från terminalen till en en fil `testResult.txt` i test-katalogen och committa det färdiga programmet till git på din dator.

Om du vill se med blotta ögat att dina funktioner fungerar kan du lägga till följande loop efter `UnityEnd();` i ´test_digitalIO_runner.c´

```c
int i; /* loop counter for the delay */	
volatile int j; /* Dummy volatile to prevent compiler optimising the variable away */
int delay_length = 400000; /* variable determining the length of a delay */

while(1)	/* repeat blink in infinity */
{				
	j=0;	/* makes sure j doesn't overflow */
	
	digitalWrite(13, 1); /* sets a bit of I/O port B to high */
	for (i=0; i<delay_length; i++) /* The delay counter */
	{
		j++;	/* some easy predictable operation */
	}
	
	digitalWrite(13, 0); /* clears a bit of I/O port B */ 
	for (i=0; i<delay_length; i++) /* The delay counter */
	{
		j++;
	}
}
```

Lagra arbetet på github och lämna in för bedömning
------
Om du är klar med all programmering är det vara dags att synka ditt lokala repo med det som du har på github.  
En viktig sak som måste göras är att lägga till eventuella nya filer till ditt repo (som `testResultat.txt`), man måste alltså tala om explicit vilka filer som git ska hålla reda på.

    >git add –all
    
säger till git att hålla reda på alla nya filer som skapats om man står i repots huvudkatalog.

Det går att fråga git-klienten om några nya filer har tillkommit i repots katalog.

    >git status
    
Innan man har lagt till filerna så uppdaterar en commit bara de filer som redan finns i repot.

Om du har gjort en slutlig commit, inklusive nya filer, kan det vara dags att görs med en push tillbaka till github (steg 3 i Figur 3: Översikt över hur man forkar, klonar och synkar kodrepot i kursen. Kursens gemensamma repo är rött, ditt privata repo är blått.). 

    >git push origin

Din gitklient är oftast så smart att den kommer ihåg varifrån man klonade repot, därför kan man oftast använda origin istället för den långa webbaddressen (<https://github.com/StudentNN/Task1501a.git>). 

Har du kommit så långt har du ett uppdaterat repo som du kan se på githubs webbsida. Nu ska du skicka in en begäran att ägaren till det gemensamma kursrepot ska titta på dina ändringar genom en pull request (steg 5 i Figur 3). Där anger du en rubrik (till exempel att du är klar med en viss uppgift), och fyller i en beskrivning av vad dina ändringar består av.
Glöm inte att ange namnen alla som bidragit med att göra klart uppgiften! Det går inte att komma i efterhand och påstå att du varit med om ditt namn inte finns med på originalinlämningen! I så fall får du göra en egen pull request efteråt.

Ulrik kommer att titta på alla som har lämnat in till fredag kväll. Om du lämnar in senare kommer de att bedömas vid terminens slut i samband med tentan.

Referenser
======
[1] Nick Parlante, Essential C, 2003, <http://cslibrary.stanford.edu/101/>

[2] C data types, <https://en.wikipedia.org/wiki/C_data_types> 

[3] Atmel SAM3X / SAM3A Series SMART ARM-based MCU DATASHEET, 2015, <http://www.atmel.com/devices/sam3x8e.aspx>

[4] SAM3X-Arduino Pin Mapping, <http://www.arduino.cc/en/Hacking/PinMappingSAM3X> 

[5] Dan Saks, Representing and Manipulating Hardware in Standard C and C++, Embedded Systems Conference San Francisco, 2002, <http://www.open-std.org/jtc1/sc22/wg21/docs/ESC_SF_02_465_paper.pdf> 

[6] Mark VanderVoord, Embedded Testing With Unity And Cmock - A Book For Those Who Code C And Want Awesome Well-Tested Products Using Free Tools And For Those Who Enjoy Short Books with Long Titles, 2010

