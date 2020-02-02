# Programming Lectures Web

Lihtne rakendus erinevate **kursuste** ja nende **loengute** esilehel kuvamiseks ning võimalusel võid kuvada ka oma tööde (PHP) lähtekoode.

## Installeerimine

**1.** Kopeeri kaust `.plw` koos selle sisuga näiteks programmi [FileZilla](https://filezilla-project.org/) abil serverisse, soovitatavalt väljapoole kausta `public_html` ning lähtekoodi kaustas `public_html` olevad failid.

**NB!** Mõnes serveris võib `public_html` asemel olla mõni teine kaustanimi, küsi selle kohta teenusepakkuja käest.

**2.** Enne rakenduse kasutamist ava fail `.plw/.settings.php` ja täida seal olevad olulised muutujad (koma järel):

```php
define("INFO_NAME", '');
define("INFO_COLLEGE", '');
define("INFO_COURSE", '');
define("INFO_YEAR", 0);
define("INFO_PHONE", '');
define("INFO_EMAIL", '');
define("INFO_REQUEST_VALUE", '');
```

Nimed räägivad enda eest :smile:

**3.** Soovi korral võid määrata rakendusele teema (failid `w3-theme-*` kaustas `.plw/css`), näiteks:

```php
define("APP_COLOR_THEME", 'blue');
define("APP_THEME", 'dark');
```

või määra teemaks `custom` ja loo lehel [W3.CSS Color Generator](https://www.w3schools.com/w3css/w3css_color_generator.asp) oma värviteema (ära unusta genereeritud CSS-koodi kopeerida faili `custom-theme.css`).

**4.** Kui vahekaardil soovid kasutada mõnda teist taustavärvi, mida `w3.css`-is ei ole, saad kasutada ka faile `w3-colors-*` ja siis hiljem sealseid värve kasutada, näiteks:

```php
define("APP_COLOR_LIBS", array('food', '2019'));
```

## Kasutamine

Kursuste ja vastavate loengute kaustad peavad asuma järgnevalt:

```
public_html
     │
     ├─ kursus1
     │     │
     │     ├─ loeng1
     │     ├─ loeng2
     │     └─ ...
     │
     ├─ kursus2
     │     └─ ...
     └─ ...
```

1. Selleks, et kursus ilmuks avalehele, tuleb kursuse kausta lisada fail `.settings` (vt. näitekausta `example_subject`) ning soovi korral ka faili `.links`, kuhu võid lisada viited erinevatele allikatele, mida kuvatakse **Eelvaade** lehel.
2. Loengute lehel saad määrata selle toimumise aega failis `.date`, siis ilmub see nime järele ülaindeksina. Kui soovid teha loengu kaustas oleva PHP-lähtekoodi nähtavaks, lisa fail `.src`, kus võid soovi korral piiritleda alamkaustaga (tühjaks jätmise korral loetakse kõik `*.php` ja `*.inc` failid).
