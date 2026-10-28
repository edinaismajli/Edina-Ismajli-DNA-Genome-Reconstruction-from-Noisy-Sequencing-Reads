# DNA Genome Reconstruction

Projekt ne C++ për rindërtimin e sekuencës së ADN-së nga reads të shkurtra me gabime.

## Qëllimi

Programi do të zhvillohet hap pas hapi. Fillimisht do të përpunojë reads të vogla shembull; më vonë do të shtohen leximi i skedarëve, gjetja e mbivendosjeve dhe rindërtimi i sekuencës.

## Kërkimi linear

Ky version kërkon një read duke i kontrolluar sekuencat një nga një. Shembulli kërkon `CGGTA` në një listë me tri reads.

### Kompleksiteti

Le të jenë:

- `n` numri i reads;
- `L` gjatësia maksimale e një read-i.

Në rastin më të keq, algoritmi i kontrollon të gjitha reads. Një krahasim mund të kontrollojë deri në `L` baza, prandaj:

- Koha: `O(nL)` në operacione mbi karaktere, ose `O(n)` krahasime të reads.
- Hapësira shtesë: `O(1)`, sepse algoritmi përdor vetëm disa variabla shtesë.

Relacioni i rekurrencës për rastin më të keq është `T(n) = T(n - 1) + O(L)`, me rastin bazë `T(1) = O(L)`. Duke e zgjeruar, marrim `T(n) = O(nL)`.
