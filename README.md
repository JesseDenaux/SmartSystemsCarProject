# SmartSystemsCarProject Jesse Denaux

In de map 'analyse' vindt u het document met de analyse uitgeschreven

In de map 'hardware' vindt u de PCB ontwerpen

In de map 'software' vindt u de code voor de ATMEGA328P en ESP32-Wrover


## Rapport

Dit rapport bespreekt het verloop van het project en de persoonlijke leerdoelen.

### Start Robotwagen project

Het project ben ik gestart met een github repository te maken voor de analyse. Na verloop van tijd heb ik hier een hardware - en software repository aan toegevoegd om duidelijk en snel te kunnen zien wat waar staat. Zo is het ook duidelijk, voor mochten anderen dit project verder zetten, in welke folder ze moeten zoeken om bepaalde zaken te vinden. 

De analyse heeft iets langer geduurd dan verwacht. Het was in het begin moeilijk om al de informatie in 1 document te krijgen en dit allemaal te onderzoeken. Dit bracht met zich mee dat het enige tijd heeft geduurd tegen dat ik al de juiste componenten had gevonden. 


### Tussentijdse presentatie

Tijdens de tussentijdse presentatie heb ik de huidige staat van het project gepresenteerd. Toen ik de presentatie maakte merkte ik al snel dat er al wel wat zaken waren veranderd ten opzichte van het begin van het project. Zo heb ik enkele schema's moeten aanpassen omdat hier nog fouten instonden van materiaal waar ik van dacht dat we dat gingen gebruiken. 

In mijn eerste stond dat ik nog gebruik ging maken van de ESP32 dev kit en hierdoor maar enkel een LDL1117 voor 5V aangezien er een van 3V in de dev kit zit. Ook stond er hier nog bij dat ik gebruik ging maken van twee motordrivers zoals in het begin was meegegeven maar dat heb ik dan ook aangepast. 

Ik had toen mijn eerste PCB laten frezen van de sensormodule. Daarnaast had ik al een plan van hoe ik de code zou schrijven maar was hier nog niet aan begonnen. 

### PCB's 

De PCB designs zijn gemaakt in Fusion 360. Het programma waar wij mee hebben leren werken in het eerste semester van het tweede jaar. 

Omdat ik nog niet zo een grote projecten had gemaakt met dit programma heb ik toch wel wat uren in moeten steken om hier deftig mee te kunnen werken. Ik had daarom in het begin ook nog al de lijnen door getrokken waardoor het al snel onoverzichtelijk was. Dit heb ik dan opgezocht hoe je dit ordelijke kon doen en heb dit dan ook nog aangepast. 

Omdat de freesmachine niet al de groottes aan kan van gaten (niet al de boren zijn ter beschikking) heb ik hier wat rekening mee moeten houden in mijn ontwerp. Hetzelfde met de rules en grootte van gaten van vias. Fusion maakt deze te klein aan als je hier zelf geen rekening mee houdt. Door de regels van Fernando toe te voegen heb ik na enkele kleine aanpassingen de geschikte bordjes kunnen ontwerpen die de frees machine kon maken. 


#### Eerste versie sensormodule:

<img src="https://user-images.githubusercontent.com/93762886/173889964-5ad1388e-66c9-411c-bbd0-d10189c548d4.png" width="200"/>

Aan deze versie van het bordje heb ik nog wel enkele aanpassingen moeten doen. Zo staan de pinnen van de linetracker nog al ver van zijkant. Er was ook geen usb aansluiting wat een vereiste was zodat de eerste jaars dit ook kunnen programmeren. Dit heb ik dan voor de tweede versie nog aangepast en daarmee enkele zaken nog wat compacter gezet zodat het bordje nog iets kleiner kon gemaakt worden. 

#### Tweede versie sensormodule: 
###### Bovenkant
<img src="https://user-images.githubusercontent.com/93762886/173891780-9d1dff90-6cf8-4e51-ae79-af16cceb64b4.png" width="200"/>

###### Onderkant
<img src="https://user-images.githubusercontent.com/93762886/173891987-805e576f-b5b2-4113-a2cb-c3f077309882.png" width="200"/>

De tweede versie is ineens ook de laatste versie van frezen. Voor deze versie heb ik de kleine smd componenten met de reflow oven gesoldeerrd. Dit was wel een toffe ervaring omdat je zo een nieuwe manier van componenten solderen ziet. Het is wel niet de beste machine want er zijn verschillende beentjes van de IC aan elkaar gesoldeerd. De andere componenten zijn wel goed gesoldeerd. Doordat de vias op waren heb ik de vias zelf gesoldeerd met overschotten van through hole component beentjes. 


#### ESP32 module: 
###### Bovenkant
<img src="https://user-images.githubusercontent.com/93762886/173892158-92f6d0fc-32a6-4a22-995c-bb0e36cece0a.png" width="300"/>

###### Onderkant
<img src="https://user-images.githubusercontent.com/93762886/173892241-076b790e-9185-439e-a5b7-8cc7d52eab67.png" width="300"/>

Van de ESP32 module heb ik maar 1 versie kunnen maken omdat ik, toen ik mijn sensormodule was aan het frezen, merkte dat ik enkele fouten had die ik dan eerste heb aangepast vooraleer ik deze ging laten frezen. Bij deze PCB heb ik wel al de componenten zelf gesoldeerd. Dit was wel een hele opgave omdat ik nog nooit met soldeer pasta en zo een kleine componenten had gewerkt. Hierdoor is er soms wat soldeersel op mijn plaatje gekomen maar dat al geluk geen banen heeft geraakt. Ook hier heb ik gebruik gemaakt van overschotten van through hole component beentjes om de vias te solderen. 

Naast dit alles was het een uitdaging om de through hole componenten te solderen omdat ik deze langs twee kanten moest solderen wat soms wel moeilijkheden met zich meebracht. 

Als laatste heb ik nog gemerkt dat de beentjes van de OLED niet in de holes passen. De holes en de afstanden tussen de holes zijn te klein ondanks dat ik dezelfde component in mijn schema heb gebruikt. Dit kan eventueel opgelost worden door hier draadjes aan te solderen maar hierdoor staat de OLED wel niet op de PCB. Daarnaast heb ik ook gemerkt dat het OLED niet zoveel plaats in beslag neemt dan ik had vrijgehouden. Had ik dit op voorhand gemeten had ik de PCB compacter kunnen maken. 

#### Resultaten

Tot mijn verbazing toe waren er maar een paar kleine foutjes in de PCB na het solderen. Sommige vias die zeer dicht bij elkaar lagen zijn per ongeluk aan elkaar gesoldeerd geraakt. Hieruit leer ik dat ik hier rekening mee moet houden als ik nog eens een PCB maak. Hetzelfde probleem had ik wat met de kleine componenten zoals de IC's of drivers. Hier zijn ook enkele baantjes aan elkaar gesoldeerd geraakt. Dit gewoon solderen is zeer moeilijk om het dan perfect te krijgen. Door gebruik te maken van een reflow oven of andere manieren waarbij je niet met de hand de kleine componenten moet gaan solderen kunnen deze fouten worden vermeden. Het vergt ook veel meer tijd door dit met de hand te doen. 

De vias heb ik getest met de multimeter en deze zijn allemaal goed gesoldeerd en daarmee verbonden. 
Doordat ik weet dat er enkele baantjes met elkaar verbonden zijn heb ik de PCB niet verder getest om te voorkomen dat deze zou ontploffen of er iets anders onverwacht mee zou gebeuren. 

### Programmatie 

Voor het programmeren heb ik het werk opgesplitst in verschillende componenten. Eerst de connectie krijgen via MQTT, daarna de verschillende sensoren en als laatste de ESP32. Eens dat elke component op zijn eigen werkte heb ik ze deel per deel bij elkaar gevoegd. De hele code is gebasseerd op mijn blokschema. 

![image](https://user-images.githubusercontent.com/93762886/173913943-d4c28188-4d0e-4da4-b7d6-ca4719779450.png)

Doordat ik niet genoeg tijd heb gehad om mijn bordje volledig te solderen en te testen tegen het einde heb ik mijn volledige code niet op het wagentje kunnen testen. De volledige code is geschreven. Wat ik wel heb kunnen testen is de ESP32 module. Deze heb ik getest op de huidige robotwagentjes en het zelfstandig rijden en het parcour werken beide. De linetracker heb ik apart wel kunnen testen en deze werkte, zie demo filmpje. 

### Conclusie

Ik heb geleerd dat een analyse zeer belangrijk is in een project. Dit is de basis van het hele project. Door hier al grondig onderzoek te doen naar de verschillende componenten en manieren van werken leer je veel bij en spaar je tijd die je daarna dan niet meer in dit proces moet steken. 

Het is zeer belangrijk om in je hoofd te houden dat de analyse niet vast staat en dat er door het project heen steeds veranderingen aan allerlei zaken gebeuren. Hier heb ik soms wel mijn hoofd over gebroken omdat ik iemand ben die graag iets afwerk en dan aan het volgende werk. Steeds terug huidige versies nemen en verschillende keren aan te passen was toch iets dat ik door dit project heb geleerd. 

Ik heb me wat verkeken bij het vele werk dat er komt kijken bij het ontwerpen van een PCB. Door dit meer in blokken te maken en op te splitsen zou ik veel minder tijd zijn verloren wanneer ik iets moest aanpassen. Ook benamingen van wires en componenten is iets wat ik ga mee nemen naar volgende projecten. Het neemt steeds veel tijd in beslag om te zoeken welke wire nu wat is. 

Wat zeker ook belangrijk is om componenten die niet standaard in Fusion zitten om die af te meten en dan te kijken hoeveel plaats ze gaan innemen op de PCB. Hiermee kan je veel plaats besparen en de PCB kleiner maken. 

Je bent ook afhankelijk van de levering van materiaal. Doordat er verschillende componenten later dan verwacht werden geleverd hebben we enkele lessen niet aan de PCB kunnen werken en hebben deze dan later dan verwacht beginnen solderen. 

Het schrijven van de software ging een pak gemakkelijker en sneller omdat dat iets is waar ik meer vertrouwd ben. Er waren al verschillende zaken die wij voor andere vakken hadden gebruikt waardoor ik die code grotendeels kon overnemen. Het is natuurlijk wel belangrijk dat je PCB optijd klaar is zodat je dit hier op kan testen en aanpassen indien nodig.

Het was voor mij de eerste keer dat ik met node-red werkte en was hier snel mee weg. Het was daardoor ook zeer tof om hier mee te werken. In de korte tijd dat ik hier mee heb gewerkt heb ik hier toch nog veel mee kunnen doen. 

Doordat ik maar weinig tijd in de node-red heb kunnen steken is deze nog niet 100% operationeel. Zo is er wel een slider voor de snelheid aanwezig maar deze is nog niet gelinkt met de ESP32. 

#### Wat ik heb geleerd

- Fusion360
- PCB frezen
- Werken met de reflow oven
- Solderen
- Werken met ESP32
- NodeRed
- Een goede analyse is zeer belangrijk
- Componenten zo vroeg mogelijk bestellen zodat ze zeker op tijd aankomen

#### Verbeteringen 

- Het ESP32 bordje zou compacter kunnen worden gemaakt en de OLED holes zouden moeten worden aangepast. 
- De code van de ESP32 kan efficiënter en compacter worden geschreven. 
- Node-red verder verbeteren en slider en serial monitor toevoegen. 

