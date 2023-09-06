# Старт-стоп таймер для мотоджимханы

Электрическая схема

[https://drive.google.com/file/d/14_QnXXG4jSQHk2mMvMcpt08meQi_OGaW/view?usp=sharing](https://github.com/alekssaff/motogymkhana_stopwatch/blob/main/scheme.pdf)

### Список компонентов

Сенсор DC12-24V Reflective photoelectric switch photocell E3Z-R61 NPN output Reflex Light Barrier 2.5m detect distance

https://aliexpress.ru/item/4000725631263.html?spm=a2g0s.12269583.0.0.7c5865fcqwORDu&sku_id=10000006378321382

Arduino nano https://aliexpress.ru/item/32341832857.html?spm=a2g0s.9042311.0.0.264d33edHslPYF&_ga=2.67126161.1801017259.1617779444-381528868.1616234156

Батарея 12V https://aliexpress.ru/item/1005001494253442.html?spm=a2g0s.9042311.0.0.264d33ed4xgVdW&_ga=2.67126161.1801017259.1617779444-381528868.1616234156&sku_id=12000016338274809

DC-DC понижающий https://aliexpress.ru/item/4001330940760.html?spm=a2g0s.9042311.0.0.264d33ed4xgVdW&_ga=2.67126161.1801017259.1617779444-381528868.1616234156

LED панель WS2812B RGB 8x32 https://aliexpress.ru/item/4001296811800.html?spm=a2g0s.9042311.0.0.264d33ed7NR1V5&_ga=2.109282181.1801017259.1617779444-381528868.1616234156

+ нужна макетная плата, на чем собрать, реле управляемое 12В, 2 кнопки, 3 резистора на 10к

### Принцип работы

Таймер стартует при первом прохождении линии сенсора и не может быть остановлен быстрее чем за 3 секунды. Финиш фиксируется так же при первом пересечении линии.

Кнопки используются для регулировки яркости LED панели. 

Пересечение линии дублируется красным диодом ниже двоеточия на панели. 

Если цвет двоеточия красный - таймер не запустится/не остановится, если зеленый, то таймер готов к запуску или остановке.

## Если вам пригодилась схема, подписывайтесь
https://www.instagram.com/alekssaff/

https://www.youtube.com/alekssaff

Прислать материальную благодарность можно сюда https://yoomoney.ru/to/41001532138726
