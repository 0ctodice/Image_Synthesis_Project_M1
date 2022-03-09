- référence -> Cube (Face carrée)

maxRes : 1000
-> carréRes = MAX * MAX avec MAX = maxRes / 2

-> cubeRes (taille des tableaux) = 6*(MAX * MAX)

-> surfaceSphere = $\pi*r²$ (r=1 -> $\pi$)

-> sphereRes (taille des tableaux)

=> $maxM = maxRes * \pi$

=> $maxP = \frac{maxM}{2}$

---> $maxM * maxP$

-> cylindreRes (taille des tableaux)

=> $maxM = maxRes * \pi$

=> $maxP = \frac{maxRes}{2}$

taille n2 * (n1 + (n2 * n3))

Objet :

- Ref canonique
===> size_t size;
     Point vertex[size];
     Vector norm[size];

- Matrice de Transfo:
H
R
T
- Resolution (distance)
- Fonction de distance
    Par point / par face
- Couleur / Matière