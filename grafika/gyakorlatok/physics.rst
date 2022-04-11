Fizika megvalósítása
====================

.. warning::

    A következőkben javaslatok szerepelnek a fizikai jelenségek modellezéséhez.
    Az alkalmazott számítási módok egyszerűsítések, helyenként heurisztikák.
    Nem szükségszerűen tükrözik a valós fizikai jelenségeket.

Surlódás, fékezés
-----------------

Modellezni szeretnénk, ahogy egy test sebessége a surlódás következtében folyamatosan csökken.
Feltételezzük a következőket.

* A számításokat :math:`t = 0` időpillanattól kezdjük.
* A test sebessége az idő függvénye, kezdetben :math:`v(0) = v_0`.
* A sebesség csökkenését az eltelt idővel tekintjük arányosnak. (*Lehetne a sebességgel is.*)
* A test sebessége egységnyi idő alatt mindig konstans szorosára változik. Jelöljük ezt :math:`\lambda`-val (:math:`\lambda \in [0, 1]`)!

Ezek alapján a test aktuális sebességét a következőképpen számíthatjuk ki:

.. math::

    v(t) = v_0 \cdot \lambda^t.

Számítsuk ki a :math:`t` időpillanatig megtett út hosszát! Ehhez az alábbi határozott integrál kiszámítására van szükség:

.. math::

    \int_{0}^{t} \! v(x) \cdot x \, \mathrm{d}x =
    \int_{0}^{t} \! v_0 \cdot \lambda^x \cdot x \, \mathrm{d}x =
    v_0 \cdot \left[ \dfrac{1}{\text{ln}\lambda} \cdot x \cdot \lambda^x - \dfrac{1}{\text{ln}^2 \lambda} \cdot \lambda^x\right]_{0}^{t}.

Behelyettesítve azt kapjuk, hogy

.. math::

    s(t) = v_0 \cdot \left(
    \dfrac{\lambda^t}{\text{ln}\lambda} \cdot t -
    \dfrac{\lambda^t}{\text{ln}^2 \lambda} +
    \dfrac{1}{\text{ln}^2 \lambda}
    \right).

A programban a keretidő (:math:`\Delta t`) alapján kell meghatározni, hogy a csúszó/fékező test sebessége milyen. Ehhez tehát ki kell számolni, hogy

* mekkora a :math:`\Delta t`-hez tartozó elmozdulásvektor, és hogy
* mennyi lesz a sebessége a testnek a keretidő végén.
* A :math:`v_0` ilyen esetben már a keretidő elején lévő sebességet jelenti.

A :math:`\Delta t` értékét érdemes másodpercben meghatározni. A :math:`\lambda` ekkor azt fogja jelenteni, hogy másodpercenként hányszorosára fog változni a test sebessége. Például, hogy ha :math:`\lambda = 0.5`, akkor az azt jelenti, hogy a test sebessége másodpercenként a felére fog csökkenni.

A :math:`v(t) = v_0 \cdot \lambda^t` helyett használhatunk :math:`e` alapú exponenciális függvényt. Ekkor a :math:`\lambda` jelentése (mértékegysége) más lesz, de a :math:`\lambda` konstans ismeretében a számítások egyszerűsödnek.
