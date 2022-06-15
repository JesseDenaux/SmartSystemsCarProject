# SmartSystemsCarProject Jesse Denaux

In de map 'analyse' vindt u het document met de analyse uitgeschreven

In de map 'hardware' vindt u de PCB ontwerpen

In de map 'software' vindt u de code voor de ATMEGA328P en ESP32-Wrover


## Rapport

Dit rapport bepreekt het verloop van het project en de persoonlijke leerdoelen

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

Omdat de freesmachine niet al de groottes aan kan van gaten (niet al de boren zijn ter beschikking) heb ik hier wat rekening mee moeten houden in mijn ontwerp. Hetzelfde met de rules en grootte van gaten van vias. Fusion maakt deze te klein aan als je hier zelf geen rekening mee houdt. Door de regels van Fernando toe te voegen heb ik na enkele kleine aanpassingen de geschikte bordjes kunnen maken die de frees machine kon maken. 


#### Eerste versie sensormodule:

<img src="https://user-images.githubusercontent.com/93762886/173889964-5ad1388e-66c9-411c-bbd0-d10189c548d4.png" width="200"/>

Aan deze versie van het bordje heb ik nog wel enkele aanpassingen moeten doen. Zo staan de pinnen van de linetracker nog al ver van zijkant. Er was ook geen usb aansluiting wat een vereiste was zodat de eerste jaars dit ook kunnen programmeren. Dit heb ik dan voor de tweede versie nog aangepast en daarmee enkele zaken nog wat compacter gezet zodat het bordje nog iets kleiner kon gemaakt worden. 

#### Tweede versie sensormodule: 
###### Bovenkant
<img src="https://user-images.githubusercontent.com/93762886/173891780-9d1dff90-6cf8-4e51-ae79-af16cceb64b4.png" width="200"/>

###### Onderkant
<img src="https://user-images.githubusercontent.com/93762886/173891987-805e576f-b5b2-4113-a2cb-c3f077309882.png" width="200"/>


#### ESP32 module: 
###### Bovenkant
<img src="https://user-images.githubusercontent.com/93762886/173892158-92f6d0fc-32a6-4a22-995c-bb0e36cece0a.png" width="300"/>

###### Onderkant
<img src="https://user-images.githubusercontent.com/93762886/173892241-076b790e-9185-439e-a5b7-8cc7d52eab67.png" width="300"/>




### Programmatie 

### Conclusie

Ik heb geleerd dat een analyse zeer belangrijk is in een project. Dit is de basis van het hele project. Door hier al grondig onderzoek te doen naar de verschillende componenten en manieren van werken leer je veel bij en spaar je tijd die je daarna dan niet meer in dit proces moet steken. 

Het is zeer belangrijk om in je hoofd te houden dat de analyse niet vast staat en dat er door het project heen steeds veranderingen aan allerlei zaken gebeuren. Hier heb ik soms wel mijn hoofd over gebroken omdat ik iemand ben die graag iets afwerk en dan aan het volgende werk. Steeds terug huidige versies nemen en verschillende keren aan te passen was toch iets dat ik door dit project heb geleerd. 
