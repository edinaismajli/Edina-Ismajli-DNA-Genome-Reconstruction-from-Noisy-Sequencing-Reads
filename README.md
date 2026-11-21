DNA Genome Reconstruction from Noisy Sequencing Reads

## Përshkrimi

Ky projekt trajton rindërtimin e një sekuence të panjohur të ADN-së nga shumë reads të shkurtra, të parenditura dhe potencialisht me gabime. Reads mund të mbivendosen, të përmbajnë zëvendësime, inserime ose fshirje, të përsëriten, të kenë mbulim të ndryshëm dhe të paraqiten në orientimin forward ose reverse-complement.

Qëllimi është të ndërtohet një zgjidhje në C++ që i gjen mbivendosjet, i organizon në një graf dhe i përdor për të prodhuar montimin më të mundshëm. Projekti lidh algoritmet e krahasimit të stringjeve, programimin dinamik, hashing-un, grafin, strategjitë greedy dhe analizën e kompleksitetit të mësuara në lëndën **Dizajni dhe Analiza e Algoritmeve**.

## Qasja algoritmike

### 1. Leximi dhe përgatitja e reads

Reads merren nga skedarë FASTA ose FASTQ. Sekuencat normalizohen në alfabetin e ADN-së (`A`, `C`, `G`, `T`, dhe opsionalisht `N`). Për secilin read merret parasysh edhe reverse-complement-i, sepse orientimi i leximit mund të jetë i kundërt.

### 2. Indeksimi dhe gjenerimi i kandidatëve

Çdo read ndahet në k-mer-a me gjatësi `k`. Një tabelë hash lidh çdo k-mer me reads ku shfaqet. Çiftet që ndajnë k-mer-a zgjidhen si kandidatë për krahasim, duke shmangur zakonisht krahasimin e të gjitha çifteve të mundshme. Parametri `k` ndikon në numrin e kandidatëve: k-mer-at e vegjël krijojnë më shumë përputhje të rastësishme, ndërsa k-mer-at e mëdhenj mund të humbin përputhje kur reads kanë gabime.

### 3. Zbulimi i mbivendosjeve të përafërta

Për çiftet kandidate krahasohet suffix-i i një read-i me prefix-in e tjetrit. Edit distance me programim dinamik llogarit koston e zëvendësimeve, inserimeve dhe fshirjeve. Mbivendosja vlerësohet sipas gjatësisë dhe normës së gabimit. Parametrat përfshijnë gjatësinë minimale të mbivendosjes dhe normën maksimale të lejuar të gabimit.

### 4. Grafi i mbivendosjeve

Çdo read/orientim përfaqësohet si nyje. Një edge i drejtuar `u -> v` tregon se fundi i read-it `u` përputhet me fillimin e read-it `v`. Pesha e edge-it përfshin gjatësinë e overlap-it dhe cilësinë ose numrin e gabimeve. Kështu grafi ruan lidhjet e mundshme mes reads dhe mund të përdoret për të zgjedhur rrugë montimi.

### 5. Montimi dhe korrigjimi i gabimeve

Një strategji greedy zgjedh mbivendosjet më të gjata dhe me cilësi më të mirë për të ndërtuar një rrugë në graf. Reads që mbështesin të njëjtin rajon mund të përdoren për konsensus të bazave dhe për korrigjimin e gabimeve të sekuencimit. Kur grafi ka disa rrugë të mundshme, përsëritjet ose mbulimi i ulët mund ta bëjnë montimin të paqartë; strategjia greedy nuk garanton gjithmonë zgjidhjen optimale.

### 6. Variacionet dhe reference-a

Kur jepet një genome reference, sekuenca e montuar krahasohet me të për të raportuar pozicione kandidate të zëvendësimeve, inserimeve dhe fshirjeve. Mbështetja nga reads dhe mbulimi përdoren për të dalluar sa më mirë gabimet e leximit nga variacionet e mundshme biologjike. Një ndryshim i vetëm nuk mjafton për të vërtetuar mutacion.

## Input-i

- Koleksion reads me gjatësi të ndryshme, në FASTA ose FASTQ.
- Opsionalisht, cilësitë e bazave nga FASTQ.
- Parametrat `k`, gjatësia minimale e overlap-it dhe norma maksimale e gabimit.
- Dataset-e që mund të përmbajnë reads të dyfishta, zëvendësime, inserime/fshirje, mutacione, reverse-complement dhe mbulim jo të njëtrajtshëm.
- Opsionalisht, një genome reference për krahasimin e rezultatit dhe raportimin e varianteve.

Për eksperimentin me Kaggle zgjidhet dataset që përmban reads të përshtatshme ose një reference prej së cilës krijohen reads sintetike. Një genome reference e vetme nuk është e njëjta gjë si koleksioni i reads të parenditura. Në raport shënohen emri dhe burimi i dataset-it, formati, madhësia dhe licenca.

## Output-i

Programi prodhon sekuencën e montuar dhe raport me:

- numrin e reads të lexuara dhe të përfshira;
- numrin e overlap-eve dhe cilësinë mesatare të tyre;
- gjatësinë e montimit;
- ndryshimet kandidate ndaj reference-s, kur reference-a është dhënë;
- kohën e ekzekutimit, memorien dhe numrin e çifteve kandidate të krahasuara.

## Analiza e algoritmeve

Le të jenë `n` numri i reads, `B` numri i përgjithshëm i bazave, `L` gjatësia maksimale e një read-i, `C` numri i çifteve kandidate dhe `E` numri i edges në graf.

- Ndërtimi i indeksit k-mer kërkon mesatarisht `O(B)` kohë dhe hapësirë, pa përfshirë overhead-in e tabelës hash.
- Edit distance standard për dy sekuenca me gjatësi deri në `L` kërkon `O(L^2)` kohë dhe `O(L)` hapësirë shtesë kur ruhen vetëm dy rreshta të matricës DP.
- Për `C` çifte, krahasimi me DP për një overlap kërkon deri në `O(C L^2)` kohë. Nëse testohen shumë gjatësi të veçanta me llogaritje të reja të DP-së, kostoja mund të rritet deri në `O(C L^3)`; një formulim semi-global ose banded DP mund ta ulë këtë punë.
- Grafi ruan deri në `O(E)` edges. Kalimi greedy pas ndërtimit kushton `O(n + E)`. Në rastin më të keq grafi është i dendur dhe `E = O(n^2)`.
- Hashimi e zvogëlon numrin e krahasimeve në shumë raste, por nuk e përjashton rastin kuadratik kur shumë reads ndajnë k-mer-a.

## Vlerësimi dhe metrikat

Rezultatet krahasohen me reference-n e njohur, kur është në dispozicion. Metrikat përfshijnë saktësinë e sekuencës, edit distance ndaj reference-s, numrin e varianteve të identifikuara saktë, përqindjen e reads të përfshira, kohën, memorien, numrin e krahasimeve kandidate dhe sjelljen kur rritet numri i reads.

Eksperimentet kryhen mbi dataset-e me madhësi në rritje. Për çdo madhësi regjistrohen parametrat, numri i reads, koha, memoria dhe krahasimet. Vlerat raportohen vetëm pasi të maten me programin.

## Sfidat

- Shmangia e krahasimit naiv `O(n^2)` të të gjitha çifteve.
- Dallimi i gabimeve të sekuencimit nga mutacionet biologjike.
- Ndërtimi dhe përpunimi i grafit të madh me memorie të kufizuar.
- Zgjedhja e `k`, overlap-it minimal dhe normës së gabimit.
- Trajtimi i rajoneve të përsëritura me disa montime të mundshme.
- Balancimi i saktësisë, kohës dhe memories për mijëra deri në qindra mijëra reads.

## Lidhja me temat e lëndës

Projekti përfshin algoritme kërkimi dhe krahasimi, hash table, sortim të kandidatëve sipas peshës, grafe, programim dinamik për edit distance, kompleksitet kohor/hapësinor dhe relacione rekurrence. Kërkimi linear shërben si pikënisje për krahasim me gjenerimin e kandidatëve përmes k-mer hashing.