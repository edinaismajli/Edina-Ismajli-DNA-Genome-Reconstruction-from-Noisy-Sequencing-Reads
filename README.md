# DNA Genome Reconstruction

Projekt C++ për ta zhvilluar hap pas hapi në Visual Studio 2022.

## Struktura aktuale

- main.cpp — nis programin dhe përmban të dhënat e vogla për demonstrim.
- Algorithms.h — deklarimet e algoritmeve.
- Algorithms.cpp — implementimi i kërkimit linear.
- DNA Genome Reconstruction.sln — zgjidhja për Visual Studio 2022.

## Gjendja

Versioni aktual kërkon një sekuencë në një listë të vogël. Kërkimi linear kontrollon reads një nga një.

Nëse n është numri i reads dhe L gjatësia maksimale e një read-i:
- Koha: O(nL) në krahasime karakteresh (ose O(n) krahasime të reads).
- Hapësira shtesë: O(1).

Relacioni i rekurrencës për rastin më të keq është T(n) = T(n - 1) + O(L), me rast bazë T(1) = O(L), pra T(n) = O(nL).

## Hapat e ardhshëm

1. Shtimi i leximit të FASTQ-së.
2. Testimi me një numër të vogël reads nga dataset-i.
3. Gjetja dhe renditja e mbivendosjeve.
4. Ndërtimi gradual i rindërtimit dhe raportimit.

Dataset-i RNA-seq mund të përdoret për demonstrim të algoritmeve, por nuk përfaqëson rindërtim të plotë të gjenomit nga DNA-ja.
